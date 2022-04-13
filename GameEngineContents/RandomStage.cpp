#include "RandomStage.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

// Static Var

// Static Func

// constructor destructor
RandomStage::RandomStage()
	: randomValue_(0)
	, roundStateValue_(3)
	, mountainDirectionValue_(0)
	, isCurve_(false)
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

	LeftOcean_ = CreateRenderer(100, RenderPivot::LEFTTOP);
	LeftOcean_->SetPivot({ -416, -32 });
	LeftOcean_->CreateAnimation("OceanTiles.bmp", "LeftOcean", 0, 3, 0.2f);
	LeftOcean_->ChangeAnimation("LeftOcean");

	rightOcean_ = CreateRenderer(100, RenderPivot::LEFTTOP);
	rightOcean_->SetPivot({ 0, -32 });
	rightOcean_->CreateAnimation("OceanTiles.bmp", "RightOcean", 4, 7, 0.2f);
	rightOcean_->ChangeAnimation("RightOcean");

	leftGround_ = CreateRenderer(100, RenderPivot::LEFTTOP);
	leftGround_->SetPivot({ -416, -32 });
	leftGround_->CreateAnimation("GroundTiles.bmp", "LeftGround", 0, 1, 0.2f);
	leftGround_->ChangeAnimation("LeftGround");

	rightGround_ = CreateRenderer(100, RenderPivot::LEFTTOP);
	rightGround_->SetPivot({ 0, -32 });
	rightGround_->CreateAnimation("GroundTiles.bmp", "RightGround", 2, 3, 0.2f);
	rightGround_->ChangeAnimation("RightGround");

	//LeftOcean_ = CreateRenderer("OceanTiles.bmp");
	//LeftOcean_->SetPivot({ -416, -32 });
	//LeftOcean_->SetIndex(0);

}

void RandomStage::Update()
{

}

void RandomStage::Render()
{

}