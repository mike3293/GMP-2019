#include "stdafx.h"

namespace IT
{
	IdTable Create(int size)
	{
		if (size > TI_MAXSIZE) 
			throw ERROR_THROW(204);
		IdTable Table;
		Table.maxSize = size;
		Table.size = 0;
		Table.table = new Entry[size];
		return Table;
	}

	void Add(IdTable& idTable, Entry entry)
	{
		if (idTable.size > idTable.maxSize) throw ERROR_THROW(205);
		idTable.table[idTable.size++] = entry;
	}

	Entry GetEntry(IdTable& idTable, int n)
	{
		return idTable.table[n];
	}

	int IsIDRegion(IdTable& idTable, unsigned char id[ID_MAXSIZE])
	{
		for (int i = 0; i < idTable.size; i++)
		{
			if (_mbscmp(idTable.table[i].idRegion, id) == 0) 
				return i; 
		}

		return TI_NULLIDX;
	}

	void Delete(IdTable& idTable)
	{
		idTable.maxSize = NULL;
		idTable.size = NULL;
		delete[] idTable.table;
	}

	void showTable(IdTable& idTable)
	{
		int i, numberOP = 0;
		std::cout << "№ > Идентификатор > Область видимости > Тип данных > Тип идентификатора > Индекс в ТЛ > Значение\n\n";
		for (i = 0; i < idTable.size; i++)
		{
			std::cout << i << " > ";
			std::cout << idTable.table[i].id << " > ";
			std::cout << idTable.table[i].idRegion << " > ";
			switch (idTable.table[i].idDataType)
			{
			case USHORT:
				if (!(idTable.table[i].idType == OP))
					std::cout << "integer" << " > "; break;
			case STR:
				if (!(idTable.table[i].idType == OP))
					std::cout << "string" << " > "; break;
			default: std::cout << "unknown" << " > "; break;
			}
			switch (idTable.table[i].idType)
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
			std::cout << idTable.table[i].idxfirstLE << " > ";
			if (idTable.table[i].idDataType == USHORT && (idTable.table[i].idType == V || idTable.table[i].idType == L))
				std::cout << std::left << idTable.table[i].value.vushort;
			else if (idTable.table[i].idDataType == STR && (idTable.table[i].idType == V || idTable.table[i].idType == L))
				std::cout << "[" << (int)idTable.table[i].value.vstr.len << "]\"" << idTable.table[i].value.vstr.str << "\"";
			else
				std::cout << "нет значения";
			std::cout << std::endl;
		}
		std::cout << std::setfill('*') << std::setw(40) << '*' <<std::setfill(' ')<<std::setw(1) << std::endl;
		std::cout << "Количество идентификаторов: " << i - numberOP << std::endl;
	}
}