#include "Trap.h"
#include "PlayLevel.h"
#include "Player.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineCollision.h>

// Static Var

// Static Func

// constructor destructor
Trap::Trap()
	: Event_(TrapEvent::None)
	, Spawn_(SpawnLoc::CENTER)
	, LOD_(0)
	, Trap_(nullptr)
	, Object_(nullptr)
	, TrapCol_(nullptr)
	, TrapCenterCol_(nullptr)
	, L_FishCol_(nullptr)
	, R_FishCol_(nullptr)

{
}

Trap::~Trap()
{
}

//member Func
void Trap::Hit(const TrapEvent& _Event)
{
	switch (_Event)
	{
	case TrapEvent::None:
	{
		if (true == Player::MainPlayer->IsJump())
		{
			break;
		}
		Player::MainPlayer->ChangeState(PlayerState::TakeHit);
		break;
	}
	case TrapEvent::Seal:
	{
		Player::MainPlayer->ChangeState(PlayerState::TakeHit);
		break;
	}
	case TrapEvent::Flag:
	{
		break;
	}
	case TrapEvent::Crack:
	{
		if (true == Player::MainPlayer->IsJump())
		{
			break;
		}

		if (true == TrapCol_->CollisionCheck("PlayerLeft", CollisionType::Rect, CollisionType::Rect) &&
			true == TrapCol_->CollisionCheck("PlayerRight", CollisionType::Rect, CollisionType::Rect))
		{
			Player::MainPlayer->ChangeState(PlayerState::FallIn);
			break;
		}
		Player::MainPlayer->ChangeState(PlayerState::TakeHit);
		break;
	}
	default:
		break;
	}
}

void Trap::Start()
{
	float x = GameEngineWindow::GetScale().Half().x;
	float y = GameEngineWindow::GetScale().Half().y;

	SetPosition({ x , y + 32 });
	SetScale(GameEngineWindow::GetScale());

	GameEngineRandom NewRandom;

	switch (NewRandom.RandomInt(1, 1)) // 임시로 None으로
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
		Event_ = TrapEvent::Crack;
		break;
	}

	float yDown = 38;
	switch (NewRandom.RandomInt(0, 0))
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
	TrapCol_ = CreateCollision("Trap", { 96,16 });
	TrapCenterCol_ = CreateCollision("TrapCenter", { 4,16 });

	Trap_->SetIndex(LOD_);
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

	if (true == TrapCol_->CollisionCheck("PlayerLeft", CollisionType::Rect, CollisionType::Rect) ||
		true == TrapCol_->CollisionCheck("PlayerRight", CollisionType::Rect, CollisionType::Rect))
	{
		Hit(Event_);
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
		Object_ = CreateRenderer("Seal.bmp", 201);
		Object_->SetIndex(0);
		Object_->SetPivot({ 0,-48 });
		break;

	case 3:
		Trap_->SetIndex(LOD_);
		break;

	case 4:
		if (nullptr != Object_)
		{
			Object_->SetIndex(1);
		}
		Trap_->SetIndex(LOD_);
		break;

	case 5:
		Trap_->SetIndex(LOD_);
		break;

	case 6:
		if (nullptr != Object_)
		{
			Object_->SetIndex(2);
		}
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