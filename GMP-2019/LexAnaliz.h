#pragma once
#include "stdafx.h"



namespace Lex
{
	bool checkBrace(unsigned char** word, int k);
	struct LEX
	{
		IT::IdTable idtable;;
		LT::LexTable lextable;
	};

	LEX lexAnaliz(Log::LOG log, In::IN in);
}