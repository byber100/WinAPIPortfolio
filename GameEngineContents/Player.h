#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSound.h>

// 어떠한 객체는 1번에 1개의 상태만이 존재한다.
// 플레이어는 1번에 1개의 함수밖에 실행할수 없다.

// if 플레이어가 공격 중이라면
//    if 플레이어가 이동중이 아니라면
//       if

enum PlayerState
{
	Move,
	Jump,
	JumpL,
	JumpR,
	TakeHit,
	Clear,
	Max
};

// 설명 :
class Player : public GameEngineActor
{
private:
	float ForwardSpeed_;
	float SideSpeed_;
	bool isJumping_;
	float4 JumpDir_;

	PlayerState CurState_;
	GameEngineRenderer* Penguin_;
	GameEngineRenderer* Shadow_;

public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	float GetForwardSpeed()
	{
		return ForwardSpeed_;
	}

protected:

private:
	void JumpLoop();
	void ChangeState(PlayerState _State);
	void StateUpdate();

	void Start() override;
	void Update() override;
	void Render() override;

	void IdleStart();
	void MoveStart();
	void JumpStart();

	void IdleUpdate();
	void MoveUpdate();
	void JumpUpdate();
	void JumpLUpdate();
	void JumpRUpdate();
};

