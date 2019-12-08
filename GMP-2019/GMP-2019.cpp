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

		MFST::Mfst mfst(lex, GRB::getGreibach(), false);
		if (!mfst.start())
			throw ERROR_THROW(600);
		std::cout << "SYN is ok" << std::endl;
		// mfst.savededucation();
		//mfst.printrules();
		if(Sem::checkSemantic(lex, log))
			std::cout << "SEM is ok" << std::endl;
		Gen::CodeGeneration(lex, parm.out);
		LT::showTable(lex.lexTable, log);
		IT::showTable(lex.idTable);

		//system("pause");
		Log::Close(log);
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
		std::cout << e.message << std::endl;
		system("pause");
	}
	return 0;
}
#endif // !TEST

