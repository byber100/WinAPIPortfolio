#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class GameEngineRenderer;
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

protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:
	GameEngineRenderer* MainRender_;
	GameEngineRenderer* VeiledRender1_;
	GameEngineRenderer* VeiledRender2_;

	bool ChangeLevel_;

	void LevelChangeAnim();
};

