#include "stdafx.h"
namespace Error
{
	/*����� ������   0-99		 ��������� ������ ����
					 100-109	 ������ ����������
					 110-119	 ������ �������� � ������ ������
	*/
	ERROR errors[ERROR_MAX_ENTRY] =  //������� ������
	{
		ERROR_ENTRY(0,"SYS: ������������ ��� ������"), //��� ������ ��� ��������� 0 - ERROR_MAX_ENTRY
		ERROR_ENTRY(1,"SYS: ��������� ����"),
		ERROR_ENTRY_NODEF(2),ERROR_ENTRY_NODEF(3),ERROR_ENTRY_NODEF(4),
		ERROR_ENTRY_NODEF5(5),ERROR_ENTRY_NODEF50(10), ERROR_ENTRY_NODEF10(60),ERROR_ENTRY_NODEF10(70),
		ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100,"SYS: �������� -in ������ ���� �����"),
		ERROR_ENTRY_NODEF(101),ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104,"SYS: ��������� ������ �������� ���������"),
		ERROR_ENTRY_NODEF5(105),
		ERROR_ENTRY(110,"SYS: ������ ��� �������� ����� � �������� ����� (-in)"),
		ERROR_ENTRY(111,"SYS: ������������ ������ � �������� ����� (-in)"),
		ERROR_ENTRY(112,"SYS: ������ ��� �������� ����� ��������� (-log)"),
		ERROR_ENTRY(113,"SYS: ������ ��� �������� ��������� ����� (-out)"),
		ERROR_ENTRY_NODEF(114), ERROR_ENTRY_NODEF5(115),
		ERROR_ENTRY_NODEF10(120),ERROR_ENTRY_NODEF10(130),ERROR_ENTRY_NODEF10(140),ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160),ERROR_ENTRY_NODEF10(170),ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY(200,"LEX: ������� ����������"), 
		ERROR_ENTRY(201,"LEX: ������ ������������ �������"),
		ERROR_ENTRY(202,"LEX: ����� �������������� ������ 8"),
		ERROR_ENTRY(203,"LEX: ������������� �� ��������"), 
		ERROR_ENTRY(204,"LEX: ������, ������������ ������ ������� ��������������� 4096"),
		ERROR_ENTRY(205,"LEX: ������� ��������������� �����������"),
		ERROR_ENTRY(206,"LEX: ������, ������������ ������ ������� ������ 4096"),
		ERROR_ENTRY(207,"LEX: ������� ������ �����������"),
		ERROR_ENTRY(208,"LEX: ������������ �������� ���� ushort 65535"), 
		ERROR_ENTRY_NODEF(209), ERROR_ENTRY_NODEF10(210), ERROR_ENTRY_NODEF10(220),
		ERROR_ENTRY_NODEF10(230), ERROR_ENTRY_NODEF10(240),ERROR_ENTRY_NODEF50(250), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400),
		ERROR_ENTRY(500,"SEM: ��� ����� ����� main"), 
		ERROR_ENTRY(501,"SEM: ����� ����� ����� ����� main"), 
		ERROR_ENTRY(502,"SEM: ������������ �������� �� ������������� ���� �������"), 
		ERROR_ENTRY(503,"SEM: ���������� ���������� ������� ������ �����������"), 
		ERROR_ENTRY(504,"SEM: ������������ ��������� �� ������������� �������"),
		ERROR_ENTRY(505,"SEM: �� ������������ ���������� ������������ ����������"), 
		ERROR_ENTRY(506,"SEM: ������ � ���������� ������� pow()"), 
		ERROR_ENTRY(507,"SEM: ������ � ���������� ������� compare()"), 
		ERROR_ENTRY(508,"SEM: ������� ��������� ��������� �� ���� ushort"), 
		ERROR_ENTRY(509,"SEM: ������ � ��������� ������� print()"), 
		ERROR_ENTRY(510,"SEM: ������ � ����������� ����������"),
		ERROR_ENTRY_NODEF(511),ERROR_ENTRY_NODEF(512),ERROR_ENTRY_NODEF(513),ERROR_ENTRY_NODEF(514
		), ERROR_ENTRY_NODEF5(515), ERROR_ENTRY_NODEF10(520),
		ERROR_ENTRY_NODEF10(530), ERROR_ENTRY_NODEF10(540), ERROR_ENTRY_NODEF50(550),
		ERROR_ENTRY(600,"SYN: �������� ��������� ���������"),
		ERROR_ENTRY(601,"SYN: ��������� ����������� � �������"),
		ERROR_ENTRY(602,"SYN: ������ � ���������"),
		ERROR_ENTRY(603,"SYN: ������ � ���������� �������"),
		ERROR_ENTRY(604,"SYN: ������ � ���������� ���������� �������"),
		ERROR_ENTRY(605,"SYN: ������ � �������"),
		ERROR_ENTRY_NODEF(606),ERROR_ENTRY_NODEF(607),ERROR_ENTRY_NODEF(608),ERROR_ENTRY_NODEF(609),
		ERROR_ENTRY_NODEF10(610),ERROR_ENTRY_NODEF10(620),ERROR_ENTRY_NODEF10(630),ERROR_ENTRY_NODEF10(640),
		ERROR_ENTRY_NODEF50(650), ERROR_ENTRY_NODEF100(700),ERROR_ENTRY_NODEF100(800),ERROR_ENTRY_NODEF100(900)
	};
	ERROR geterror(int id)
	{
		ERROR error_info ;											// �������� ��������� ������� ���� ����� �������
		if (id > 0 && id < ERROR_MAX_ENTRY)							// ����������� ���������
		{ 
			error_info.id = errors[id].id;
			strcpy_s(error_info.message, errors[id].message);
			error_info.inext.col = -1;
			error_info.inext.line = -1;
		}
		else
		{
			error_info.id = errors[0].id;
			strcpy_s(error_info.message, errors[0].message);
		}
		return error_info;
	}

	ERROR geterrorin(int id, int line, int col)
	{
		ERROR error_info;												//	�������� ��������� ������� ���� ����� �������
		if (id > 0 && id < ERROR_MAX_ENTRY)						// ��������� ���������
		{
			error_info.id = errors[id].id;
			error_info.inext.col = col;
			error_info.inext.line = line;
			strcpy_s(error_info.message, errors[id].message);
			return error_info;
		}
		else
		{
			error_info.id = 0; // ������
			error_info.inext.col = -1;
			error_info.inext.line = -1;
			strcpy_s(error_info.message, errors[0].message);
			return error_info;
		}
	}
	;
};