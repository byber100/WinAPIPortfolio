#include "LevelChanger.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>


// Static Var

// Static Func

// constructor destructor
LevelChanger::LevelChanger()
	: Changing_(false)
{
}

LevelChanger::~LevelChanger()
{
}

//member Func
void LevelChanger::LevelChangeAnim(const std::string& _NextLevel)
{
	if (true == Changing_)
	{
		if (800.f > VeiledRender_->GetScale().x)
		{
			VeiledRender_->SetIncreasinglyScale({ 1,0 });
		}
		else
		{
			GameEngine::GetInst().ChangeLevel(_NextLevel);
		}
	}
	else
	{
		VeiledRender_->SetPivot(float4::ZERO);
		VeiledRender_->SetScale({ 0, GetScale().y });
		Changing_ = true;
	}
}

void LevelChanger::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale(GameEngineWindow::GetScale());

	VeiledRender_ = CreateRenderer("ImageBlinder.bmp", 400);
	VeiledRender_->SetPivot({ 1000,1000 });

	LevelRegist("LevelChanger");
}

void LevelChanger::Update()
{

}
