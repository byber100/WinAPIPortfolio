#include "TitleLevel.h"
#include "GameEngine/GameEngine.h"
#include "TitleLogo.h"
#include "TitleBackGround.h"

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Loading() 
{

	CreateActor<TitleBackGround>(0);

	CreateActor<TitleLogo>(1);

}

void TitleLevel::Update()
{
	// GameEngine::GlobalEngine().ChangeLevel("Play");
}