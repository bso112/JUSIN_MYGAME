#pragma once
#include "Base.h"

BEGIN(MyGame)
/*
몬스터, 아이템을 랜덤하게 스폰해주는 클래스
*/
class CGameObject;
class CSpawner : public CBase
{
	DECLARE_SINGLETON(CSpawner)
private:
	explicit CSpawner();
	virtual ~CSpawner() = default;

private:
	list<CGameObject*> m_listGO[MAX_DEPTH];
public:
	HRESULT Ready_Prototypes(PDIRECT3DDEVICE9 _pGraphic_Device, _uint _iLevel);
	HRESULT Spawn(_uint _iLevel);
	HRESULT	Add_Interact(CGameObject* _pInteractor, _uint _iDepth);

public:
	CGameObject*	PickObject(POINT& _pt, _uint _iLevel);


	// CBase을(를) 통해 상속됨
	virtual void Free() override;

};
END
