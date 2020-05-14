#pragma once
#include "Terrain.h"

BEGIN(MyGame)
class CStair final: public CTerrain
{
public:
	enum TYPE { TYPE_UP, TYPE_DOWN, TYPE_END};
private:
	explicit CStair(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CStair(CStair& _rhs);
	virtual ~CStair() = default;

private:
	TYPE	m_eType = TYPE_END;
	//플레이어와 닿은 적이 있는가.
	_bool	m_bContacted = false;
public:
	virtual	HRESULT	Initialize() override;

protected:
	virtual void OnCollisionEnterTerrain(CGameObject* _pOther);

};
END
