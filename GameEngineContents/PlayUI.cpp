#include "PlayUI.h"
#include "Player.h"
#include "PlayLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>

PlayUI* PlayUI::MainUI = nullptr;
int PlayUI::Stage_ = 1;
int PlayUI::RestDistance_ = 0; // MapLevel에서 정해줌

PlayUI::PlayUI()
	: Score_(0)
	, HiScore_(0)
	, Speed_(5)
	, CountTime_(0) // MapLevel에서 정해줌
	, CountMode_(TimeScoreCount::OFF)
	, CalTime_(0)
	, VeiledDebuging_(true)
	, ScoreTile1_ (nullptr)
	, ScoreTile2_ (nullptr)
	, ScoreTile3_ (nullptr)
	, ScoreTile4_ (nullptr)
	, ScoreTile5_ (nullptr)
	, ScoreTile6_ (nullptr)
	, HiScoreTile1_ (nullptr)
	, HiScoreTile2_	(nullptr)
	, HiScoreTile3_	(nullptr)
	, HiScoreTile4_	(nullptr)
	, HiScoreTile5_	(nullptr)
	, HiScoreTile6_	(nullptr)
	, StageTile1_ (nullptr)
	, StageTile2_ (nullptr)
	, TimeCountTile1_ (nullptr)
	, TimeCountTile2_ (nullptr)
	, TimeCountTile3_ (nullptr)
	, TimeCountTile4_ (nullptr)
	, RestDistanceTile1_ (nullptr)
	, RestDistanceTile2_ (nullptr)
	, RestDistanceTile3_ (nullptr)
	, RestDistanceTile4_ (nullptr)
	, SpeedTile1_ (nullptr)
	, SpeedTile2_ (nullptr)
	, SpeedTile3_ (nullptr)
	, SpeedTile4_ (nullptr)
	, SpeedTile5_ (nullptr)
	, SpeedTile6_ (nullptr)

{
}

PlayUI::~PlayUI()
{
}

void PlayUI::NumberUpdate(int _Object, const std::vector<GameEngineRenderer*> NumberImages)
{

	std::string Value = std::to_string(_Object);
                                                  
	size_t Count = Value.size() <= NumberImages.size() ? Value.size() : NumberImages.size();

	for (size_t i = 0; i < NumberImages.size(); i++) // 기본 랜더 초기화
	{
		NumberImages[i]->SetIndex(0);
	}

	//       [9][9][9]
	// [0][0][0][0][0]  자릿 수 고려하여 랜더

	int OverCount = NumberImages.size() - Count;
	int StringCount = 0;
	for (size_t i = OverCount; i < Count + OverCount; i++)
	{
		NumberImages[i]->SetIndex(Value[StringCount++] - '0');
	}
}

void PlayUI::DebugUIOn()
{
	{
		std::string UpdateText = std::to_string(Score_);
		DedugText_.Draw("Score: " + UpdateText, { 0,0 }, RGB(255,255,255), 20, 0);
	}
	{
		std::string UpdateText = std::to_string(HiScore_);
		DedugText_.Draw("HiScore: " + UpdateText, { 0,20 }, RGB(255, 255, 255), 20, 0);
	}
	{
		std::string UpdateText = std::to_string(Stage_);
		DedugText_.Draw("Stage: " + UpdateText, { 0,40 }, RGB(255, 255, 255), 20, 0);
	}
	{
		std::string UpdateText = std::to_string(CountTime_);
		DedugText_.Draw("TimeCount: " + UpdateText, { 0,60 }, RGB(255, 255, 255), 20, 0);
	}
	{
		std::string UpdateText = std::to_string(RestDistance_);
		DedugText_.Draw("RestDistance: " + UpdateText, { 0,80 }, RGB(255, 255, 255), 20, 0);
	}
	{
		std::string UpdateText = std::to_string(Speed_);
		std::string SpeedText = { 7 };
		if (nullptr != Player::MainPlayer)
		{
			SpeedText = std::to_string(Player::MainPlayer->GetForwardSpeed());
		}
		DedugText_.Draw("Speed: " + UpdateText + " ( " + SpeedText + " )", {0,100}, RGB(255, 255, 255), 20, 0);
	}
}

