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

		Gen::CodeGeneration(lex, parm.out);
		//IT::showTable(lex.idtable);
		//bool rc = PolishNotation(17, lex);
		/*bool rc = PolishNotation(64, lex);
		if (rc)
			std::cout << "Польская запись построена" << std::endl;
		else
			std::cout << "Польская запись не построена" << std::endl;
		LT::showTable(lex.lextable, log);*/

		/*LT::showTable(lex.lextable, log);
		IT::showTable(lex.idtable);
		LT::Delete(lex.lextable);
		IT::Delete(lex.idtable);*/

		//MFST::Mfst mfst(lex, GRB::getGreibach());
		//mfst.start();
		// mfst.savededucation();
		//mfst.printrules();
		std::cout << Sem::checkSemantic(lex, log);
		LT::showTable(lex.lextable, log);
		//IT::showTable(lex.idtable);

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

