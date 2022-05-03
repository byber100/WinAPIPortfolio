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
	Flag
};

class Trap : public GameEngineActor
{
private:	// member Var
	float4 DirVector_;
	int LOD_;
	SpawnLoc Spawn_;

	GameEngineRenderer* Hole_;

	GameEngineCollision* HoleCol_;
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

protected:
	void Start() override;
	void Update() override;
	void Render() override;
};

