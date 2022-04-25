#include "TitleLevel.h"
#include "Title.h"
#include "LevelChanger.h"

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Loading() 
{
	CreateActor<LevelChanger>(0);
	CreateActor<Title>(1);
}

void TitleLevel::Update()
{
	
}