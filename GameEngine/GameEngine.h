#pragma once

// 분류 :
// 용도 :
// 설명 :
class GameEngine
{
private:	// member Var

public:		
	GameEngine(); // default constructor 디폴트 생성자
	~GameEngine(); // default destructor 디폴트 소멸자

public:		// delete constructor
	GameEngine(const GameEngine& _other) = delete; // default Copy constructor 디폴트 복사생성자
	GameEngine(GameEngine&& _other) noexcept; // default RValue Copy constructor 디폴트 RValue 복사생성자

public:		//delete operator
	GameEngine& operator=(const GameEngine& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngine& operator=(const GameEngine&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:		//member Func
};

