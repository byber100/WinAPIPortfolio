#include "CompanyLevel.h"
#include "CompanyBack.h"
#include "KonamiLogo.h"

// Static Var

// Static Func

// constructor destructor
CompanyLevel::CompanyLevel()
{
}

CompanyLevel::~CompanyLevel()
{
}

//member Func
void CompanyLevel::Loading()
{
	CreateActor<CompanyBack>();
	CreateActor<KonamiLogo>();
}

void CompanyLevel::Update()
{
	
}
