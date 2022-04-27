#pragma once
#include <GameEngine/GameEngineLevel.h>

// �з� :
// �뵵 :
// ���� :
class LevelChanger;
class MapLevel : public GameEngineLevel
{
private:	// member Var
	LevelChanger* LevelChanger_;

public:		
	MapLevel(); // default constructor ����Ʈ ������
	~MapLevel(); // default destructor ����Ʈ �Ҹ���

public:		// delete constructor
	MapLevel(const MapLevel& _Other) = delete; // default Copy constructor ����Ʈ ���������
	MapLevel(MapLevel&& _Other) noexcept = delete; // default RValue Copy constructor ����Ʈ RValue ���������

public:		//delete operator
	MapLevel& operator=(const MapLevel& _Other) = delete; // default Copy operator ����Ʈ ���� ������
	MapLevel& operator=(const MapLevel&& _Other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

protected:
	void Loading() override;
	void Update() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
};

