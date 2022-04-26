#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� :
// �뵵 :
// ���� :
class GameEngineRenderer;
class CompanyBack : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* BackGround_;
	GameEngineRenderer* Software_;

public:		
	CompanyBack(); // default constructor ����Ʈ ������
	~CompanyBack(); // default destructor ����Ʈ �Ҹ���

public:		// delete constructor
	CompanyBack(const CompanyBack& _Other) = delete; // default Copy constructor ����Ʈ ���������
	CompanyBack(CompanyBack&& _Other) noexcept = delete; // default RValue Copy constructor ����Ʈ RValue ���������

public:		//delete operator
	CompanyBack& operator=(const CompanyBack& _Other) = delete; // default Copy operator ����Ʈ ���� ������
	CompanyBack& operator=(const CompanyBack&& _Other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:
	void Start() override;
	void Update() override;
	void Render() override;
};

