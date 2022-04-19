#include "PlayLevel.h"
#include "Player.h"
#include "PlayUI.h"
#include "RandomStage.h"
#include "HoleTrap.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineDebug.h>

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
	:PlayerInfo_(nullptr)
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
	CreateActor<PlayUI>(2);

	PlayLevelStage = this;
}

void PlayLevel::Update() 
{
	if (nullptr == PlayerInfo_ ||
		nullptr == StageInfo_)
	{
		MsgBoxAssert("필수 액터 정보가 없습니다.")
	}
	//Time -= GameEngineTime::GetDeltaTime();

	//if (0 >= Time)
	//{
	//	BgmPlayer.Stop();
	//}

	float LevelInterTime = PlayLevelStage->GetLevelInterTime();

	if (0.0f >= CurframeTime_)
	{
		++FrameUnitCount_;
		is2FrameUnit_ = false;
		CurframeTime_ = LevelInterTime;
		++Distance_;

		if (2 == FrameUnitCount_)
		{
			--FrameCount;
			FrameUnitCount_ = 0;
			is2FrameUnit_ = true;

			StageInfo_->MountainFrame();
			CreateActor<HoleTrap>();
		}
	}
	CurframeTime_ -= GameEngineTime::GetDeltaTime();
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