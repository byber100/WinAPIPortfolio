#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 :
// 용도 :
// 설명 :
class MainMap : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* Map_;

public:		
	MainMap(); // default constructor 디폴트 생성자
	~MainMap(); // default destructor 디폴트 소멸자

public:		// delete constructor
	MainMap(const MainMap& _Other) = delete; // default Copy constructor 디폴트 복사생성자
	MainMap(MainMap&& _Other) noexcept = delete; // default RValue Copy constructor 디폴트 RValue 복사생성자

public:		//delete operator
	MainMap& operator=(const MainMap& _Other) = delete; // default Copy operator 디폴트 대입 연산자
	MainMap& operator=(const MainMap&& _Other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:		//member Func
	void Start() override;
	void Update() override;
	void Render() override;
};

