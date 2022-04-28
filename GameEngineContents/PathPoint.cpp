#include "PathPoint.h"
#include <GameEngine/GameEngineRenderer.h>

// Static Var

// Static Func

// constructor destructor
PathPoint::PathPoint()
	: DrawMode_(DrawMode::None)
	, Color_(LineColor::BLACK)
	, Drawing_(false)
	, DrawSpeed_(0)
	, StartPos_(float4::ZERO)
	, Dir_(float4::ZERO)
	, Lengh_(0)
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
			GameEngineRenderer* Path = CreateRenderer("PathBrushColors.bmp", 4);
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
			float4 ScaleDir = float4::ZERO;
			float4 Lengh = float4::ZERO;
			if (0 == DrawSpeed_)
			{
				return;
			}
			if (0 < Dir_.x && 0 == Dir_.y) // to right
			{
				DrawingPath_.back()->SetPivotType(RenderPivot::LEFTCENTER);
				ScaleDir.x = 1;
				Lengh.x = Lengh_;
			}
			else if (0 > Dir_.x && 0 == Dir_.y) // to left
			{
				DrawingPath_.back()->SetPivotType(RenderPivot::RIGHTCENTER);
				ScaleDir.x = 1;
				Lengh.x = Lengh_;
				if (RenderPivot::RIGHTCENTER != DrawingPath_.back()->GetPivotType())
				{
					Lengh_ *= -1;
				}
			}
			else if (0 == Dir_.x && 0 < Dir_.y) // to bottom
			{
				DrawingPath_.back()->SetPivotType(RenderPivot::TOP);
				ScaleDir.y = 1;
				Lengh.y = Lengh_;
			}
			else if (0 == Dir_.x && 0 > Dir_.y) // to top
			{
				DrawingPath_.back()->SetPivotType(RenderPivot::BOT);
				ScaleDir.y = 1;
				Lengh.y = Lengh_;
				if (RenderPivot::BOT != DrawingPath_.back()->GetPivotType())
				{
					Lengh_ *= -1;
				}
			}
			
			if (Lengh.x > DrawingPath_.back()->GetScale().x ||
				Lengh.y > DrawingPath_.back()->GetScale().y)
			{
				DrawingPath_.back()->SetIncreasinglyScale(ScaleDir * DrawSpeed_ * GameEngineTime::GetInst()->GetDeltaTime());
			}
		}
		else
		{
			if (0 < Dir_.x && 0 == Dir_.y) // to right
			{
				GameEngineRenderer* Path = CreateRenderer("PathBrushColors.bmp", 3, RenderPivot::LEFTCENTER);
				Path->SetIndex((int)Color_);
				Path->SetPivot(StartPos_);
				Path->SetScale({ 7,7 });
				DrawingPath_.push_back(Path);
			}
			else if (0 > Dir_.x && 0 == Dir_.y) // to left
			{
				GameEngineRenderer* Path = CreateRenderer("PathBrushColors.bmp", 3, RenderPivot::RIGHTCENTER);
				Path->SetIndex((int)Color_);
				Path->SetPivot(StartPos_);
				Path->SetScale({ 7,7 });
				DrawingPath_.push_back(Path);
			}
			else if (0 == Dir_.x && 0 < Dir_.y) // to bottom
			{
				GameEngineRenderer* Path = CreateRenderer("PathBrushColors.bmp", 3, RenderPivot::TOP);
				Path->SetIndex((int)Color_);
				Path->SetPivot(StartPos_);
				Path->SetScale({ 7,7 });
				DrawingPath_.push_back(Path);
			}
			else if (0 == Dir_.x && 0 > Dir_.y) // to top
			{
				GameEngineRenderer* Path = CreateRenderer("PathBrushColors.bmp", 3, RenderPivot::BOT);
				Path->SetIndex((int)Color_);
				Path->SetPivot(StartPos_);
				Path->SetScale({ 7,7 });
				DrawingPath_.push_back(Path);
			}

			Drawing_ = true;
		}
		break;
	}
	default:
		break;
	}
}