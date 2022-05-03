#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>

// 설명 :
class Player;
class PlayUI;
class RandomStage;
class LevelChanger;
class House;
class PlayLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	PlayLevel();
	~PlayLevel();

private:
	// delete Function
	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;

	float CurframeTime_;
	int FrameUnitCount_; // 게임프레임 최소 단위시간

	float UnitSecond_;
	bool ArriveOn_;

	GameEngineSoundPlayer BgmPlayer;

	LevelChanger* LevelChanger_;
	House* HouseInfo_;

	bool isColDebug_;

public:
	static PlayLevel* PlayLevelStage;
	static int FrameCount;
	static bool is2FrameUnit_; // 2번째 단위시간

	static bool LevelChangeOn_;

	float GetLevelInterTime();
	float GetCurframeTime()
	{
		return CurframeTime_;
	}

protected:
	void Loading() override;
	void Update() override;

	void LevelChangeStart(GameEngineLevel* _NextLevel) override;
	void LevelChangeEnd(GameEngineLevel* _PrevLevel) override;

private:
	void Arrive();
};