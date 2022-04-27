#include "MapLevel.h"
#include "MainMap.h"
#include "LevelChanger.h"
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