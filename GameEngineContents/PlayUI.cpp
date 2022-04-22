#include "PlayUI.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

int PlayUI::RestDistance_ = 1500;

PlayUI::PlayUI()
	: Score_(0)
	, HiScore_(0)
	, Stage_(1)
	, TimeOut_(100)
	, Speed_(5)
{
}

PlayUI::~PlayUI()
{
}

void PlayUI::NumberUpdate(int _Object,
	GameEngineRenderer* _Word1,
	GameEngineRenderer* _Word2 /*= nullptr*/,
	GameEngineRenderer* _Word3 /*= nullptr*/,
	GameEngineRenderer* _Word4 /*= nullptr*/,
	GameEngineRenderer* _Word5 /*= nullptr*/,
	GameEngineRenderer* _Word6 /*= nullptr*/)
{
	int Object = _Object;
	int SingleNumber[6] = {};

	//while (0 != Object)
	//{
	//	Object % 10;
	//	Object /= 10;
	//	
	//	for (size_t i = 6; i == 0; --i)
	//	{
	//		Object % 10;
	//		Object

	//	}
	//}
}

void PlayUI::Start()
{
	SetPosition(float4::ZERO);
	SetScale(GameEngineWindow::GetScale());

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
	ScoreTile2_->SetIndex(0);
	ScoreTile3_->SetIndex(0);
	ScoreTile4_->SetIndex(0);
	ScoreTile5_->SetIndex(0);
	ScoreTile6_->SetIndex(0);
	HiScoreTile1_->SetIndex(0);
	HiScoreTile2_->SetIndex(0);
	HiScoreTile3_->SetIndex(0);
	HiScoreTile4_->SetIndex(0);
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
	SpeedTile1_->SetIndex(12);
	SpeedTile2_->SetIndex(11);
	SpeedTile3_->SetIndex(10);
	SpeedTile4_->SetIndex(10);
	SpeedTile5_->SetIndex(10);
	SpeedTile6_->SetIndex(10);
}

void PlayUI::Update()
{
	
}

void PlayUI::Render()
{
	
}