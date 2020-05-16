#pragma once
#include "Base.h"

BEGIN(MyGame)
/*
����, �������� �����ϰ� �������ִ� Ŭ����
*/
class CGameObject;
class CSpawner : public CBase
{
	DECLARE_SINGLETON(CSpawner)
private:
	explicit CSpawner();
	virtual ~CSpawner() = default;

private:
	list<CGameObject*> m_listGO[DEPTH];
public:
	HRESULT Ready_Prototypes(PDIRECT3DDEVICE9 _pGraphic_Device, _uint _iLevel);
	HRESULT Spawn(_uint _iLevel);

public:
	CGameObject*	PickObject(POINT& _pt, _uint _iLevel);

	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;

};
END
