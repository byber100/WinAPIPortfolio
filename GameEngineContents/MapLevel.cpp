#include "MapLevel.h"
#include "MainMap.h"
#include "LevelChanger.h"
#include "Player.h"
#include "PlayUI.h"
#include <GameEngineBase/GameEngineInput.h>


// Static Var

// Static Func

// constructor destructor
MapLevel::MapLevel()
{
}

MapLevel::~MapLevel()
{
}

//member Func
void MapLevel::Loading()
{
	if (nullptr == PlayUI::MainUI)
	{
		PlayUI::MainUI = CreateActor<PlayUI>(5, "MainUI");
	}

	LevelChanger_ = CreateActor<LevelChanger>(0);
	CreateActor<MainMap>(1);
	
	GameEngineInput::GetInst()->CreateKey("GameStart", VK_SPACE);
}

void MapLevel::Update()
{
	//test///////////////////////////////////////
	if (true == LevelChanger_->GetChanging())
	{
		LevelChanger_->LevelChangeAnim("Play");
	}
	if (GameEngineInput::GetInst()->IsDown("GameStart"))
	{
		dynamic_cast<LevelChanger*>(FindActor("LevelChanger"))->LevelChangeAnim("Play");
	}
}

void MapLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	
}

void MapLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	PlayUI::MainUI->NextLevelOn();
}