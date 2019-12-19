#include "stdafx.h"
int _tmain(int argc, _TCHAR ** argv)
{
	setlocale(LC_ALL, "rus");
	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLine(log, L"����", L" ��� ������", L"");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		Log::WriteIn(log, in);
		Lex::LEX lex = Lex::lexAnaliz(log, in);
		std::cout << "����������� ������ �������� ��� ������\n\n";
		*log.stream << "\n����������� ������ �������� ��� ������\n\n";

		MFST::Mfst mfst(lex, GRB::getGreibach(), parm.trace);
		if (!mfst.start())
			throw ERROR_THROW(600);
		std::cout << "�������������� ������ �������� ��� ������\n";
		*log.stream << "�������������� ������ �������� ��� ������\n\n";
		mfst.printrules();

		if (Sem::checkSemantic(lex, log))
		{
			std::cout << "\n������������� ������ �������� ��� ������\n\n";
			*log.stream << "������������� ������ �������� ��� ������\n\n";
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
		std::cout << "������ " << error.id << ": " << error.message << ", ������ " << error.inext.line << ", ������� " << error.inext.col << std::endl;
		system("pause");
	}
	return 0;
}

