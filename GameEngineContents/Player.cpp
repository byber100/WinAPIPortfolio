#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineCollision.h>

Player* Player::MainPlayer = nullptr;

Player::Player() 
	: ForwardSpeed_(7.0f) // 0¿¡ µµ´ÞÇÏ¸é ¾Ö´Ï¸ØÃã
	, SideSpeed_(200.0f)
	, isJumping_(false)
	, BounceCnt_(0)
	, isBounce_(false)
	, isClear_(false)
	, ClearSoundOn_(false)
	, TriggerTime_(0)
	, DebugModeOn_(false)
	, HitInfo_(PlayerHit::HitLeft)
{
	ChangeState(MAX);
}

Player::~Player() 
{
}

void Player::DebugPlayerOn()
{
	{
		std::string UpdateText = std::to_string(BounceCnt_);
		DedugText_.Draw("BounceCnt: " + UpdateText, { 0,400 }, RGB(255, 255, 255), 0, 0);
	}
	{
		std::string xText = std::to_string(GetPosition().x);
		std::string yText = std::to_string(GetPosition().y);
		DedugText_.Draw("Position: " + xText + " , " + yText, {0,420}, RGB(255, 255, 255), 0, 0);
	}
	{
		std::string xText = std::to_string(Penguin_->GetPivot().x);
		std::string yText = std::to_string(Penguin_->GetPivot().y);
		DedugText_.Draw("Pivot: " + xText + " , " + yText, { 0,440 }, RGB(255, 255, 255), 0, 0);
	}
	{
		std::string UpdateText = std::to_string(isJumping_);
		DedugText_.Draw("isJump: " + UpdateText, { 0,460 }, RGB(255, 255, 255), 0, 0);
	}
}

void Player::JumpLoop()
{
	Penguin_->SetPivotMove(MoveDir_ * GameEngineTime::GetDeltaTime());
	MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 400.0f;

	if (-20 > Penguin_->GetPivot().y)
	{
		Shadow_->SetIndex(1);
		if (-40 > Penguin_->GetPivot().y)
		{
			Shadow_->SetIndex(2);
		}
	}
}

void Player::PushLoop()
{
	
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
			TakeHitStart();
			break;
		case Evasion:
			EvasionStart();
			break;
		case FallIn:
			FallInStart();
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
		TakeHitUpdate();
		break;
	case Evasion:
		TakeHitUpdate();
		break;
	case FallIn:
		FallInUpdate();
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
	Penguin_->CreateAnimation("Player.bmp", "PushLeft", 0, 0, 0, false);
	Penguin_->CreateAnimation("Player.bmp", "PushRight", 1, 1, 0, false);
	Penguin_->ChangeAnimation("Walk");

	Shadow_ = CreateRenderer("PlayerShadow.bmp",300);
	Shadow_->SetPivot({ 0,45 });
	Shadow_->SetIndex(0);
	
	PlayerLeftCol_ = CreateCollision("PlayerLeft", { 30,20 }, { -20,45 });
	PlayerRightCol_ = CreateCollision("PlayerRight", { 30,20 }, { 20,45 });
	PlayerJumpCol_ = CreateCollision("PlayerJump", { 48,64 });

	LevelRegist("Penguin");

	{
		GameEngineInput::GetInst()->CreateKey("MoveLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("MoveRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("Fast", VK_UP);
		GameEngineInput::GetInst()->CreateKey("DebugingFast", 'w');
		GameEngineInput::GetInst()->CreateKey("Slow", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("Jump", VK_SPACE);
		GameEngineInput::GetInst()->CreateKey("PlayerDebug", VK_TAB);
	}

	ChangeState(Move);
}

void Player::Update()
{
	StateUpdate();
	PlayerJumpCol_->SetPivot(Penguin_->GetPivot());
}

void Player::Render()
{
	//DebugRectRender();
	if (GameEngineInput::GetInst()->IsDown("PlayerDebug"))
	{
		if (false == DebugModeOn_)
		{
			DebugModeOn_ = true;
		}
		else
		{
			DebugModeOn_ = false;
		}
	}
	if (true == DebugModeOn_)
	{
		DebugPlayerOn();
	}
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
