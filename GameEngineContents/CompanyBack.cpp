#include "CompanyBack.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>


// Static Var

// Static Func

// constructor destructor
CompanyBack::CompanyBack()
{
}

CompanyBack::~CompanyBack()
{
}

//member Func
void CompanyBack::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale(GameEngineWindow::GetScale());

	BackGround_ = CreateRenderer("BackCompany.bmp", 1);
	Software_ = CreateRenderer("Software.bmp", 0);
	Software_->SetPivot({ 0, 50 });
}
void CompanyBack::Update()
{
	if (0.5f < GetAccTime())
	{
		Software_->SetOrder(1);
	}
	if (3.0f < GetAccTime())
	{
		GameEngine::GetInst().ChangeLevel("Title");
	}
}
void CompanyBack::Render()
{

}