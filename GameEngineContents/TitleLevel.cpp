#include "TitleLevel.h"
#include "Title.h"

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Loading() 
{
	CreateActor<Title>();
}

void TitleLevel::Update()
{
	
}