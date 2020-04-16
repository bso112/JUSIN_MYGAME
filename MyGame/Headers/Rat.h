#pragma once
#include "Monster.h"

BEGIN(MyGame)
class CRat final : public CMonster
{
private:
	explicit CRat();
	virtual ~CRat() = default;
	
public:
	virtual HRESULT	Initialize_Prototype(_tchar* _pFilePath = nullptr);
	virtual HRESULT Initialize(void * _param = nullptr);
	virtual _int	Update(_double _timeDelta);
	virtual _int	LateUpate(_double _timeDelta);
	virtual HRESULT	Render();

public:
	static CRat* Create();
	// CMonster을(를) 통해 상속됨
	virtual CGameObject * Clone(void * _param = nullptr) override;

private:
	virtual void Process() override;
	virtual void Update_State() override;
	virtual void OnDead() override;
	virtual void OnTakeDamage() override;
	virtual void Scene_Change() override;
};
END
