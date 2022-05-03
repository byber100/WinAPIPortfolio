#include "PlayLevel.h"
#include "ContentsEnum.h"
#include "Player.h"
#include "PlayUI.h"
#include "PlayBack.h"
#include "RandomStage.h"
#include "Trap.h"
#include "House.h"
#include "LevelChanger.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>

PlayLevel* PlayLevel::PlayLevelStage = nullptr;
int PlayLevel::FrameCount = 64; // Start Stage Stay Time
bool PlayLevel::is2FrameUnit_ = false;
bool PlayLevel::LevelChangeOn_ = false;

PlayLevel::PlayLevel() 
	: UnitSecond_(1.0f)
	, ArriveOn_(false)
	, LevelChanger_(nullptr)
	, HouseInfo_ (nullptr)
	, isColDebug_(false)
{
}

PlayLevel::~PlayLevel() 
{
}

float PlayLevel::GetLevelInterTime()
{
	if (nullptr == Player::MainPlayer)
	{
		MsgBoxAssert("�÷��̾� ������ �����ϴ�.");
	}

	float PlayerSpeed = Player::MainPlayer->GetForwardSpeed();
	PlayerSpeed = 1 / PlayerSpeed;
	return PlayerSpeed;
}

void PlayLevel::Arrive()
{
	if (false == ArriveOn_)
	{
		if (false == Player::MainPlayer->IsClear())
		{
			Player::MainPlayer->ChangeState(Clear);
		}
		ArriveOn_ = true;
	}
}

void PlayLevel::Loading()
{
	if (nullptr == Player::MainPlayer)
	{
		Player::MainPlayer = CreateActor<Player>((int)ORDER::PLAYER, "MainPlayer");
	}
	if (nullptr == RandomStage::MainStage)
	{
		RandomStage::MainStage = CreateActor<RandomStage>((int)ORDER::BACKGROUND, "MainStage");
	}

	LevelChanger_ = CreateActor<LevelChanger>((int)ORDER::UI);
	CreateActor<PlayBack>((int)ORDER::BACKGROUND);

	PlayLevelStage = this;

	// Test///////////////////////////////////////////////////
	GameEngineInput::GetInst()->CreateKey("TestTrap", 'Q');
	GameEngineInput::GetInst()->CreateKey("ToPrevLevel", '1');
	GameEngineInput::GetInst()->CreateKey("DebugCol", VK_TAB);

	if (nullptr == Player::MainPlayer ||
		nullptr == RandomStage::MainStage ||
		nullptr == PlayUI::MainUI)
	{
		MsgBoxAssert("�ʼ� ���� ������ �����ϴ�.")
	}
}

void PlayLevel::Update() 
{
	if (GameEngineInput::GetInst()->IsDown("ToPrevLevel"))
	{
		GameEngine::GetInst().ChangeLevel("Map");
	}
	if (GameEngineInput::GetInst()->IsDown("TestTrap"))
	{
		CreateActor<Trap>((int)ORDER::TRAP);
	}
	if (GameEngineInput::GetInst()->IsDown("DebugCol"))
	{
		IsDebugModeSwitch();
	}

	if (true == LevelChangeOn_)
	{
		LevelChanger_->LevelChangeAnim("Map");
	}

	if (60 == PlayUI::RestDistance_)
	{
		if (nullptr == HouseInfo_)
		{
 			HouseInfo_ = CreateActor<House>((int)ORDER::OBJECT);
			HouseInfo_->isFlagUp_ = false;
		}
	}

	int t = PlayUI::MainUI->GetCountTime();
	if (0 != t)
	{
		if (0 < PlayUI::RestDistance_)
		{
			if (0 < UnitSecond_)
			{
				UnitSecond_ -= GameEngineTime::GetInst()->GetDeltaTime();
			}
			else
			{
				if (11 >= PlayUI::MainUI->GetCountTime() &&
					1 < PlayUI::MainUI->GetCountTime()) // �ð� 10�� �˶�
				{
					GameEngineSound::SoundPlayOneShot("SFX9.mp3");
				}
				
				UnitSecond_ = 1.0f;

				--t;
				PlayUI::MainUI->SetCountTime(t);
			}
		}
		else
		{
			Arrive();
			return;
		}
	}
	else
	{
		if (true== PlayUI::MainUI->IsTimeOver())
		{
			Player::MainPlayer->ChangeState(PlayerState::Pause);
		}
		return;
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

			RandomStage::MainStage->MountainFrame();
			//CreateActor<Trap>((int)ORDER::TRAP);
		}
	}
	CurframeTime_ -= GameEngineTime::GetDeltaTime();
}

void PlayLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	ArriveOn_ = false;
	CurframeTime_ = 0;
}

void PlayLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != HouseInfo_)
	{
		HouseInfo_->Death();
		HouseInfo_ = nullptr;
	}

	LevelChangeOn_ = false;

	PlayUI::MainUI->NextLevelOn();
	if (false == PlayUI::MainUI->IsTimeOver())
	{
		++PlayUI::Stage_;
	}
}
