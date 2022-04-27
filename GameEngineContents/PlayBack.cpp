#include "PlayBack.h"


// Static Var

// Static Func

// constructor destructor
PlayBack::PlayBack()
{
}

PlayBack::~PlayBack()
{
}

//member Func
void PlayBack::Start()
{
	GameEngineRenderer* Renderer = CreateRenderer("PlayBack.bmp", 500, RenderPivot::LEFTTOP);
}