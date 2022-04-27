#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 :
// 용도 :
// 설명 :
class PlayBack : public GameEngineActor
{
private:	// member Var

public:		
	PlayBack(); // default constructor 디폴트 생성자
	~PlayBack(); // default destructor 디폴트 소멸자

public:		// delete constructor
	PlayBack(const PlayBack& _Other) = delete; // default Copy constructor 디폴트 복사생성자
	PlayBack(PlayBack&& _Other) noexcept = delete; // default RValue Copy constructor 디폴트 RValue 복사생성자

public:		//delete operator
	PlayBack& operator=(const PlayBack& _Other) = delete; // default Copy operator 디폴트 대입 연산자
	PlayBack& operator=(const PlayBack&& _Other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:
	void Start() override;
};

