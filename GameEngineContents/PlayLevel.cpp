#include "PlayLevel.h"
#include "Player.h"
#include "PlayUI.h"
#include "RandomStage.h"
#include "HoleTrap.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineInput.h>

PlayLevel* PlayLevel::PlayLevelStage = nullptr;
int PlayLevel::FrameCount = 64; // Start Stage Stay Time
bool PlayLevel::is2FrameUnit_ = false;

enum class ORDER
{
	BACKGROUND,
	PLAYER,
	UI
};

PlayLevel::PlayLevel() 
	: PlayerInfo_(nullptr)
	, UnitSecond_(1.0f)
{
}

PlayLevel::~PlayLevel() 
{
}

float PlayLevel::GetLevelInterTime()
{
	if (nullptr == PlayerInfo_)
	{
		MsgBoxAssert("플레이어 정보가 없습니다.");
	}

	float PlayerSpeed = PlayerInfo_->GetForwardSpeed();
	PlayerSpeed = 1 / PlayerSpeed;
	return PlayerSpeed;
}

void PlayLevel::Loading()
{
	
	StageInfo_ = CreateActor<RandomStage>(0);
	PlayerInfo_ = CreateActor<Player>(1);
	UI_ = CreateActor<PlayUI>(3);

	PlayLevelStage = this;

	// Test///////////////////////////////////////////////////
	GameEngineInput::GetInst()->CreateKey("TestTrap", 'Q');

	if (nullptr == PlayerInfo_ ||
		nullptr == StageInfo_ ||
		nullptr == UI_)
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
	if (GameEngineInput::GetInst()->IsDown("TestTrap"))
	{
		CreateActor<HoleTrap>(2);
	}

	int t = UI_->GetCountTime();
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
			UI_->SetCountTime(t);
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
				//CreateActor<HoleTrap>(2);
			}
		}
		CurframeTime_ -= GameEngineTime::GetDeltaTime();
	}
	else
	{
		PlayerInfo_->ChangeState(PlayerState::Pause);
	}

	
}
void PlayLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	//if (_NextLevel->GetNameCopy() != "Title")
	//{
	//	PlayerInfo_->NextLevelOn();
	//}
}

void PlayLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	// Player->SetPosition();

	// BgmPlayer = GameEngineSound::SoundPlayControl("BGM.MP3");

	//GameEngineSound::SoundPlayOneShot("vo_shk.mp3");
	//Time = 5.0f;

}