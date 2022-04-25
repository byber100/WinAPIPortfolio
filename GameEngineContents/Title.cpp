#include "Title.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngine.h>


Title::Title() 
	: ChangeLevel_(false)
{
	
}

Title::~Title() 
{
}

void Title::LevelChangeAnim()
{
	if (true == ChangeLevel_)
	{
		if (800.f > VeiledRender1_->GetScale().x)
		{
			VeiledRender1_->SetincreasinglyScale({ 1,0 });
		}
		else
		{
			GameEngine::GetInst().ChangeLevel("Play");
		}
	}
	else
	{
		VeiledRender1_->SetPivot(float4::ZERO);
		VeiledRender1_->SetScale({ 0, GetScale().y });
		ChangeLevel_ = true;
	}
}

void Title::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale(GameEngineWindow::GetScale());

	MainRender_ = CreateRenderer("Titles.bmp");
	MainRender_->CreateAnimation("Titles.bmp", "TitleAnim", 2, 3, 0.2f);
	MainRender_->SetIndex(0);

	VeiledRender1_ = CreateRenderer("ImageBlinder.bmp");
	VeiledRender1_->SetPivot({ 140,-520 });

	GameEngineInput::GetInst()->CreateKey("Select", '1');
}

void Title::Update()
{
	if (true == ChangeLevel_)
	{
		LevelChangeAnim();
	}

	if (false == ChangeLevel_ && 1100.f > VeiledRender1_->GetPivot().x)
	{
		VeiledRender1_->SetPivotMove(float4::RIGHT * 1500.0f * GameEngineTime::GetDeltaTime());
	}

	if (2.8 < GetAccTime())
	{
		if (false == ChangeLevel_)
		{
			VeiledRender1_->SetPivot({ 1000, 1000 });

			if (GameEngineInput::GetInst()->IsDown("Select"))
			{
				LevelChangeAnim();
			}
		}
	}
	else if (2.5f < GetAccTime())
	{
		VeiledRender1_->SetPivot(float4::ZERO);
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