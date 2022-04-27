#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� :
// �뵵 :
// ���� :
enum class LineColor
{
	BLACK,
	GRAY,
	OCHER
};

class PathPoint : public GameEngineActor
{
private:	// member Var
	bool ResetPath_;

	std::list< GameEngineRenderer*> Points_;
	std::list< GameEngineRenderer*> Paths_;

	std::list<GameEngineRenderer*>::iterator StartPointIter = Points_.begin();
	std::list<GameEngineRenderer*>::iterator EndPointIter = Points_.end();
	std::list<GameEngineRenderer*>::iterator StartPathIter = Paths_.begin();
	std::list<GameEngineRenderer*>::iterator EndPathIter = Paths_.end();

public:		
	PathPoint(); // default constructor ����Ʈ ������
	~PathPoint(); // default destructor ����Ʈ �Ҹ���

public:		// delete constructor
	PathPoint(const PathPoint& _Other) = delete; // default Copy constructor ����Ʈ ���������
	PathPoint(PathPoint&& _Other) noexcept = delete; // default RValue Copy constructor ����Ʈ RValue ���������

public:		//delete operator
	PathPoint& operator=(const PathPoint& _Other) = delete; // default Copy operator ����Ʈ ���� ������
	PathPoint& operator=(const PathPoint&& _Other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void DrawPoint(const float4& _Pos);
	void DrawPath(const float4& _StartPos, const float4& _EndPos, LineColor _Color);

private:
	void Start() override;
	void Update() override;
	void Render() override;
};

