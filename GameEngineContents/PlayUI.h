#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFont.h>

// ���� :
class Player;
class PlayUI : public GameEngineActor
{
public:
	static PlayUI* MainUI;

private:
	// Interface Renderer //////////////////////////////////////////////////////
	std::vector<GameEngineRenderer*> ScoreImages;
	GameEngineRenderer* ScoreTile1_; // 240 92
	GameEngineRenderer* ScoreTile2_;
	GameEngineRenderer* ScoreTile3_;
	GameEngineRenderer* ScoreTile4_;
	GameEngineRenderer* ScoreTile5_;
	GameEngineRenderer* ScoreTile6_;

	std::vector<GameEngineRenderer*> HiScoreImages;
	GameEngineRenderer* HiScoreTile1_; // 496 92
	GameEngineRenderer* HiScoreTile2_;
	GameEngineRenderer* HiScoreTile3_;
	GameEngineRenderer* HiScoreTile4_;
	GameEngineRenderer* HiScoreTile5_;
	GameEngineRenderer* HiScoreTile6_;

	std::vector<GameEngineRenderer*> StageImages;
	GameEngineRenderer* StageTile1_; // 816 92
	GameEngineRenderer* StageTile2_;

	std::vector<GameEngineRenderer*> TimeCountImages;
	GameEngineRenderer* TimeCountTile1_; // 288 124
	GameEngineRenderer* TimeCountTile2_;
	GameEngineRenderer* TimeCountTile3_;
	GameEngineRenderer* TimeCountTile4_;

	std::vector<GameEngineRenderer*> RestDistanceImages;
	GameEngineRenderer* RestDistanceTile1_; // 496 124
	GameEngineRenderer* RestDistanceTile2_;
	GameEngineRenderer* RestDistanceTile3_;
	GameEngineRenderer* RestDistanceTile4_;

	GameEngineRenderer* SpeedTile1_; // 752 124
	GameEngineRenderer* SpeedTile2_;
	GameEngineRenderer* SpeedTile3_;
	GameEngineRenderer* SpeedTile4_;
	GameEngineRenderer* SpeedTile5_;
	GameEngineRenderer* SpeedTile6_;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int Score_;
	int HiScore_;
	int Stage_;
	int Speed_;
	int CountTime_;

	GameEngineFont DedugText_;
	bool VeiledDebuging_;


public:
	// constrcuter destructer
	PlayUI();
	~PlayUI();

	// delete Function
	PlayUI(const PlayUI& _Other) = delete;
	PlayUI(PlayUI&& _Other) noexcept = delete;
	PlayUI& operator=(const PlayUI& _Other) = delete;
	PlayUI& operator=(PlayUI&& _Other) noexcept = delete;

	static int RestDistance_;

	int GetCountTime()
	{
		return CountTime_;
	}
	void SetCountTime(int _Count)
	{
		CountTime_ = _Count;
	}
	int GetStage()
	{
		return Stage_;
	}

protected:

private:
	void NumberUpdate(int _Object, const std::vector<GameEngineRenderer*> ScoreImage);
	void DebugUIOn();

	void UpdateSpeed();

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

	void Start() override;
	void Update() override;
	void Render() override;
};