void PlayUI::UpdateSpeed()
{
	float Speed = static_cast<float>(Speed_);
	if (nullptr != Player::MainPlayer)
	{
		Speed = Player::MainPlayer->GetForwardSpeed();
	}

	if (1.0f > Speed)
	{
		Speed_ = 0;
		SpeedTile1_->SetIndex(12);
		SpeedTile2_->SetIndex(12);
		SpeedTile3_->SetIndex(12);
		SpeedTile4_->SetIndex(12);
		SpeedTile5_->SetIndex(12);
		SpeedTile6_->SetIndex(12);
	}
	else if (13.0f <= Speed)
	{
		Speed_ = 12;
		SpeedTile1_->SetIndex(10);
		SpeedTile2_->SetIndex(10);
		SpeedTile3_->SetIndex(10);
		SpeedTile4_->SetIndex(10);
		SpeedTile5_->SetIndex(10);
		SpeedTile6_->SetIndex(10);
	}
	else if (12.0f <= Speed && 13.0f > Speed)
	{
		Speed_ = 11;
		SpeedTile1_->SetIndex(10);
		SpeedTile2_->SetIndex(10);
		SpeedTile3_->SetIndex(10);
		SpeedTile4_->SetIndex(10);
		SpeedTile5_->SetIndex(10);
		SpeedTile6_->SetIndex(11);
	}
	else if (11.0f <= Speed && 12.0f > Speed)
	{
		Speed_ = 10;
		SpeedTile1_->SetIndex(10);
		SpeedTile2_->SetIndex(10);
		SpeedTile3_->SetIndex(10);
		SpeedTile4_->SetIndex(10);
		SpeedTile5_->SetIndex(10);
		SpeedTile6_->SetIndex(12);
	}
	else if (10.0f <= Speed && 11.0f > Speed)
	{
		Speed_ = 9;
		SpeedTile1_->SetIndex(10);
		SpeedTile2_->SetIndex(10);
		SpeedTile3_->SetIndex(10);
		SpeedTile4_->SetIndex(10);
		SpeedTile5_->SetIndex(11);
		SpeedTile6_->SetIndex(12);
	}
	else if (9.0f <= Speed && 10.0f > Speed)
	{
		Speed_ = 8;
		SpeedTile1_->SetIndex(10);
		SpeedTile2_->SetIndex(10);
		SpeedTile3_->SetIndex(10);
		SpeedTile4_->SetIndex(10);
		SpeedTile5_->SetIndex(12);
		SpeedTile6_->SetIndex(12);
	}
	else if (8.0f <= Speed && 9.0f > Speed)
	{
		Speed_ = 7;
		SpeedTile1_->SetIndex(10);
		SpeedTile2_->SetIndex(10);
		SpeedTile3_->SetIndex(10);
		SpeedTile4_->SetIndex(11);
		SpeedTile5_->SetIndex(12);
		SpeedTile6_->SetIndex(12);
	}
	else if (7.0f <= Speed && 8.0f > Speed)
	{
		Speed_ = 6;
		SpeedTile1_->SetIndex(10);
		SpeedTile2_->SetIndex(10);
		SpeedTile3_->SetIndex(10);
		SpeedTile4_->SetIndex(12);
		SpeedTile5_->SetIndex(12);
		SpeedTile6_->SetIndex(12);
	}
	else if (6.0f <= Speed && 7.0f > Speed)
	{
		Speed_ = 5;
		SpeedTile1_->SetIndex(10);
		SpeedTile2_->SetIndex(10);
		SpeedTile3_->SetIndex(11);
		SpeedTile4_->SetIndex(12);
		SpeedTile5_->SetIndex(12);
		SpeedTile6_->SetIndex(12);
	}
	else if (5.0f <= Speed && 6.0f > Speed)
	{
		Speed_ = 4;
		SpeedTile1_->SetIndex(10);
		SpeedTile2_->SetIndex(10);
		SpeedTile3_->SetIndex(12);
		SpeedTile4_->SetIndex(12);
		SpeedTile5_->SetIndex(12);
		SpeedTile6_->SetIndex(12);
	}
	else if (4.0f <= Speed && 5.0f > Speed)
	{
		Speed_ = 3;
		SpeedTile1_->SetIndex(10);
		SpeedTile2_->SetIndex(11);
		SpeedTile3_->SetIndex(12);
		SpeedTile4_->SetIndex(12);
		SpeedTile5_->SetIndex(12);
		SpeedTile6_->SetIndex(12);
	}
	else if (3.0f <= Speed && 4.0f > Speed)
	{
		Speed_ = 2;
		SpeedTile1_->SetIndex(10);
		SpeedTile2_->SetIndex(12);
		SpeedTile3_->SetIndex(12);
		SpeedTile4_->SetIndex(12);
		SpeedTile5_->SetIndex(12);
		SpeedTile6_->SetIndex(12);
	}
	else if (1.0f <= Speed && 3.0f > Speed)
	{
		Speed_ = 1;
		SpeedTile1_->SetIndex(11);
		SpeedTile2_->SetIndex(12);
		SpeedTile3_->SetIndex(12);
		SpeedTile4_->SetIndex(12);
		SpeedTile5_->SetIndex(12);
		SpeedTile6_->SetIndex(12);
	}
}

