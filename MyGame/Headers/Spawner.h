#pragma once
#include "Base.h"

BEGIN(MyGame)
/*
����, �������� �����ϰ� �������ִ� Ŭ����
*/
class CGameObject;
class CTransform;
class CInventory;
//�����ʿ� ����ؾ� ������ �Ȱ��Ҷ� ��ŷ�ؼ� visuable üũ�� �� ����.
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
	//�⺻�� ����
	HRESULT	Ready_BasicItem(CInventory* _pInventory);

public:
	list<CGameObject*>* Get_Actors();

public:
	CGameObject*	PickObject(POINT& _pt, _uint _iLevel);
	CGameObject*	PickCharacter(Vector3 _vPos, _uint _iLevel, CTransform* pSelfTransform);
	CGameObject *	PickCharacter(POINT& _pt, _uint _iLevel, CTransform * pSelfTransform);
	_int			Clear_DeadObjects(_uint _iLevel);
	//ĳ���͵��� ���ִ� Ÿ�� �ε����� �����´�.
	vector<pair<int, int>> Get_CharacterTileIndexs();

public:
	void	SetActive(_bool _bActive, _uint _iLevel);


	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;

};
END
