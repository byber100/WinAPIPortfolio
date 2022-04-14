#include "RandomStage.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineDebug.h>

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
void RandomStage::MountainMove(GameEngineRenderer* _Mountain)
{
	if (1 == MountainDirectionValue_) // Turn Left
	{
		float4 MovingRenderer = _Mountain->GetPivot();
		MovingRenderer += float4::RIGHT * 32.0f;
		if (384.0f <= _Mountain->GetPivot().ix())
		{
			_Mountain->SetPivotPos({ -1280.0f, -64.0f });
		}
	}

	if (2 == MountainDirectionValue_) // Turn Right
	{
		_Mountain->SetPivotMove(float4::LEFT * 32.0f);
		if (-1216.0f >= _Mountain->GetPivotPos().ix())
		{
			_Mountain->SetPivotPos({ 448.0f, -64.0f });
		}
	}
}

void RandomStage::MountainFrame()
{
	if (true == isCurve_)
	{
		Mountain1_->GetPivot();
		MountainMove(Mountain1_);
		MountainMove(Mountain2_);
	}
}

void RandomStage::CurveFrameCount()
{
	PlayLevel::frameCount_ = 26 * randomValue_.RandomInt(1, 1);
}

void RandomStage::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale(GameEngineWindow::GetScale());

	BackStage_ = CreateRenderer("BackStage.bmp", 100);
	LeftOcean_->SetPivot({ 0,-48 });

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

void RandomStage::TilemapChange()
{
	if (3 < RoundStateValue_)
	{
		MsgBoxAssert("존재하지 않는 상태입니다.");
		return;
	}
	
	if (true == PlayLevel::is2FrameUnit_)
	{
		PlayLevel::frameCount_ = 16 * RandomValue_.RandomInt(1, 1); // Change Time

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
					CurveTiles_->SetIndex(0); //TurnLeftOcean
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
					CurveTiles_->SetIndex(1); //TurnRightOcean
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
					CurveTiles_->SetIndex(3); //TurnRightGround
					CurveFrameCount();
				}
				if (0 == RoundStateValue_) // Turn Left
				{
					RoundStateValue_ = 3;
					isCurve_ = true;
					MountainDirectionValue_ = 1;
					CurveTiles_->SetIndex(2); //TurnLeftGround
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
			MsgBoxAssert("존재하지 않는 상태는 실행할 수 없습니다.");
			return;
		}
	}
}

void RandomStage::ResetStageOrder()
{
	BackStage_->SetOrder(100);
	LeftOcean_->SetOrder(100);
	RightOcean_->SetOrder(100);
	LeftGround_->SetOrder(100);
	RightGround_->SetOrder(100);
	CurveTiles_->SetOrder(100);
	Mountain1_->SetOrder(100);
	Mountain2_->SetOrder(100);
	LeftGlacier_->SetOrder(100);
	RightGlacier_->SetOrder(100);

}

void RandomStage::Update()
{
	

	if (true == PlayLevel::is1FrameUnit_)
	{
		float FrameTime = 2 * PlayLevel::frameTime_;

		LeftOcean_->SetFrameTime(FrameTime);
		RightOcean_->SetFrameTime(FrameTime);
		LeftGround_->SetFrameTime(FrameTime);
		RightGround_->SetFrameTime(FrameTime);
	}

	ResetStageOrder();
}

void RandomStage::Render()
{
	if (0 == PlayLevel::frameCount_)
	{
		TilemapChange();
	}

	BackStage_->SetOrder(102);
	Mountain1_->SetOrder(102);
	Mountain2_->SetOrder(102);

	switch (RoundStateValue_)
	{
	case 0:
		if (true == isCurve_)
		{
			MsgBoxAssert("존재하지 않는 상태입니다.");
			return;
		}
		LeftOcean_->SetOrder(102);
		RightOcean_->SetOrder(102);
		LeftGlacier_->SetOrder(102);
		RightGlacier_->SetOrder(102);
		break;

	case 1:
		LeftOcean_->SetOrder(102);
		RightGround_->SetOrder(102);
		if (true == isCurve_)
		{
			CurveTiles_->SetOrder(102);
		}
		else
		{
			LeftGlacier_->SetOrder(102);
		}
		break;

	case 2:
		LeftGround_->SetOrder(102);
		RightOcean_->SetOrder(102);
		if (true == isCurve_)
		{
			CurveTiles_->SetOrder(102);
		}
		else
		{
			RightGlacier_->SetOrder(102);
		}
		break;

	case 3:
		LeftGround_->SetOrder(102);
		RightGround_->SetOrder(102);
		if (true == isCurve_)
		{
			CurveTiles_->SetOrder(102);
		}
		break;

	default:
		MsgBoxAssert("존재하지 않는 상태는 실행할 수 없습니다.");
		return;
	}
}