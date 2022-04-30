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
	, Time_(0)
	, DrawClear_(false)
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
		DrawClear_ = true;
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
	if (false == DrawClear_)
	{
		switch (DrawMode_)
		{
		case DrawMode::None:
		{
			DrawClear_ = true;
			return;
		}
		case DrawMode::Point:
		{
			if (true != DrawClear_)
			{
				GameEngineRenderer* Path = CreateRenderer("PathBrushColors.bmp", 4);
				Path->SetIndex((int)Color_);
				Path->SetPivot(StartPos_);
				DrawClear_ = true;
			}
			break;
		}
		case DrawMode::Line:
		{
			if (true == Drawing_)
			{
				if (0 >= DrawSpeed_)
				{
					Drawing_ = false;
					DrawClear_ = true;
					return;
				}

				// 선형보간
				Time_ += DrawSpeed_ * GameEngineTime::GetInst()->GetDeltaTime();
				float LerpLengh = GameEngineMath::LerpLimit(0, Lengh_, Time_);

				if (0 < Dir_.x && 0 == Dir_.y) // to right
				{
					DrawingPath_.back()->SetScale({ LerpLengh, 7 });
				}
				else if (0 > Dir_.x && 0 == Dir_.y) // to left
				{
					DrawingPath_.back()->SetScale({ LerpLengh, 7 });
				}
				else if (0 == Dir_.x && 0 < Dir_.y) // to bottom
				{
					DrawingPath_.back()->SetScale({ 7, LerpLengh });
				}
				else if (0 == Dir_.x && 0 > Dir_.y) // to top
				{
					DrawingPath_.back()->SetScale({ 7, LerpLengh });
				}

				if (LerpLengh >= Lengh_) // 그리려는 길이 이상이면 끝낸다.
				{
					Drawing_ = false;
					DrawClear_ = true;
				}
			}
			else
			{
				GameEngineRenderer* Path = CreateRenderer("PathBrushColors.bmp", 3);

				// alignment
				if (0 < Dir_.x && 0 == Dir_.y) // to right
				{
					Path->SetPivotType(RenderPivot::LEFTCENTER);
					StartPos_.x -= 3.5f;
				}
				else if (0 > Dir_.x && 0 == Dir_.y) // to left
				{
					Path->SetPivotType(RenderPivot::RIGHTCENTER);
					StartPos_.x += 3.5f;
				}
				else if (0 == Dir_.x && 0 < Dir_.y) // to bottom
				{
					Path->SetPivotType(RenderPivot::TOP);
					StartPos_.y -= 3.5f;
				}
				else if (0 == Dir_.x && 0 > Dir_.y) // to top
				{
					Path->SetPivotType(RenderPivot::BOT);
					StartPos_.y += 3.5f;
				}
				Lengh_ += 7.f;
				
				Path->SetIndex((int)Color_);
				Path->SetPivot(StartPos_);
				DrawingPath_.push_back(Path);
				Drawing_ = true;
			}
			break;
		}
		default:
			break;
		}
	}
}