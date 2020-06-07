#pragma once
#include "Character.h"

BEGIN(MyGame)
class CKeyMgr;
class CItem;
class CEquipment;
class CHpBar;
class CWand;
class CScroll;
class CHero abstract : public CCharacter
{
public:
	enum CLOTH { CLOTH_NAKED, CLOTH_BASIC, CLOTH_LEATHER, CLOTH_END };
protected:
	CLOTH		m_eCurrCloth = CLOTH_BASIC;
	CAnimator*	m_pAnimator[CLOTH_END];

protected:
	Vector3			m_vDst = {};
	//무언가를 던지려는 상태인가
	_bool			m_bThrowMode = false;
	//레이저를 쏘는 상태인가
	_bool			m_bZapMode = false;
	//발사되는 아이템
	CItem*			m_pItemToThrow = nullptr;
	CWand*			m_pWandToZap = nullptr;
	CEquipment*		m_pEquipments[BODY_END];

	//아이템을 인첸트하려는 상태인가
	_bool			m_bEnchantMode = false;
public:
	HRESULT	PlayAnimation(const _tchar* _pTag);
	HRESULT	ThrowItem(CItem* _pItem);
	HRESULT	Equip(CEquipment* _pItem, BODYPART _eBodyPart);
	HRESULT	UnEquip(BODYPART _eBodyPart);
	HRESULT	Zap(CWand* _pWand);
	void	Set_Cloth(CLOTH _eCloth);
	HRESULT	Explore();
	void	SelectItemToEnchant(CScroll* pScroll) { m_bEnchantMode = true; }
public:
	_bool	Has_Key();

protected:
	explicit CHero(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CHero(CHero& _hero);
	virtual ~CHero() = default;

protected:
	virtual HRESULT	OnKeyDown(_int KeyCode) override;
	virtual	void OnAttack(CGameObject * _pOther);
	

public:
	//히어로가 위치할 처음 위치를 구한다.
	HRESULT	Set_InitialPos();
	//이전 층에서의 마지막 위치를 구한다.
	HRESULT	Set_LastPos();



public:
	virtual void Free() override;


};
END
