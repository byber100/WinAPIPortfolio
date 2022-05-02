#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� :
// �뵵 :
// ���� :
class GameEngineRenderer;
class House : public GameEngineActor
{
private:	// member Var
	int LOD_;
	float DownTime_;

	GameEngineRenderer* House_;

public:		
	House(); // default constructor ����Ʈ ������
	~House(); // default destructor ����Ʈ �Ҹ���

public:		// delete constructor
	House(const House& _Other) = delete; // default Copy constructor ����Ʈ ���������
	House(House&& _Other) noexcept = delete; // default RValue Copy constructor ����Ʈ RValue ���������

public:		//delete operator
	House& operator=(const House& _Other) = delete; // default Copy operator ����Ʈ ���� ������
	House& operator=(const House&& _Other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:		//member Func
	void Start() override;
	void Update() override;
	void Render() override;
};

