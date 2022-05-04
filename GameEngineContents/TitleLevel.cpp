#include "TitleLevel.h"
#include "Title.h"
#include "LevelChanger.h"
#include <GameEngineBase/GameEngineSound.h>

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

void TitleLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	//GameEngineSound::SoundPlayOneShot("TitleBGM.mp3");
}