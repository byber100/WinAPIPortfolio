#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� :
// �뵵 :
// ���� :
class GameEngineRandom;
class RandomStage : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* LeftOcean_;
	GameEngineRenderer* rightOcean_;
	GameEngineRenderer* leftGround_;
	GameEngineRenderer* rightGround_;
	GameEngineRenderer* CurveTiles_;
	GameEngineRenderer* mountain1_;
	GameEngineRenderer* mountain2_;
	GameEngineRenderer* leftGlacier_;
	GameEngineRenderer* rightGlacier_;

	GameEngineRandom* randomValue_;

	unsigned int roundStateValue_; // �� ����
	unsigned int mountainDirectionValue_; // �� �̵� ���� �� 0==stay, 1==right, 2==left
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

protected: //member Func
	void Start() override;
	void Update() override;
	void Render() override;

	void MountainMove(GameEngineRenderer* _mountain);
	void MountainFrame();
	void CurveFrameCount();
	void TilemapChange();
};

