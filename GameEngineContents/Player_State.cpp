#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>



void Player::IdleUpdate() 
{
	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::Move);
		return;
	}


	if (true == GameEngineInput::GetInst()->IsDown("Fire"))
	{
		ChangeState(PlayerState::Attck);
		return;
	}
}

void Player::AttackUpdate() 
{
	SetMove(MoveDir * GameEngineTime::GetDeltaTime());

	MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * 1000.0f;
}

void Player::MoveUpdate()
{

	if (true == GameEngineInput::GetInst()->IsDown("Fire"))
	{
		ChangeState(PlayerState::Attck);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		// °¡¼Ó·Â
		MoveDir += float4::RIGHT * GameEngineTime::GetDeltaTime() * AccSpeed_;
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir += float4::LEFT * GameEngineTime::GetDeltaTime() * AccSpeed_;
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		MoveDir += float4::UP * GameEngineTime::GetDeltaTime() * AccSpeed_;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * AccSpeed_;
	}

	if (0.3f <= MoveDir.Len2D())
	{
		MoveDir.Range2D(0.3f);
	}

	if (false == IsMoveKey())
	{
		MoveDir += -MoveDir * GameEngineTime::GetDeltaTime();

		if (0.005f >= MoveDir.Len2D())
		{
			MoveDir = float4::ZERO;
			return;
		}

		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		return;
	}

	SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);


}


//////////////////////////////////////// State

void Player::IdleStart() 
{

}

void Player::AttackStart() 
{

	MoveDir = float4::UP * 500.0f;
}

void Player::MoveStart()
{

}

