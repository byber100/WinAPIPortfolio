#include "AntarcticAdventure.h"
#include "PlayLevel.h"
#include "TitleLevel.h"
#include "CompanyLevel.h"
#include "MapLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineSound.h>

AntarcticAdventure::AntarcticAdventure()
{
	// 업데이트 오더 범위
	// ~100: 기타 레벨의 액터
	// ~200: 플레이 트랩 액터
	// ~300: 플레이어
	// ~400: 레벨체인저
	// ~500: 플레이 UI
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
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("Titles.bmp");
		Image->CutCount(1, 4);
	}
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
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("PlayerShadow.bmp");
		Image->CutCount(1, 4);
	}
	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("InterfaceWords.bmp");
		Image->CutCount(13, 1);
	}
	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("HoleTraps.bmp");
		Image->CutCount(1, 9);
	}

	CreateLevel<CompanyLevel>("Company");
	CreateLevel<TitleLevel>("Title");
	CreateLevel<MapLevel>("Map");
	CreateLevel<PlayLevel>("Play");
	ChangeLevel("Play");
}

void AntarcticAdventure::GameLoop()
{

}
void AntarcticAdventure::GameEnd()
{

}