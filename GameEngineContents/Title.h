#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class GameEngineRenderer;
class LevelChanger;
class Title : public GameEngineActor
{
public:
	// constrcuter destructer
	Title();
	~Title();

	// delete Function
	Title(const Title& _Other) = delete;
	Title(Title&& _Other) noexcept = delete;
	Title& operator=(const Title& _Other) = delete;
	Title& operator=(Title&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
	void Render() override;

private:
	GameEngineRenderer* MainRender_;
	GameEngineRenderer* VeiledRender_;

	LevelChanger* ChangerInfo_;
};

