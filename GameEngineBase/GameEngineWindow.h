#pragma once

// �з� :
// �뵵 :
// ���� :
class GameEngineWindow
{
private:	// member Var

public:		
	GameEngineWindow(); // default constructor ����Ʈ ������
	~GameEngineWindow(); // default destructor ����Ʈ �Ҹ���

public:		// delete constructor
	GameEngineWindow(const GameEngineWindow& _other) = delete; // default Copy constructor ����Ʈ ���������
	GameEngineWindow(GameEngineWindow&& _other) noexcept; // default RValue Copy constructor ����Ʈ RValue ���������

public:		//delete operator
	GameEngineWindow& operator=(const GameEngineWindow& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineWindow& operator=(const GameEngineWindow&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:		//member Func
};

