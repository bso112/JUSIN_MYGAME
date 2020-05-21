#pragma once
#include "Character.h"

BEGIN(MyGame)
class CKeyMgr;
class CItem;
class CHero abstract : public CCharacter
{
protected:
	enum CLOTH	{ CLOTH_NAKED, CLOTH_BASIC, CLOTH_LEATHER, CLOTH_END};

protected:
	CLOTH		m_eCurrCloth = CLOTH_BASIC;
	CAnimator*	m_pAnimator[CLOTH_END];

protected:
	Vector3		m_vDst = {};
	//���𰡸� �������� �����ΰ�
	_bool		m_bThrowMode = false;
	//�߻�Ǵ� ������
	CItem*		m_pItemToThrow = nullptr;
	
public:
	HRESULT	PlayAnimation(const _tchar* _pTag);
	_bool	Has_Key(TIER _tier);
	HRESULT	ThrowItem(CItem* _pItem);
protected:
	explicit CHero(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CHero(CHero& _hero);
	virtual ~CHero() = default;

protected:
	virtual HRESULT	OnKeyDown(_int KeyCode) override;
	virtual	void OnAttack(CGameObject * _pOther);
	//����ΰ� ��ġ�� ó�� ��ġ�� ���Ѵ�.
	HRESULT	Set_InitialPos();

	
public:
	virtual void Free() override;


};
END
