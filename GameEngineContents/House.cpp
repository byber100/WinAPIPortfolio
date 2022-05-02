#include "House.h"
#include "PlayLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>


// Static Var
int House::LOD_ = 0;
// Static Func

// constructor destructor
House::House()
	: DownTime_(0)
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
	//DownTime_ -= 0.07f * GameEngineTime::GetDeltaTime();
	//if (0.0f >= DownTime_)
	//{
	//	if (false == PlayLevel::is2FrameUnit_)
	//	{
	//		++LOD_;
	//		DownTime_ = PlayLevel::PlayLevelStage->GetCurframeTime();
	//	}
	//}

	switch (LOD_)
	{
	case 0:
		break;
	case 1:
		House_ = CreateRenderer("House1.bmp", 200);
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;

	case 5:
		House_->SetOrder(0);
		House_ = CreateRenderer("House2.bmp", 200);
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;

	case 10:
		House_->SetOrder(0);
		House_ = CreateRenderer("House3.bmp", 200);
		break;
	case 11:
		break;
	case 12:
		break;
	case 13:
		break;
	case 14:
		break;

	case 15:
		House_->SetOrder(0);
		House_ = CreateRenderer("House4.bmp", 200);
		break;
	case 16:
		break;
	case 17:
		break;
	case 18:
		break;
	case 19:
		break;

	case 20:
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