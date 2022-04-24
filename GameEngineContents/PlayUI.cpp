#include "PlayUI.h"
#include "Player.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>

int PlayUI::RestDistance_ = 1500;

PlayUI::PlayUI()
	: Score_(0)
	, HiScore_(0)
	, Stage_(1)
	, TimeOut_(100)
	, Speed_(5)
	, VeiledDebuging_(true)
{
}

PlayUI::~PlayUI()
{
}

void PlayUI::NumberUpdate(int _Object, const std::vector<GameEngineRenderer*> ScoreImage)
{
	std::string Value = std::to_string(_Object);
	int a = ScoreImage.size();

	for (size_t i = 0; i < ScoreImage.size(); i++)
	{
		if (nullptr == &Value[i])
		{
			ScoreImage[i]->SetIndex(0);
		}
		ScoreImage[i]->SetIndex(Value[i] - '0');
	}
}

void PlayUI::DebugUIOn()
{
	{
		std::string UpdateText = std::to_string(Score_);
		DedugText_.Draw("Score: " + UpdateText, { 0,0 }, 20, 0);
	}
	{
		std::string UpdateText = std::to_string(HiScore_);
		DedugText_.Draw("HiScore: " + UpdateText, { 0,20 }, 20, 0);
	}
	{
		std::string UpdateText = std::to_string(Stage_);
		DedugText_.Draw("Stage: " + UpdateText, { 0,40 }, 20, 0);
	}
	{
		std::string UpdateText = std::to_string(TimeOut_);
		DedugText_.Draw("TimeOut: " + UpdateText, { 0,60 }, 20, 0);
	}
	{
		std::string UpdateText = std::to_string(RestDistance_);
		DedugText_.Draw("RestDistance: " + UpdateText, { 0,80 }, 20, 0);
	}
	{
		std::string UpdateText = std::to_string(Speed_);
		std::string SpeedText = std::to_string(PlayerInfo_->GetForwardSpeed());
		DedugText_.Draw("Speed: " + UpdateText + " ( " + SpeedText + " )", {0,100}, 20, 0);
	}
}

