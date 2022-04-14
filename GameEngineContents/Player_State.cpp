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

}

void Player::IdleUpdate()
{
	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::Move);
		return;
	}
}

void Player::MoveUpdate()
{
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
		if (110.0f > ForwardSpeed_)
		{
			ForwardSpeed_ = (ForwardSpeed_ + 10.0f * GameEngineTime::GetDeltaTime());
		}
	}
	if (true == GameEngineInput::GetInst()->IsPress("Slow"))
	{
		if (1.0f < ForwardSpeed_)
		{
			ForwardSpeed_ = (ForwardSpeed_ - 10.0f * GameEngineTime::GetDeltaTime());
		}
	}
}

void Player::JumpUpdate()
{

}