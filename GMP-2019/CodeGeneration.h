#pragma once
#include "stdafx.h"

#define SEM_GREAT ">"
#define SEM_LESS "<"
#define SEM_EQUAL "=="
#define SEM_GREATEQUAL ">="
#define SEM_LESSEQUAL "<="
#define SEM_NOTEQUAL "!="

namespace Gen
{
	void CodeGeneration(Lex::LEX& tables, wchar_t outfile[]);
};