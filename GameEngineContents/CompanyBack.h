#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 :
// 용도 :
// 설명 :
class GameEngineRenderer;
class CompanyBack : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* BackGround_;
	GameEngineRenderer* Software_;

public:		
	CompanyBack(); // default constructor 디폴트 생성자
	~CompanyBack(); // default destructor 디폴트 소멸자

public:		// delete constructor
	CompanyBack(const CompanyBack& _Other) = delete; // default Copy constructor 디폴트 복사생성자
	CompanyBack(CompanyBack&& _Other) noexcept = delete; // default RValue Copy constructor 디폴트 RValue 복사생성자

public:		//delete operator
	CompanyBack& operator=(const CompanyBack& _Other) = delete; // default Copy operator 디폴트 대입 연산자
	CompanyBack& operator=(const CompanyBack&& _Other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:
	void Start() override;
	void Update() override;
	void Render() override;
};

