#include "RandomStage.h"
#include "Player.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineImage.h>

// Static Var

// Static Func

// constructor destructor
RandomStage::RandomStage()
	: RoundStateValue_(3)
	, MountainDirectionValue_(0)
	, isCurve_(false)
	, BackStage_(nullptr)
	, LeftOcean_(nullptr)
	, RightOcean_(nullptr)
	, LeftGround_(nullptr)
	, RightGround_(nullptr)
	, CurveTiles_(nullptr)
	, Mountain1_(nullptr)
	, Mountain2_(nullptr)
	, LeftGlacier_(nullptr)
	, RightGlacier_(nullptr)
{
}

RandomStage::~RandomStage()
{
}

//member Func
void RandomStage::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale(GameEngineWindow::GetScale());

	BackStage_ = CreateRenderer("BackStage.bmp", 100);
	BackStage_->SetPivot({ 0,-48 });

	LeftOcean_ = CreateRenderer(100, RenderPivot::LEFTTOP);
	LeftOcean_->SetPivot({ -416, -32 });
	LeftOcean_->CreateAnimation("OceanTiles.bmp", "LeftOcean", 0, 3, 0.2f);
	LeftOcean_->ChangeAnimation("LeftOcean");

	RightOcean_ = CreateRenderer(100, RenderPivot::LEFTTOP);
	RightOcean_->SetPivot({ 0, -32 });
	RightOcean_->CreateAnimation("OceanTiles.bmp", "RightOcean", 4, 7, 0.2f);
	RightOcean_->ChangeAnimation("RightOcean");

	LeftGround_ = CreateRenderer(100, RenderPivot::LEFTTOP);
	LeftGround_->SetPivot({ -416, -32 });
	LeftGround_->CreateAnimation("GroundTiles.bmp", "LeftGround", 0, 1, 0.2f);
	LeftGround_->ChangeAnimation("LeftGround");

	RightGround_ = CreateRenderer(100, RenderPivot::LEFTTOP);
	RightGround_->SetPivot({ 0, -32 });
	RightGround_->CreateAnimation("GroundTiles.bmp", "RightGround", 2, 3, 0.2f);
	RightGround_->ChangeAnimation("RightGround");

	CurveTiles_ = CreateRenderer("CurveTiles.bmp", 100, RenderPivot::LEFTTOP);
	CurveTiles_->SetPivot({ -416, -32 });
	// CurveTiles_->SetIndex(0);
	// 0: letf ocean
	// 1: right ocean
	// 2: left ground
	// 3: right ground

	Mountain1_ = CreateRenderer("Mountain.bmp", 100, RenderPivot::LEFTTOP);
	Mountain1_->SetPivot({ -832, -64 });

	Mountain2_ = CreateRenderer("Mountain.bmp", 100, RenderPivot::LEFTTOP);
	Mountain2_->SetPivot({ 0, -64 });

	LeftGlacier_ = CreateRenderer("Glaciers.bmp", 100, RenderPivot::LEFTTOP);
	LeftGlacier_->SetPivot({ -416, -64 });
	LeftGlacier_->SetIndex(0);

	RightGlacier_ = CreateRenderer("Glaciers.bmp", 100, RenderPivot::LEFTTOP);
	RightGlacier_->SetPivot({ 0, -64 });
	RightGlacier_->SetIndex(1);
}

void RandomStage::Update()
{

}

void RandomStage::UpdateAfter()
{
	BackStage_->Render();
	Mountain1_->Render();
	Mountain2_->Render();

	switch (RoundStateValue_)
	{
	case 0:
		if (true == isCurve_)
		{
			MsgBoxAssert("잘못된 커브");
			return;
		}
		LeftOcean_->Render();
		RightOcean_->Render();
		LeftGlacier_->Render();
		RightGlacier_->Render();
		break;

	case 1:
		LeftOcean_->Render();
		RightGround_->Render();
		if (true == isCurve_)
		{
			CurveTiles_->Render();
		}
		else
		{
			LeftGlacier_->Render();
		}
		break;

	case 2:
		LeftGround_->Render();
		RightOcean_->Render();
		if (true == isCurve_)
		{
			CurveTiles_->Render();
		}
		else
		{
			RightGlacier_->Render();
		}
		break;

	case 3:
		LeftGround_->Render();
		RightGround_->Render();
		if (true == isCurve_)
		{
			CurveTiles_->Render();
		}
		break;

	default:
		MsgBoxAssert("없는 스테이지");
		return;
	}
}

void RandomStage::Render()
{
	
}