void PlayUI::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainUI = this;
}

void PlayUI::Start()
{
	DedugText_.Load("arial.ttf");
	GameEngineInput::GetInst()->CreateKey("UIDebug", VK_TAB);
	
	SetPosition(float4::ZERO);
	SetScale(GameEngineWindow::GetScale());
	GameEngineRenderer* Renderer = CreateRenderer("UIBack.bmp", 500, RenderPivot::LEFTTOP);
	
	{
		float StartXPos = 240.0f;
		float StartYPos = 92.0f;
		ScoreTile1_ = CreateRenderer("InterfaceWords.bmp", 501, RenderPivot::LEFTTOP);
		ScoreTile1_->SetPivot({ StartXPos + (24 * 0), StartYPos });
		ScoreTile2_ = CreateRenderer("InterfaceWords.bmp", 501, RenderPivot::LEFTTOP);
		ScoreTile2_->SetPivot({ StartXPos + (24 * 1), StartYPos });
		ScoreTile3_ = CreateRenderer("InterfaceWords.bmp", 501, RenderPivot::LEFTTOP);
		ScoreTile3_->SetPivot({ StartXPos + (24 * 2), StartYPos });
		ScoreTile4_ = CreateRenderer("InterfaceWords.bmp", 501, RenderPivot::LEFTTOP);
		ScoreTile4_->SetPivot({ StartXPos + (24 * 3), StartYPos });
		ScoreTile5_ = CreateRenderer("InterfaceWords.bmp", 501, RenderPivot::LEFTTOP);
		ScoreTile5_->SetPivot({ StartXPos + (24 * 4), StartYPos });
		ScoreTile6_ = CreateRenderer("InterfaceWords.bmp", 501, RenderPivot::LEFTTOP);
		ScoreTile6_->SetPivot({ StartXPos + (24 * 5), StartYPos });

		ScoreImages.push_back(ScoreTile1_);
		ScoreImages.push_back(ScoreTile2_);
		ScoreImages.push_back(ScoreTile3_);
		ScoreImages.push_back(ScoreTile4_);
		ScoreImages.push_back(ScoreTile5_);
		ScoreImages.push_back(ScoreTile6_);
	}
	{
		float StartXPos = 496.0f;
		float StartYPos = 92.0f;
		HiScoreTile1_ = CreateRenderer("InterfaceWords.bmp", 501, RenderPivot::LEFTTOP);
		HiScoreTile1_->SetPivot({ StartXPos + (24 * 0), StartYPos });
		HiScoreTile2_ = CreateRenderer("InterfaceWords.bmp", 501, RenderPivot::LEFTTOP);
		HiScoreTile2_->SetPivot({ StartXPos + (24 * 1), StartYPos });
		HiScoreTile3_ = CreateRenderer("InterfaceWords.bmp", 501, RenderPivot::LEFTTOP);
		HiScoreTile3_->SetPivot({ StartXPos + (24 * 2), StartYPos });
		HiScoreTile4_ = CreateRenderer("InterfaceWords.bmp", 501, RenderPivot::LEFTTOP);
		HiScoreTile4_->SetPivot({ StartXPos + (24 * 3), StartYPos });
		HiScoreTile5_ = CreateRenderer("InterfaceWords.bmp", 501, RenderPivot::LEFTTOP);
		HiScoreTile5_->SetPivot({ StartXPos + (24 * 4), StartYPos });
		HiScoreTile6_ = CreateRenderer("InterfaceWords.bmp", 501, RenderPivot::LEFTTOP);
		HiScoreTile6_->SetPivot({ StartXPos + (24 * 5), StartYPos });

		HiScoreImages.push_back(HiScoreTile1_);
		HiScoreImages.push_back(HiScoreTile2_);
		HiScoreImages.push_back(HiScoreTile3_);
		HiScoreImages.push_back(HiScoreTile4_);
		HiScoreImages.push_back(HiScoreTile5_);
		HiScoreImages.push_back(HiScoreTile6_);
	}
	{
		float StartXPos = 816.0f;
		float StartYPos = 92.0f;
		StageTile1_ = CreateRenderer("InterfaceWords.bmp", 501, RenderPivot::LEFTTOP);
		StageTile1_->SetPivot({ StartXPos + (24 * 0), StartYPos });
		StageTile2_ = CreateRenderer("InterfaceWords.bmp", 501, RenderPivot::LEFTTOP);
		StageTile2_->SetPivot({ StartXPos + (24 * 1), StartYPos });

		StageImages.push_back(StageTile1_);
		StageImages.push_back(StageTile2_);
	}
	{
		float StartXPos = 288.0f;
		float StartYPos = 120.0f;
		TimeCountTile1_ = CreateRenderer("InterfaceWords.bmp", 501, RenderPivot::LEFTTOP);
		TimeCountTile1_->SetPivot({ StartXPos + (24 * 0), StartYPos });
		TimeCountTile2_ = CreateRenderer("InterfaceWords.bmp", 501, RenderPivot::LEFTTOP);
		TimeCountTile2_->SetPivot({ StartXPos + (24 * 1), StartYPos });
		TimeCountTile3_ = CreateRenderer("InterfaceWords.bmp", 501, RenderPivot::LEFTTOP);
		TimeCountTile3_->SetPivot({ StartXPos + (24 * 2), StartYPos });
		TimeCountTile4_ = CreateRenderer("InterfaceWords.bmp", 501, RenderPivot::LEFTTOP);
		TimeCountTile4_->SetPivot({ StartXPos + (24 * 3), StartYPos });

		TimeCountImages.push_back(TimeCountTile1_);
		TimeCountImages.push_back(TimeCountTile2_);
		TimeCountImages.push_back(TimeCountTile3_);
		TimeCountImages.push_back(TimeCountTile4_);
	}
	{
		float StartXPos = 496.0f;
		float StartYPos = 120.0f;
		RestDistanceTile1_ = CreateRenderer("InterfaceWords.bmp", 501, RenderPivot::LEFTTOP);
		RestDistanceTile1_->SetPivot({ StartXPos + (24 * 0), StartYPos });
		RestDistanceTile2_ = CreateRenderer("InterfaceWords.bmp", 501, RenderPivot::LEFTTOP);
		RestDistanceTile2_->SetPivot({ StartXPos + (24 * 1), StartYPos });
		RestDistanceTile3_ = CreateRenderer("InterfaceWords.bmp", 501, RenderPivot::LEFTTOP);
		RestDistanceTile3_->SetPivot({ StartXPos + (24 * 2), StartYPos });
		RestDistanceTile4_ = CreateRenderer("InterfaceWords.bmp", 501, RenderPivot::LEFTTOP);
		RestDistanceTile4_->SetPivot({ StartXPos + (24 * 3), StartYPos });

		RestDistanceImages.push_back(RestDistanceTile1_);
		RestDistanceImages.push_back(RestDistanceTile2_);
		RestDistanceImages.push_back(RestDistanceTile3_);
		RestDistanceImages.push_back(RestDistanceTile4_);
	}
	{
		float StartXPos = 752.0f;
		float StartYPos = 120.0f;
		SpeedTile1_ = CreateRenderer("InterfaceWords.bmp", 501, RenderPivot::LEFTTOP);
		SpeedTile1_->SetPivot({ StartXPos + (24 * 0), StartYPos });
		SpeedTile2_ = CreateRenderer("InterfaceWords.bmp", 501, RenderPivot::LEFTTOP);
		SpeedTile2_->SetPivot({ StartXPos + (24 * 1), StartYPos });
		SpeedTile3_ = CreateRenderer("InterfaceWords.bmp", 501, RenderPivot::LEFTTOP);
		SpeedTile3_->SetPivot({ StartXPos + (24 * 2), StartYPos });
		SpeedTile4_ = CreateRenderer("InterfaceWords.bmp", 501, RenderPivot::LEFTTOP);
		SpeedTile4_->SetPivot({ StartXPos + (24 * 3), StartYPos });
		SpeedTile5_ = CreateRenderer("InterfaceWords.bmp", 501, RenderPivot::LEFTTOP);
		SpeedTile5_->SetPivot({ StartXPos + (24 * 4), StartYPos });
		SpeedTile6_ = CreateRenderer("InterfaceWords.bmp", 501, RenderPivot::LEFTTOP);
		SpeedTile6_->SetPivot({ StartXPos + (24 * 5), StartYPos });
	}
}

