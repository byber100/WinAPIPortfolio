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
	, BrushPos_{ 640,580 }
{
}

MapLevel::~MapLevel()
{
}

//member Func
void  MapLevel::ContinuousDrawing(const float4& _Dir, const float& _Lengh, const float& _DrawSpeed, const int& _PassStage)
{
	PathPoint* Path = CreateActor<PathPoint>((int)ORDER::BACKGROUND);

	if (_PassStage >= PlayUI::MainUI->GetStage())
	{
		Path->Draw(DrawMode::Line, BrushPos_, _Dir, _Lengh, _DrawSpeed, LineColor::GRAY);
	}
	else
	{
		Path->Draw(DrawMode::Line, BrushPos_, _Dir, _Lengh, _DrawSpeed, LineColor::OCHER);
	}

	PathAll_.push_back(Path);
	++StrockCnt_;
	BrushPos_ += _Dir * _Lengh;
}

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
	{// test///////////////////////////////////////////////////////////////////
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
	
	float DrawSpeed = 15.f;
	switch (StrockCnt_)
	{
	case 0:
	{
		if (0 == PathAll_.size())										// fisrt draw
		{
			PathPoint* Path = CreateActor<PathPoint>((int)ORDER::BACKGROUND);
			Path->Draw(DrawMode::Point, BrushPos_);
			PathAll_.push_back(Path);
			++StrockCnt_;
		}
		break;
	}
	case 1:
	{
		if (true == PathAll_.back()->isClear())
		{
			ContinuousDrawing(float4::LEFT, 90.f, DrawSpeed, 1);
		}
		break;
	}
	case 2:
	{
		if (true == PathAll_.back()->isClear())
		{
			ContinuousDrawing(float4::UP, 120.f, DrawSpeed, 1);
		}
		break;
	}
	case 3:
	{
		if (true == PathAll_.back()->isClear())
		{
			ContinuousDrawing(float4::LEFT, 30.f, DrawSpeed, 1);
		}
		break;
	}
	case 4:
	{
		if (true == PathAll_.back()->isClear())
		{
			ContinuousDrawing(float4::UP, 30.f, DrawSpeed, 1);
		}
		break;
	}
	case 5:
	{
		if (true == PathAll_.back()->isClear())
		{
			ContinuousDrawing(float4::LEFT, 70.f, DrawSpeed, 1);
		}
		break;
	}
	case 6:
	{
		if (true == PathAll_.back()->isClear())
		{
			ContinuousDrawing(float4::DOWN, 60.f, DrawSpeed, 1);
		}
		break;
	}
	case 7:
	{
		if (true == PathAll_.back()->isClear())
		{
			ContinuousDrawing(float4::LEFT, 60.f, DrawSpeed, 1);
		}
		break;
	}
	case 8:
	{
		if (true == PathAll_.back()->isClear())
		{
			ContinuousDrawing(float4::UP, 130.f, DrawSpeed, 1);
		}
		break;
	}
	case 9:
	{
		if (true == PathAll_.back()->isClear())
		{
			ContinuousDrawing(float4::RIGHT, 60.f, DrawSpeed, 1);
		}
		break;
	}
	case 10:
	{
		if (true == PathAll_.back()->isClear())
		{
			ContinuousDrawing(float4::UP, 60.f, DrawSpeed, 1);
		}
		break;
	}
	case 11:
	{
		if (true == PathAll_.back()->isClear())
		{
			PathPoint* Path = CreateActor<PathPoint>((int)ORDER::BACKGROUND);
			Path->Draw(DrawMode::Point, BrushPos_);
			PathAll_.push_back(Path);
			++StrockCnt_;
		}
		break;
	}
	case 12:
	{
		if (true == PathAll_.back()->isClear())
		{
			ContinuousDrawing(float4::UP, 30.f, DrawSpeed, 2);
		}
		break;
	}
	case 13:
	{
		if (true == PathAll_.back()->isClear())
		{
			ContinuousDrawing(float4::RIGHT, 125.f, DrawSpeed, 2);
		}
		break;
	}
	case 14:
	{
		if (true == PathAll_.back()->isClear())
		{
			ContinuousDrawing(float4::DOWN, 30.f, DrawSpeed, 2);
		}
		break;
	}
	case 15:
	{
		if (true == PathAll_.back()->isClear())
		{
			ContinuousDrawing(float4::RIGHT, 65.f, DrawSpeed, 2);
		}
		break;
	}
	case 16:
	{
		if (true == PathAll_.back()->isClear())
		{
			ContinuousDrawing(float4::DOWN, 100.f, DrawSpeed, 2);
		}
		break;
	}
	case 17:
	{
		if (true == PathAll_.back()->isClear())
		{
			ContinuousDrawing(float4::RIGHT, 35.f, DrawSpeed, 2);
		}
		break;
	}
	case 18:
	{
		if (true == PathAll_.back()->isClear())
		{
			ContinuousDrawing(float4::DOWN, 120.f, DrawSpeed, 2);
		}
		break;
	}
	case 19:
	{
		if (true == PathAll_.back()->isClear())
		{
			ContinuousDrawing(float4::LEFT, 35.f, DrawSpeed, 2);
		}
		break;
	}
	case 20:
	{
		if (true == PathAll_.back()->isClear())
		{
			ContinuousDrawing(float4::DOWN, 60.f, DrawSpeed, 2);
		}
		break;
	}
	default:
	{
		if (true == LevelChanger_->GetChanging())
		{
			LevelChanger_->LevelChangeAnim("Play");
		}
		if (GameEngineInput::GetInst()->IsDown("GameStart"))
		{
			GameEngineInput::GetInst()->Reset();
			dynamic_cast<LevelChanger*>(FindActor("LevelChanger"))->LevelChangeAnim("Play");
		}
		break;
	}
	}
}

void MapLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	BrushPos_ = { 640,580 };
	StrockCnt_ = 0;
}

void MapLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	PlayUI::MainUI->NextLevelOn();
	
	std::list<PathPoint*>::iterator StartIter = PathAll_.begin();
	std::list<PathPoint*>::iterator EndIter = PathAll_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr == *StartIter)
		{
			continue;
		}
		(*StartIter)->Death();
	}

	PathAll_.clear();
}