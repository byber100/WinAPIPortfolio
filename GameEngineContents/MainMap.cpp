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
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale(GameEngineWindow::GetScale());

	MapImage_ = CreateRenderer("Map.bmp", 2);
	MapImage_->SetPivot({ 0,35 });
}
void MainMap::Update()
{
	
}
void MainMap::Render()
{

}