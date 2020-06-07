#pragma once
#include "Base.h"
#include "Level.h"
BEGIN(MyGame)

//레벨(층수)가 넘어가도 이전층의 정보는 저장되어야한다. 다시 돌아올 수 있기 때문에.
class CSpawner;
class CCharacter;
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
	_int	Get_CurrDepth();
	void	Clear_DeadObjects();
	HRESULT	Set_Visuable(Vector3 _vPos, _int _iRange);
	HRESULT	Explore(Vector3 _vPos);
	Vector3	Get_RandomPos(Vector3 _vPos, _int _iRange);
public:
	HRESULT Initialize_Prototypes(PDIRECT3DDEVICE9 _pGraphic_Device);
	HRESULT	Initialize();
	CTerrain*		PickTile(POINT& pt);
	CGameObject*	PickObject(POINT& pt);
	CCharacter*		PickCharacter(POINT& pt);
	_bool			IsMovable(Vector3& _vPos);

protected:
	virtual HRESULT	OnKeyDown(_int KeyCode);
public:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;
};
END
