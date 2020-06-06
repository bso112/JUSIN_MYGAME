#pragma once
#include "Character.h"
#include "State.h"
BEGIN(MyGame)

class CAnimator;
class CHpBar;
class CItem;
class CMonster abstract : public CCharacter
{

protected:
	explicit CMonster(PDIRECT3DDEVICE9 _pGraphic_Device) :CCharacter(_pGraphic_Device) {};
	explicit CMonster(CMonster& _rhs);
	virtual ~CMonster() = default;

protected:
	CAnimator*		m_pAnimator = nullptr;
	CHpBar*			m_pHpBar = nullptr;
	//�󸶳� ��������� �ῡ�� ���°�
	_int			m_iAwakeRange = 0;
public:
	virtual HRESULT	Initialize(void * _param);
	virtual _int	Update(_double _timeDelta);
	virtual _int	LateUpate(_double _timeDelta);
	virtual HRESULT	Render();
	
public:
	//�ῡ�� ���°�
	_bool	IsAwake();

protected:
	//�÷��̾�� �ϼ��� ���ؼ� �ڽ��� �������� �ӵ��� ����Ѵ�.
	_float		CalulateSpeed(_int movePerturn);

public:
	HRESULT	Throw_Item(CItem* pItem);

protected:
	virtual	HRESULT	OnRender();
	virtual void OnDead();
	virtual	void OnAttack(CGameObject * _pOther);
	virtual void OnTakeDamage(float _fDamage) override;


public:
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;









};
END
