#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineRandom.h>

// �з� :
// �뵵 :
// ���� :
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

	unsigned int RoundStateValue_; // �� ����
	unsigned int MountainDirectionValue_; // �� �̵� ���� �� 0==stay, 1==right, 2==left
	bool isCurve_;


public:
	RandomStage(); // default constructor ����Ʈ ������
	~RandomStage(); // default destructor ����Ʈ �Ҹ���

public:		// delete constructor
	RandomStage(const RandomStage& _Other) = delete; // default Copy constructor ����Ʈ ���������
	RandomStage(RandomStage&& _Other) noexcept = delete; // default RValue Copy constructor ����Ʈ RValue ���������

public:		//delete operator
	RandomStage& operator=(const RandomStage& _Other) = delete; // default Copy operator ����Ʈ ���� ������
	RandomStage& operator=(const RandomStage&& _Other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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

