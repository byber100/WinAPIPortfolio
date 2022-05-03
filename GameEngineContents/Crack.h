#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� :
// �뵵 :
// ���� :
class Crack : public GameEngineActor
{
private:	// member Var
	float4 DirVector_;
	int LOD_;

	GameEngineRenderer* Crack_;

public:		
	Crack(); // default constructor ����Ʈ ������
	~Crack(); // default destructor ����Ʈ �Ҹ���

public:		// delete constructor
	Crack(const Crack& _Other) = delete; // default Copy constructor ����Ʈ ���������
	Crack(Crack&& _Other) noexcept = delete; // default RValue Copy constructor ����Ʈ RValue ���������

public:		//delete operator
	Crack& operator=(const Crack& _Other) = delete; // default Copy operator ����Ʈ ���� ������
	Crack& operator=(const Crack&& _Other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

protected:
	void Start() override;
	void Update() override;
	void Render() override;
};

