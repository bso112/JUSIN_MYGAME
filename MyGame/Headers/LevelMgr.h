#pragma once
#include "Base.h"
#include "Level.h"
BEGIN(MyGame)

//����(����)�� �Ѿ�� �������� ������ ����Ǿ���Ѵ�. �ٽ� ���ƿ� �� �ֱ� ������.
class CSpawner;
class CLevelMgr final: public CBase
{
	DECLARE_SINGLETON(CLevelMgr)
private:
	explicit CLevelMgr();
	virtual ~CLevelMgr() = default;

private:
	CLevel*		m_aLevel[MAX_DEPTH];
	CSpawner*	m_pSpawner = nullptr;
	_uint		m_iCurrLevel = 0;

public:
	CLevel*	Get_CurrLevel();
	_uint	Get_CurrDepth() { return m_iCurrLevel; }
	
public:
	HRESULT Initialize_Prototypes(PDIRECT3DDEVICE9 _pGraphic_Device);
	HRESULT	Initialize();
	CTerrain*		PickTile(POINT& pt);
	CGameObject*	PickObject(POINT& pt);
	_bool			IsMovable(Vector3& _vPos);
public:
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;
};
END
