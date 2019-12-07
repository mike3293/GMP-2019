#pragma once
#define ID_MAXSIZE		8			// ������������ ���������� �������� � ��������������
#define TI_MAXSIZE		4096		// ������������ ���������� ����� � ������� ���������������
#define TI_INT_DEFAULT	0x0000		// �������� �� ��������� ��� ���� integer
#define TI_STR_DEFAULT	0x00		// �������� �� ��������� ��� ���� string
#define TI_NULLIDX		0xffff		// ��� �������� ������� ���������������
#define TI_STR_MAXSIZE	255			// 

namespace IT			// ������� ���������������
{
	enum IDDATATYPE { INT = 1, STR = 2 };			// ���� ������ ���������������: integer, string
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4, OP = 5, LIB = 6 };	// ���� ���������������: ����������, �������, ��������, �������, ��������

	struct Entry	// ������ ������� ���������������
	{
		int			idxfirstLE;						// ������ ������ ������ � ������� ������
		unsigned char	idRegion[TI_STR_MAXSIZE];	// �������� ��� ������� ���������
		unsigned char	id[ID_MAXSIZE];				// �������������� (������������� ��������� �� ID_MAXSIZE)
		IDDATATYPE	idDataType;						// ��� ������
		IDTYPE		idType;							// ��� ��������������
		union
		{
			unsigned short vint;								// �������� integer
			struct
			{
				unsigned char len;						// ���������� �������� � string
				unsigned char str[TI_STR_MAXSIZE - 1];	// ������� string
			} vstr;				// �������� string
		} value;		// �������� ��������������
	};

	struct IdTable				// ��������� ������� ���������������
	{
		int maxsize;			// ������� ������� ��������������� < TI_MAXSIZE
		int size;				// ������� ������ ������� ��������������� < maxsize
		Entry* table;			// ������ ����� ������� ���������������
	};

	IdTable Create(				// ������� ������� ���������������
		int size				// ������� ������� ��������������� < TI_MAXSIZE
	);

	void Add(				// �������� ������ � ������� ���������������
		IdTable& idtable,	// ��������� ������� ���������������
		Entry entry			// ������ ������� ���������������
	);

	Entry GetEntry(			// �������� ������ ������� ���������������
		IdTable& idtable,	// ��������� ������� ���������������
		int n				// ����� ���������� ������
	);

	int IsIDRegion(				// �������: ����� ������ (���� ����), TI_NULLIDX (���� ���)
		IdTable& idtable,	// ��������� ������� ���������������
		unsigned char id[ID_MAXSIZE]	// �������������
	);

	void Delete(IdTable& idtable);	// ������� ������� ������ (���������� ������)
	void showTable(IdTable& idtable);
};