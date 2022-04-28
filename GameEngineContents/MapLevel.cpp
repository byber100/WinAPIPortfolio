#include "MapLevel.h"
#include "ContentsEnum.h"
#include "MainMap.h"
#include "LevelChanger.h"
#include "Player.h"
#include "PlayUI.h"
#include "PathPoint.h"
#include <GameEngineBase/GameEngineInput.h>


// Static Var

// Static Func

// constructor destructor
MapLevel::MapLevel()
{
	//HBRUSH h_brush = CreateSolidBrush(RGB(73, 67, 254));
	//RECT r = { 0,0,GameEngineWindow::GetScale().ix(),GameEngineWindow::GetScale().iy() };
	//FillRect(GameEngine::BackBufferDC(), &r, h_brush);
	//DeleteObject(h_brush);
}

MapLevel::~MapLevel()
{
}

//member Func
void MapLevel::Loading()
{
	if (nullptr == PlayUI::MainUI)
	{
		PlayUI::MainUI = CreateActor<PlayUI>((int)ORDER::UI, "MainUI");
	}

	LevelChanger_ = CreateActor<LevelChanger>((int)ORDER::UI);
	CreateActor<MainMap>((int)ORDER::BACKGROUND);
	
	GameEngineInput::GetInst()->CreateKey("GameStart", VK_SPACE);
}

void MapLevel::Update()
{
	//test////////////////////////////////////////
	if (true == LevelChanger_->GetChanging())
	{
		LevelChanger_->LevelChangeAnim("Play");
	}
	if (GameEngineInput::GetInst()->IsDown("GameStart"))
	{
		GameEngineInput::GetInst()->Reset();
		dynamic_cast<LevelChanger*>(FindActor("LevelChanger"))->LevelChangeAnim("Play");
	}
	
	//if (0 == PathAll_.size())
	//{
	//	PathPoint* Path = CreateActor<PathPoint>((int)ORDER::BACKGROUND);
	//	Path->Draw(DrawMode::Point, { 643,575 });
	//	PathAll_.push_back(Path);
	//}
	if (0 == PathAll_.size())
	{
		PathPoint* Path = CreateActor<PathPoint>((int)ORDER::BACKGROUND);
		Path->Draw(DrawMode::Line, { 500,500 }, float4::LEFT, 100.f, LineColor::GRAY);
		PathAll_.push_back(Path);
	}
}

void MapLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	
}

void MapLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	PlayUI::MainUI->NextLevelOn();
}