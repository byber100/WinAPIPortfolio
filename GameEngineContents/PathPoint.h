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
	float4 Dir_;
	float Lengh_;
	float LerpAlpha_; // �������� ���İ� -> 0 �� ����� ���� ����

	std::vector< GameEngineRenderer*> DrawingPath_;
	bool DrawClear_;

public:
	void Draw(const DrawMode& _Mode, 
		const float4& _StartPos,
		const float4& _Dir = {float4::ZERO},
		const float& _Lengh = 0,
		const float& _LenghAlpha = 0,
		const float& _DrawSpeed = 0,
		const LineColor& _Color = LineColor::BLACK)
	{
		DrawMode_ = _Mode;
		StartPos_ = _StartPos;
		Dir_ = _Dir;
		Lengh_ = _Lengh;
		LerpAlpha_ = _LenghAlpha;
		DrawSpeed_ = _DrawSpeed;
		Color_ = _Color;
	}

	bool isClear()
	{
		return DrawClear_;
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

