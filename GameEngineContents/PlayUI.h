#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class PlayUI : public GameEngineActor
{
private:
	// Interface Renderer //////////////////////////////////////////////////////
	GameEngineRenderer* ScroeTile1_;
	GameEngineRenderer* ScroeTile2_;
	GameEngineRenderer* ScroeTile3_;
	GameEngineRenderer* ScroeTile4_;
	GameEngineRenderer* ScroeTile5_;
	GameEngineRenderer* ScroeTile6_;

	GameEngineRenderer* HiScroeTile1_;
	GameEngineRenderer* HiScroeTile2_;
	GameEngineRenderer* HiScroeTile3_;
	GameEngineRenderer* HiScroeTile4_;
	GameEngineRenderer* HiScroeTile5_;
	GameEngineRenderer* HiScroeTile6_;

	GameEngineRenderer* StageTile1_;
	GameEngineRenderer* StageTile2_;

	GameEngineRenderer* TimeOutTile1_;
	GameEngineRenderer* TimeOutTile2_;
	GameEngineRenderer* TimeOutTile3_;
	GameEngineRenderer* TimeOutTile4_;

	GameEngineRenderer* RestDistanceTile1_;
	GameEngineRenderer* RestDistanceTile2_;
	GameEngineRenderer* RestDistanceTile3_;
	GameEngineRenderer* RestDistanceTile4_;

	GameEngineRenderer* SpeedTile1_;
	GameEngineRenderer* SpeedTile2_;
	GameEngineRenderer* SpeedTile3_;
	GameEngineRenderer* SpeedTile4_;
	GameEngineRenderer* SpeedTile5_;
	GameEngineRenderer* SpeedTile6_;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int Score_;
	int HiScore_;
	int Stage_;
	int TimeOut_;
	int Speed_;

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



protected:

private:
	void Start() override;
	void Update() override;
	void Render() override;
};

