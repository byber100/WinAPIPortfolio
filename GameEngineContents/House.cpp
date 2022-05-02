#include "House.h"
#include "PlayUI.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>


// Static Var

// Static Func

// constructor destructor
House::House()
	: LOD_(0)
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

	switch (LOD_)
	{
	case 0:
		House_ = CreateRenderer("House1.bmp", 200);
		break;
	case 1:
		House_->SetOrder(0);
		House_ = CreateRenderer("House2.bmp", 200);
		break;
	case 2:
		House_->SetOrder(0);
		House_ = CreateRenderer("House3.bmp", 200);
		break;
	case 3:
		House_->SetOrder(0);
		House_ = CreateRenderer("House4.bmp", 200);
		break;
	case 4:
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