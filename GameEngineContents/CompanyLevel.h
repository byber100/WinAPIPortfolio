#pragma once
#include <GameEngine/GameEngineLevel.h>

// �з� :
// �뵵 :
// ���� :
class CompanyLevel : public GameEngineLevel
{
private:	// member Var

public:		
	CompanyLevel(); // default constructor ����Ʈ ������
	~CompanyLevel(); // default destructor ����Ʈ �Ҹ���

public:		// delete constructor
	CompanyLevel(const CompanyLevel& _Other) = delete; // default Copy constructor ����Ʈ ���������
	CompanyLevel(CompanyLevel&& _Other) noexcept = delete; // default RValue Copy constructor ����Ʈ RValue ���������

public:		//delete operator
	CompanyLevel& operator=(const CompanyLevel& _Other) = delete; // default Copy operator ����Ʈ ���� ������
	CompanyLevel& operator=(const CompanyLevel&& _Other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

protected:
	void Loading() override;
	void Update() override;
};

