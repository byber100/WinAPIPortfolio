#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>


Player::Player() 
	: ForwardSpeed_(8.0f) // 0¿¡ µµ´ÞÇÏ¸é ¾Ö´Ï¸ØÃã
	, SideSpeed_(200.0f)
	, isJumping_(false)
{
}

Player::~Player() 
{
}

void Player::JumpLoop()
{
	Penguin_->SetPivotMove(JumpDir_ * GameEngineTime::GetDeltaTime());
	JumpDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 400.0f;

	if (-20 > Penguin_->GetPivot().y)
	{
		Shadow_->SetIndex(1);
		if (-40 > Penguin_->GetPivot().y)
		{
			Shadow_->SetIndex(2);
		}
	}
	
}

void Player::ChangeState(PlayerState _State)
{
	if (CurState_ != _State)
	{
		switch (_State)
		{
		case Move:
			MoveStart();
			break;
		case Jump:
			JumpStart();
			break;
		case JumpL:
			JumpStart();
			break;
		case JumpR:
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
	case Move:
		MoveUpdate();
		break;
	case Jump:
		JumpUpdate();
		break;
	case JumpL:
		JumpLUpdate();
		break;
	case JumpR:
		JumpRUpdate();
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
	SetPosition({ 512 , 619 });
	SetScale({ 80, 90 });

	Penguin_ = CreateRenderer(301);
	Penguin_->SetPivot({ 0, 0 });
	Penguin_->CreateAnimation("Player.bmp", "Walk", 2, 5, 0.13f);
	Penguin_->CreateAnimation("Player.bmp", "Jump", 9, 10, 0.1f);
	Penguin_->ChangeAnimation("Walk");

	Shadow_ = CreateRenderer("PlayerShadow.bmp",300);
	Shadow_->SetPivot({ 0,45 });
	Shadow_->SetIndex(0);

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
	//DebugRectRender();
}