void PlayUI::Update()
{
	if (CountMode_ == TimeScoreCount::ON)
	{
		if (0.08f < CalTime_)
		{
			CalTime_ = 0;

			if (0 != CountTime_)
			{
				--CountTime_;
				Score_ += 100;
				GameEngineSound::SoundPlayOneShot("SFX1.mp3");
			}
			else
			{
				PlayLevel::LevelChangeOn_ = true;
				return;
			}
		}
		CalTime_ += GameEngineTime::GetInst()->GetDeltaTime();
		return;
	}

	if (0 != CountTime_)
	{
		if (nullptr != Player::MainPlayer && 0 != RestDistance_)
		{
			UpdateSpeed();
		}
	}
	else
	{
		GameEngineRenderer* TimeOver = CreateRenderer("TimeOver.bmp", 500);
		TimeOver->SetPivot(GetScale().Half());
	}
}

void PlayUI::Render()
{
	NumberUpdate(Score_, ScoreImages);
	NumberUpdate(HiScore_, HiScoreImages);
	NumberUpdate(Stage_, StageImages);
	NumberUpdate(CountTime_, TimeCountImages);
	NumberUpdate(RestDistance_, RestDistanceImages);

	if (GameEngineInput::GetInst()->IsDown("UIDebug"))
	{
		if (false == VeiledDebuging_)
		{
			VeiledDebuging_ = true;
		}
		else
		{
			VeiledDebuging_ = false;
		}
	}
	if (true == VeiledDebuging_)
	{
		DebugUIOn();
	}
}

void PlayUI::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	CountMode_ = TimeScoreCount::OFF;
}