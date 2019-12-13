#include "stdafx.h"

#define PLUS '+'
#define MINUS '-'
#define STAR '*'
#define SLASH '/'
#define EQUAL '='

using namespace std;

namespace Lex
{
	LEX lexAnaliz(Log::LOG log, In::IN in)
	{
		LEX lex;
		LT::LexTable lexTable = LT::Create(LT_MAXSIZE); //�������� ������� ���� �������
		IT::IdTable idTable = IT::Create(TI_MAXSIZE);//�������� ������� ���� �������

		unsigned char** word = new unsigned char*[MAX_WORDS]; //��������� ������ ��� ���������� ������
		for (int i = 0; i < MAX_WORDS; i++)
			word[i] = new unsigned char[WORD_SIZE] {NULL};
		
		word = divideText(in); //���������� �� ������� 


		int indexLex = 0;		// ������ �������
		int indexID = 0;		// ������ �����.
		int countLit = 1;		// ������� ���������
		int line = 1;			// ����� ������
		int enterCount = 0;		// ���-�� main

		unsigned char emptystr[] = "";	// ������ ������
		unsigned char* regionPrefix = new unsigned char[10]{ "" };	// ������� �������
		unsigned char* bufRegionPrefix = new unsigned char[10]{ "" };	// ����� ��� ��������
		unsigned char* oldRegionPrefix = new unsigned char[10]{ "" };	// ���������� �������
		unsigned char* L = new unsigned char[2]{ "L" };		// ��������� ������ ��� ��� ��������� + \0
		unsigned char* bufL = new unsigned char[TI_STR_MAXSIZE];
		unsigned char* nameLiteral = new unsigned char[TI_STR_MAXSIZE]{ "" };
		char* charCountLit = new char[10]{ "" };		// ��� ��������� ������ ��������
		unsigned char* startWord = new unsigned char[WORD_SIZE] {NULL}; //��� ������� ���������

		bool findFunc = false;
		bool findParm = false;
		bool findDeclaration = false;
		IT::Entry entryIT; //�������� ������� ��� ��������� � ���� ��������������� 

		for (int i = 0; word[i] != NULL; i++, indexLex++) //������ �� ���� ��������
		{

			bool findSameID = false; 

			FST::FST fstLib(word[i], FST_USELIB); // �������� �� �������� �����
			if (FST::execute(fstLib))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_USELIB, LT_TI_NULLIDX, line); //�������� ���������
				LT::Add(lexTable, entryLT); //���������� ��������� � �������
				continue;
			}

