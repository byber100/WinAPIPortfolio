#pragma once

// �з� :
// �뵵 :
// ���� :
class GameEngine
{
private:	// member Var

public:		
	GameEngine(); // default constructor ����Ʈ ������
	~GameEngine(); // default destructor ����Ʈ �Ҹ���

public:		// delete constructor
	GameEngine(const GameEngine& _other) = delete; // default Copy constructor ����Ʈ ���������
	GameEngine(GameEngine&& _other) noexcept; // default RValue Copy constructor ����Ʈ RValue ���������

public:		//delete operator
	GameEngine& operator=(const GameEngine& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngine& operator=(const GameEngine&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:		//member Func
};

