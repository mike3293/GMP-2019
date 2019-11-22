#include "stdafx.h"

namespace IT
{
	IdTable Create(int size)
	{
		if (size > TI_MAXSIZE) 
			throw ERROR_THROW(5);
		IdTable Table;
		Table.maxsize = size;
		Table.size = 0;
		Table.table = new Entry[size];
		return Table;
	}

	void Add(IdTable& idtable, Entry entry)
	{
		if (idtable.size > idtable.maxsize) throw ERROR_THROW(6);
		idtable.table[idtable.size++] = entry;
	}

	Entry GetEntry(IdTable& idtable, int n)
	{
		return idtable.table[n];
	}

	int IsIDRegion(IdTable& idtable, unsigned char id[ID_MAXSIZE])
	{
		for (int i = 0; i < idtable.size; i++)
		{
			if (_mbscmp(idtable.table[i].idRegion, id) == 0) 
				return i; 
		}

		return TI_NULLIDX;
	}

	void Delete(IdTable& idtable)
	{
		idtable.maxsize = NULL;
		idtable.size = NULL;
		delete[] idtable.table;
	}

	void showTable(IdTable& idtable)
	{
		int i, numberOP = 0;
		std::cout << "№ > Идентификатор > Область видимости > Тип данных > Тип идентификатора > Индекс в ТЛ > Значение\n\n";
		for (i = 0; i < idtable.size; i++)
		{
			std::cout << i << " > ";
			std::cout << idtable.table[i].id << " > ";
			std::cout << idtable.table[i].idRegion << " > ";
			switch (idtable.table[i].iddatatype)
			{
			case INT:
				if (!(idtable.table[i].idtype == OP))
					std::cout << "integer" << " > "; break;
			case STR:
				if (!(idtable.table[i].idtype == OP))
					std::cout << "string" << " > "; break;
			default: std::cout << "unknown" << " > "; break;
			}
			switch (idtable.table[i].idtype)
			{
			case V: std::cout << "переменная > "; break;
			case F: std::cout << "функция > "; break;
			case P: std::cout << "параметр > "; break;
			case L: std::cout << "литерал > "; break;
			case OP: 
				std::cout << "оператор > ";
				numberOP++;
				break;
			default: std::cout << "unknown > "; break;
			}
			std::cout << idtable.table[i].idxfirstLE << " > ";
			if (idtable.table[i].iddatatype == INT && (idtable.table[i].idtype == V || idtable.table[i].idtype == L))
				std::cout << std::left << idtable.table[i].value.vint;
			else if (idtable.table[i].iddatatype == STR && (idtable.table[i].idtype == V || idtable.table[i].idtype == L))
				std::cout << "[" << (int)idtable.table[i].value.vstr.len << "]\"" << idtable.table[i].value.vstr.str << "\"";
			else
				std::cout << "нет значения";
			std::cout << std::endl;
		}
		std::cout << std::setfill('*') << std::setw(40) << '*' <<std::setfill(' ')<<std::setw(1) << std::endl;
		std::cout << "Количество идентификаторов: " << i - numberOP << std::endl;
	}
}