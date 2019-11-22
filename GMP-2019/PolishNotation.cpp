#include "stdafx.h"
#include <queue>

using namespace std;
bool PolishNotation(int i, Lex::LEX& lex)
{
	stack<LT::Entry> stack;									
	
	queue<LT::Entry> queue;	

	int lineNum = lex.lextable.table[i].sn;
	LT::Entry temp;			// лексема дл€ подстановки
	temp.idxTI = INT_MIN;
	temp.lexema = '#';
	temp.sn = lineNum;

	LT::Entry funcParm;			// лексема дл€ вызова функции
	funcParm.idxTI = INT_MIN;
	funcParm.lexema = '@';
	funcParm.sn = lineNum;
	int countLex = 0;															// количество преобразованных лексем
	int countParm = 0;															// количество параметров функции
	int posLex = i;																// запоминаем номер лексемы перед преобразованием
	bool findFunc = false;														// флаг дл€ функции
	bool findComma = false;														// флаг дл€ зап€той (кол-во параметров +2 сразу)
	char* buf = new char[2];													// буфер дл€ countParm в строковом представлении
	for (i; lex.lextable.table[i].lexema != LEX_SEMICOLON; i++, countLex++)
	{
		switch (lex.lextable.table[i].lexema)
		{
		case LEX_ID:			
		{
			if (lex.idtable.table[lex.lextable.table[i].idxTI].idtype == IT::F)
				findFunc = true;
			queue.push(lex.lextable.table[i]);
			continue;
		}
		case LEX_LITERAL:				
		{
			queue.push(lex.lextable.table[i]);										
			continue;
		}
		case LEX_LEFTTHESIS:	
		{
			stack.push(lex.lextable.table[i]);										// помещаем в стек
			continue;
		}
		case LEX_RIGHTTHESIS:				
		{
			if (findFunc)															// если это вызов функции, то лексемы () замен€ютс€ на @ и кол-во параметров
			{
				if (findComma)
				{
					countParm++;
				}
				lex.lextable.table[i] = funcParm;
				queue.push(lex.lextable.table[i]);									// добавл€ем в очередь лексему вызова функции
				_itoa_s(countParm, buf, 2, 10);										// преобразование числа countParm в строку
				stack.top().lexema = buf[0];
				stack.top().idxTI = INT_MIN;
				stack.top().sn = lineNum;						// заполн€ем лексему, указывающую количество параметров функции
				queue.push(stack.top());											// добавл€ем в очередь эту лексему
				findFunc = false;
			}
			else {
				while (stack.top().lexema != LEX_LEFTTHESIS)						// пока не встретим (
				{
					queue.push(stack.top());										// выталкиваем со стека в очередь
					stack.pop();

					if (stack.empty())
						return false;
				}
			}
			stack.pop();															// уничтожаем ( или лексему, указывающую количество параметров функции
			continue;
		}
		case LEX_OPERATOR:															// если знак оператора
		{
			while (!stack.empty() && lex.lextable.table[i].priority <= stack.top().priority)	// пока приоритет текущего оператора 
																					//меньше или равен приоритету оператора в вершине стека
			{
				queue.push(stack.top());											// выталкиваем со стека в выходную строку
				stack.pop();
			}
			stack.push(lex.lextable.table[i]);
			continue;
		}
		case LEX_COMMA:																// если зап€та€
		{
			findComma = true;
			countParm++;
			continue;
		}
		}
	}
	while (!stack.empty())															// если стек не пустой
	{
		if (stack.top().lexema == LEX_LEFTTHESIS || stack.top().lexema == LEX_RIGHTTHESIS)
			return false;
		queue.push(stack.top());													// выталкиваем все в очередь
		stack.pop();
	}
	while (countLex != 0)															// замена текущего выражени€ в таблице лексем на польскую запись
	{
		if (!queue.empty()) {
			lex.lextable.table[posLex++] = queue.front();	
			queue.pop();
		}
		else
		{
			lex.lextable.table[posLex++] = temp;
		}
		countLex--;
	}
	for (int i = 0; i < posLex; i++)												// восстановление индексов первого вхождени€ в таблицу лексем у операторов из таблицы идентификаторов
	{
		if (lex.lextable.table[i].lexema == LEX_OPERATOR || lex.lextable.table[i].lexema == LEX_LITERAL)
			lex.idtable.table[lex.lextable.table[i].idxTI].idxfirstLE = i;
	}
	return true;
}