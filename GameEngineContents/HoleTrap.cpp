#include "HoleTrap.h"
#include "PlayLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>

// Static Var

// Static Func

// constructor destructor
HoleTrap::HoleTrap()
	: LOD_(0)
	, Hole_(nullptr)
{
	GameEngineRandom NewRandom;
	float yDown = 38;

	switch (NewRandom.RandomInt(0, 2))
	{
	case 0:
		DirVector_ = { 0, yDown };
		break;
	case 1:
		DirVector_ = { 32, yDown };
		break;
	case 2:
		DirVector_ = { -32, yDown };
		break;
	default:
		Death();
		break;
	}
}

HoleTrap::~HoleTrap()
{
}

//member Func
void HoleTrap::Start()
{
	float x = GameEngineWindow::GetScale().Half().x;
	float y = GameEngineWindow::GetScale().Half().y;

	SetPosition({ x , y + 32 });
	SetScale(GameEngineWindow::GetScale());

	Hole_ = CreateRenderer("HoleTraps.bmp", 200);
	Hole_->SetIndex(LOD_);
}

void HoleTrap::Update()
{
	float DownTime = PlayLevel::PlayLevelStage->GetCurframeTime();
	if (0.0f >= DownTime)
	{
		int LODInterval = 607;
		if (false == PlayLevel::is2FrameUnit_)
		{

			if (LODInterval > GetPosition().y)
			{
				SetMove(DirVector_);
				++LOD_;
			}
		}
		else
		{
			if (LODInterval < GetPosition().y)
			{
				SetMove({ DirVector_.x , DirVector_.y - 14 });
				++LOD_;
			}
		}

		DownTime -= GameEngineTime::GetDeltaTime();
	}

	switch (LOD_)
	{
	case 0:
		Hole_->SetIndex(LOD_);
		break;

	case 1:
		Hole_->SetIndex(LOD_);
		break;

	case 2:
		Hole_->SetIndex(LOD_);
		break;

	case 3:
		Hole_->SetIndex(LOD_);
		break;

	case 4:
		Hole_->SetIndex(LOD_);
		break;

	case 5:
		Hole_->SetIndex(LOD_);
		break;

	case 6:
		Hole_->SetIndex(LOD_);
		break;

	case 7:
		Hole_->SetIndex(LOD_);
		break;

	case 9:
		Hole_->SetIndex(LOD_);
		break;

	default:
		LOD_ = 0;
		break;
	}

	if (768 < GetPosition().y)
	{
		Death();
	}
}

void HoleTrap::Render()
{
	
}