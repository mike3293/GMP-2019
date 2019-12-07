#include "stdafx.h"


using namespace std;
namespace Gen
{
	void CodeGeneration(Lex::LEX& lex, wchar_t outfile[])
	{
		std::ofstream out(outfile);									//открывает файл для записи
		if (!out.is_open())											//проверка на открытие файла иначе ошибка
			throw ERROR_THROW(110);

		out << ".586\n\t.model flat, stdcall\n\tincludelib libucrt.lib\n\tincludelib kernel32.lib";
		out << "\n\tincludelib ../Debug/StaticLib.lib\n\n\tEXTERN printS :PROC\n\tEXTERN printN :PROC";
		//out << "\tprint PROTO: DWORD\n\tcompare PROTO : DWORD, : DWORD\n\tpow PROTO : DWORD, : DWORD\n";
		out << "\n\tExitProcess PROTO :DWORD\n";
		out << "\n.stack 4096\n";

		out << "\n.const\n";
		for (int i = 0; i < lex.idtable.size; i++)
		{
			if (lex.idtable.table[i].idType == IT::L)
			{
				out << "\t" << lex.idtable.table[i].id;
				if (lex.idtable.table[i].idDataType == IT::STR)
				{
					out << " BYTE '" << lex.idtable.table[i].value.vstr.str << "', 0\n";
				}
				if (lex.idtable.table[i].idDataType == IT::INT)
				{
					out << " WORD " << lex.idtable.table[i].value.vint << endl;
				}
			}
		}

		out << "\n.data\n";
		for (int i = 0; i < lex.lextable.size; i++)
		{
			if (lex.lextable.table[i].lexema == LEX_VAR)
			{
				out << "\t" << lex.idtable.table[lex.lextable.table[i + 2].idxTI].idRegion;
				if (lex.idtable.table[lex.lextable.table[i + 2].idxTI].idDataType == IT::STR)
				{
					out << " DWORD ?\n";
				}
				if (lex.idtable.table[lex.lextable.table[i + 2].idxTI].idDataType == IT::INT)
				{
					out << " DWORD ?\n";
				}
				i += 3;
			}
		}

		stack<string> stk;
		int num_of_points = 0,
			num_of_ret = 0,
			num_of_ends = 0;
		string strret = "",
			func_name = "";					// имя локальной функции
		bool flag_func = false,					// внутри локальной функции?
			flag_ret = false,					// был ret?
			flag_body = false,					// внутри главной функции?
			flag_if = false,					// внутри if?
			flag_then = false,					// внутри then?
			flag_else = false;					// внутри then/else?
		out << "\n.code\n";
		for (int i = 0; i < lex.lextable.size; i++)
		{
			switch (lex.lextable.table[i].lexema)
			{
			case LEX_FUNCTION:
			{
				out << "\t" << /*(func_name =*/ lex.idtable.table[lex.lextable.table[++i].idxTI].id/*)*/ << " PROC ";
				i += 2;
				for (;lex.lextable.table[i].lexema != LEX_RIGHTTHESIS; i++)
				{
					if (lex.lextable.table[i].lexema == LEX_ID || lex.lextable.table[i].lexema == LEX_LITERAL)
					{
						if (lex.idtable.table[lex.lextable.table[i].idxTI].idType == IT::P)
						{
							out << lex.idtable.table[lex.lextable.table[i].idxTI].idRegion << " : ";
							if (lex.idtable.table[lex.lextable.table[i].idxTI].idDataType == IT::INT)
							{
								out << "WORD";
							}
							else		// STR
							{
								out << "DWORD";
							}
						}
						if (lex.lextable.table[i + 1].lexema == LEX_COMMA)
						{
							out << ", ";
							i++;
						}
					}
				}
				flag_func = true;
				out << endl;
				break;
			}
			case LEX_MAIN:
			{
				flag_body = true;
				out << "\n\tmain PROC\n";
				break;
			}
			case LEX_PRINT:
			{
				if (lex.idtable.table[lex.lextable.table[i + 2].idxTI].idDataType == IT::INT)
				{
					out << "\t\tpush " << lex.idtable.table[lex.lextable.table[i + 2].idxTI].id << "\n\t\tcall printN\n";
				}
				else
				{
					out << "\t\tpush offset " << lex.idtable.table[lex.lextable.table[i + 2].idxTI].id << "\n\t\tcall printS\n";
				}
				break;
			}
			}
		}
		out << "\n\t\tpush 0\n\t\tcall ExitProcess\n\tmain ENDP\nend main";

		out.close();
	}
}