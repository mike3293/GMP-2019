#pragma once
#define ID_MAXSIZE		8			// максимальное количество символов в идентификаторе
#define TI_MAXSIZE		4096		// максимальное количество строк в таблице идентификаторов
#define TI_INT_DEFAULT	0x0000		// значение по умолчанию дл€ типа integer
#define TI_STR_DEFAULT	0x00		// значение по умолчанию дл€ типа string
#define TI_NULLIDX		0xffff		// нет элемента таблицы идентификаторов
#define TI_STR_MAXSIZE	255			// 

namespace IT			// таблица идентификаторов
{
	enum IDDATATYPE { USHORT = 1, STR = 2 };			// типы данных идентификаторов: integer, string
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4, OP = 5, LIB = 6 };	// типы идентификаторов: переменна€, функци€, параметр, литерал, оператор

	struct Entry	// строка таблицы идентификаторов
	{
		int			idxfirstLE;						// индекс первой строки в таблице лексем
		unsigned char	idRegion[TI_STR_MAXSIZE];	// префиксы дл€ области видимости
		unsigned char	id[ID_MAXSIZE];				// индентификатор (автоматически усекаетс€ до ID_MAXSIZE)
		IDDATATYPE	idDataType;						// тип данных
		IDTYPE		idType;							// тип идентификатора
		union
		{
			unsigned short vushort;								// значение integer
			struct
			{
				unsigned char len;						// количество символов в string
				unsigned char str[TI_STR_MAXSIZE - 1];	// символы string
			} vstr;				// значение string
		} value;		// значение идентификатора
	};

	struct IdTable				// экземпл€р таблицы идентификаторов
	{
		int maxSize;			// емкость таблицы идентификаторов < TI_MAXSIZE
		int size;				// текущий размер таблицы идентификаторов < maxSize
		Entry* table;			// массив строк таблицы идентификаторов
	};

	IdTable Create(				// создать таблицу идентификаторов
		int size				// емкость таблицы идентификаторов < TI_MAXSIZE
	);

	void Add(				// добавить строку в таблицу идентификаторов
		IdTable& idTable,	// экземпл€р таблицы идентификаторов
		Entry entry			// строка таблицы идентификаторов
	);

	Entry GetEntry(			// получить строку таблицы идентификаторов
		IdTable& idTable,	// экземпл€р таблицы идентификаторов
		int n				// номер получаемой строки
	);

	int IsIDRegion(				// возврат: номер строки (если есть), TI_NULLIDX (если нет)
		IdTable& idTable,	// экземпл€р таблицы идентификаторов
		unsigned char id[ID_MAXSIZE]	// идентификатор
	);

	void Delete(IdTable& idTable);	// удалить таблицу лексем (освободить пам€ть)
	void showTable(IdTable& idTable);
};