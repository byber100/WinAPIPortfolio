#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� :
// �뵵 :
// ���� :
class PlayBack : public GameEngineActor
{
private:	// member Var

public:		
	PlayBack(); // default constructor ����Ʈ ������
	~PlayBack(); // default destructor ����Ʈ �Ҹ���

public:		// delete constructor
	PlayBack(const PlayBack& _Other) = delete; // default Copy constructor ����Ʈ ���������
	PlayBack(PlayBack&& _Other) noexcept = delete; // default RValue Copy constructor ����Ʈ RValue ���������

public:		//delete operator
	PlayBack& operator=(const PlayBack& _Other) = delete; // default Copy operator ����Ʈ ���� ������
	PlayBack& operator=(const PlayBack&& _Other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:
	void Start() override;
};

