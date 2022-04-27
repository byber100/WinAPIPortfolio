#include "MainMap.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>


// Static Var

// Static Func

// constructor destructor
MainMap::MainMap()
{
}

MainMap::~MainMap()
{
}

//member Func
void MainMap::Start()
{
	SetPosition(float4::ZERO);
	SetScale(GameEngineWindow::GetScale());

	Map_ = CreateRenderer("Map.bmp", 2, RenderPivot::LEFTTOP);
	LevelRegist("Map");
}
void MainMap::Update()
{
	
}
void MainMap::Render()
{

}