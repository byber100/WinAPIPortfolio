#include "PlayLevel.h"
#include "Player.h"
#include "PlayUI.h"
#include "RandomStage.h"
#include <GameEngineBase/GameEngineTime.h>

enum class ORDER
{
	BACKGROUND,
	PLAYER,
	UI
};

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::Loading()
{
	CreateActor<RandomStage>();
	CreateActor<Player>();
	CreateActor<PlayUI>();

}

void PlayLevel::Update() 
{
	//Time -= GameEngineTime::GetDeltaTime();

	//if (0 >= Time)
	//{
	//	BgmPlayer.Stop();
	//}
}
void PlayLevel::LevelChangeStart()
{
	// Player->SetPosition();

	// BgmPlayer = GameEngineSound::SoundPlayControl("BGM.MP3");

	//GameEngineSound::SoundPlayOneShot("vo_shk.mp3");
	//Time = 5.0f;

}