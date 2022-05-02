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
	Ceremony,
	Pause,
	MAX
};

// ���� :
class GameEngineSound;
class Player : public GameEngineActor
{
public:
	static Player* MainPlayer;

private:
	float ForwardSpeed_;
	float SideSpeed_;
	bool isJumping_;
	float4 JumpDir_;

	PlayerState CurState_;
	GameEngineRenderer* Penguin_;
	GameEngineRenderer* Shadow_;

	GameEngineSoundPlayer PlayBGM_;

	bool isClear_;
	bool ClearSoundOn_;
	float ClearTime_;

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
	bool IsClear()
	{
		return isClear_;
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
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;


	void MoveStart();
	void JumpStart();
	void PauseStart();
	void ClearStart();
	void CeremonyStart();

	void MoveUpdate();
	void JumpUpdate();
	void JumpLUpdate();
	void JumpRUpdate();
	void PauseUpdate();
	void ClearUpdate();
	void CeremonyUpdate();
};

