#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� :
// �뵵 :
// ���� :
class GameEngineRenderer;
class KonamiLogo : public GameEngineActor
{
private:	// member Var
	GameEngineRenderer* Konami_;

public:		
	KonamiLogo(); // default constructor ����Ʈ ������
	~KonamiLogo(); // default destructor ����Ʈ �Ҹ���

public:		// delete constructor
	KonamiLogo(const KonamiLogo& _Other) = delete; // default Copy constructor ����Ʈ ���������
	KonamiLogo(KonamiLogo&& _Other) noexcept = delete; // default RValue Copy constructor ����Ʈ RValue ���������

public:		//delete operator
	KonamiLogo& operator=(const KonamiLogo& _Other) = delete; // default Copy operator ����Ʈ ���� ������
	KonamiLogo& operator=(const KonamiLogo&& _Other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:		//member Func
	void Start() override;
	void Update() override;
	void Render() override;
};

