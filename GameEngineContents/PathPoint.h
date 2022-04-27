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

