#include "stdafx.h"

#ifdef TEST
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
		In::IN in = In::getin(parm.in, parm.out);
		Log::WriteIn(log, in);

		/*unsigned char* test = new unsigned char[22]{ "define integer abcd6|" };
		in.text = test;
		Lex::LEX lex = Lex::lexAnaliz(log, in);*/

		LT::LexTable lexTable = LT::Create(LT_MAXSIZE+1); //создание таблицы макс размера

		//IT::IdTable idTable = IT::Create(TI_MAXSIZE+1);//создание таблицы макс размера


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
#endif // TEST

