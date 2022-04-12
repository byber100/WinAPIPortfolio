#include "AntarcticAdventure.h"
#include "PlayLevel.h"
#include "TitleLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineSound.h>

AntarcticAdventure::AntarcticAdventure()
{
}

AntarcticAdventure::~AntarcticAdventure()
{
}

void AntarcticAdventure::GameInit()
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 1280, 768 });


	{
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("WinAPIPortfolio");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Image");

		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}
	}

	{

		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("WinAPIPortfolio");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Sound");

		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile();

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineSound::LoadRes(AllImageFileList[i].GetFullPath());
		}

	}


	//GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("Right_Beam_Kirby.bmp");
	//Image->Cut({ 256, 256 });


	CreateLevel<TitleLevel>("Title");
	CreateLevel<PlayLevel>("Play");

	ChangeLevel("Play");
}

void AntarcticAdventure::GameLoop()
{

}
void AntarcticAdventure::GameEnd()
{

}