#include "House.h"
#include "PlayUI.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>


// Static Var
bool House::isFlagUp_ = false;
// Static Func

// constructor destructor
House::House()
	: LOD_(0)
	, FlagFrameTime_(0)
	, House_(nullptr)
	, Flag_(nullptr)
{
}

House::~House()
{
}

//member Func
void House::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());

	Flag_ = CreateRenderer("Flag.bmp", 0, RenderPivot::LEFTTOP);
	Flag_->SetPivot({ 0,-56 });
}

void House::Update()
{
	if (true == isFlagUp_)
	{
		Flag_->SetOrder(200);

		FlagFrameTime_ += GameEngineTime::GetInst()->GetDeltaTime();
		if (0.3f < FlagFrameTime_)
		{
			if (-130 < Flag_->GetPivot().y)
			{
				float Up = Flag_->GetPivot().y;
				Flag_->SetPivot({ 0,Up - 12 });
			}
			FlagFrameTime_ = 0;
		}
	}

	if (60 == PlayUI::RestDistance_)
	{
		LOD_ = 0;
	}
	if (45 == PlayUI::RestDistance_)
	{
		LOD_ = 1;
	}
	else if (30 == PlayUI::RestDistance_)
	{
		LOD_ = 2;
	}
	else if (15 == PlayUI::RestDistance_)
	{
		LOD_ = 3;
	}
	else if (0 == PlayUI::RestDistance_)
	{
		LOD_ = 4;
	}
	else if (60 < PlayUI::RestDistance_)
	{
		LOD_ = 5;
	}
}

void House::Render()
{
	switch (LOD_)
	{
	case 0:
		House_ = CreateRenderer("House1.bmp", 201);
		break;
	case 1:
		House_->SetOrder(0);
		House_ = CreateRenderer("House2.bmp", 201);
		break;
	case 2:
		House_->SetOrder(0);
		House_ = CreateRenderer("House3.bmp", 201);
		break;
	case 3:
		House_->SetOrder(0);
		House_ = CreateRenderer("House4.bmp", 201);
		break;
	case 4:
		House_->SetOrder(0);
		House_ = CreateRenderer("House5.bmp", 201);
		break;
	default:
		break;
	}
}