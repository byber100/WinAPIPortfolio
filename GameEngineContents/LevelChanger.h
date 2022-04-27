#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 :
// 용도 :
// 설명 :
class GameEngineRenderer;
class LevelChanger : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* VeiledRender_;
	bool Changing_;

public:
	bool GetChanging()
	{
		return Changing_;
	}

public:		
	LevelChanger(); // default constructor 디폴트 생성자
	~LevelChanger(); // default destructor 디폴트 소멸자

public:		// delete constructor
	LevelChanger(const LevelChanger& _Other) = delete; // default Copy constructor 디폴트 복사생성자
	LevelChanger(LevelChanger&& _Other) noexcept = delete; // default RValue Copy constructor 디폴트 RValue 복사생성자

public:		//delete operator
	LevelChanger& operator=(const LevelChanger& _Other) = delete; // default Copy operator 디폴트 대입 연산자
	LevelChanger& operator=(const LevelChanger&& _Other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:
	void Start() override;
	void Update() override;

public:
	void LevelChangeAnim(const std::string& _NextLevel);
};

