#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 :
// 용도 :
// 설명 :
enum class SpawnLoc
{
	LEFT,
	CENTER,
	RIGHT
};

enum class TrapEvent
{
	None,
	Seal,
	Fish,
	Flag
};

class Trap : public GameEngineActor
{
private:	// member Var
	float4 DirVector_;
	int LOD_;
	SpawnLoc Spawn_;

	GameEngineRenderer* Hole_;

	GameEngineCollision* HoleCol_;
	GameEngineCollision* L_FishCol_;
	GameEngineCollision* R_FishCol_;

public:		
	Trap(); // default constructor 디폴트 생성자
	~Trap(); // default destructor 디폴트 소멸자

public:		// delete constructor
	Trap(const Trap& _Other) = delete; // default Copy constructor 디폴트 복사생성자
	Trap(Trap&& _Other) noexcept = delete; // default RValue Copy constructor 디폴트 RValue 복사생성자

public:		//delete operator
	Trap& operator=(const Trap& _Other) = delete; // default Copy operator 디폴트 대입 연산자
	Trap& operator=(const Trap&& _Other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

protected:
	void Start() override;
	void Update() override;
	void Render() override;
};

