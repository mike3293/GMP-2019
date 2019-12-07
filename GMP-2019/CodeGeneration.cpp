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
		out << "\n\tincludelib ../Debug/StaticLib.lib\n\n\tEXTERN printS :PROC\n\tEXTERN printN :PROC\n\tEXTERN raise :PROC";
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
					out << " DWORD 0\n";
				}
				if (lex.idtable.table[lex.lextable.table[i + 2].idxTI].idDataType == IT::INT)
				{
					out << " WORD 0\n";
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
		out << "\n.code";
		for (int i = 0; i < lex.lextable.size; i++)
		{
			switch (lex.lextable.table[i].lexema)
			{
			case LEX_FUNCTION:
			{
				func_name = (const char*)lex.idtable.table[lex.lextable.table[++i].idxTI].idRegion;
				out << "\t" << func_name << " PROC ";
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
			case LEX_EQUAL: //TODO
			{
				int result_position = i - 1;
				while (lex.lextable.table[i].lexema != LEX_SEMICOLON)
				{
					switch (lex.lextable.table[i].lexema)
					{
					case LEX_ID:
					{
						out << "\tpush " << lex.idtable.table[lex.lextable.table[i].idxTI].idRegion << endl;
						stk.push((const char*)lex.idtable.table[lex.lextable.table[i].idxTI].idRegion);
						break;
					}
					case LEX_LITERAL:
					{
						if (lex.idtable.table[lex.lextable.table[i].idxTI].idDataType == IT::INT)
						{
							out << "\tpush " << lex.idtable.table[lex.lextable.table[i].idxTI].id << endl;
							stk.push((const char*)lex.idtable.table[lex.lextable.table[i].idxTI].id);
						}
						if (lex.idtable.table[lex.lextable.table[i].idxTI].idDataType == IT::STR)
						{
							out << "\tpush offset " << lex.idtable.table[lex.lextable.table[i].idxTI].id << endl;
							stk.push("offset " + (string)(const char*)lex.idtable.table[lex.lextable.table[i].idxTI].id);
						}
						break;
					}
					}
					i++;
				}
				out << "\tpop " << lex.idtable.table[lex.lextable.table[result_position].idxTI].idRegion << "\n";
				break;
			}
			case LEX_RETURN:
			{
				out << "\tpush ";
				i++;
				if (lex.idtable.table[lex.lextable.table[i].idxTI].idType == IT::L)
				{
					out << lex.idtable.table[lex.lextable.table[i++].idxTI].value.vint << endl;
				}
				else
				{
					out << lex.idtable.table[lex.lextable.table[i++].idxTI].idRegion << endl;
				}
				if (flag_func)
				{
					out << "\tjmp local" << num_of_ret << endl;
					flag_ret = true;
				}
				if (flag_body)
				{
					out << "\tjmp theend\n";
					flag_ret = true;
				}
				break;
			}
			case LEX_RIGHTBRACE:
			{
				if (flag_body && !flag_then && !flag_else && !flag_func)
				{
					if (flag_ret)
					{
						out << "theend:\n";
						flag_ret = false;
					}
					out << "\tcall ExitProcess\nmain ENDP\nend main";
				}
				if (flag_func)
				{
					if (flag_ret)
					{
						out << "local" << num_of_ret++ << ":\n";
						out << "\tpop ax\n\tret\n"; // string?
						flag_ret = false;
					}
					out << func_name << " ENDP\n\n";
					flag_func = false;
				}
				if (flag_then)
				{
					flag_then = false;
					if (flag_else)
					{
						out << "\tjmp e" << num_of_ends << endl;
						flag_else = false;
					}
					out << "m" << num_of_points++ << ":\n";
				}
				if (flag_else)
				{
					flag_else = false;
					out << "e" << num_of_ends++ << ":\n";
				}
				break;
			}
			case LEX_IF:
			{
				flag_if = true;
				break;
			}
			case LEX_LEFTTHESIS:
			{
				if (flag_if)
				{
					if (lex.lextable.table[i + 2].lexema == LEX_LOGICAL)
					{
						out << "\tmov ax, " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].idRegion << endl;
						out << "\tcmp ax, " << lex.idtable.table[lex.lextable.table[i + 3].idxTI].idRegion << endl;
						if ((string)(const char*)lex.idtable.table[lex.lextable.table[i + 2].idxTI].id == SEM_GREAT)
						{
							out << "\tjg m" << num_of_points << endl;
							out << "\tjl m" << num_of_points + 1 << endl;
							out << "\tje m" << num_of_points + 1 << endl;
						}
						else if ((string)(const char*)lex.idtable.table[lex.lextable.table[i + 2].idxTI].id == SEM_LESS)
						{
							out << "\tjl m" << num_of_points << endl;
							out << "\tjg m" << num_of_points + 1 << endl;
							out << "\tje m" << num_of_points + 1 << endl;
						}
						else if ((string)(const char*)lex.idtable.table[lex.lextable.table[i + 2].idxTI].id == SEM_EQUAL)
						{
							out << "\tje m" << num_of_points << endl;
							out << "\tjg m" << num_of_points + 1 << endl;
							out << "\tjl m" << num_of_points + 1 << endl;
						}
						else if ((string)(const char*)lex.idtable.table[lex.lextable.table[i + 2].idxTI].id == SEM_GREATEQUAL)
						{
							out << "\tje m" << num_of_points << endl;
							out << "\tjg m" << num_of_points << endl;
							out << "\tjl m" << num_of_points + 1 << endl;
						}
						else if ((string)(const char*)lex.idtable.table[lex.lextable.table[i + 2].idxTI].id == SEM_LESSEQUAL)
						{
							out << "\tje m" << num_of_points << endl;
							out << "\tjl m" << num_of_points << endl;
							out << "\tjg m" << num_of_points + 1<< endl;
						}
						int j = i;
						while (lex.lextable.table[j++].lexema != LEX_RIGHTBRACE)
						{
							while (lex.lextable.table[j].lexema == DIV)
								j++;
							if (lex.lextable.table[j + 2].lexema == LEX_ELSE)
							{
								flag_else = true;
								break;
							}
						}
					}
					flag_then = true;
					out << "m" << num_of_points++ << ":\n";
					flag_if = false;
					break;
				}
				break;
			}
			case LEX_ELSE:
			{
				flag_else = true;
				break;
			}
			case LEX_PRINT:
			{
				if (lex.idtable.table[lex.lextable.table[i + 2].idxTI].idDataType == IT::INT)
				{
					out << "\tpush " << lex.idtable.table[lex.lextable.table[i + 2].idxTI].idRegion << "\n\tcall printN\n";
				}
				else
				{
					out << "\tpush offset " << lex.idtable.table[lex.lextable.table[i + 2].idxTI].id << "\n\tcall printS\n";		// Only for literals
				}
				break;
			}
			}
		}
		//out << "\n\tpush 0\n\tcall ExitProcess\n\tmain ENDP\nend main";

		out.close();
	}
}