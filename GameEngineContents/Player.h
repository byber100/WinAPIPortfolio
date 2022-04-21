#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSound.h>

// ��� ��ü�� 1���� 1���� ���¸��� �����Ѵ�.
// �÷��̾�� 1���� 1���� �Լ��ۿ� �����Ҽ� ����.

// if �÷��̾ ���� ���̶��
//    if �÷��̾ �̵����� �ƴ϶��
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

// ���� :
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

