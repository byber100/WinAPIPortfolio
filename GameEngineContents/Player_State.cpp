#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>


void Player::IdleStart()
{

}

void Player::MoveStart()
{

}

void Player::JumpStart()
{
	JumpDir_ = float4::UP * 500.0f;
}

void Player::IdleUpdate()
{
	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::Move);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Jump"))
	{
		ChangeState(PlayerState::Jump);
		return;
	}
}

void Player::MoveUpdate()
{
	if (true == GameEngineInput::GetInst()->IsDown("Jump"))
	{
		ChangeState(PlayerState::Jump);
		return;
	}

	Render_->ChangeAnimation("Walk");

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		if (288 < GetPosition().ix())
		{
			SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * 250.0f);
		}
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		if (736 > GetPosition().ix())
		{
			SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 250.0f);
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
		Render_->ChangeAnimation("Jump");
		Render_->SetPivotMove(JumpDir_ * GameEngineTime::GetDeltaTime());

		JumpDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 1000.0f;
	}
	else
	{
		Render_->SetPivot(float4::ZERO);
   		Render_->ChangeAnimation("Walk");
		isJumping_ = false;
		ChangeState(PlayerState::Move);
	}
}