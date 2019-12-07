#include "stdafx.h"


using namespace std;
namespace Gen
{
	void CodeGeneration(Lex::LEX& lex, wchar_t outfile[])
	{
		std::ofstream out(outfile);									//открывает файл для записи
		if (!out.is_open())											//проверка на открытие файла иначе ошибка
			throw ERROR_THROW(110);

		out << ".586\n\t.model flat, stdcall\n\tincludelib libucrt.lib\n\tincludelib kernel32.lib\n\tincludelib ../Debug/Standard_Library.lib\n\tExitProcess PROTO :DWORD\n\n";
		out << "\toutc PROTO: DWORD\n\toutd PROTO: DWORD\n\tstrl PROTO: DWORD\n\tpower PROTO: DWORD, :DWORD\n";
		out << "\n.stack 4096\n";

		out << ".const\n";
		for (int i = 0; i < lex.idtable.size; i++)
		{
			if (lex.idtable.table[i].idtype == IT::L)
			{
				out << "\t" << lex.idtable.table[i].id;
				if (lex.idtable.table[i].idDataType == IT::STR)
				{
					out << " BYTE " << lex.idtable.table[i].value.vstr.str << ", 0\n";
				}
				if (lex.idtable.table[i].idDataType == IT::INT)
				{
					out << " WORD " << lex.idtable.table[i].value.vint << endl;
				}
			}
		}

		out << ".data\n";
		for (int i = 0; i < lex.lextable.size; i++)
		{
			if (lex.lextable.table[i].lexema == LEX_VAR)
			{
				out << "\t" << lex.idtable.table[lex.lextable.table[i + 2].idxTI].id;
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

		out.close();
	}
}