#pragma once
#include "GameObject.h"

BEGIN(MyGame)
class CStateCon;
class CCharacter;
class CActor abstract : public CGameObject
{
protected:
	explicit CActor(PDIRECT3DDEVICE9 _pGraphic_Device) :CGameObject(_pGraphic_Device) {};
	explicit CActor(CActor& _actor);
	virtual ~CActor() = default;

protected:
	CStateCon* m_pStateCon = nullptr;
	//��Ŀ���ϰ� �ִ� ���
	CCharacter*	m_pFocus = nullptr;
	//���ݹ���
	_uint	m_iAttackRange = 0;
public:
	CCharacter*	Get_Focus() { return m_pFocus; }
	//Ÿ���� �� ��ü�� �߽����� �ش� ������ �ִ°�?
	bool	IsTargetInRange(CCharacter* pTarget, _int _iRange);
	//��� ������ ����ִ��� �ε����� �����Ѵ�.
	HRESULT	Get_TerrainIndex(pair<_int, _int>& _out);
public:
	virtual _int	Start();
	virtual _int	Update();
public:
	virtual HRESULT Act() = 0;
};
END
