#pragma once
#include <GameEngine/GameEngineLevel.h>

// 분류 :
// 용도 :
// 설명 :
class CompanyLevel : public GameEngineLevel
{
private:	// member Var

public:		
	CompanyLevel(); // default constructor 디폴트 생성자
	~CompanyLevel(); // default destructor 디폴트 소멸자

public:		// delete constructor
	CompanyLevel(const CompanyLevel& _Other) = delete; // default Copy constructor 디폴트 복사생성자
	CompanyLevel(CompanyLevel&& _Other) noexcept = delete; // default RValue Copy constructor 디폴트 RValue 복사생성자

public:		//delete operator
	CompanyLevel& operator=(const CompanyLevel& _Other) = delete; // default Copy operator 디폴트 대입 연산자
	CompanyLevel& operator=(const CompanyLevel&& _Other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

protected:
	void Loading() override;
	void Update() override;
};

