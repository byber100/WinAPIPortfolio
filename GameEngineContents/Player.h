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
	Pause
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
	void SetForwardSpeed(float _Speed)
	{
		ForwardSpeed_ = _Speed;
	}

protected:

public:
	void ChangeState(PlayerState _State);

private:
	void JumpLoop();
	void StateUpdate();

	void Start() override;
	void Update() override;
	void Render() override;

	void IdleStart();
	void MoveStart();
	void JumpStart();
	void PauseStart();

	void IdleUpdate();
	void MoveUpdate();
	void JumpUpdate();
	void JumpLUpdate();
	void JumpRUpdate();
	void PauseUpdate();
};

