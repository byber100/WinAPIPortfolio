#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineSound.h>

Player* Player::MainPlayer = nullptr;

Player::Player() 
	: ForwardSpeed_(7.0f) // 0¿¡ µµ´ÞÇÏ¸é ¾Ö´Ï¸ØÃã
	, SideSpeed_(200.0f)
	, isJumping_(false)
	, isClear_(false)
	, ClearSoundOn_(false)
	, TriggerTime_(0)
{
	ChangeState(MAX);
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
			ClearStart();
			break;
		case Ceremony:
			CeremonyStart();
			break;
		case Pause:
			PauseStart();
			break;
		case MAX:
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
		ClearUpdate();
		break;
	case Ceremony:
		CeremonyUpdate();
		break;
	case Pause:
		PauseUpdate();
		break;
	case MAX:
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
	Penguin_->CreateAnimation("Player.bmp", "ClearWalk", 2, 5, 0.05f);
	Penguin_->CreateAnimation("Player.bmp", "Jump", 9, 10, 0.1f);
	Penguin_->CreateAnimation("Player.bmp", "Clear", 11, 12, 0.5f);
	Penguin_->CreateAnimation("Player.bmp", "Ceremony", 13, 13, 0, false);
	Penguin_->ChangeAnimation("Walk");

	Shadow_ = CreateRenderer("PlayerShadow.bmp",300);
	Shadow_->SetPivot({ 0,45 });
	Shadow_->SetIndex(0);

	PlayerCol_ = CreateCollision("PlayerCol", { 100,30 }, { 0,40 });

	LevelRegist("Penguin");

	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("MoveRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("Fast", VK_UP);
		GameEngineInput::GetInst()->CreateKey("DebugingFast", 'w');
		GameEngineInput::GetInst()->CreateKey("Slow", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("Jump", VK_SPACE);
	}

	ChangeState(Move);
}

void Player::Update()
{
	StateUpdate();
}

void Player::Render()
{
	//DebugRectRender();
}

void Player::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	PlayBGM_ = GameEngineSound::SoundPlayControl("PlayBGM.mp3");
	ForwardSpeed_ = 7.f;
	SetPosition({ 512 , 619 });
	Penguin_->SetPivot({ 0, 0 });
	ChangeState(Move);
	isClear_ = false;
	ClearSoundOn_ = false;
}

void Player::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	PlayBGM_.Stop();
}
