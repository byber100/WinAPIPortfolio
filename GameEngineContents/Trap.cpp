#include "Trap.h"
#include "PlayLevel.h"
#include "Player.h"
#include "PlayUI.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineSound.h>

// Static Var

// Static Func

// constructor destructor
Trap::Trap()
	: SetComplete_(false)
	, Event_(TrapEvent::None)
	, Spawn_(SpawnLoc::CENTER)
	, LOD_(0)
	, isFishLeft_(true)
	, FishState_(FishState::None)
	, Trap_(nullptr)
	, Seal_(nullptr)
	, Fish_(nullptr)
	, TrapCol_(nullptr)
	, TrapSubCol_(nullptr)
	, TrapCenterCol_(nullptr)
	, FishCol_(nullptr)
{
}

Trap::~Trap()
{
}

//member Func
void Trap::TrapSetting(TrapEvent _Event, SpawnLoc _Spawn)
{
	if (false == SetComplete_)
	{
		Event_ = _Event;
		Spawn_ = _Spawn;
	}
}

void Trap::Hit(const TrapEvent& _Event)
{
	switch (_Event)
	{
	case TrapEvent::Hole:
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
	case TrapEvent::Fish:
	{
		if (true == Player::MainPlayer->IsJump())
		{
			break;
		}
		Player::MainPlayer->ChangeState(PlayerState::TakeHit);
		break;
	}
	case TrapEvent::Flag:
	{
		if (true == Player::MainPlayer->IsJump())
		{
			break;
		}
		GameEngineSound::SoundPlayOneShot("SFX6.mp3");
		PlayUI::MainUI->AddScore(500);
		Death();
		break;
	}
	case TrapEvent::Crack:
	{
		if (true == Player::MainPlayer->IsJump())
		{
			break;
		}

		if (true == TrapCenterCol_->CollisionCheck("PlayerLeft", CollisionType::Rect, CollisionType::Rect) ||
			true == TrapCenterCol_->CollisionCheck("PlayerRight", CollisionType::Rect, CollisionType::Rect))
		{
			Player::MainPlayer->ChangeState(PlayerState::FallIn);
			break;
		}
		Player::MainPlayer->ChangeState(PlayerState::Evasion);
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
}

void Trap::Update()
{
	if (false == SetComplete_)
	{
		// 트랩이 내려가는 방향
		float yDown = 38;
		if (Event_ == TrapEvent::Crack)
		{
			switch (Spawn_)
			{
			case SpawnLoc::RIGHT:
				DirVector_ = { 12, yDown };
				break;
			case SpawnLoc::LEFT:
				DirVector_ = { -12, yDown };
				break;
			default:
				Death();
				return;
			}
		}
		else
		{
			switch (Spawn_)
			{
			case SpawnLoc::CENTER:
				DirVector_ = { 0, yDown };
				break;
			case SpawnLoc::RIGHT:
				DirVector_ = { 32, yDown };
				break;
			case SpawnLoc::LEFT:
				DirVector_ = { -32, yDown };
				break;
			default:
				break;
			}
		}

		// 트랩의 충돌 및 랜더링 초기화
		if (Event_ == TrapEvent::Flag)
		{
			Trap_ = CreateRenderer("ScoreFlag.bmp", 200);
			TrapCol_ = CreateCollision("Trap", { 24,32 });
		}
		else if (Event_ == TrapEvent::Crack)
		{
			Trap_ = CreateRenderer("Crack.bmp", 200);
			TrapCol_ = CreateCollision("LCrack", { 128,16 }, { -192,0 });
			TrapSubCol_ = CreateCollision("RCrack", { 128,16 }, { 144,0 });
			TrapCenterCol_ = CreateCollision("TrapCenter", { 164,16 }, { -24,0 });
		}
		else
		{
			if (Event_ == TrapEvent::Seal)
			{
				Seal_ = CreateRenderer("Seal.bmp");
				Seal_->SetIndex(0);
				Seal_->SetPivot({ 0,-48 });
			}
			Trap_ = CreateRenderer("Traps.bmp", 200);
			TrapCol_ = CreateCollision("Trap", { 96,16 });
			TrapCenterCol_ = CreateCollision("TrapCenter", { 4,16 });
		}

		Trap_->SetIndex(LOD_); // LOD 자동
		SetComplete_ = true;
	}

	if (Event_ == TrapEvent::None)
	{
		Death();
		return;
	}

	///////////////////////////////////////////////////////////////////////////////////////

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

	if (nullptr != Fish_)
	{
		if (FishState_ == FishState::Jump)
		{
			if (0 > Fish_->GetPivot().y)
			{
				FishDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 2000.0f;

				if (-30 < Fish_->GetPivot().x && 30 > Fish_->GetPivot().x)
				{
					if (Spawn_ == SpawnLoc::RIGHT || true == isFishLeft_)
					{
						FishDir_ += float4::LEFT * 2000.f * GameEngineTime::GetDeltaTime();
					}
					else if (Spawn_ == SpawnLoc::LEFT || false == isFishLeft_)
					{
						FishDir_ += float4::RIGHT * 2000.f * GameEngineTime::GetDeltaTime();
					}
				}
			}
			else
			{
				Fish_->SetPivot({ -1000,-1000 });
			}
		}
		else
		{
			FishDir_ = float4::UP * 700.f;
			FishState_ = FishState::Jump;
		}
		
		Fish_->SetPivotMove(FishDir_ * GameEngineTime::GetDeltaTime());
		FishCol_->SetPivot(Fish_->GetPivot());

		if (true == FishCol_->CollisionCheck("PlayerJump", CollisionType::Rect, CollisionType::Rect) &&
			true == Player::MainPlayer->IsJump())
		{
			GameEngineSound::SoundPlayOneShot("SFX7.mp3");
			PlayUI::MainUI->AddScore(300);
			Fish_->SetPivot({ -1000,1000 });
		}
	}

	if (nullptr == TrapSubCol_)
	{
		if (true == TrapCol_->CollisionCheck("PlayerLeft", CollisionType::Rect, CollisionType::Rect) ||
			true == TrapCol_->CollisionCheck("PlayerRight", CollisionType::Rect, CollisionType::Rect))
		{
			Hit(Event_);
		}
	}
	else
	{
		if (true == TrapSubCol_->CollisionCheck("PlayerLeft", CollisionType::Rect, CollisionType::Rect) ||
			true == TrapCol_->CollisionCheck("PlayerRight", CollisionType::Rect, CollisionType::Rect))
		{
			Hit(Event_);
		}
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
		if (Event_ == TrapEvent::Seal)
		{
			Seal_->SetOrder(201);
		}
		else if (Event_ == TrapEvent::Fish)
		{
			if (FishState_ == FishState::None)
			{
				Fish_ = CreateRenderer(201);
				Fish_->CreateAnimation("Fish.bmp", "L_Fish", 0, 3, 0.2f, false);
				Fish_->CreateAnimation("Fish.bmp", "R_Fish", 4, 7, 0.2f, false);
				FishCol_ = CreateCollision("Fish", { 32,32 });

				if (Spawn_ == SpawnLoc::RIGHT)
				{
					Fish_->ChangeAnimation("L_Fish");
				}
				else if (Spawn_ == SpawnLoc::LEFT)
				{
					Fish_->ChangeAnimation("R_Fish");
				}
				else if (Spawn_ == SpawnLoc::CENTER)
				{
					GameEngineRandom NewRandom;

					switch (NewRandom.RandomInt(0, 1))
					{
					case 0:
						Fish_->ChangeAnimation("L_Fish");
						break;
					default:
						isFishLeft_ = false;
						Fish_->ChangeAnimation("R_Fish");
						break;
					}
				}
				FishState_ = FishState::Create;
			}
		}
		Trap_->SetIndex(LOD_);
		break;

	case 3:
		Trap_->SetIndex(LOD_);
		break;

	case 4:
		if (nullptr != Seal_)
		{
			Seal_->SetIndex(1);
		}
		Trap_->SetIndex(LOD_);
		break;

	case 5:
		Trap_->SetIndex(LOD_);
		break;

	case 6:
		if (nullptr != Seal_)
		{
			Seal_->SetIndex(2);
		}
		Trap_->SetIndex(LOD_);
		break;

	case 7:
		if (nullptr != Seal_)
		{
			Seal_->SetOrder(302);
		}
		if (Event_ == TrapEvent::Crack)
		{
			LOD_ = 6;
			PlayUI::MainUI->AddScore(30);
			Death();
		}
		else if (Event_ == TrapEvent::Flag)
		{
			Trap_->SetOrder(301);
		}
		Trap_->SetIndex(LOD_);
		break;

	default:
		LOD_ = 0;
		break;
	}
}