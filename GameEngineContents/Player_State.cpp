#include "Player.h"
#include "PlayUI.h"
#include "House.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>


void Player::MoveStart()
{
	Penguin_->ChangeAnimation("Walk");
	Penguin_->PauseOff();
}

void Player::JumpStart()
{
	GameEngineSound::SoundPlayOneShot("SFX2.mp3");
	Penguin_->ChangeAnimation("Jump");
	MoveDir_ = float4::UP * 200.0f;
	isJumping_ = true;
}

void Player::PauseStart()
{
	Penguin_->PauseOn();
	ForwardSpeed_ = 0.0f;
	TriggerTime_ = 0;

	if (0 == PlayUI::MainUI->GetCountTime())
	{
		PlayBGM_.Stop();
		PlayBGM_= GameEngineSound::SoundPlayControl("TimeoverBGM.mp3");
	}
}

void Player::ClearStart()
{
	isClear_ = true;
	TriggerTime_ = 0;
	ForwardSpeed_ = 0.0f;
	Penguin_->SetPivot(float4::ZERO);
	Penguin_->ChangeAnimation("ClearWalk");
}

void Player::CeremonyStart()
{
	Penguin_->ChangeAnimation("Ceremony");
	TriggerTime_ = 1.4f;
}

void Player::TakeHitStart()
{
	GameEngineSound::SoundPlayOneShot("SFX3.mp3");
	ForwardSpeed_ = 4.0f;

	if (true == PlayerLeftCol_->CollisionCheck("TrapCenter"))
	{
		Penguin_->ChangeAnimation("PushRight");
		HitInfo_ = PlayerHit::HitRight;
	}
	else if (true == PlayerRightCol_->CollisionCheck("TrapCenter"))
	{
		Penguin_->ChangeAnimation("PushLeft");
		HitInfo_ = PlayerHit::HitLeft;
	}
	else if (true == PlayerLeftCol_->CollisionCheck("Trap")) // 오른쪽으로 밀림
	{
		Penguin_->ChangeAnimation("PushRight");
		HitInfo_ = PlayerHit::HitRight;
	}
	else if (true == PlayerRightCol_->CollisionCheck("Trap")) // 왼쪽으로 밀림
	{
		Penguin_->ChangeAnimation("PushLeft");
		HitInfo_ = PlayerHit::HitLeft;
	}
}

void Player::FallInStart()
{

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Player::MoveUpdate()
{
	if (0 >= PlayUI::RestDistance_)
	{
		ForwardSpeed_ = 0.0f;
		return;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Jump"))
	{
		if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
		{
			ChangeState(PlayerState::JumpL);
			return;
		}
		if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
		{
			ChangeState(PlayerState::JumpR);
			return;
		}
		ChangeState(PlayerState::Jump);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		if (288 < GetPosition().ix())
		{
			SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * SideSpeed_);
		}
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		if (736 > GetPosition().ix())
		{
			SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * SideSpeed_);
		}
	}
	if (true == GameEngineInput::GetInst()->IsPress("Fast"))
	{
		if (18.0f > ForwardSpeed_)
		{
			ForwardSpeed_ = (ForwardSpeed_ + 10.0f * GameEngineTime::GetDeltaTime());
		}
	}
	if (true == GameEngineInput::GetInst()->IsPress("Slow"))
	{
		if (4.0f < ForwardSpeed_)
		{
			ForwardSpeed_ = (ForwardSpeed_ - 10.0f * GameEngineTime::GetDeltaTime());
		}
	}
	if (true == GameEngineInput::GetInst()->IsDown("DebugingFast"))
	{
		if (99 > ForwardSpeed_)
		{
			ForwardSpeed_ = 200;
		}
		else
		{
			ForwardSpeed_ = 7;
		}
	}
}

