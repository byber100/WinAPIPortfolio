#include "House.h"
#include "PlayLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>


// Static Var

// Static Func

// constructor destructor
House::House()
	: LOD_(0)
	, DownTime_(0)
	, House_(nullptr)
{
}

House::~House()
{
}

//member Func
void House::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());

	LevelRegist("House");
}

void House::Update()
{
	DownTime_ -= 0.07f * GameEngineTime::GetDeltaTime();
	if (0.0f >= DownTime_)
	{
		if (false == PlayLevel::is2FrameUnit_)
		{
			++LOD_;
			DownTime_ = PlayLevel::PlayLevelStage->GetCurframeTime();
		}
	}

	switch (LOD_)
	{
	case 0:
		break;
	case 1:
		House_ = CreateRenderer("House1.bmp", 200);
		break;

	case 2:
		House_->SetOrder(0);
		House_ = CreateRenderer("House2.bmp", 200);
		break;

	case 3:
		House_->SetOrder(0);
		House_ = CreateRenderer("House3.bmp", 200);
		break;

	case 4:
		House_->SetOrder(0);
		House_ = CreateRenderer("House4.bmp", 200);
		break;

	case 5:
		House_->SetOrder(0);
		House_ = CreateRenderer("House5.bmp", 200);
		break;
	default:
		break;
	}
}

void House::Render()
{

}