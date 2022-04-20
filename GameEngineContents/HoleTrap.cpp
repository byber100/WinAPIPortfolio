#include "HoleTrap.h"
#include "PlayLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>

// Static Var

// Static Func

// constructor destructor
HoleTrap::HoleTrap()
	: TrapLOD_(0)
	, Hole_(nullptr)
{
	GameEngineRandom NewRandom;
	float yDown = 38;

	switch (NewRandom.RandomInt(0, 4))
	{
	case 0:
		DirVector_ = { 0, yDown };
		break;
	case 1:
		DirVector_ = { 21, yDown };
		break;
	case 2:
		DirVector_ = { 42, yDown };
		break;
	case 3:
		DirVector_ = { -21, yDown };
		break;
	case 4:
		DirVector_ = { -42, yDown };
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
	float x = static_cast<int>(GameEngineWindow::GetScale().Half().ix());
	float y = static_cast<int>(GameEngineWindow::GetScale().Half().iy());

	SetPosition({ x , y + 32 });
	SetScale(GameEngineWindow::GetScale());

	Hole_ = CreateRenderer("HoleTraps.bmp", 200);
	Hole_->SetIndex(TrapLOD_);
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
				++TrapLOD_;
			}
		}
		else
		{
			if (LODInterval < GetPosition().y)
			{
				SetMove({ DirVector_.x , DirVector_.y - 14 });
				++TrapLOD_;
			}
		}

		DownTime -= GameEngineTime::GetDeltaTime();
	}

	switch (TrapLOD_)
	{
	case 0:
		Hole_->SetIndex(TrapLOD_);
		break;

	case 1:
		Hole_->SetIndex(TrapLOD_);
		break;

	case 2:
		Hole_->SetIndex(TrapLOD_);
		break;

	case 3:
		Hole_->SetIndex(TrapLOD_);
		break;

	case 4:
		Hole_->SetIndex(TrapLOD_);
		break;

	case 5:
		Hole_->SetIndex(TrapLOD_);
		break;

	case 6:
		Hole_->SetIndex(TrapLOD_);
		break;

	case 7:
		Hole_->SetIndex(TrapLOD_);
		break;

	case 9:
		Hole_->SetIndex(TrapLOD_);
		break;

	default:
		TrapLOD_ = 0;
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