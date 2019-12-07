#include "stdafx.h"
#include <queue>

namespace Sem
{
	bool Sem::checkSemantic(Lex::LEX& tables, Log::LOG& log)
	{
		for (int i = 0; i < tables.lextable.size; i++)
		{
			switch (tables.lextable.table[i].lexema)
			{
				case LEX_LOGICAL: // проверка логический операторов
				{
					IT::IDDATATYPE dataTypeLeftOp = tables.idtable.table[tables.lextable.table[i - 1].idxTI].idDataType;
					IT::IDDATATYPE dataTypeRightOp = tables.idtable.table[tables.lextable.table[i + 1].idxTI].idDataType;

					if(dataTypeLeftOp != IT::INT || dataTypeRightOp != IT::INT)
						throw ERROR_THROW_IN(508, tables.lextable.table[i].sn, 0);

					break;
				}
				case LEX_POW: // проверка pow 
				{
					int paramsCount = 0;

					for (int j = i + 2; tables.lextable.table[j].lexema != LEX_RIGHTTHESIS; j++)
					{
						if (tables.lextable.table[j].lexema == LEX_ID || tables.lextable.table[j].lexema == LEX_LITERAL)
						{
							paramsCount++;
							IT::IDDATATYPE ctype = tables.idtable.table[tables.lextable.table[j].idxTI].idDataType;
							if (ctype != IT::INT)
								throw ERROR_THROW_IN(506, tables.lextable.table[i].sn, 0);
						}
					}
					if (paramsCount != 2)
						throw ERROR_THROW_IN(506, tables.lextable.table[i].sn, 0);
					break;
				}
				case LEX_COMPARE: // проверка compare
				{
					int paramsCount = 0;

					for (int j = i + 2; tables.lextable.table[j].lexema != LEX_RIGHTTHESIS; j++)
					{
						if (tables.lextable.table[j].lexema == LEX_ID || tables.lextable.table[j].lexema == LEX_LITERAL)
						{
							paramsCount++;
							IT::IDDATATYPE ctype = tables.idtable.table[tables.lextable.table[j].idxTI].idDataType;
							if (ctype != IT::STR)
								throw ERROR_THROW_IN(507, tables.lextable.table[i].sn, 0);
						}
					}
					if (paramsCount != 2)
						throw ERROR_THROW_IN(507, tables.lextable.table[i].sn, 0);
					break;
				}
				case LEX_ID: // проверка типа возвращаемого значения  
				{
					IT::Entry tmp = tables.idtable.table[tables.lextable.table[i].idxTI];

					if (i > 0 && tables.lextable.table[i - 1].lexema == LEX_FUNCTION)
					{
						if (tmp.idtype == IT::F) //функция, не процедура
						{
							for (int k = i + 1; k != tables.lextable.size; k++)
							{
								char l = tables.lextable.table[k].lexema;
								if (l == LEX_RETURN)
								{
									int lexAfterReturn = tables.lextable.table[k + 1].idxTI; // след. за return
									if (lexAfterReturn != TI_NULLIDX)
									{
										// тип функции и возвращаемого значения не совпадают
										if (tables.idtable.table[lexAfterReturn].idDataType != tmp.idDataType)
										{
											throw ERROR_THROW_IN(502, tables.lextable.table[k].sn, 0);
										}
									}
									break;
								}
							}
						}
					}
					if (tables.lextable.table[i + 1].lexema == LEX_LEFTTHESIS && tables.lextable.table[i - 1].lexema != LEX_FUNCTION) // вызов
					{
						if (tmp.idtype == IT::F)
						{
							
							std::queue<LT::Entry> queue;

							int protoParamsCount = 0;
							
							for (int iterator = tmp.idxfirstLE + 1; tables.lextable.table[iterator].lexema != LEX_RIGHTTHESIS; iterator++)
							{
								if (tables.lextable.table[iterator].lexema == LEX_ID) {
									/*if(tables.idtable.table[tables.lextable.table[iterator].idxTI].idtype == IT::P)*/
									protoParamsCount++;
									queue.push(tables.lextable.table[iterator]);
								}
							}
							if (protoParamsCount > PARAMS_MAX)
								throw ERROR_THROW_IN(503, tables.lextable.table[i].sn, 0);
							
							// проверка передаваемых параметров
							for (int j = i + 1; tables.lextable.table[j].lexema != LEX_RIGHTTHESIS; j++)
							{
								// проверка соответствия передаваемых параметров прототипам
								if (tables.lextable.table[j].lexema == LEX_ID || tables.lextable.table[j].lexema == LEX_LITERAL)
								{
									IT::IDDATATYPE ctype = tables.idtable.table[tables.lextable.table[j].idxTI].idDataType;
									if (!queue.empty())
									{
										if (ctype != tables.idtable.table[queue.front().idxTI].idDataType)
										{
											// Несовпадение типов передаваемых параметров
											throw ERROR_THROW_IN(504, tables.lextable.table[i].sn, 0);
										}
										queue.pop();
									}
									else
									{
										// Количество передаваемых и принимаемых параметров не совпадает
										throw ERROR_THROW_IN(505, tables.lextable.table[i].sn, 0);
									}
								}
							}
							if (!queue.empty())
							{
								throw ERROR_THROW_IN(505, tables.lextable.table[i].sn, 0);
							}
						}
					}
					break;
				}

			}
		}
		return true;
	}
}