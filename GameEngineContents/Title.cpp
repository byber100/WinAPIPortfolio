#include "Title.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>


Title::Title() 
{
	
}

Title::~Title() 
{
}

void Title::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale(GameEngineWindow::GetScale());

	MainRender_ = CreateRenderer("Titles.bmp");
	MainRender_->CreateAnimation("Titles.bmp", "TitleAnim", 2, 3, 0.5f);
	MainRender_->SetIndex(0);

	VeiledRender_ = CreateRenderer("Titles.bmp");
	VeiledRender_->SetIndex(0);
	VeiledRender_->SetPivot({ 140,-520 });

	GameEngineInput::GetInst()->CreateKey("Select", '1');
}

void Title::Update()
{
	if (1100.f > VeiledRender_->GetPivot().x)
	{
		VeiledRender_->SetPivotMove(float4::RIGHT * 1500.0f * GameEngineTime::GetDeltaTime());
	}

	if (2.5f < GetAccTime())
	{
		if (GameEngineInput::GetInst()->IsDown("Select"))
		{
			GameEngine::GetInst().ChangeLevel("Play");
		}

		MainRender_->ChangeAnimation("TitleAnim");
	}
	else if (1.0f < GetAccTime())
	{
		MainRender_->SetIndex(3);
	}
	else if (0.5f < GetAccTime())
	{
		MainRender_->SetIndex(1);
	}
}

void Title::Render() 
{
	
}