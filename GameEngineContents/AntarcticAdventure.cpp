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
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 1024, 768 });

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
	//{
	//	GameEngineDirectory ResourcesDir;
	//	ResourcesDir.MoveParent("WinAPIPortfolio");
	//	ResourcesDir.Move("Resources");
	//	ResourcesDir.Move("Sound");

	//	std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile();

	//	for (size_t i = 0; i < AllImageFileList.size(); i++)
	//	{
	//		GameEngineSound::LoadRes(AllImageFileList[i].GetFullPath());
	//	}
	//}

	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("OceanTiles.bmp");
		Image->CutCount(4, 2);
	}
	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("GroundTiles.bmp");
		Image->CutCount(2, 2);
	}
	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("CurveTiles.bmp");
		Image->CutCount(1, 4);
	}
	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("Glaciers.bmp");
		Image->CutCount(1, 2);
	}
	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("Player.bmp");
		Image->CutCount(5, 3);
	}
	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("HoleTraps.bmp");
		Image->CutCount(1, 9);
	}
	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("InterfaceWords.bmp");
		Image->CutCount(13, 1);
	}

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