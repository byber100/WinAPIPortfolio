#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 :
// 용도 :
// 설명 :
class GameEngineRenderer;
class House : public GameEngineActor
{
private:	// member Var
	int LOD_;
	float DownTime_;

	GameEngineRenderer* House_;

public:		
	House(); // default constructor 디폴트 생성자
	~House(); // default destructor 디폴트 소멸자

public:		// delete constructor
	House(const House& _Other) = delete; // default Copy constructor 디폴트 복사생성자
	House(House&& _Other) noexcept = delete; // default RValue Copy constructor 디폴트 RValue 복사생성자

public:		//delete operator
	House& operator=(const House& _Other) = delete; // default Copy operator 디폴트 대입 연산자
	House& operator=(const House&& _Other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:		//member Func
	void Start() override;
	void Update() override;
	void Render() override;
};

