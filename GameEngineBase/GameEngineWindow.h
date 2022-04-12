#pragma once

// 분류 :
// 용도 :
// 설명 :
class GameEngineWindow
{
private:	// member Var

public:		
	GameEngineWindow(); // default constructor 디폴트 생성자
	~GameEngineWindow(); // default destructor 디폴트 소멸자

public:		// delete constructor
	GameEngineWindow(const GameEngineWindow& _other) = delete; // default Copy constructor 디폴트 복사생성자
	GameEngineWindow(GameEngineWindow&& _other) noexcept; // default RValue Copy constructor 디폴트 RValue 복사생성자

public:		//delete operator
	GameEngineWindow& operator=(const GameEngineWindow& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineWindow& operator=(const GameEngineWindow&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:		//member Func
};

