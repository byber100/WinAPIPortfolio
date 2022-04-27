#include "PathPoint.h"
#include <GameEngine/GameEngineRenderer.h>

// Static Var

// Static Func

// constructor destructor
PathPoint::PathPoint()
	: ResetPath_(false)
{
}

PathPoint::~PathPoint()
{
}

//member Func
void PathPoint::DrawPoint(const float4& _Pos)
{
	GameEngineRenderer* Point = CreateRenderer("PathBrushColors.bmp", 4);
	Point->SetIndex(0);
	Point->SetPivot(_Pos);
	Points_.push_back(Point);
}

void PathPoint::DrawPath(const float4& _StartPos, const float4& _RelativePos, LineColor _Color)
{


	if (nullptr == Paths_.back())
	{
		return;
	}

	float4 EndPos = { _StartPos.x + _RelativePos.x ,_StartPos.y - _RelativePos.y };

	if (EndPos.ix() != Paths_.back()->GetPivot().ix() && // have to Edit!!!!!!!!!!!
		EndPos.iy() != Paths_.back()->GetPivot().iy())
	{
		GameEngineRenderer* Path = CreateRenderer("PathBrushColors.bmp", 3);
		Path->SetIndex((int)_Color);

		float PrevPos_x = Paths_.back()->GetPivot().x;
		float PrevPos_y = Paths_.back()->GetPivot().y;

		float Start_x = _StartPos.x != PrevPos_x ? _StartPos.x : PrevPos_x;
		if (Start_x < PrevPos_x)	// 양수
		{
			Start_x = PrevPos_x + 1;
		}
		else if (Start_x > PrevPos_x)// 음수
		{
			Start_x = PrevPos_x - 1;
		}

		float Start_y = _StartPos.x != PrevPos_x ? _StartPos.x : PrevPos_x;
		if (Start_y < PrevPos_y)	// 양수
		{
			Start_y = PrevPos_y + 1;
		}
		else if (Start_y > PrevPos_y)// 음수
		{
			Start_y = PrevPos_y - 1;
		}
		
		Path->SetPivot({ Start_x,Start_y });;
		Path->SetScale({ 70,70 });
		Paths_.push_back(Path);
	}
}

void PathPoint::Start()
{
	SetPosition(float4::ZERO);

	
}
void PathPoint::Update()
{
	if (false == ResetPath_)
	{
		DrawPoint({ 640,575 });
		DrawPath({ 500,100 }, { 100,10 }, LineColor::GRAY);
	}
}
void PathPoint::Render()
{

	//Release();
}