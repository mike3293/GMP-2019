#include "stdafx.h"
#include <queue>

using namespace std;
bool PolishNotation(int i, Lex::LEX& lex)
{
	stack<LT::Entry> stack;									
	
	queue<LT::Entry> queue;	

	int lineNum = lex.lexTable.table[i].numberOfString;
	LT::Entry temp;			// ������� ��� �����������
	temp.idxTI = INT_MIN;
	temp.lexema = '#';
	temp.numberOfString = lineNum;

	LT::Entry funcParm;			// ������� ��� ������ �������
	funcParm.idxTI = INT_MIN;
	funcParm.lexema = '@';
	funcParm.numberOfString = lineNum;
	int countLex = 0;															// ���������� ��������������� ������
	int countParm = 0;															// ���������� ���������� �������
	int posLex = i;																// ���������� ����� ������� ����� ���������������
	bool findFunc = false;														// ���� ��� �������
	bool findComma = false;														// ���� ��� ������� (���-�� ���������� +2 �����)
	char* buf = new char[2];													// ����� ��� countParm � ��������� �������������
	for (i; lex.lexTable.table[i].lexema != LEX_SEMICOLON; i++, countLex++)
	{
		switch (lex.lexTable.table[i].lexema)
		{
		case LEX_ID:			
		{
			if (lex.idTable.table[lex.lexTable.table[i].idxTI].idType == IT::F)
				findFunc = true;
			queue.push(lex.lexTable.table[i]);
			continue;
		}
		case LEX_LITERAL:				
		{
			queue.push(lex.lexTable.table[i]);										
			continue;
		}
		case LEX_LEFTTHESIS:	
		{
			stack.push(lex.lexTable.table[i]);										// �������� � ����
			continue;
		}
		case LEX_RIGHTTHESIS:				
		{
			if (findFunc)															// ���� ��� ����� �������, �� ������� () ���������� �� @ � ���-�� ����������
			{
				if (findComma)
				{
					countParm++;
				}
				lex.lexTable.table[i] = funcParm;
				queue.push(lex.lexTable.table[i]);									// ��������� � ������� ������� ������ �������
				_itoa_s(countParm, buf, 2, 10);										// �������������� ����� countParm � ������
				stack.top().lexema = buf[0];
				stack.top().idxTI = INT_MIN;
				stack.top().numberOfString = lineNum;						// ��������� �������, ����������� ���������� ���������� �������
				queue.push(stack.top());											// ��������� � ������� ��� �������
				findFunc = false;
			}
			else {
				while (stack.top().lexema != LEX_LEFTTHESIS)						// ���� �� �������� (
				{
					queue.push(stack.top());										// ����������� �� ����� � �������
					stack.pop();

					if (stack.empty())
						return false;
				}
			}
			stack.pop();															// ���������� ( ��� �������, ����������� ���������� ���������� �������
			continue;
		}
		case LEX_OPERATOR:															// ���� ���� ���������
		{
			while (!stack.empty() && lex.lexTable.table[i].priority <= stack.top().priority)	// ���� ��������� �������� ��������� 
																					//������ ��� ����� ���������� ��������� � ������� �����
			{
				queue.push(stack.top());											// ����������� �� ����� � �������� ������
				stack.pop();
			}
			stack.push(lex.lexTable.table[i]);
			continue;
		}
		case LEX_COMMA:																// ���� �������
		{
			findComma = true;
			countParm++;
			continue;
		}
		}
	}
	while (!stack.empty())															// ���� ���� �� ������
	{
		if (stack.top().lexema == LEX_LEFTTHESIS || stack.top().lexema == LEX_RIGHTTHESIS)
			return false;
		queue.push(stack.top());													// ����������� ��� � �������
		stack.pop();
	}
	while (countLex != 0)															// ������ �������� ��������� � ������� ������ �� �������� ������
	{
		if (!queue.empty()) {
			lex.lexTable.table[posLex++] = queue.front();	
			queue.pop();
		}
		else
		{
			lex.lexTable.table[posLex++] = temp;
		}
		countLex--;
	}
	for (int i = 0; i < posLex; i++)												// �������������� �������� ������� ��������� � ������� ������ � ���������� �� ������� ���������������
	{
		if (lex.lexTable.table[i].lexema == LEX_OPERATOR || lex.lexTable.table[i].lexema == LEX_LITERAL)
			lex.idTable.table[lex.lexTable.table[i].idxTI].idxfirstLE = i;
	}
	return true;
}