void PlayUI::UpdateSpeed()
{
	float Speed = PlayerInfo_->GetForwardSpeed();

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

void PlayUI::Start()
{
	DedugText_.Load("arial.ttf");
	GameEngineInput::GetInst()->CreateKey("UIDebug", VK_TAB);

	SetPosition(float4::ZERO);
	SetScale(GameEngineWindow::GetScale());

	PlayerInfo_ = dynamic_cast<Player*>(GetLevel()->FindActor("Penguin"));

	GameEngineRenderer* Renderer = CreateRenderer("BackInterface.bmp", 400, RenderPivot::LEFTTOP);
	
	{
		float StartXPos = 240.0f;
		float StartYPos = 92.0f;
		ScoreTile1_ = CreateRenderer("InterfaceWords.bmp", 401, RenderPivot::LEFTTOP);
		ScoreTile1_->SetPivot({ StartXPos + (24 * 0), StartYPos });
		ScoreTile2_ = CreateRenderer("InterfaceWords.bmp", 401, RenderPivot::LEFTTOP);
		ScoreTile2_->SetPivot({ StartXPos + (24 * 1), StartYPos });
		ScoreTile3_ = CreateRenderer("InterfaceWords.bmp", 401, RenderPivot::LEFTTOP);
		ScoreTile3_->SetPivot({ StartXPos + (24 * 2), StartYPos });
		ScoreTile4_ = CreateRenderer("InterfaceWords.bmp", 401, RenderPivot::LEFTTOP);
		ScoreTile4_->SetPivot({ StartXPos + (24 * 3), StartYPos });
		ScoreTile5_ = CreateRenderer("InterfaceWords.bmp", 401, RenderPivot::LEFTTOP);
		ScoreTile5_->SetPivot({ StartXPos + (24 * 4), StartYPos });
		ScoreTile6_ = CreateRenderer("InterfaceWords.bmp", 401, RenderPivot::LEFTTOP);
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
		HiScoreTile1_ = CreateRenderer("InterfaceWords.bmp", 401, RenderPivot::LEFTTOP);
		HiScoreTile1_->SetPivot({ StartXPos + (24 * 0), StartYPos });
		HiScoreTile2_ = CreateRenderer("InterfaceWords.bmp", 401, RenderPivot::LEFTTOP);
		HiScoreTile2_->SetPivot({ StartXPos + (24 * 1), StartYPos });
		HiScoreTile3_ = CreateRenderer("InterfaceWords.bmp", 401, RenderPivot::LEFTTOP);
		HiScoreTile3_->SetPivot({ StartXPos + (24 * 2), StartYPos });
		HiScoreTile4_ = CreateRenderer("InterfaceWords.bmp", 401, RenderPivot::LEFTTOP);
		HiScoreTile4_->SetPivot({ StartXPos + (24 * 3), StartYPos });
		HiScoreTile5_ = CreateRenderer("InterfaceWords.bmp", 401, RenderPivot::LEFTTOP);
		HiScoreTile5_->SetPivot({ StartXPos + (24 * 4), StartYPos });
		HiScoreTile6_ = CreateRenderer("InterfaceWords.bmp", 401, RenderPivot::LEFTTOP);
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
		StageTile1_ = CreateRenderer("InterfaceWords.bmp", 401, RenderPivot::LEFTTOP);
		StageTile1_->SetPivot({ StartXPos + (24 * 0), StartYPos });
		StageTile2_ = CreateRenderer("InterfaceWords.bmp", 401, RenderPivot::LEFTTOP);
		StageTile2_->SetPivot({ StartXPos + (24 * 1), StartYPos });
	}
	{
		float StartXPos = 288.0f;
		float StartYPos = 120.0f;
		TimeOutTile1_ = CreateRenderer("InterfaceWords.bmp", 401, RenderPivot::LEFTTOP);
		TimeOutTile1_->SetPivot({ StartXPos + (24 * 0), StartYPos });
		TimeOutTile2_ = CreateRenderer("InterfaceWords.bmp", 401, RenderPivot::LEFTTOP);
		TimeOutTile2_->SetPivot({ StartXPos + (24 * 1), StartYPos });
		TimeOutTile3_ = CreateRenderer("InterfaceWords.bmp", 401, RenderPivot::LEFTTOP);
		TimeOutTile3_->SetPivot({ StartXPos + (24 * 2), StartYPos });
		TimeOutTile4_ = CreateRenderer("InterfaceWords.bmp", 401, RenderPivot::LEFTTOP);
		TimeOutTile4_->SetPivot({ StartXPos + (24 * 3), StartYPos });

		TimeOutImages.push_back(TimeOutTile1_);
		TimeOutImages.push_back(TimeOutTile2_);
		TimeOutImages.push_back(TimeOutTile3_);
		TimeOutImages.push_back(TimeOutTile4_);
	}
	{
		float StartXPos = 496.0f;
		float StartYPos = 120.0f;
		RestDistanceTile1_ = CreateRenderer("InterfaceWords.bmp", 401, RenderPivot::LEFTTOP);
		RestDistanceTile1_->SetPivot({ StartXPos + (24 * 0), StartYPos });
		RestDistanceTile2_ = CreateRenderer("InterfaceWords.bmp", 401, RenderPivot::LEFTTOP);
		RestDistanceTile2_->SetPivot({ StartXPos + (24 * 1), StartYPos });
		RestDistanceTile3_ = CreateRenderer("InterfaceWords.bmp", 401, RenderPivot::LEFTTOP);
		RestDistanceTile3_->SetPivot({ StartXPos + (24 * 2), StartYPos });
		RestDistanceTile4_ = CreateRenderer("InterfaceWords.bmp", 401, RenderPivot::LEFTTOP);
		RestDistanceTile4_->SetPivot({ StartXPos + (24 * 3), StartYPos });

		RestDistanceImages.push_back(RestDistanceTile1_);
		RestDistanceImages.push_back(RestDistanceTile2_);
		RestDistanceImages.push_back(RestDistanceTile3_);
		RestDistanceImages.push_back(RestDistanceTile4_);
	}
	{
		float StartXPos = 752.0f;
		float StartYPos = 120.0f;
		SpeedTile1_ = CreateRenderer("InterfaceWords.bmp", 401, RenderPivot::LEFTTOP);
		SpeedTile1_->SetPivot({ StartXPos + (24 * 0), StartYPos });
		SpeedTile2_ = CreateRenderer("InterfaceWords.bmp", 401, RenderPivot::LEFTTOP);
		SpeedTile2_->SetPivot({ StartXPos + (24 * 1), StartYPos });
		SpeedTile3_ = CreateRenderer("InterfaceWords.bmp", 401, RenderPivot::LEFTTOP);
		SpeedTile3_->SetPivot({ StartXPos + (24 * 2), StartYPos });
		SpeedTile4_ = CreateRenderer("InterfaceWords.bmp", 401, RenderPivot::LEFTTOP);
		SpeedTile4_->SetPivot({ StartXPos + (24 * 3), StartYPos });
		SpeedTile5_ = CreateRenderer("InterfaceWords.bmp", 401, RenderPivot::LEFTTOP);
		SpeedTile5_->SetPivot({ StartXPos + (24 * 4), StartYPos });
		SpeedTile6_ = CreateRenderer("InterfaceWords.bmp", 401, RenderPivot::LEFTTOP);
		SpeedTile6_->SetPivot({ StartXPos + (24 * 5), StartYPos });
	}

	ScoreTile1_->SetIndex(0);
	ScoreTile2_->SetIndex(1);
	ScoreTile3_->SetIndex(2);
	ScoreTile4_->SetIndex(3);
	ScoreTile5_->SetIndex(4);
	ScoreTile6_->SetIndex(5);
	HiScoreTile1_->SetIndex(6);
	HiScoreTile2_->SetIndex(7);
	HiScoreTile3_->SetIndex(8);
	HiScoreTile4_->SetIndex(9);
	HiScoreTile5_->SetIndex(0);
	HiScoreTile6_->SetIndex(0);
	StageTile1_->SetIndex(0);
	StageTile2_->SetIndex(0);
	TimeOutTile1_->SetIndex(0);
	TimeOutTile2_->SetIndex(0);
	TimeOutTile3_->SetIndex(0);
	TimeOutTile4_->SetIndex(0);

	RestDistanceTile1_->SetIndex(0);
	RestDistanceTile2_->SetIndex(0);
	RestDistanceTile3_->SetIndex(0);
	RestDistanceTile4_->SetIndex(0);
}

void PlayUI::Update()
{
	//NumberUpdate(RestDistance_, RestDistanceImages);
	UpdateSpeed();

}

void PlayUI::Render()
{
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