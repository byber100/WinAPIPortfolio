#include "MapLevel.h"
#include "ContentsEnum.h"
#include "MainMap.h"
#include "LevelChanger.h"
#include "Player.h"
#include "PlayUI.h"
#include "PathPoint.h"
#include <GameEngineBase/GameEngineInput.h>


// Static Var

// Static Func

// constructor destructor
MapLevel::MapLevel()
	: LevelChanger_(nullptr)
	, StrockCnt_(0)
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
	
	float DrawSpeed = 50.f;
	switch (StrockCnt_)
	{
	case 0:
	{
		if (0 == PathAll_.size())										// fisrt draw
		{
			PathPoint* Path = CreateActor<PathPoint>((int)ORDER::BACKGROUND);
			Path->Draw(DrawMode::Point, { 643,575 });
			PathAll_.push_back(Path);
		}
		if (true == PathAll_.back()->isClear())
		{
			++StrockCnt_;
			break;
		}
		break;
	}
	case 1:
	{
		if (true == PathAll_.back()->isClear())
		{
			PathPoint* Path = CreateActor<PathPoint>((int)ORDER::BACKGROUND);
			Path->Draw(DrawMode::Line, { 500,500 }, float4::UP, 50.f, DrawSpeed, LineColor::GRAY);
			PathAll_.push_back(Path);
			++StrockCnt_;
		}
		break;
	}
	case 2:
	{
		if (true == PathAll_.back()->isClear())
		{
			PathPoint* Path = CreateActor<PathPoint>((int)ORDER::BACKGROUND);
			Path->Draw(DrawMode::Line, { 260-3.5f,500 }, float4::UP, 40.f, DrawSpeed, LineColor::GRAY);
			PathAll_.push_back(Path);
			++StrockCnt_;
		}
		break;
	}
	default:
		break;
	}
}

void MapLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	
}

void MapLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	PlayUI::MainUI->NextLevelOn();
}