#include "PlayUI.h"

PlayUI::PlayUI()
{
}

PlayUI::~PlayUI()
{
}


void PlayUI::Start()
{
	SetPosition({ 640, 600 });
	SetScale({ 1280, 200 });
}

void PlayUI::Render()
{
	DebugRectRender();
}