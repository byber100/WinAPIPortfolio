#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineFont.h>

enum PlayerState
{
	Move,
	Jump,
	JumpL,
	JumpR,
	TakeHit,
	TakeHitL,
	TakeHitR,
	FallIn,
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
	float4 PushDir_;
	int BounceCnt_;
	bool isBounce_;

	PlayerState CurState_;
	GameEngineRenderer* Penguin_;
	GameEngineRenderer* Shadow_;
	GameEngineCollision* PlayerLeftCol_;
	GameEngineCollision* PlayerRightCol_;

	GameEngineSoundPlayer PlayBGM_;

	bool isClear_;
	bool ClearSoundOn_;
	float TriggerTime_; // ���� �÷��̾� �̺�Ʈ�� ���� ��

	GameEngineFont DedugText_;
	bool DebugModeOn_;

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
	bool IsJump()
	{
		return isJumping_;
	}

protected:

public:
	void ChangeState(PlayerState _State);

private:
	void DebugPlayerOn();
	void JumpLoop();
	void PushLoop();
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
	void TakeHitStart();
	void FallInStart();

	void MoveUpdate();
	void JumpUpdate();
	void JumpLUpdate();
	void JumpRUpdate();
	void PauseUpdate();
	void ClearUpdate();
	void CeremonyUpdate();
	void TakeHitUpdate();
	void FallInUpdate();
};

