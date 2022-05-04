#include "Title.h"
#include "LevelChanger.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineSound.h>


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
	MainRender_->CreateAnimation("Titles.bmp", "TitleAnim", 2, 3, 0.2f);
	MainRender_->SetIndex(0);

	VeiledRender_ = CreateRenderer("ImageBlinder.bmp");
	VeiledRender_->SetPivot({ 140,-520 });

	GameEngineInput::GetInst()->CreateKey("Select", '1');

	ChangerInfo_ = dynamic_cast<LevelChanger*>(GetLevel()->FindActor("LevelChanger"));
}

void Title::Update()
{
	if (true == ChangerInfo_->GetChanging())
	{
		ChangerInfo_->LevelChangeAnim("Map");
	}

	if (false == ChangerInfo_->GetChanging() && 1100.f > VeiledRender_->GetPivot().x)
	{
		VeiledRender_->SetPivotMove(float4::RIGHT * 1500.0f * GameEngineTime::GetDeltaTime());
	}

	if (2.8 < GetAccTime())
	{
		if (false == ChangerInfo_->GetChanging())
		{
			VeiledRender_->SetPivot({ 1000, 1000 });

			if (GameEngineInput::GetInst()->IsDown("Select"))
			{
				ChangerInfo_->LevelChangeAnim("Map");
			}
		}
	}
	else if (2.5f < GetAccTime())
	{
		VeiledRender_->SetPivot(float4::ZERO);
		MainRender_->ChangeAnimation("TitleAnim");
		GameEngineSound::SoundPlayOneShot("TitleBGM.mp3");
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