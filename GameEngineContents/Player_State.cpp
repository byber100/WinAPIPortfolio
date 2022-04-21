#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>


void Player::MoveStart()
{
	Render_->ChangeAnimation("Walk");
}

void Player::JumpStart()
{
	Render_->ChangeAnimation("Jump");
	JumpDir_ = float4::UP * 200.0f;
}

void Player::MoveUpdate()
{
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
}

void Player::JumpUpdate()
{
	if (1 > Render_->GetPivot().iy())
	{
		Render_->SetPivotMove(JumpDir_ * GameEngineTime::GetDeltaTime());
		JumpDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 400.0f;
	}
	else
	{
		Render_->SetPivot(float4::ZERO);
   		Render_->ChangeAnimation("Walk");
		isJumping_ = false;
		ChangeState(PlayerState::Move);
	}
}

void Player::JumpLUpdate()
{
	if (1 > Render_->GetPivot().iy())
	{
		Render_->SetPivotMove(JumpDir_ * GameEngineTime::GetDeltaTime());
		JumpDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 400.0f;

		if (288 < GetPosition().ix())
		{
			SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * SideSpeed_ * 0.8f);
		}
	}
	else
	{
		Render_->SetPivot(float4::ZERO);
		Render_->ChangeAnimation("Walk");
		isJumping_ = false;
		ChangeState(PlayerState::Move);
	}
}

void Player::JumpRUpdate()
{
	if (1 > Render_->GetPivot().iy())
	{
		Render_->SetPivotMove(JumpDir_ * GameEngineTime::GetDeltaTime());
		JumpDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 400.0f;

		if (736 > GetPosition().ix())
		{
			SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * SideSpeed_ * 0.8f);
		}
	}
	else
	{
		Render_->SetPivot(float4::ZERO);
		Render_->ChangeAnimation("Walk");
		isJumping_ = false;
		ChangeState(PlayerState::Move);
	}
}