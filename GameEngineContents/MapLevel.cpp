#include "MapLevel.h"
#include "ContentsEnum.h"
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
		PlayUI::MainUI = CreateActor<PlayUI>((int)ORDER::UI, "MainUI");
	}

	LevelChanger_ = CreateActor<LevelChanger>((int)ORDER::UI);
	CreateActor<MainMap>((int)ORDER::BACKGROUND);
	
	GameEngineInput::GetInst()->CreateKey("GameStart", VK_SPACE);
}

void MapLevel::Update()
{
	//test////////////////////////////////////////
	if (true == LevelChanger_->GetChanging())
	{
		LevelChanger_->LevelChangeAnim("Play");
	}
	if (GameEngineInput::GetInst()->IsDown("GameStart"))
	{
		GameEngineInput::GetInst()->Reset();
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