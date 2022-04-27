#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� :
// �뵵 :
// ���� :
class MainMap : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* Map_;

public:		
	MainMap(); // default constructor ����Ʈ ������
	~MainMap(); // default destructor ����Ʈ �Ҹ���

public:		// delete constructor
	MainMap(const MainMap& _Other) = delete; // default Copy constructor ����Ʈ ���������
	MainMap(MainMap&& _Other) noexcept = delete; // default RValue Copy constructor ����Ʈ RValue ���������

public:		//delete operator
	MainMap& operator=(const MainMap& _Other) = delete; // default Copy operator ����Ʈ ���� ������
	MainMap& operator=(const MainMap&& _Other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:		//member Func
	void Start() override;
	void Update() override;
	void Render() override;
};

