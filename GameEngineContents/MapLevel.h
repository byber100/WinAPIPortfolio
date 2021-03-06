#pragma once
#include <GameEngine/GameEngineLevel.h>

// 분류 :
// 용도 :
// 설명 :
class LevelChanger;
class PathPoint;
class MapLevel : public GameEngineLevel
{
private:	// member Var
	LevelChanger* LevelChanger_;

	std::vector< PathPoint*> PathAll_;
	int StrockCnt_;
	float4 BrushPos_;

public:		
	MapLevel(); // default constructor 디폴트 생성자
	~MapLevel(); // default destructor 디폴트 소멸자

public:		// delete constructor
	MapLevel(const MapLevel& _Other) = delete; // default Copy constructor 디폴트 복사생성자
	MapLevel(MapLevel&& _Other) noexcept = delete; // default RValue Copy constructor 디폴트 RValue 복사생성자

public:		//delete operator
	MapLevel& operator=(const MapLevel& _Other) = delete; // default Copy operator 디폴트 대입 연산자
	MapLevel& operator=(const MapLevel&& _Other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:
	void ContinuousDrawing(const float4& _Dir, const float& _Lengh, const float& _DrawSpeed, const int& _PassStage);

protected:
	void Loading() override;
	void Update() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
};

