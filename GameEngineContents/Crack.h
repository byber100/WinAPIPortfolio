#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 :
// 용도 :
// 설명 :
class Crack : public GameEngineActor
{
private:	// member Var
	float4 DirVector_;
	int LOD_;

	GameEngineRenderer* Crack_;

public:		
	Crack(); // default constructor 디폴트 생성자
	~Crack(); // default destructor 디폴트 소멸자

public:		// delete constructor
	Crack(const Crack& _Other) = delete; // default Copy constructor 디폴트 복사생성자
	Crack(Crack&& _Other) noexcept = delete; // default RValue Copy constructor 디폴트 RValue 복사생성자

public:		//delete operator
	Crack& operator=(const Crack& _Other) = delete; // default Copy operator 디폴트 대입 연산자
	Crack& operator=(const Crack&& _Other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

protected:
	void Start() override;
	void Update() override;
	void Render() override;
};

