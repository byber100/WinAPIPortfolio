#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� :
// �뵵 :
// ���� :
class HoleTrap : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* Hole_;

	float4 DirVector_;
	int LOD_;

public:		
	HoleTrap(); // default constructor ����Ʈ ������
	~HoleTrap(); // default destructor ����Ʈ �Ҹ���

public:		// delete constructor
	HoleTrap(const HoleTrap& _Other) = delete; // default Copy constructor ����Ʈ ���������
	HoleTrap(HoleTrap&& _Other) noexcept = delete; // default RValue Copy constructor ����Ʈ RValue ���������

public:		//delete operator
	HoleTrap& operator=(const HoleTrap& _Other) = delete; // default Copy operator ����Ʈ ���� ������
	HoleTrap& operator=(const HoleTrap&& _Other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

protected:
	void Start() override;
	void Update() override;
	void Render() override;
};

