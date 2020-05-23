#pragma once
#include "Character.h"

BEGIN(MyGame)
class CKeyMgr;
class CItem;
class CEquipment;
class CHero abstract : public CCharacter
{
protected:
	enum CLOTH	{ CLOTH_NAKED, CLOTH_BASIC, CLOTH_LEATHER, CLOTH_END};
	enum BODYPART { BODY_HAND, BODY_TORSO, BODY_FINGER, BODY_FINGER2, BODY_END };
protected:
	CLOTH		m_eCurrCloth = CLOTH_BASIC;
	CAnimator*	m_pAnimator[CLOTH_END];

protected:
	Vector3		m_vDst = {};
	//무언가를 던지려는 상태인가
	_bool		m_bThrowMode = false;
	//발사되는 아이템
	CItem*		m_pItemToThrow = nullptr;
	CEquipment*		m_pEquipments[BODY_END];
	
public:
	HRESULT	PlayAnimation(const _tchar* _pTag);
	HRESULT	ThrowItem(CItem* _pItem);
	HRESULT	Equip(CEquipment* _pItem, _uint _eBodyPart);
	HRESULT	UnEquip(_uint _eBodyPart);


public:
	_bool	Has_Key();

protected:
	explicit CHero(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CHero(CHero& _hero);
	virtual ~CHero() = default;

protected:
	virtual HRESULT	OnKeyDown(_int KeyCode) override;
	virtual	void OnAttack(CGameObject * _pOther);
	//히어로가 위치할 처음 위치를 구한다.
	HRESULT	Set_InitialPos();

	
public:
	virtual void Free() override;


};
END
