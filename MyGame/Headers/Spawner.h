#pragma once
#include "Base.h"

BEGIN(MyGame)
/*
몬스터, 아이템을 랜덤하게 스폰해주는 클래스
*/
class CGameObject;
class CTransform;
class CInventory;
//스포너에 등록해야 전장의 안개할때 피킹해서 visuable 체크할 수 있음.
class CSpawner : public CBase
{
	DECLARE_SINGLETON(CSpawner)
private:
	explicit CSpawner();
	virtual ~CSpawner() = default;
private:
	list<CGameObject*> m_listGO[MAX_DEPTH];
	list<CGameObject*> m_listCharacter[MAX_DEPTH];
public:
	HRESULT Ready_Prototypes(PDIRECT3DDEVICE9 _pGraphic_Device, _uint _iLevel);
	HRESULT Spawn(_uint _iLevel);
	HRESULT	Add_Interact(CGameObject* _pInteractor, _uint _iDepth);
	HRESULT	Set_Visuable(Vector3 _vPlayerPos, _int _iRange, _int _iDepth);
	//기본템 셋팅
	HRESULT	Ready_BasicItem(CInventory* _pInventory);

public:
	list<CGameObject*>* Get_Actors();

public:
	CGameObject*	PickObject(POINT& _pt, _uint _iLevel);
	CGameObject*	PickCharacter(Vector3 _vPos, _uint _iLevel, CTransform* pSelfTransform);
	CGameObject *	PickCharacter(POINT& _pt, _uint _iLevel, CTransform * pSelfTransform);
	_int			Clear_DeadObjects(_uint _iLevel);
	//캐릭터들이 서있는 타일 인덱스를 가져온다.
	vector<pair<int, int>> Get_CharacterTileIndexs();

public:
	void	SetActive(_bool _bActive, _uint _iLevel);


	// CBase을(를) 통해 상속됨
	virtual void Free() override;

};
END
