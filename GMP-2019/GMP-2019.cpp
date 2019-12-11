#include "stdafx.h"
#ifndef TEST
int _tmain(int argc, _TCHAR ** argv)
{
	setlocale(LC_ALL, "rus");
	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLine(log, L"Тест", L" Без ошибок", L"");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		Log::WriteIn(log, in);
		Lex::LEX lex = Lex::lexAnaliz(log, in);
		std::cout << "Лексический анализ завершён без ошибок\n\n";
		*log.stream << "\nЛексический анализ завершён без ошибок\n\n";
		//IT::showTable(lex.idTable);
		//bool rc = PolishNotation(17, lex);
		/*bool rc = PolishNotation(64, lex);
		if (rc)
			std::cout << "Польская запись построена" << std::endl;
		else
			std::cout << "Польская запись не построена" << std::endl;
		LT::showTable(lex.lexTable, log);*/

		/*LT::showTable(lex.lexTable, log);
		IT::showTable(lex.idTable);
		LT::Delete(lex.lexTable);
		IT::Delete(lex.idTable);*/

		MFST::Mfst mfst(lex, GRB::getGreibach(), true);
		if (!mfst.start())
			throw ERROR_THROW(600);
		std::cout << "Синтаксический анализ завершён без ошибок\n";
		*log.stream << "Синтаксический анализ завершён без ошибок\n\n";
		// mfst.savededucation();
		mfst.printrules();
		if (Sem::checkSemantic(lex, log))
		{
			std::cout << "\nСемантический анализ завершён без ошибок\n\n";
			*log.stream << "Семантический анализ завершён без ошибок\n\n";
		}
		Gen::CodeGeneration(lex, parm.out);
		LT::showTable(lex.lexTable, log);
		IT::showTable(lex.idTable, log);

		//system("pause");
		Log::Close(log);
	}
	catch (Error::ERROR error)
	{
		Log::WriteError(log, error);
		std::cout << "Ошибка " << error.id << ": " << error.message << ", строка " << error.inext.line << ", позиция " << error.inext.col << std::endl;
		system("pause");
	}
	return 0;
}
#endif // !TEST

