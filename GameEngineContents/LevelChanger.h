#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� :
// �뵵 :
// ���� :
class GameEngineRenderer;
class LevelChanger : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* VeiledRender_;
	bool Changing_;

public:
	bool GetChanging()
	{
		return Changing_;
	}

public:		
	LevelChanger(); // default constructor ����Ʈ ������
	~LevelChanger(); // default destructor ����Ʈ �Ҹ���

public:		// delete constructor
	LevelChanger(const LevelChanger& _Other) = delete; // default Copy constructor ����Ʈ ���������
	LevelChanger(LevelChanger&& _Other) noexcept = delete; // default RValue Copy constructor ����Ʈ RValue ���������

public:		//delete operator
	LevelChanger& operator=(const LevelChanger& _Other) = delete; // default Copy operator ����Ʈ ���� ������
	LevelChanger& operator=(const LevelChanger&& _Other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:
	void Start() override;
	void Update() override;

public:
	void LevelChangeAnim(const std::string& _NextLevel);
};

