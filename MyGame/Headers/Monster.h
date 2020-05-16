#pragma once
#include "Character.h"
#include "State.h"
BEGIN(MyGame)

class CAnimator;
class CMonster abstract : public CCharacter
{

protected:
	explicit CMonster(PDIRECT3DDEVICE9 _pGraphic_Device) :CCharacter(_pGraphic_Device) {};
	explicit CMonster(CMonster& _rhs);
	virtual ~CMonster() = default;

protected:
	CAnimator*		m_pAnimator = nullptr;

public:
	virtual _int	Update(_double _timeDelta);
	virtual _int	LateUpate(_double _timeDelta);
	virtual HRESULT	Render();

protected:
	virtual	HRESULT	OnRender();


public:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;









};
END
