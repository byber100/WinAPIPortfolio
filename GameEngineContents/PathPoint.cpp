#include "PathPoint.h"
#include <GameEngine/GameEngineRenderer.h>

// Static Var

// Static Func

// constructor destructor
PathPoint::PathPoint()
	: Drawing_(false)
	, DrawSpeed_(0)
	, StartPos_(float4::ZERO)
	, Dir_(float4::ZERO)
{
}

PathPoint::~PathPoint()
{
}

//member Func
void PathPoint::DrawPoint(const float4& StartPos_)
{
	GameEngineRenderer* Point = CreateRenderer("PathBrushColors.bmp", 4);
	Point->SetIndex(0);
	Point->SetPivot(StartPos_);
}

void PathPoint::DrawPath(const float4& StartPos_, const float4& RelativePos_, LineColor _Color)
{
	if (false != Drawing_)
	{
		DrawingPath_.back()->SetIncreasinglyScale(RelativePos_ * GameEngineTime::GetInst()->GetDeltaTime());
	}
	else
	{
		GameEngineRenderer* Path = CreateRenderer("PathBrushColors.bmp", 4);
		Path->SetIndex((int) _Color);
		Path->SetPivot(StartPos_);
		Path->SetScale({ 7,7 });
		DrawingPath_.push_back(Path);
		Drawing_ = true;
	}
}

void PathPoint::Start()
{
	SetPosition(float4::ZERO);
	DrawMode_ = DrawMode::None;
	Color_ = LineColor::BLACK;
}
void PathPoint::Update()
{
	
}
void PathPoint::Render()
{
	switch (DrawMode_)
	{
	case DrawMode::None:
	{
		return;
	}
	case DrawMode::Point:
	{
		if (true != Drawing_)
		{
			GameEngineRenderer* Path = CreateRenderer("PathBrushColors.bmp", 3);
			Path->SetIndex((int)Color_);
			Path->SetPivot(StartPos_);
			Drawing_ = true;
		}
		break;
	}
	case DrawMode::Line:
	{
		if (true == Drawing_)
		{
			if (0 < Dir_.x && 0 == Dir_.y)
			{
				DrawingPath_.back()->SetPivotType(RenderPivot::LEFTCENTER);
			}
			else if (0 > Dir_.x && 0 == Dir_.y)
			{
				DrawingPath_.back()->SetPivotType(RenderPivot::RIGHTCENTER);
			}
			else if (0 == Dir_.x && 0 < Dir_.y)
			{
				DrawingPath_.back()->SetPivotType(RenderPivot::TOP);
			}
			else if (0 == Dir_.x && 0 > Dir_.y)
			{
				DrawingPath_.back()->SetPivotType(RenderPivot::BOT);
			}
			else
			{
				return;
			}

			DrawingPath_.back()->SetIncreasinglyScale(Dir_ * DrawSpeed_ * GameEngineTime::GetInst()->GetDeltaTime());
		}
		else
		{
			GameEngineRenderer* Path = CreateRenderer("PathBrushColors.bmp", 4);
			Path->SetIndex((int)Color_);
			Path->SetPivot(StartPos_);
			Path->SetScale({ 7,7 });
			DrawingPath_.push_back(Path);
			Drawing_ = true;
		}
		break;
	}
	default:
		break;
	}
}