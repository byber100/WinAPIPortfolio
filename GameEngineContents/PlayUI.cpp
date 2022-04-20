#include "PlayUI.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

PlayUI::PlayUI()
{
}

PlayUI::~PlayUI()
{
}


void PlayUI::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale(GameEngineWindow::GetScale());

	GameEngineRenderer* Renderer = CreateRenderer("BackInterface.bmp", 400);
	
}

void PlayUI::Update()
{
	
}

void PlayUI::Render()
{
	
}