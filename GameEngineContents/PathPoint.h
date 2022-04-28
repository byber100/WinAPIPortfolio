#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 :
// 용도 :
// 설명 :
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

	std::vector< GameEngineRenderer*> DrawingPath_;

public:
	void Draw(const DrawMode& _Mode, 
		const float4& _StartPos,
		const float4& _Dir = {float4::ZERO},
		const float& _DrawSpeed = 0,
		const LineColor& _Color = LineColor::BLACK)
	{
		DrawMode_ = _Mode;
		StartPos_ = _StartPos;
		Dir_ = _Dir;
		DrawSpeed_ = _DrawSpeed;
		Color_ = _Color;
	}

public:		
	PathPoint(); // default constructor 디폴트 생성자
	~PathPoint(); // default destructor 디폴트 소멸자

public:		// delete constructor
	PathPoint(const PathPoint& _Other) = delete; // default Copy constructor 디폴트 복사생성자
	PathPoint(PathPoint&& _Other) noexcept = delete; // default RValue Copy constructor 디폴트 RValue 복사생성자

public:		//delete operator
	PathPoint& operator=(const PathPoint& _Other) = delete; // default Copy operator 디폴트 대입 연산자
	PathPoint& operator=(const PathPoint&& _Other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	void DrawPoint(const float4& _Pos);
	void DrawPath(const float4& _StartPos, const float4& _EndPos, LineColor _Color);

private:
	void Start() override;
	void Update() override;
	void Render() override;
};

