#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 :
// 용도 :
// 설명 :
class GameEngineRenderer;
class KonamiLogo : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* Konami_;

public:		
	KonamiLogo(); // default constructor 디폴트 생성자
	~KonamiLogo(); // default destructor 디폴트 소멸자

public:		// delete constructor
	KonamiLogo(const KonamiLogo& _Other) = delete; // default Copy constructor 디폴트 복사생성자
	KonamiLogo(KonamiLogo&& _Other) noexcept = delete; // default RValue Copy constructor 디폴트 RValue 복사생성자

public:		//delete operator
	KonamiLogo& operator=(const KonamiLogo& _Other) = delete; // default Copy operator 디폴트 대입 연산자
	KonamiLogo& operator=(const KonamiLogo&& _Other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:		//member Func
	void Start() override;
	void Update() override;
	void Render() override;
};

