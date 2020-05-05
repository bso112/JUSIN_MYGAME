#pragma once
#include "Character.h"
#include "State.h"
BEGIN(MyGame)

class CHero;
class CMonster abstract : public CCharacter
{

protected:
	explicit CMonster(PDIRECT3DDEVICE9 _pGraphic_Device) :CCharacter(_pGraphic_Device) {};
	explicit CMonster(CMonster& _rhs);
	virtual ~CMonster() = default;

protected:
	CHero*	m_pHero = nullptr;
	//인식범위
	_uint	m_iRecogRange = 0;
protected:
	CAIState* m_pSLEEPING	= nullptr;
	CAIState* m_pHUNTING	= nullptr;
	CAIState* m_pWANDERING	= nullptr;


public:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;









};
END
