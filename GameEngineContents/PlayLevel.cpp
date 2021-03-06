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
	, HouseInfo_(nullptr)
	, CreateState_(CreateTrap::None)
	, SpawnCnt_(0)
	, NumOfTrap_(1)
	, PatternVal_(0)
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
		MsgBoxAssert("플레이어 정보가 없습니다.");
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

void PlayLevel::TrapSpawnSetting(int _RandomTrap, const int& _Km /*= 1*/)
{
	if (CreateState_ == CreateTrap::Ready)
	{
		if (_Km > SpawnCnt_)
		{
			return;
		}
		else
		{
			SpawnCnt_ = 0;
			++NumOfTrap_;
		}
	}

	switch (_RandomTrap)
	{
	case 1:
	{
		Trap* TrapUnit0 = CreateActor<Trap>((int)ORDER::TRAP);
		TrapUnit0->TrapSetting(TrapEvent::Crack, SpawnLoc::LEFT);
		CreatedTrap_.push_back(TrapUnit0);
	}
		break;

	case 2:
	{
		Trap* TrapUnit0 = CreateActor<Trap>((int)ORDER::TRAP);
		TrapUnit0->TrapSetting(TrapEvent::Crack, SpawnLoc::RIGHT);
		CreatedTrap_.push_back(TrapUnit0);
	}
		break;

	case 3:
	{
		Trap* TrapUnit0 = CreateActor<Trap>((int)ORDER::TRAP);
		TrapUnit0->TrapSetting(TrapEvent::Hole, SpawnLoc::LEFT);
		CreatedTrap_.push_back(TrapUnit0);
	}
		break;

	case 4:
	{
		Trap* TrapUnit0 = CreateActor<Trap>((int)ORDER::TRAP);
		TrapUnit0->TrapSetting(TrapEvent::Hole, SpawnLoc::CENTER);
		CreatedTrap_.push_back(TrapUnit0);
	}
		break;

	case 5:
	{
		Trap* TrapUnit0 = CreateActor<Trap>((int)ORDER::TRAP);
		TrapUnit0->TrapSetting(TrapEvent::Hole, SpawnLoc::RIGHT);
		CreatedTrap_.push_back(TrapUnit0);
	}
		break;

	case 6:
	{
		Trap* TrapUnit0 = CreateActor<Trap>((int)ORDER::TRAP);
		TrapUnit0->TrapSetting(TrapEvent::Hole, SpawnLoc::LEFT);
		Trap* TrapUnit1 = CreateActor<Trap>((int)ORDER::TRAP);
		TrapUnit1->TrapSetting(TrapEvent::Hole, SpawnLoc::RIGHT);
		CreatedTrap_.push_back(TrapUnit0);
		CreatedTrap_.push_back(TrapUnit1);
	}
		break;

	case 7:
	{
		Trap* TrapUnit0 = CreateActor<Trap>((int)ORDER::TRAP);
		TrapUnit0->TrapSetting(TrapEvent::Seal, SpawnLoc::LEFT);
		CreatedTrap_.push_back(TrapUnit0);
	}
		break;

	case 8:
	{
		Trap* TrapUnit0 = CreateActor<Trap>((int)ORDER::TRAP);
		TrapUnit0->TrapSetting(TrapEvent::Seal, SpawnLoc::CENTER);
		CreatedTrap_.push_back(TrapUnit0);
	}
		break;

	case 9:
	{
		Trap* TrapUnit0 = CreateActor<Trap>((int)ORDER::TRAP);
		TrapUnit0->TrapSetting(TrapEvent::Seal, SpawnLoc::RIGHT);
		CreatedTrap_.push_back(TrapUnit0);
	}
		break;

	case 10:
	{
		Trap* TrapUnit0 = CreateActor<Trap>((int)ORDER::TRAP);
		GameEngineRandom NewRandom;
		int RandomVal = NewRandom.RandomInt(0, 2);
		if (0 == RandomVal)
		{
			TrapUnit0->TrapSetting(TrapEvent::Hole, SpawnLoc::LEFT);
		}
		else if (1 == RandomVal)
		{
			TrapUnit0->TrapSetting(TrapEvent::Fish, SpawnLoc::LEFT);
		}
		else if (2 == RandomVal)
		{
			TrapUnit0->TrapSetting(TrapEvent::Flag, SpawnLoc::LEFT);
		}
		CreatedTrap_.push_back(TrapUnit0);
	}
		break;

	case 11:
	{
		Trap* TrapUnit0 = CreateActor<Trap>((int)ORDER::TRAP);
		GameEngineRandom NewRandom;
		int RandomVal = NewRandom.RandomInt(0, 2);
		if (0 == RandomVal)
		{
			TrapUnit0->TrapSetting(TrapEvent::Hole, SpawnLoc::CENTER);
		}													  												  
		else if (1 == RandomVal)							  
		{													  
			TrapUnit0->TrapSetting(TrapEvent::Fish, SpawnLoc::CENTER);
		}													  
		else if (2 == RandomVal)							  
		{													  
			TrapUnit0->TrapSetting(TrapEvent::Flag, SpawnLoc::CENTER);
		}
		CreatedTrap_.push_back(TrapUnit0);
	}
		break;

	case 12:
	{
		Trap* TrapUnit0 = CreateActor<Trap>((int)ORDER::TRAP);
		GameEngineRandom NewRandom;
		int RandomVal = NewRandom.RandomInt(0, 2);
		if (0 == RandomVal)
		{
			TrapUnit0->TrapSetting(TrapEvent::Hole, SpawnLoc::RIGHT);
		}
		else if (1 == RandomVal)
		{
			TrapUnit0->TrapSetting(TrapEvent::Fish, SpawnLoc::RIGHT);
		}
		else if (2 == RandomVal)
		{
			TrapUnit0->TrapSetting(TrapEvent::Flag, SpawnLoc::RIGHT);
		}
		CreatedTrap_.push_back(TrapUnit0);
	}
		break;
	default:
		break;
	}

	if (CreateState_ == CreateTrap::None)
	{
		CreateState_ = CreateTrap::Ready;
	}
}

void PlayLevel::TrapPattern()
{
	if (60 >= PlayUI::RestDistance_)
	{
		return;
	}

	switch (NumOfTrap_)
	{
	case 1:
	{
		TrapSpawnSetting(0, 15);
	}
		break;
	case 2:
		TrapSpawnSetting(RandomTrap_.RandomInt(1, 12));
		break;
	default:
		NumOfTrap_ = 1;
		break;
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
		MsgBoxAssert("필수 액터 정보가 없습니다.")
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
		Trap* TrapUnit = CreateActor<Trap>((int)ORDER::TRAP);
		TrapUnit->TrapSetting(TrapEvent::Fish, SpawnLoc::LEFT);
		CreatedTrap_.push_back(TrapUnit);
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

	TrapPattern();

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
					1 < PlayUI::MainUI->GetCountTime()) // 시간 10초 알람
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
		++SpawnCnt_;
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
		}
	}
	CurframeTime_ -= GameEngineTime::GetDeltaTime();
}

void PlayLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	ArriveOn_ = false;
	CurframeTime_ = 0;
	SpawnCnt_ = 0;
	NumOfTrap_ = 1;
	CreateState_ = CreateTrap::None;
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

	for (Trap* CreatedTrap : CreatedTrap_)
	{
		if (nullptr == CreatedTrap)
		{
			continue;
		}
		CreatedTrap->Death();

		CreatedTrap_.clear();
	}
}