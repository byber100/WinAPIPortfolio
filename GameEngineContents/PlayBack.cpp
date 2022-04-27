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
	GameEngineRenderer* Renderer = CreateRenderer("BackInterface.bmp", 500, RenderPivot::LEFTTOP);
}