#include "PlayUI.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

int PlayUI::RestDistance_ = 1500;

PlayUI::PlayUI()
	: Score_(0)
	, HiScore_(0)
	, Stage_(1)
	, TimeOut_(100)
	, Speed_(5)
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