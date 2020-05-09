#pragma once
#include "Character.h"
#include "State.h"
BEGIN(MyGame)

class CMonster abstract : public CCharacter
{

protected:
	explicit CMonster(PDIRECT3DDEVICE9 _pGraphic_Device) :CCharacter(_pGraphic_Device) {};
	explicit CMonster(CMonster& _rhs);
	virtual ~CMonster() = default;





public:
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;









};
END
