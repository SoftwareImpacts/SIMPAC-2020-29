#include "src/codegen/emit.h"
#include "src/codegen/indent.h"
#include "src/codegen/input_api.h"
#include "src/codegen/skeleton/skeleton.h"
#include "src/dfa/action.h"

namespace re2c
{

static void need               (OutputFile & o, uint32_t ind, bool & readCh, uint32_t n, bool bSetMarker);
static void emit_match         (OutputFile & o, uint32_t ind, bool & readCh, const State * const s);
static void emit_initial       (OutputFile & o, uint32_t ind, bool & readCh, const State * const s, const Initial & init, const std::set<label_t> & used_labels);
static void emit_save          (OutputFile & o, uint32_t ind, bool & readCh, const State * const s, uint32_t save);
static void emit_accept_binary (OutputFile & o, uint32_t ind, bool & readCh, const State * const s, const accept_t & accept, uint32_t l, uint32_t r);
static void emit_accept        (OutputFile & o, uint32_t ind, bool & readCh, const State * const s, const accept_t & accept);
static void emit_rule          (OutputFile & o, uint32_t ind, const State * const s, const RuleOp * const rule, const std::string & condName);
static void genYYFill          (OutputFile & o, uint32_t need);
static void genSetCondition    (OutputFile & o, uint32_t ind, const std::string & newcond);

void emit_action
	( const Action & action
	, OutputFile & o
	, uint32_t ind
	, bool & readCh
	, const State * const s
	, const std::string & condName
	, const std::set<label_t> & used_labels
	)
{
	switch (action.type)
	{
		case Action::MATCH:
			emit_match (o, ind, readCh, s);
			break;
		case Action::INITIAL:
			emit_initial (o, ind, readCh, s, * action.info.initial, used_labels);
			break;
		case Action::SAVE:
			emit_save (o, ind, readCh, s, action.info.save);
			break;
		case Action::MOVE:
			break;
		case Action::ACCEPT:
			emit_accept (o, ind, readCh, s, * action.info.accept);
			break;
		case Action::RULE:
			emit_rule (o, ind, s, action.info.rule, condName);
			break;
	}
}

void emit_match (OutputFile & o, uint32_t ind, bool & readCh, const State * const s)
{
	if (DFlag)
	{
		return;
	}

	const bool read_ahead = s
		&& s->next
		&& s->next->action.type != Action::RULE;
	if (s->link)
	{
		o << input_api.stmt_skip (ind);
	}
	else if (!read_ahead)
	{
		/* do not read next char if match */
		o << input_api.stmt_skip (ind);
		readCh = true;
	}
	else
	{
		o << input_api.stmt_skip_peek (ind);
		readCh = false;
	}

	if (s->link)
	{
		need(o, ind, readCh, s->depth, false);
	}
}

void emit_initial (OutputFile & o, uint32_t ind, bool & readCh, const State * const s, const Initial & initial, const std::set<label_t> & used_labels)
{
	if (DFlag)
	{
		return;
	}

	if (used_labels.count(s->label))
	{
		if (s->link)
		{
			o << input_api.stmt_skip (ind);
		}
		else
		{
			o << input_api.stmt_skip_peek (ind);
		}
	}

	if (used_labels.count(initial.label))
	{
		o << labelPrefix << initial.label << ":\n";
	}
	else if (initial.label == label_counter_t::FIRST)
	{
		o << "\n";
	}

	if (dFlag)
	{
		o << indent(ind) << mapCodeName["YYDEBUG"] << "(" << initial.label << ", *" << mapCodeName["YYCURSOR"] << ");" << "\n";
	}

	if (s->link)
	{
		need(o, ind, readCh, s->depth, initial.setMarker && bUsedYYMarker);
	}
	else
	{
		if (initial.setMarker && bUsedYYMarker)
		{
			o << input_api.stmt_backup (ind);
		}
		readCh = false;
	}
}

void emit_save (OutputFile & o, uint32_t ind, bool & readCh, const State * const s, uint32_t save)
{
	if (DFlag)
	{
		return;
	}

	o.insert_yyaccept_selector (ind, save);

	if (s->link)
	{
		if (bUsedYYMarker)
		{
			o << input_api.stmt_skip_backup (ind);
		}
		need(o, ind, readCh, s->depth, false);
	}
	else
	{
		if (bUsedYYMarker)
		{
			o << input_api.stmt_skip_backup_peek (ind);
		}
		else
		{
			o << input_api.stmt_skip_peek (ind);
		}
		readCh = false;
	}
}

void emit_accept_binary (OutputFile & o, uint32_t ind, bool & readCh, const State * const s, const accept_t & accept, uint32_t l, uint32_t r)
{
	if (l < r)
	{
		const uint32_t m = (l + r) >> 1;
		o << indent(ind) << "if (" << mapCodeName["yyaccept"] << (r == l+1 ? " == " : " <= ") << m << ") {\n";
		emit_accept_binary (o, ++ind, readCh, s, accept, l, m);
		o << indent(--ind) << "} else {\n";
		emit_accept_binary (o, ++ind, readCh, s, accept, m + 1, r);
		o << indent(--ind) << "}\n";
	}
	else
	{
		genGoTo(o, ind, s, accept.find(l)->second, readCh);
	}
}

void emit_accept (OutputFile & o, uint32_t ind, bool & readCh, const State * const s, const accept_t & accept)
{
	if (accept.size() > 0)
	{
		bUsedYYMarker = true;
		if (!DFlag)
		{
			o << input_api.stmt_restore (ind);
		}

		if (readCh) // shouldn't be necessary, but might become at some point
		{
			o << input_api.stmt_peek (ind);
			readCh = false;
		}

		if (accept.size() > 1)
		{
			o.set_used_yyaccept ();

			if (gFlag && accept.size() >= cGotoThreshold)
			{
				o << indent(ind++) << "{\n";
				o << indent(ind++) << "static void *" << mapCodeName["yytarget"] << "[" << accept.size() << "] = {\n";
				for (accept_t::const_iterator it = accept.begin(); it != accept.end(); ++it)
				{
					o << indent(ind) << "&&" << labelPrefix << it->second->label << ",\n";
				}
				o << indent(--ind) << "};\n";
				o << indent(ind) << "goto *" << mapCodeName["yytarget"] << "[" << mapCodeName["yyaccept"] << "];\n";
				o << indent(--ind) << "}\n";
			}
			else if (sFlag || (accept.size() == 2 && !DFlag))
			{
				emit_accept_binary (o, ind, readCh, s, accept, 0, accept.size() - 1);
			}
			else if (DFlag)
			{
				for (accept_t::const_iterator it = accept.begin(); it != accept.end(); ++it)
				{
					o << s->label << " -> " << it->second->label;
					o << " [label=\"yyaccept=" << it->first << "\"]\n";
				}
			}
			else
			{
				o << indent(ind) << "switch (" << mapCodeName["yyaccept"] << ") {\n";

				accept_t::const_iterator it = accept.begin(), end = accept.end();
		
				while (it != end)
				{
					accept_t::const_iterator tmp = it;

					if (++it == end)
					{
						o << indent(ind) << "default:\t";
					}
					else
					{
						o << indent(ind) << "case " << tmp->first << ": \t";
					}

					genGoTo(o, 0, s, tmp->second, readCh);
				}
			
				o << indent(ind) << "}\n";
			}
		}
		else
		{
			// no need to write if statement here since there is only case 0.
			genGoTo(o, ind, s, accept.find(0)->second, readCh);
		}
	}
}

void emit_rule (OutputFile & o, uint32_t ind, const State * const s, const RuleOp * const rule, const std::string & condName)
{
	if (DFlag)
	{
		o << s->label << " [label=\"" << rule->code->source << ":" << rule->code->line << "\"]\n";
		return;
	}

	uint32_t back = rule->ctx->fixedLength();
	if (back != 0u && !DFlag)
	{
		o << input_api.stmt_restorectx (ind);
	}

	if (rule->code->newcond.length() && condName != rule->code->newcond)
	{
		genSetCondition(o, ind, rule->code->newcond);
	}

	if (!yySetupRule.empty() && !rule->code->autogen)
	{
		o << indent(ind) << yySetupRule << "\n";
	}

	o.write_line_info (rule->code->line, rule->code->source.c_str ());
	o << indent(ind);
	if (flag_skeleton)
	{
		o << "{ if (cursor == &data[result[i].endpos] && result[i].rule == " << rule->accept << ") ";
		o << "{ cursor = &data[result[i].startpos]; continue; }";
		o << " else ";
		o << "{ printf (\"error: %lu/%u, %u/%u, '%s'\\n\", cursor - data, result[i].endpos, result[i].rule, "
			<< rule->accept
			<< ", &data[result[i].startpos]); return 1; } }";
	}
	else if (rule->code->autogen)
	{
		o << replaceParam(condGoto, condGotoParam, condPrefix + rule->code->newcond);
	}
	else
	{
		o << rule->code->text;
	}
	o << "\n";
	o.insert_line_info ();
}

void need (OutputFile & o, uint32_t ind, bool & readCh, uint32_t n, bool bSetMarker)
{
	if (DFlag)
	{
		return;
	}

	uint32_t fillIndex = last_fill_index;

	if (fFlag)
	{
		last_fill_index++;
		if (bUseYYSetStateParam)
		{
			o << indent(ind) << mapCodeName["YYSETSTATE"] << "(" << fillIndex << ");\n";
		}
		else
		{
			o << indent(ind) << replaceParam(mapCodeName["YYSETSTATE"], yySetStateParam, fillIndex) << "\n";
		}
	}

	if (bUseYYFill && n > 0)
	{
		o << indent(ind);
		if (n == 1)
		{
			if (bUseYYFillCheck)
			{
				o << "if (" << input_api.expr_lessthan_one () << ") ";
			}
			genYYFill(o, n);
		}
		else
		{
			if (bUseYYFillCheck)
			{
				o << "if (" << input_api.expr_lessthan (n) << ") ";
			}
			genYYFill(o, n);
		}
	}

	if (fFlag)
	{
		o << mapCodeName["yyFillLabel"] << fillIndex << ":\n";
	}

	if (n > 0)
	{
		if (bSetMarker)
		{
			o << input_api.stmt_backup_peek (ind);
		}
		else
		{
			o << input_api.stmt_peek (ind);
		}
		readCh = false;
	}
}

void genYYFill(OutputFile & o, uint32_t need)
{
	if (bUseYYFillParam)
	{
		o << mapCodeName["YYFILL"];
		if (!bUseYYFillNaked)
		{
			o << "(" << need << ");";
		}
		o << "\n";
	}
	else
	{
		o << replaceParam(mapCodeName["YYFILL"], yyFillLength, need);
		if (!bUseYYFillNaked)
		{
			o << ";";
		}
		o << "\n";
	}
}

void genSetCondition(OutputFile & o, uint32_t ind, const std::string& newcond)
{
	if (bUseYYSetConditionParam)
	{
		o << indent(ind) << mapCodeName["YYSETCONDITION"] << "(" << condEnumPrefix << newcond << ");\n";
	}
	else
	{
		o << indent(ind) << replaceParam(mapCodeName["YYSETCONDITION"], yySetConditionParam, condEnumPrefix + newcond) << "\n";
	}
}

} // namespace re2c