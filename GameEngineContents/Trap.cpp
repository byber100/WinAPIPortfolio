#include "Trap.h"
#include "PlayLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>

// Static Var

// Static Func

// constructor destructor
Trap::Trap()
	: Event_(TrapEvent::None)
	, Spawn_(SpawnLoc::CENTER)
	, LOD_(0)
	, Trap_(nullptr)
	, TrapCol_(nullptr)
	, L_FishCol_(nullptr)
	, R_FishCol_(nullptr)

{
}

Trap::~Trap()
{
}

//member Func
void Trap::Start()
{
	float x = GameEngineWindow::GetScale().Half().x;
	float y = GameEngineWindow::GetScale().Half().y;

	SetPosition({ x , y + 32 });
	SetScale(GameEngineWindow::GetScale());

	GameEngineRandom NewRandom;

	switch (NewRandom.RandomInt(0, 0)) // 임시로 None으로
	{
	case 0:
		Event_ = TrapEvent::None;
		break;
	case 1:
		Event_ = TrapEvent::Seal;
		break;
	case 2:
		Event_ = TrapEvent::Fish;
		break;
	case 3:
		Event_ = TrapEvent::Flag;
		break;
	default:
		break;
	}

	float yDown = 38;
	switch (NewRandom.RandomInt(0, 2))
	{
	case 0:
		DirVector_ = { 0, yDown };
		Spawn_ = SpawnLoc::CENTER;
		break;
	case 1:
		DirVector_ = { 32, yDown };
		Spawn_ = SpawnLoc::RIGHT;
		break;
	case 2:
		DirVector_ = { -32, yDown };
		Spawn_ = SpawnLoc::LEFT;
		break;
	default:
		Death();
		break;
	}

	Trap_ = CreateRenderer("Traps.bmp", 200);

	Trap_->SetIndex(LOD_);
	//TrapCol_=CreateCollision("TrapCol",)
}

void Trap::Update()
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
				SetMove({ DirVector_.x , DirVector_.y - 18 });

				if (680 < GetPosition().y)
				{
					++LOD_;
				}
			}
		}
		DownTime -= GameEngineTime::GetDeltaTime();
	}

	if (768 < GetPosition().y)
	{
		Death();
	}
}

void Trap::Render()
{
	switch (LOD_)
	{
	case 0:
		Trap_->SetIndex(LOD_);
		break;

	case 1:
		Trap_->SetIndex(LOD_);
		break;

	case 2:
		Trap_->SetIndex(LOD_);
		break;

	case 3:
		Trap_->SetIndex(LOD_);
		break;

	case 4:
		Trap_->SetIndex(LOD_);
		break;

	case 5:
		Trap_->SetIndex(LOD_);
		break;

	case 6:
		Trap_->SetIndex(LOD_);
		break;

	case 7:
		Trap_->SetIndex(LOD_);
		break;

	default:
		LOD_ = 0;
		break;
	}
}