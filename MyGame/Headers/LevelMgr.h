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
	_int		m_iCurrLevel = 0;

public:
	HRESULT	Next_Level();
	HRESULT	Prv_Level();
	CLevel*	Get_CurrLevel();
	CLevel*	Get_Level(_int index);
	_int	Get_CurrDepth() { return m_iCurrLevel; }
	void	Clear_DeadObjects();
	HRESULT	Set_Visuable(Vector3 _vPos, _int _iRange);
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
