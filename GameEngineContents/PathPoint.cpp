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

				// 방향 보정 및 길이 체크
				float4 ScaleDir = float4::ZERO;
				float4 Lengh = float4::ZERO;
				if (0 < Dir_.x && 0 == Dir_.y) // to right
				{
					ScaleDir.x = 1;
					Lengh.x = Lengh_;
				}
				else if (0 > Dir_.x && 0 == Dir_.y) // to left
				{
					ScaleDir.x = 1;
					Lengh.x = Lengh_;
					if (RenderPivot::RIGHTCENTER != DrawingPath_.back()->GetPivotType())
					{
						Lengh_ *= -1;
					}
				}
				else if (0 == Dir_.x && 0 < Dir_.y) // to bottom
				{
					ScaleDir.y = 1;
					Lengh.y = Lengh_;
				}
				else if (0 == Dir_.x && 0 > Dir_.y) // to top
				{
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
				else
				{
					Drawing_ = false;
					DrawClear_ = true;
				}
			}
			else
			{
				GameEngineRenderer* Point = CreateRenderer("PathBrushColors.bmp", 3); // Path 부들거림 가리기
				Point->SetIndex((int)Color_);
				Point->SetPivot(StartPos_);
				Point->SetScale({ 7,7 });

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
}