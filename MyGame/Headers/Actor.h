#pragma once
#include "GameObject.h"

BEGIN(MyGame)
class CActor abstract : public CGameObject
{
protected:
	explicit CActor(PDIRECT3DDEVICE9 _pGraphic_Device) :CGameObject(_pGraphic_Device) {};
	explicit CActor(CActor& _actor);
	virtual ~CActor() = default;

public:
	virtual HRESULT Act() = 0;
};
END
