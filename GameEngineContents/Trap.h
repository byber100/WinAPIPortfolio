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
	Seal,
	Fish,
	Flag,
	Crack
};

class Trap : public GameEngineActor
{
private:	// member Var
	TrapEvent Event_;
	SpawnLoc Spawn_;
	float4 DirVector_;
	int LOD_;

	GameEngineRenderer* Trap_;
	GameEngineRenderer* Object_;

	GameEngineCollision* TrapCol_;
	GameEngineCollision* TrapCenterCol_;
	GameEngineCollision* L_FishCol_;
	GameEngineCollision* R_FishCol_;

public:		
	Trap(); // default constructor ����Ʈ ������
	~Trap(); // default destructor ����Ʈ �Ҹ���

public:		// delete constructor
	Trap(const Trap& _Other) = delete; // default Copy constructor ����Ʈ ���������
	Trap(Trap&& _Other) noexcept = delete; // default RValue Copy constructor ����Ʈ RValue ���������

public:		//delete operator
	Trap& operator=(const Trap& _Other) = delete; // default Copy operator ����Ʈ ���� ������
	Trap& operator=(const Trap&& _Other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:
	void Hit(const TrapEvent& _Event);

	void Start() override;
	void Update() override;
	void Render() override;
};