void Player::JumpUpdate()
{
	if (1 > Penguin_->GetPivot().iy())
	{
		JumpLoop();
	}
	else
	{
		Penguin_->SetPivot(float4::ZERO);
		Penguin_->ChangeAnimation("Walk");
		Shadow_->SetIndex(0);
		isJumping_ = false;
		ChangeState(PlayerState::Move);
	}
}

void Player::JumpLUpdate()
{
	if (1 > Penguin_->GetPivot().iy())
	{
		JumpLoop();

		if (288 < GetPosition().ix())
		{
			SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * SideSpeed_ * 0.8f);
		}
	}
	else
	{
		Penguin_->SetPivot(float4::ZERO);
		Penguin_->ChangeAnimation("Walk");
		Shadow_->SetIndex(0);
		isJumping_ = false;
		ChangeState(PlayerState::Move);
	}
}

void Player::JumpRUpdate()
{
	if (1 > Penguin_->GetPivot().iy())
	{
		JumpLoop();

		if (736 > GetPosition().ix())
		{
			SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * SideSpeed_ * 0.8f);
		}
	}
	else
	{
		Penguin_->SetPivot(float4::ZERO);
		Penguin_->ChangeAnimation("Walk");
		Shadow_->SetIndex(0);
		isJumping_ = false;
		ChangeState(PlayerState::Move);
	} 
}

void Player::PauseUpdate()
{
	if (0 == PlayUI::MainUI->GetCountTime())
	{
		TriggerTime_ += GameEngineTime::GetInst()->GetDeltaTime();
		if (5 < TriggerTime_)
		{
			PlayBGM_.Stop();
		}
	}
}

void Player::ClearUpdate()
{
	float y = 564;

	if (512 - 8 < GetPosition().x && 512 + 8 > GetPosition().x &&
		y - 8 < GetPosition().y && y + 8 > GetPosition().y)
	{
		Penguin_->ChangeAnimation("Clear");
		House::isFlagUp_ = true;

		if (false == ClearSoundOn_)
		{
			PlayBGM_.Stop();
			GameEngineSound::SoundPlayOneShot("ClearBGM.mp3");
			ClearSoundOn_ = true;
			TriggerTime_ = 4.6f;
		}

		TriggerTime_ -= GameEngineTime::GetInst()->GetDeltaTime();
		if (0 > TriggerTime_)
		{
			ChangeState(PlayerState::Ceremony);
		}
		return;
	}

	TriggerTime_ += 0.02f * GameEngineTime::GetInst()->GetDeltaTime();
	float4 ClearMove = float4::LerpLimit(GetPosition(), { 512 , y }, TriggerTime_);
	SetPosition(ClearMove);
}

void Player::CeremonyUpdate()
{
	TriggerTime_ -= GameEngineTime::GetInst()->GetDeltaTime();
	if (0 > TriggerTime_)
	{
		PlayUI::MainUI->StartTimeScore();
	}
}

void Player::TakeHitUpdate()
{
	if (false == isBounce_)
	{
		isBounce_ = true;
		MoveDir_ = float4::UP * (200.0f -20 * BounceCnt_);
	}
	
	Penguin_->SetPivotMove(MoveDir_ * GameEngineTime::GetDeltaTime());
	MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 1000.0f;

	if (0 < Penguin_->GetPivot().y)
	{
		if (true == isBounce_)
		{
			GameEngineSound::SoundPlayOneShot("SFX4.mp3");
			Penguin_->SetPivot(float4::ZERO);
			++BounceCnt_;
			isBounce_ = false;
		}
		if (4 <= BounceCnt_)
		{
			BounceCnt_ = 0;
			ChangeState(PlayerState::Move);
		}
	}

	if (PlayerHit::HitLeft == HitInfo_) // 왼쪽 밀림
	{
		if (288 < GetPosition().x)
		{
			SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * 150.f);
		}
	}
	else
	{
		if (736 > GetPosition().x)
		{
			SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 150.f);
		}
	}
	
}

void Player::FallInUpdate()
{

}