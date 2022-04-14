#include "RandomStage.h"
#include "Player.h"
#include "PlayLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineImage.h>

// Static Var

// Static Func

// constructor destructor
RandomStage::RandomStage()
	: RoundStateValue_(0)
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
	BackStage_->SetPivot({ 0,16 });

	LeftOcean_ = CreateRenderer(100, RenderPivot::LEFTTOP);
	LeftOcean_->SetPivot({ -416, 0 });
	LeftOcean_->CreateAnimation("OceanTiles.bmp", "LeftOcean", 0, 3, 0.2f);
	LeftOcean_->ChangeAnimation("LeftOcean");

	RightOcean_ = CreateRenderer(100, RenderPivot::LEFTTOP);
	RightOcean_->SetPivot({ 0, 0 });
	RightOcean_->CreateAnimation("OceanTiles.bmp", "RightOcean", 4, 7, 0.2f);
	RightOcean_->ChangeAnimation("RightOcean");

	LeftGround_ = CreateRenderer(100, RenderPivot::LEFTTOP);
	LeftGround_->SetPivot({ -416, 0 });
	LeftGround_->CreateAnimation("GroundTiles.bmp", "LeftGround", 0, 1, 0.2f);
	LeftGround_->ChangeAnimation("LeftGround");

	RightGround_ = CreateRenderer(100, RenderPivot::LEFTTOP);
	RightGround_->SetPivot({ 0, 0 });
	RightGround_->CreateAnimation("GroundTiles.bmp", "RightGround", 2, 3, 0.2f);
	RightGround_->ChangeAnimation("RightGround");

	CurveTiles_ = CreateRenderer("CurveTiles.bmp", 100, RenderPivot::LEFTTOP);
	CurveTiles_->SetPivot({ -416, 0 });
	// CurveTiles_->SetIndex(0);
	// 0: letf ocean
	// 1: right ocean
	// 2: left ground
	// 3: right ground

	Mountain1_ = CreateRenderer("Mountain.bmp", 100, RenderPivot::LEFTTOP);
	Mountain1_->SetPivot({ -832, -32 });

	Mountain2_ = CreateRenderer("Mountain.bmp", 100, RenderPivot::LEFTTOP);
	Mountain2_->SetPivot({ 0, -32 });

	LeftGlacier_ = CreateRenderer("Glaciers.bmp", 100, RenderPivot::LEFTTOP);
	LeftGlacier_->SetPivot({ -416, -32 });
	LeftGlacier_->SetIndex(0);

	RightGlacier_ = CreateRenderer("Glaciers.bmp", 100, RenderPivot::LEFTTOP);
	RightGlacier_->SetPivot({ 0, -32 });
	RightGlacier_->SetIndex(1);
}

void RandomStage::MountainMove(GameEngineRenderer* _Mountain)
{
	if (1 == MountainDirectionValue_) // Turn Left
	{
		_Mountain->SetPivotMove(float4::RIGHT * 32.0f);
		if (384.0f <= _Mountain->GetPivot().ix())
		{
			_Mountain->SetPivot({ -1280.0f, -32.0f });
		}
	}

	if (2 == MountainDirectionValue_) // Turn Right
	{
		_Mountain->SetPivotMove(float4::LEFT * 32.0f);
		if (-1216.0f >= _Mountain->GetPivot().ix())
		{
			_Mountain->SetPivot({ 448.0f, -32.0f });
		}
	}
}

void RandomStage::MountainFrame()
{
	if (true == isCurve_)
	{
		MountainMove(Mountain1_);
		MountainMove(Mountain2_);
	}
}

void RandomStage::CurveFrameCount()
{
	PlayLevel::FrameCount = 26 * RandomValue_.RandomInt(1, 1);
}

void RandomStage::StageChange()
{
	if (3 < RoundStateValue_)
	{
		MsgBoxAssert("없는 라운드 타일");
		return;
	}

	if (true == PlayLevel::is2FrameUnit_)
	{
		PlayLevel::FrameCount = 16 * RandomValue_.RandomInt(1, 1); // Change Time

		switch (RoundStateValue_)
		{
		case 0: // L Ocean, R Ocean
			RoundStateValue_ = RandomValue_.RandomInt(1, 2);
			break;

		case 1: // L Ocean, R Ground
			if (false == isCurve_)
			{
				RoundStateValue_ = RandomValue_.RandomInt(0, 3);
				while (2 == RoundStateValue_)
				{
					RoundStateValue_ = RandomValue_.RandomInt(0, 3);
				}
				if (1 == RoundStateValue_) // Turn Left
				{
					isCurve_ = true;
					MountainDirectionValue_ = 1;
					CurveTiles_->SetIndex(0); //ChangeAnimation("TurnLeftOcean");
					CurveFrameCount();
				}
			}
			else
			{
				isCurve_ = false;
			}
			break;

		case 2: // L Ground, R Ocean
			if (false == isCurve_)
			{
				RoundStateValue_ = RandomValue_.RandomInt(0, 3);
				while (1 == RoundStateValue_)
				{
					RoundStateValue_ = RandomValue_.RandomInt(0, 3);
				}
				if (2 == RoundStateValue_) // Trun Right
				{
					isCurve_ = true;
					MountainDirectionValue_ = 2;
					CurveTiles_->SetIndex(1); //ChangeAnimation("TurnRightOcean");
					CurveFrameCount();
				}
			}
			else
			{
				isCurve_ = false;
			}
			break;

		case 3: // L Ground, R Ground
			if (false == isCurve_)
			{
				RoundStateValue_ = RandomValue_.RandomInt(0, 3);
				if (3 == RoundStateValue_) // Turn Right
				{
					isCurve_ = true;
					MountainDirectionValue_ = 2;
					CurveTiles_->SetIndex(3); //ChangeAnimation("TurnRightGround");
					CurveFrameCount();
				}
				if (0 == RoundStateValue_) // Turn Left
				{
					RoundStateValue_ = 3;
					isCurve_ = true;
					MountainDirectionValue_ = 1;
					CurveTiles_->SetIndex(2); //ChangeAnimation("TurnLeftGround");
					CurveFrameCount();
				}
			}
			else
			{
				isCurve_ = false;
				MountainDirectionValue_ = 0;
			}
			break;

		default:
			MsgBoxAssert("없는 라운드 타일");
			return;
		}
	}
}

void RandomStage::Update()
{
	if (0 == PlayLevel::FrameCount)
	{
		StageChange();
	}

	if (false == PlayLevel::is2FrameUnit_)
	{
		float FrameTime = 2 * PlayLevel::PlayLevelStage->GetLevelInterTime(); // 임의로 2로 함

		LeftOcean_->SetInterTime(FrameTime);
		RightOcean_->SetInterTime(FrameTime);
		LeftGround_->SetInterTime(FrameTime);
		RightGround_->SetInterTime(FrameTime);
	}
}

void RandomStage::Render()
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