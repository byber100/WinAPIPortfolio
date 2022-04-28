#include "PlayLevel.h"
#include "ContentsEnum.h"
#include "Player.h"
#include "PlayUI.h"
#include "PlayBack.h"
#include "RandomStage.h"
#include "HoleTrap.h"
#include "House.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>

PlayLevel* PlayLevel::PlayLevelStage = nullptr;
int PlayLevel::FrameCount = 64; // Start Stage Stay Time
bool PlayLevel::is2FrameUnit_ = false;

PlayLevel::PlayLevel() 
	: UnitSecond_(1.0f)
{
}

PlayLevel::~PlayLevel() 
{
}

float PlayLevel::GetLevelInterTime()
{
	if (nullptr == Player::MainPlayer)
	{
		MsgBoxAssert("플레이어 정보가 없습니다.");
	}

	float PlayerSpeed = Player::MainPlayer->GetForwardSpeed();
	PlayerSpeed = 1 / PlayerSpeed;
	return PlayerSpeed;
}

void PlayLevel::Loading()
{
	if (nullptr == Player::MainPlayer)
	{
		Player::MainPlayer = CreateActor<Player>((int)ORDER::PLAYER, "MainPlayer");
	}

	StageInfo_ = CreateActor<RandomStage>((int)ORDER::BACKGROUND);
	CreateActor<PlayBack>((int)ORDER::BACKGROUND);

	PlayLevelStage = this;

	// Test///////////////////////////////////////////////////
	GameEngineInput::GetInst()->CreateKey("TestTrap", 'Q');
	GameEngineInput::GetInst()->CreateKey("ToPrevLevel", '1');

	if (nullptr == Player::MainPlayer ||
		nullptr == StageInfo_ ||
		nullptr == PlayUI::MainUI)
	{
		MsgBoxAssert("필수 액터 정보가 없습니다.")
	}
}

void PlayLevel::Update() 
{
	//Time -= GameEngineTime::GetDeltaTime();

	//if (0 >= Time)
	//{
	//	BgmPlayer.Stop();
	//}

	// Test///////////////////////////////////////////////////
	if (GameEngineInput::GetInst()->IsDown("ToPrevLevel"))
	{
		Player::MainPlayer->SetForwardSpeed(7.f);
		GameEngine::GetInst().ChangeLevel("Map");
	}
	if (GameEngineInput::GetInst()->IsDown("TestTrap"))
	{
		CreateActor<HoleTrap>((int)ORDER::TRAP);
	}

	int t = PlayUI::MainUI->GetCountTime();
	if (0 != t)
	{
		if (0 < UnitSecond_)
		{
			UnitSecond_ -= GameEngineTime::GetInst()->GetDeltaTime();
		}
		else
		{
			UnitSecond_ = 1.0f;
			
			--t;
			PlayUI::MainUI->SetCountTime(t);
		}
	}
	else
	{
		Player::MainPlayer->ChangeState(PlayerState::Pause);
	}

	float LevelInterTime = PlayLevelStage->GetLevelInterTime();

	if (0.0f >= CurframeTime_)
	{
		++FrameUnitCount_;
		is2FrameUnit_ = false;
		CurframeTime_ = LevelInterTime;
		if (0 != PlayUI::RestDistance_)
		{
			--PlayUI::RestDistance_;
		}

		if (2 == FrameUnitCount_)
		{
			--FrameCount;
			FrameUnitCount_ = 0;
			is2FrameUnit_ = true;

			StageInfo_->MountainFrame();
			//CreateActor<HoleTrap>((int)ORDER::TRAP);
		}
	}
	CurframeTime_ -= GameEngineTime::GetDeltaTime();
	
}

void PlayLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	// Player->SetPosition();

	// BgmPlayer = GameEngineSound::SoundPlayControl("BGM.MP3");

	//GameEngineSound::SoundPlayOneShot("vo_shk.mp3");
	//Time = 5.0f;

}

void PlayLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	//if (_NextLevel->GetNameCopy() != "Title")
	//{
	//	PlayerInfo_->NextLevelOn();
	//}

	PlayUI::MainUI->NextLevelOn();
}
