#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineRandom.h>

// 분류 :
// 용도 :
// 설명 :
class RandomStage : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* BackStage_;
	GameEngineRenderer* LeftOcean_;
	GameEngineRenderer* RightOcean_;
	GameEngineRenderer* LeftGround_;
	GameEngineRenderer* RightGround_;
	GameEngineRenderer* CurveTiles_;
	GameEngineRenderer* Mountain1_;
	GameEngineRenderer* Mountain2_;
	GameEngineRenderer* LeftGlacier_;
	GameEngineRenderer* RightGlacier_;

	GameEngineRandom RandomValue_;

	unsigned int RoundStateValue_; // 맵 상태
	unsigned int MountainDirectionValue_; // 산 이동 방향 값 0==stay, 1==right, 2==left
	bool isCurve_;


public:
	RandomStage(); // default constructor 디폴트 생성자
	~RandomStage(); // default destructor 디폴트 소멸자

public:		// delete constructor
	RandomStage(const RandomStage& _Other) = delete; // default Copy constructor 디폴트 복사생성자
	RandomStage(RandomStage&& _Other) noexcept = delete; // default RValue Copy constructor 디폴트 RValue 복사생성자

public:		//delete operator
	RandomStage& operator=(const RandomStage& _Other) = delete; // default Copy operator 디폴트 대입 연산자
	RandomStage& operator=(const RandomStage&& _Other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private: //member Func
	void MountainMove(GameEngineRenderer* _Mountain);
	void CurveFrameCount();
	void StageChange();

	void Start() override;
	void Update() override;
	void Render() override;

public:
	void MountainFrame();
};

