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

	LeftOcean_ = CreateRenderer("OceanTiles.bmp");
	LeftOcean_->SetPivot({ -416, -32 });
	LeftOcean_->CreateAnimation("OceanTiles.bmp", "LeftOcean", 0, 3, 0.2f);
	LeftOcean_->ChangeAnimation("LeftOcean");



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