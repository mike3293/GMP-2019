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
		LT::LexTable lextable = LT::Create(LT_MAXSIZE); //создание таблицы макс размера
		IT::IdTable idtable = IT::Create(TI_MAXSIZE);//создание таблицы макс размера

		unsigned char** word = new unsigned char*[MAX_WORDS]; //выделение памяти для разделения лексем
		for (int i = 0; i < MAX_WORDS; i++)
			word[i] = new unsigned char[WORD_SIZE] {NULL};
		
		word = divideText(in); //разделение на лексемы 


		int indexLex = 0;		// индекс лексемы
		int indexID = 0;		// индекс идент.
		int countLit = 1;		// счетчик литералов
		int line = 1;			// номер строки

		unsigned char emptystr[] = "";	// пустая строка
		unsigned char* regionPrefix = new unsigned char[10]{ "" };	// текущий префикс
		unsigned char* bufRegionPrefix = new unsigned char[10]{ "" };	// буфер для префикса
		unsigned char* oldRegionPrefix = new unsigned char[10]{ "" };	// предыдущий префикс
		unsigned char* L = new unsigned char[2]{ "L" };		// начальный символ для имён литералов + \0
		unsigned char* bufL = new unsigned char[TI_STR_MAXSIZE];
		unsigned char* nameLiteral = new unsigned char[TI_STR_MAXSIZE]{ "" };
		char* charCountLit = new char[10]{ "" };		// для строковой записи счетчика
		unsigned char* startWord = new unsigned char[WORD_SIZE] {NULL}; //для области видимости

		bool findFunc = false;
		bool findParm = false;
		IT::Entry entryIT; //создание лексемы для занесения в табл идентификаторов 

		for (int i = 0; word[i] != NULL; i++, indexLex++) //проход по всем лексемам
		{

			bool findSameID = false; 

			FST::FST fstIf(word[i], FST_IF); // проверка на ключевое слово
			if (FST::execute(fstIf))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_IF, LT_TI_NULLIDX, line); //создание структуры
				LT::Add(lextable, entryLT); //добавление структуры в таблицу
				continue;
			}

			FST::FST fstElse(word[i], FST_ELSE); // проверка на ключевое слово
			if (FST::execute(fstElse))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_ELSE, LT_TI_NULLIDX, line); //создание структуры
				LT::Add(lextable, entryLT); //добавление структуры в таблицу
				continue;
			}
			
			FST::FST fstLogical(word[i], FST_LOGICAL); // проверка на ключевое слово
			if (FST::execute(fstLogical))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_LOGICAL, LT_TI_NULLIDX, line); //создание структуры
				LT::Add(lextable, entryLT); //добавление структуры в таблицу
				continue;
			}

			FST::FST fstDeclare(word[i], FST_DECLARE); // проверка на ключевое слово
			if (FST::execute(fstDeclare))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_VAR, LT_TI_NULLIDX, line); //создание структуры
				LT::Add(lextable, entryLT); //добавление структуры в таблицу
				continue;
			}
			FST::FST fstTypeInteger(word[i], FST_INTEGER);// проверка на ключевое слово
			if (FST::execute(fstTypeInteger))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_INTEGER, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);

				entryIT.iddatatype = IT::INT; //запись типа идентификатора в структуру
				continue;
			}
			FST::FST fstTypeString(word[i], FST_STRING);// проверка на ключевое слово
			if (FST::execute(fstTypeString))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_STRING, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);

				entryIT.iddatatype = IT::STR;			//запись типа идентификатора в структуру
				_mbscpy(entryIT.value.vstr.str, emptystr); //очистка строки для записи идентификатора
				continue;
			}
			FST::FST fstFunction(word[i], FST_FUNCTION);// проверка на ключевое слово
			if (FST::execute(fstFunction))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_FUNCTION, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);

				entryIT.idtype = IT::F;
				findFunc = true; //установка флага функции
				continue;
			}
			FST::FST fstReturn(word[i], FST_RETURN);// проверка на ключевое слово
			if (FST::execute(fstReturn))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_RETURN, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}
			FST::FST fstPrint(word[i], FST_PRINT);// проверка на ключевое слово
			if (FST::execute(fstPrint))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_PRINT, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}
			FST::FST fstMain(word[i], FST_MAIN);// проверка на ключевое слово
			if (FST::execute(fstMain))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_MAIN, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);

				_mbscpy(oldRegionPrefix, regionPrefix);
				_mbscpy(regionPrefix, word[i]);
				continue;
			}
			FST::FST fstIdentif(word[i], FST_ID); //проверка на идентификатор
			if (FST::execute(fstIdentif))
			{
				FST::FST fstLibFunc(word[i], FST_LIBFUNC); //проверка на substr и strlen

				if((_mbslen(word[i]) > ID_MAXSIZE - 1) && !(FST::execute(fstLibFunc)))
					throw ERROR_THROW_IN(116, line, 0);
				_mbscpy(startWord, word[i]);

				// поиск такого же
				if (findFunc)	// если функция
				{
					int idx = IT::IsIDRegion(idtable, word[i]);	// ищем без префикса
					if (idx != TI_NULLIDX)						// если такой идентификатор уже есть
					{
						if (lextable.table[indexLex-1].lexema == LEX_FUNCTION)
							throw ERROR_THROW_IN(114, line, 0);
						LT::Entry entryLT;
						writeEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lextable, entryLT);
						findFunc = false;
						continue;
					}
				}
				else
				{
					int idx = IT::IsIDRegion(idtable, word[i]);	
					if (idx != TI_NULLIDX)					
					{
						if (lextable.table[indexLex - 2].lexema == LEX_VAR)
							throw ERROR_THROW_IN(114, line, 0);
						LT::Entry entryLT;
						writeEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lextable, entryLT);
						continue;
					}
					_mbscpy(bufRegionPrefix, regionPrefix);
					word[i] = _mbscat(bufRegionPrefix, word[i]);
					idx = IT::IsIDRegion(idtable, word[i]);
					if (idx != TI_NULLIDX)		// если такой идентификатор уже есть
					{
						if (lextable.table[indexLex - 2].lexema == LEX_VAR)
							throw ERROR_THROW_IN(114, line, 0);
						LT::Entry entryLT;
						writeEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lextable, entryLT);
						continue;
					}
				}
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_ID, indexID++, line);
				LT::Add(lextable, entryLT);
				if (findParm)				// если параметр
				{
					entryIT.idtype = IT::P;
				}
				else if (!findFunc) 
				{
					// если переменная
					entryIT.idtype = IT::V;
					if (entryIT.iddatatype == IT::INT)
						entryIT.value.vint = TI_INT_DEFAULT;
					if (entryIT.iddatatype == IT::STR) {
						entryIT.value.vstr.len = 0;
						memset(entryIT.value.vstr.str, TI_STR_DEFAULT, sizeof(char));
					}
				}
				else {		// если функция
					_mbscpy(oldRegionPrefix, regionPrefix);
					_mbscpy(regionPrefix, word[i]);
				}

				entryIT.idxfirstLE = indexLex;
				_mbscpy(entryIT.id, startWord);
				_mbscpy(entryIT.idRegion, word[i]);
				IT::Add(idtable, entryIT);
				findFunc = false;
				continue;
			}

			FST::FST fstLiteralInt(word[i], FST_INTLIT); //если литерал 
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
					value = atoi((char*)word[i]);	// значение литерала
				}
				for (int k = 0; k < idtable.size; k++) // поиск такого же
				{
					if (idtable.table[k].value.vint == value && idtable.table[k].idtype == IT::L)
					{
						LT::Entry entryLT;
						writeEntry(entryLT, LEX_LITERAL, k, line);
						LT::Add(lextable, entryLT);
						findSameID = true;
						break;
					}
			}
				if (findSameID)	// если был найден такой же
				{
					continue;
				}
					
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_LITERAL, indexID++, line);
				LT::Add(lextable, entryLT);
				entryIT.idtype = IT::L;
				entryIT.iddatatype = IT::INT;
				entryIT.value.vint = value;
				entryIT.idxfirstLE = indexLex;	//номер в табл лексем
				_itoa_s(countLit++, charCountLit, sizeof(char) * 10, 10);	// преобразуем значение счетчика в строку(charCountLit) 
				
				// формирование имени литерала
				_mbscpy(bufL, L);	// помещаем в буфер "L"
				word[i] = _mbscat(bufL, (unsigned char*)charCountLit);	// формируем имя для литерала
				_mbscpy(entryIT.id, word[i]);
				_mbscpy(entryIT.idRegion, emptystr);
				IT::Add(idtable, entryIT);
				continue;
			}
			FST::FST fstLiteralString(word[i], FST_STRLIT);
			if (FST::execute(fstLiteralString))
			{
				// запись значения
				int length = _mbslen(word[i]);
				for (int k = 0; k < length; k++)	// перезапись массива, убираем кавычки
					word[i][k] = word[i][k + 1];

				word[i][length - 2] = '\0';

					
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_LITERAL, indexID++, line);
				LT::Add(lextable, entryLT);
				_mbscpy(entryIT.value.vstr.str, word[i]);	// запись значиния строкового литерала
				entryIT.value.vstr.len = length - 2;		// запись длины строкового литерала
				entryIT.idtype = IT::L;
				entryIT.iddatatype = IT::STR;
				entryIT.idxfirstLE = indexLex;
				// формирование имени литерала
				_itoa_s(countLit++, charCountLit, sizeof(char) * 10, 10);	// преобразуем значение счетчика в строку(charCountLit)
				_mbscpy(bufL, L);	// помещаем в буфер "L"
				nameLiteral = _mbscat(bufL, (unsigned char*)charCountLit);	// формируем имя для литерала (L + charCountLit)
				_mbscpy(entryIT.id, nameLiteral);
				_mbscpy(entryIT.idRegion, emptystr);
				IT::Add(idtable, entryIT);
				continue;
			}

			FST::FST fstOperator(word[i], FST_OPERATOR);
			if (FST::execute(fstOperator))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_OPERATOR, indexID++, line);
				switch (word[i][0])
				{
				case PLUS: case MINUS:
					entryLT.priority = 2;
					break;
				case SLASH: case STAR:
					entryLT.priority = 3;
					break;
				}
				LT::Add(lextable, entryLT);
				_mbscpy(entryIT.id, word[i]);
				entryIT.idxfirstLE = indexLex;
				entryIT.idtype = IT::OP;
				IT::Add(idtable, entryIT);
				continue;
			}
			FST::FST fstSemicolon(word[i], FST_SEMICOLON);
			if (FST::execute(fstSemicolon))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_SEMICOLON, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}
			FST::FST fstComma(word[i], FST_COMMA);
			if (FST::execute(fstComma))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_COMMA, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}
			FST::FST fstLeftBrace(word[i], FST_LEFTBRACE);
			if (FST::execute(fstLeftBrace))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_LEFTBRACE, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}
			FST::FST fstRightBrace(word[i], FST_BRACELET);
			if (FST::execute(fstRightBrace))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_BRACELET, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}
			FST::FST fstLeftThesis(word[i], FST_LEFTTHESIS);
			if (FST::execute(fstLeftThesis))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_LEFTTHESIS, LT_TI_NULLIDX, line);
				entryLT.priority = 0;
				LT::Add(lextable, entryLT);
				if (idtable.table[indexID - 1].idtype == IT::F)
					findParm = true;
				continue;
			}
			FST::FST fstRightThesis(word[i], FST_RIGHTTHESIS);
			if (FST::execute(fstRightThesis))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_RIGHTTHESIS, LT_TI_NULLIDX, line);
				entryLT.priority = 0;

				if (findParm && word[i + 1][0] != LEX_LEFTBRACE && word[i + 2][0] != LEX_LEFTBRACE && !checkBrace(word, i + 1))		// если после функции нет {
					_mbscpy(regionPrefix, oldRegionPrefix);		// возвращаем предыдущую обл. видимости
				findParm = false;
				LT::Add(lextable, entryLT);
				continue;
			}
			FST::FST fstEqual(word[i], FST_EQUAL);
			if (FST::execute(fstEqual))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_EQUAL, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}
			if (word[i][0] == DIV) {
				line++;
				indexLex--;
				continue;
			}
			throw ERROR_THROW_IN(115, line, 0);
		}
		lex.idtable = idtable;
		lex.lextable = lextable;
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