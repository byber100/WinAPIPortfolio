#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>


Player::Player() 
	: ForwardSpeed_(100.0f)
	, SideSpeed_(300.0f)
{
}

Player::~Player() 
{
}

// 아무키도 눌리지 않았다면 false
// 아무키든 눌렸다면 true
bool Player::IsMoveKey()
{
	if (false == GameEngineInput::GetInst()->IsPress("MoveLeft") &&
		false == GameEngineInput::GetInst()->IsPress("MoveRight") &&
		false == GameEngineInput::GetInst()->IsPress("Fast") &&
		false == GameEngineInput::GetInst()->IsPress("Slow"))
	{
		return false;
	}

	return true;
}

void Player::ChangeState(PlayerState _State)
{
	if (CurState_ != _State)
	{
		switch (_State)
		{
		case Idle:
			IdleStart();
			break;
		case Move:
			MoveStart();
			break;
		case Jump:
			JumpStart();
			break;
		case TakeHit:
			break;
		case Clear:
			break;
		case Max:
			break;
		default:
			break;
		}
	}

	CurState_ = _State;
}

void Player::StateUpdate()
{
	switch (CurState_)
	{
	case Idle:
		IdleUpdate();
		break;
	case Move:
		MoveUpdate();
		break;
	case Jump:
		JumpUpdate();
		break;
	case TakeHit:
		break;
	case Clear:
		break;
	case Max:
		break;
	default:
		break;
	}
}

void Player::Start() 
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 5, 5 });

	Render_ = CreateRenderer(300);
	Render_->SetPivot({ 0, 235 });
	Render_->CreateAnimation("Player.bmp", "Walk", 2, 5, 0.13f);
	Render_->ChangeAnimation("Walk");

	LevelRegist("Penguin");

	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("Fast", 'W');
		GameEngineInput::GetInst()->CreateKey("Slow", 'S');
		GameEngineInput::GetInst()->CreateKey("Jump", VK_SPACE);
	}
}

void Player::Update()
{
	StateUpdate();
}

void Player::Render()
{
	DebugRectRender();
	Render_->Render();
}
