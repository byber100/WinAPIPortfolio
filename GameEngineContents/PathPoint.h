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

enum class DrawMode
{
	None,
	Point,
	Line
};

class PathPoint : public GameEngineActor
{
private:	// member Var
	DrawMode DrawMode_;
	LineColor Color_;

	bool Drawing_;
	float DrawSpeed_;

	float4 StartPos_;
	float4 RelativePos_;

	std::vector< GameEngineRenderer*> DrawingPath_;

public:
	void Draw(const DrawMode& _Mode, 
		const float4& _StartPos,
		const float4& _RelativePos = {float4::ZERO},
		const float& _DrawSpeed = 0,
		const LineColor& _Color = LineColor::BLACK)
	{
		DrawMode_ = _Mode;
		StartPos_ = _StartPos;
		RelativePos_ = _RelativePos;
		DrawSpeed_ = _DrawSpeed;
		Color_ = _Color;
	}

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
