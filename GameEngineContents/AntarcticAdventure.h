#pragma once
#include <GameEngine/GameEngine.h>

// ���� : �������� ������� ������ �����ϱ� �׳� ���͵�����̶� �������ϴ�.
//       �����е��� ���� �ڽ��� ������� ���ӿ� �´� �̸��� �̳༮���� �ٿ��ֽø� �˴ϴ�.
class AntarcticAdventure : public GameEngine
{
public:
	// constrcuter destructer
	AntarcticAdventure();
	~AntarcticAdventure();

	// delete Function
	AntarcticAdventure(const AntarcticAdventure& _Other) = delete;
	AntarcticAdventure(AntarcticAdventure&& _Other) noexcept = delete;
	AntarcticAdventure& operator=(const AntarcticAdventure& _Other) = delete;
	AntarcticAdventure& operator=(AntarcticAdventure&& _Other) noexcept = delete;

	void GameInit() override;
	void GameLoop() override;
	void GameEnd() override;

protected:

private:

};

