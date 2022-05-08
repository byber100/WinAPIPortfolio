#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� :
// �뵵 :
// ���� :
enum class SpawnLoc
{
	LEFT,
	CENTER,
	RIGHT
};

enum class TrapEvent
{
	None,
	Hole,
	Seal,
	Fish,
	Flag,
	Crack
};

enum class FishState
{
	None,
	Create,
	Jump
};

class Trap : public GameEngineActor
{
private:	// member Var
	bool SetComplete_;
	TrapEvent Event_;
	SpawnLoc Spawn_;
	float4 DirVector_;
	int LOD_;
	bool isFishLeft_;

	float4 FishDir_;
	FishState FishState_;

	GameEngineRenderer* Trap_;
	GameEngineRenderer* Seal_;
	GameEngineRenderer* Fish_;

	GameEngineCollision* TrapCol_;
	GameEngineCollision* TrapCenterCol_;
	GameEngineCollision* FishCol_;

public:		
	Trap(); // default constructor ����Ʈ ������
	~Trap(); // default destructor ����Ʈ �Ҹ���

public:		// delete constructor
	Trap(const Trap& _Other) = delete; // default Copy constructor ����Ʈ ���������
	Trap(Trap&& _Other) noexcept = delete; // default RValue Copy constructor ����Ʈ RValue ���������

public:		//delete operator
	Trap& operator=(const Trap& _Other) = delete; // default Copy operator ����Ʈ ���� ������
	Trap& operator=(const Trap&& _Other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void TrapSetting(TrapEvent _Event, SpawnLoc _Spawn);

private:
	void Hit(const TrapEvent& _Event);

	void Start() override;
	void Update() override;
	void Render() override;
};

