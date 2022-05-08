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
	, CreateState_(CreateTrap::None)
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

void PlayLevel::TrapSpawnSetting(TrapSpawn _SpawnState)
{
	switch (_SpawnState)
	{
	case TrapSpawn::L_Crack:
	{
		Trap* TrapUnit0 = CreateActor<Trap>((int)ORDER::TRAP);
		TrapUnit0->TrapSetting(TrapEvent::Crack, SpawnLoc::LEFT);
	}
		break;

	case TrapSpawn::R_Crack:
	{
		Trap* TrapUnit0 = CreateActor<Trap>((int)ORDER::TRAP);
		TrapUnit0->TrapSetting(TrapEvent::Crack, SpawnLoc::RIGHT);
	}
		break;

	case TrapSpawn::L_Hole:
	{
		Trap* TrapUnit0 = CreateActor<Trap>((int)ORDER::TRAP);
		TrapUnit0->TrapSetting(TrapEvent::Hole, SpawnLoc::LEFT);
	}
		break;

	case TrapSpawn::C_Hole:
	{
		Trap* TrapUnit0 = CreateActor<Trap>((int)ORDER::TRAP);
		TrapUnit0->TrapSetting(TrapEvent::Hole, SpawnLoc::CENTER);
	}
		break;

	case TrapSpawn::R_Hole:
	{
		Trap* TrapUnit0 = CreateActor<Trap>((int)ORDER::TRAP);
		TrapUnit0->TrapSetting(TrapEvent::Hole, SpawnLoc::RIGHT);
	}
		break;

	case TrapSpawn::LR_Hole:
	{
		Trap* TrapUnit0 = CreateActor<Trap>((int)ORDER::TRAP);
		TrapUnit0->TrapSetting(TrapEvent::Hole, SpawnLoc::LEFT);
		Trap* TrapUnit1 = CreateActor<Trap>((int)ORDER::TRAP);
		TrapUnit1->TrapSetting(TrapEvent::Hole, SpawnLoc::RIGHT);
	}
		break;

	case TrapSpawn::L_Seal:
	{
		Trap* TrapUnit0 = CreateActor<Trap>((int)ORDER::TRAP);
		TrapUnit0->TrapSetting(TrapEvent::Seal, SpawnLoc::LEFT);
	}
		break;

	case TrapSpawn::C_Seal:
	{
		Trap* TrapUnit0 = CreateActor<Trap>((int)ORDER::TRAP);
		TrapUnit0->TrapSetting(TrapEvent::Seal, SpawnLoc::CENTER);
	}
		break;

	case TrapSpawn::R_Seal:
	{
		Trap* TrapUnit0 = CreateActor<Trap>((int)ORDER::TRAP);
		TrapUnit0->TrapSetting(TrapEvent::Seal, SpawnLoc::RIGHT);
	}
		break;

	case TrapSpawn::L_Random:
	{
		Trap* TrapUnit0 = CreateActor<Trap>((int)ORDER::TRAP);
		GameEngineRandom NewRandom;
		int RandomVal = NewRandom.RandomInt(0, 3);
		if (0 == RandomVal)
		{
			TrapUnit0->TrapSetting(TrapEvent::Hole, SpawnLoc::LEFT);
		}
		else if (1 == RandomVal)
		{
			TrapUnit0->TrapSetting(TrapEvent::Seal, SpawnLoc::LEFT);
		}
		else if (2 == RandomVal)
		{
			TrapUnit0->TrapSetting(TrapEvent::Fish, SpawnLoc::LEFT);
		}
		else if (3 == RandomVal)
		{
			TrapUnit0->TrapSetting(TrapEvent::Flag, SpawnLoc::LEFT);
		}
	}
		break;

	case TrapSpawn::C_Random:
	{
		Trap* TrapUnit0 = CreateActor<Trap>((int)ORDER::TRAP);
		GameEngineRandom NewRandom;
		int RandomVal = NewRandom.RandomInt(0, 3);
		if (0 == RandomVal)
		{
			TrapUnit0->TrapSetting(TrapEvent::Hole, SpawnLoc::CENTER);
		}													  
		else if (1 == RandomVal)							  
		{													  
			TrapUnit0->TrapSetting(TrapEvent::Seal, SpawnLoc::CENTER);
		}													  
		else if (2 == RandomVal)							  
		{													  
			TrapUnit0->TrapSetting(TrapEvent::Fish, SpawnLoc::CENTER);
		}													  
		else if (3 == RandomVal)							  
		{													  
			TrapUnit0->TrapSetting(TrapEvent::Flag, SpawnLoc::CENTER);
		}
	}
		break;

	case TrapSpawn::R_Random:
	{
		Trap* TrapUnit0 = CreateActor<Trap>((int)ORDER::TRAP);
		GameEngineRandom NewRandom;
		int RandomVal = NewRandom.RandomInt(0, 3);
		if (0 == RandomVal)
		{
			TrapUnit0->TrapSetting(TrapEvent::Hole, SpawnLoc::RIGHT);
		}
		else if (1 == RandomVal)
		{
			TrapUnit0->TrapSetting(TrapEvent::Seal, SpawnLoc::RIGHT);
		}
		else if (2 == RandomVal)
		{
			TrapUnit0->TrapSetting(TrapEvent::Fish, SpawnLoc::RIGHT);
		}
		else if (3 == RandomVal)
		{
			TrapUnit0->TrapSetting(TrapEvent::Flag, SpawnLoc::RIGHT);
		}
	}
		break;
	default:
		break;
	}
	CreateState_ = CreateTrap::Ready;
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

	if (CreateState_ == CreateTrap::None) // 단일 트랩 생성
	{
		TrapSpawnSetting(TrapSpawn::C_Random);
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
}