			FST::FST fstIf(word[i], FST_IF); // �������� �� �������� �����
			if (FST::execute(fstIf))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_IF, LT_TI_NULLIDX, line); //�������� ���������
				LT::Add(lexTable, entryLT); //���������� ��������� � �������
				continue;
			}

			FST::FST fstElse(word[i], FST_ELSE); // �������� �� �������� �����
			if (FST::execute(fstElse))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_ELSE, LT_TI_NULLIDX, line); //�������� ���������
				LT::Add(lexTable, entryLT); //���������� ��������� � �������
				continue;
			}
			
			FST::FST fstLogical(word[i], FST_LOGICAL); // �������� �� �������� �����
			if (FST::execute(fstLogical))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_LOGICAL, indexID++, line); //�������� ���������
				LT::Add(lexTable, entryLT); //���������� ��������� � �������
				_mbscpy(entryIT.id, word[i]);

				entryIT.idxfirstLE = indexLex;
				entryIT.idType = IT::OP;
				IT::Add(idTable, entryIT);
				continue;
			}

			FST::FST fstDeclare(word[i], FST_DECLARE); // �������� �� �������� �����
			if (FST::execute(fstDeclare))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_VAR, LT_TI_NULLIDX, line); //�������� ���������
				LT::Add(lexTable, entryLT); //���������� ��������� � �������
				continue;
			}
			FST::FST fstTypeInteger(word[i], FST_INTEGER);// �������� �� �������� �����
			if (FST::execute(fstTypeInteger))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_USHORT, LT_TI_NULLIDX, line);
				LT::Add(lexTable, entryLT);

				entryIT.idDataType = IT::USHORT; //������ ���� �������������� � ���������
				findDeclaration = true;
				continue;
			}
			FST::FST fstTypeString(word[i], FST_STRING);// �������� �� �������� �����
			if (FST::execute(fstTypeString))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_STRING, LT_TI_NULLIDX, line);
				LT::Add(lexTable, entryLT);

				entryIT.idDataType = IT::STR;			//������ ���� �������������� � ���������
				_mbscpy(entryIT.value.vstr.str, emptystr); //������� ������ ��� ������ ��������������
				findDeclaration = true;
				continue;
			}
			FST::FST fstFunction(word[i], FST_FUNCTION);// �������� �� �������� �����
			if (FST::execute(fstFunction))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_FUNCTION, LT_TI_NULLIDX, line);
				LT::Add(lexTable, entryLT);

				entryIT.idType = IT::F;
				findFunc = true; //��������� ����� �������
				continue;
			}
			FST::FST fstReturn(word[i], FST_RETURN);// �������� �� �������� �����
			if (FST::execute(fstReturn))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_RETURN, LT_TI_NULLIDX, line);
				LT::Add(lexTable, entryLT);
				continue;
			}
			FST::FST fstPrint(word[i], FST_PRINT);// �������� �� �������� �����
			if (FST::execute(fstPrint))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_PRINT, LT_TI_NULLIDX, line);
				LT::Add(lexTable, entryLT);
				continue;
			}
			FST::FST fstMain(word[i], FST_MAIN);// �������� �� �������� �����
			if (FST::execute(fstMain))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_MAIN, LT_TI_NULLIDX, line);
				LT::Add(lexTable, entryLT);
				enterCount++;
				_mbscpy(oldRegionPrefix, regionPrefix);
				_mbscpy(regionPrefix, word[i]);
				continue;
			}
			FST::FST fstIdentif(word[i], FST_ID); //�������� �� �������������
			if (FST::execute(fstIdentif))
			{
				FST::FST fstLibPow(word[i], FST_LIB_POW); //��������
				FST::FST fstLibCompare(word[i], FST_LIB_COMPARE); //��������

				if(_mbslen(word[i]) > ID_MAXSIZE)
					throw ERROR_THROW_IN(202, line, 0);
				_mbscpy(startWord, word[i]);

				// ����� ������ ��
				if (findFunc)	// ���� �������
				{
					int idx = IT::IsIDRegion(idTable, word[i]);	// ���� ��� ��������
					if (idx != TI_NULLIDX)						// ���� ����� ������������� ��� ����
					{
						if (lexTable.table[indexLex-1].lexema == LEX_FUNCTION)
							throw ERROR_THROW_IN(200, line, 0);
						LT::Entry entryLT;
						writeEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lexTable, entryLT);
						findFunc = false;
						continue;
					}
				}
				else
				{
					int idx = IT::IsIDRegion(idTable, word[i]);	
					if (idx != TI_NULLIDX)					
					{
						if (lexTable.table[indexLex - 2].lexema == LEX_VAR)
							throw ERROR_THROW_IN(200, line, 0);
						LT::Entry entryLT;
						writeEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lexTable, entryLT);
						continue;
					}
					_mbscpy(bufRegionPrefix, regionPrefix);
					word[i] = _mbscat(bufRegionPrefix, word[i]);
					idx = IT::IsIDRegion(idTable, word[i]);
					if (idx != TI_NULLIDX)		// ���� ����� ������������� ��� ����
					{
						if (lexTable.table[indexLex - 2].lexema == LEX_VAR)
							throw ERROR_THROW_IN(200, line, 0);
						LT::Entry entryLT;
						writeEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lexTable, entryLT);
						continue;
					}
				}
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_ID, indexID++, line);
				if (findParm)				// ���� ��������
				{
					entryIT.idType = IT::P;
				}
				else if (!findFunc) 
				{
					// ���� ����������
					if (findDeclaration)
					{
						entryIT.idType = IT::V;
						if (entryIT.idDataType == IT::USHORT)
							entryIT.value.vushort = TI_INT_DEFAULT;
						if (entryIT.idDataType == IT::STR) {
							entryIT.value.vstr.len = 0;
							memset(entryIT.value.vstr.str, TI_STR_DEFAULT, sizeof(char));
						}
						findDeclaration = false;
					}
					else
					{
						FST::FST fstLibPow(startWord, FST_LIB_POW);
						FST::FST fstLibCompare(startWord, FST_LIB_COMPARE);
						if (FST::execute(fstLibPow))
						{
							entryLT.lexema = LEX_POW;
							entryIT.idType = IT::LIB;
						}
						else if (FST::execute(fstLibCompare))
						{
							entryLT.lexema = LEX_COMPARE;
							entryIT.idType = IT::LIB;
						}
						else
						{
							throw ERROR_THROW_IN(203, line, 0);
						}
					}
				}
				else {		// ���� �������
					_mbscpy(oldRegionPrefix, regionPrefix);
					_mbscpy(regionPrefix, word[i]);
				}

				LT::Add(lexTable, entryLT);
				entryIT.idxfirstLE = indexLex;
				_mbscpy(entryIT.id, startWord);
				_mbscpy(entryIT.idRegion, word[i]);
				IT::Add(idTable, entryIT);
				findFunc = false;
				continue;
			}

			FST::FST fstLiteralInt(word[i], FST_INTLIT); //���� ������� 
			FST::FST fstLiteralHex(word[i], FST_HEXLIT);

			if (FST::execute(fstLiteralInt) || FST::execute(fstLiteralHex))
			{
				unsigned short value;
				char* buf;
				if (word[i][1] == 'x')
				{
					value = strtoll((const char*)word[i], NULL, 16);
				}
				else
				{
					if(atoi((char*)word[i]) > MAX_USHORT)
						throw ERROR_THROW_IN(208, line, 0);
					value = atoi((char*)word[i]);	// �������� ��������
				}
				for (int k = 0; k < idTable.size; k++) // ����� ������ ��
				{
					if (idTable.table[k].value.vushort == value && idTable.table[k].idType == IT::L)
					{
						LT::Entry entryLT;
						writeEntry(entryLT, LEX_LITERAL, k, line);
						LT::Add(lexTable, entryLT);
						findSameID = true;
						break;
					}
			}
				if (findSameID)	// ���� ��� ������ ����� ��
				{
					continue;
				}
					
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_LITERAL, indexID++, line);
				LT::Add(lexTable, entryLT);
				entryIT.idType = IT::L;
				entryIT.idDataType = IT::USHORT;
				entryIT.value.vushort = value;
				entryIT.idxfirstLE = indexLex;	//����� � ���� ������
				_itoa_s(countLit++, charCountLit, sizeof(char) * 10, 10);	// ����������� �������� �������� � ������(charCountLit) 
				
				// ������������ ����� ��������
				_mbscpy(bufL, L);	// �������� � ����� "L"
				word[i] = _mbscat(bufL, (unsigned char*)charCountLit);	// ��������� ��� ��� ��������
				_mbscpy(entryIT.id, word[i]);
				_mbscpy(entryIT.idRegion, word[i]);
				IT::Add(idTable, entryIT);
				continue;
			}
			FST::FST fstLiteralString(word[i], FST_STRLIT);
			if (FST::execute(fstLiteralString))
			{
				// ������ ��������
				int length = _mbslen(word[i]);
				for (int k = 0; k < length; k++)	// ���������� �������, ������� �������
					word[i][k] = word[i][k + 1];

				word[i][length - 2] = '\0';

					
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_LITERAL, indexID++, line);
				LT::Add(lexTable, entryLT);
				_mbscpy(entryIT.value.vstr.str, word[i]);	// ������ �������� ���������� ��������
				entryIT.value.vstr.len = length - 2;		// ������ ����� ���������� ��������
				entryIT.idType = IT::L;
				entryIT.idDataType = IT::STR;
				entryIT.idxfirstLE = indexLex;
				// ������������ ����� ��������
				_itoa_s(countLit++, charCountLit, sizeof(char) * 10, 10);	// ����������� �������� �������� � ������(charCountLit)
				_mbscpy(bufL, L);	// �������� � ����� "L"
				nameLiteral = _mbscat(bufL, (unsigned char*)charCountLit);	// ��������� ��� ��� �������� (L + charCountLit)
				_mbscpy(entryIT.id, nameLiteral);
				_mbscpy(entryIT.idRegion, nameLiteral);
				IT::Add(idTable, entryIT);
				continue;
			}
			FST::FST fstSemicolon(word[i], FST_SEMICOLON);
			if (FST::execute(fstSemicolon))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_SEMICOLON, LT_TI_NULLIDX, line);
				LT::Add(lexTable, entryLT);
				continue;
			}
			FST::FST fstComma(word[i], FST_COMMA);
			if (FST::execute(fstComma))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_COMMA, LT_TI_NULLIDX, line);
				LT::Add(lexTable, entryLT);
				continue;
			}
			FST::FST fstLeftBrace(word[i], FST_LEFTBRACE);
			if (FST::execute(fstLeftBrace))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_LEFTBRACE, LT_TI_NULLIDX, line);
				LT::Add(lexTable, entryLT);
				continue;
			}
			FST::FST fstRightBrace(word[i], FST_BRACELET);
			if (FST::execute(fstRightBrace))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_RIGHTBRACE, LT_TI_NULLIDX, line);
				LT::Add(lexTable, entryLT);
				continue;
			}
			FST::FST fstLeftThesis(word[i], FST_LEFTTHESIS);
			if (FST::execute(fstLeftThesis))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_LEFTTHESIS, LT_TI_NULLIDX, line);
				entryLT.priority = 0;
				LT::Add(lexTable, entryLT);
				if (idTable.table[indexID - 1].idType == IT::F)
					findParm = true;
				continue;
			}
			FST::FST fstRightThesis(word[i], FST_RIGHTTHESIS);
			if (FST::execute(fstRightThesis))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_RIGHTTHESIS, LT_TI_NULLIDX, line);
				entryLT.priority = 0;

				if (findParm && word[i + 1][0] != LEX_LEFTBRACE && word[i + 2][0] != LEX_LEFTBRACE && !checkBrace(word, i + 1))		// ���� ����� ������� ��� {
					_mbscpy(regionPrefix, oldRegionPrefix);		// ���������� ���������� ���. ���������
				findParm = false;
				LT::Add(lexTable, entryLT);
				continue;
			}
			FST::FST fstEqual(word[i], FST_EQUAL);
			if (FST::execute(fstEqual))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_EQUAL, LT_TI_NULLIDX, line);
				LT::Add(lexTable, entryLT);
				continue;
			}
			if (word[i][0] == DIV) {
				line++;
				indexLex--;
				continue;
			}
			throw ERROR_THROW_IN(201, line, 0);
		}
		if (enterCount == 0)
		{
			throw ERROR_THROW_IN(500, 0, 0);
		}
		if (enterCount > 1)
		{
			throw ERROR_THROW_IN(501, 0, 0);
		}
		lex.idTable = idTable;
		lex.lexTable = lexTable;
		return lex;
	}

	bool checkBrace(unsigned char** word, int k)
	{
		while (word[k][0] == DIV)
		{
			k++;
		}
		if (word[k][0] == LEX_LEFTBRACE)
			return 1;
		else
			return 0;
	}
}