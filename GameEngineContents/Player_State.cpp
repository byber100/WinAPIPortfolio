#include "Player.h"
#include "PlayUI.h"
#include "House.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>


void Player::MoveStart()
{
	Penguin_->ChangeAnimation("Walk");
	Penguin_->PauseOff();
}

void Player::JumpStart()
{
	GameEngineSound::SoundPlayOneShot("SFX2.mp3");
	Penguin_->ChangeAnimation("Jump");
	JumpDir_ = float4::UP * 200.0f;
}

void Player::PauseStart()
{
	Penguin_->PauseOn();
	ForwardSpeed_ = 0.0f;
}

void Player::ClearStart()
{
	isClear_ = true;
	ClearTime_ = 0;
	ForwardSpeed_ = 0.0f;
	Penguin_->SetPivot(float4::ZERO);
	Penguin_->ChangeAnimation("ClearWalk");
}

void Player::CeremonyStart()
{
	Penguin_->ChangeAnimation("Ceremony");
	ClearTime_ = 1.4f;
}

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
		if (14.0f > ForwardSpeed_)
		{
			ForwardSpeed_ = (ForwardSpeed_ + 10.0f * GameEngineTime::GetDeltaTime());
		}
	}
	if (true == GameEngineInput::GetInst()->IsPress("Slow"))
	{
		if (2.0f < ForwardSpeed_)
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
			ClearTime_ = 4.6f;
		}

		ClearTime_ -= GameEngineTime::GetInst()->GetDeltaTime();
		if (0 > ClearTime_)
		{
			ChangeState(PlayerState::Ceremony);
		}
		return;
	}

	ClearTime_ += 0.02f * GameEngineTime::GetInst()->GetDeltaTime();
	float4 ClearMove = float4::LerpLimit(GetPosition(), { 512 , y }, ClearTime_);
	SetPosition(ClearMove);
}

void Player::CeremonyUpdate()
{
	ClearTime_ -= GameEngineTime::GetInst()->GetDeltaTime();
	if (0 > ClearTime_)
	{
		PlayUI::MainUI->StartTimeScore();
	}
}
