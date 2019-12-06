#pragma once
#include "stdafx.h"
#define GRB_ERROR_SERIES 600
#define NS(n)	GRB::Rule::Chain::N(n)
#define TS(n)	GRB::Rule::Chain::T(n)
#define ISNS(n)	GRB::Rule::Chain::isN(n)

namespace GRB
{
	Greibach greibach(
		NS('S'), // ��������� ������
		TS('$'), //��� �����      
		7,									  // ���������� ������
		Rule(
			NS('S'), 
			GRB_ERROR_SERIES + 0,    // �������� ��������� ���������
			4,                                
			Rule::Chain(7, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}')),
			Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S')),
			Rule::Chain(12, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}')),
			Rule::Chain(8, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S'))
		),
		Rule(
			NS('N'), 
			GRB_ERROR_SERIES + 1,    // ����������� � ��������
			14,                                
			Rule::Chain(5, TS('d'), TS('t'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(4, TS('p'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(4, TS('p'), TS('l'), TS(';'), NS('N')),
			Rule::Chain(4, TS('p'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(12, TS('c'), TS('('), NS('C'), TS(')'), TS('{'), NS('N'), TS('}'), TS('e'), TS('{'), NS('N'), TS('}'), NS('N')),
			Rule::Chain(8, TS('c'), TS('('), NS('C'), TS(')'), TS('{'), NS('N'), TS('}'), NS('N')),

			Rule::Chain(3, TS('p'), NS('E'), TS(';')),
			Rule::Chain(4, TS('d'), TS('t'), TS('i'), TS(';')),
			Rule::Chain(3, TS('p'), TS('i'), TS(';')),
			Rule::Chain(3, TS('p'), TS('l'), TS(';')),
			Rule::Chain(11, TS('c'), TS('('), NS('C'), TS(')'), TS('{'), NS('N'), TS('}'), TS('e'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(7, TS('c'), TS('('), NS('C'), TS(')'), TS('{'), NS('N'), TS('}'))
		),
		Rule(
			NS('E'), 
			GRB_ERROR_SERIES + 2,    // ������ � ���������
			12,                                 
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
			Rule::Chain(4, TS('b'), TS('('), NS('W'), TS(')')),
			Rule::Chain(4, TS('a'), TS('('), NS('W'), TS(')')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M')),
			Rule::Chain(5, TS('b'), TS('('), NS('W'), TS(')'), NS('M')),
			Rule::Chain(5, TS('a'), TS('('), NS('W'), TS(')'), NS('M'))
		),
		Rule(
			NS('F'),
			GRB_ERROR_SERIES + 3,    // ������ � ���������� �������
			2,                                 
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F'))
		),
		Rule(
			NS('W'), 
			GRB_ERROR_SERIES + 4,    // ������ � ���������� ���������� ������� 
			4,                                 
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
		),
		Rule(
			NS('M'), 
			GRB_ERROR_SERIES + 5,    // ��������
			2,								  //
			Rule::Chain(2, TS('v'), NS('E')),
			Rule::Chain(3, TS('v'), NS('E'), NS('M'))
		),
		Rule(
			NS('C'),
			GRB_ERROR_SERIES + 6,    // ��������
			5,								  //
			Rule::Chain(3, TS('i'), TS('o'), TS('i')),
			Rule::Chain(3, TS('i'), TS('o'), TS('l')),
			Rule::Chain(3, TS('l'), TS('o'), TS('i')),
			Rule::Chain(3, TS('l'), TS('o'), TS('l')),
			Rule::Chain(1, TS('i'))
		)

	);
}