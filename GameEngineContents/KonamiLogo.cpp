#include "KonamiLogo.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>

// Static Var

// Static Func

// constructor destructor
KonamiLogo::KonamiLogo()
{
}

KonamiLogo::~KonamiLogo()
{
}

//member Func
void KonamiLogo::Start()
{
	SetPosition({ GameEngineWindow::GetScale().Half().x, 700 });
	SetScale(GameEngineWindow::GetScale());

	Konami_ = CreateRenderer("Konami.bmp", 1);
}
void KonamiLogo::Update()
{
	if (350 < GetPosition().iy())
	{
		SetMove(float4::UP * GameEngineTime::GetDeltaTime() * 800);
	}
}
void KonamiLogo::Render()
{
	
}