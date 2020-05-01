#pragma once
#include "Terrain.h"

BEGIN(MyGame)
class CDoor final : public CTerrain
{
private:
	explicit CDoor(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CDoor(CDoor& _rhs);
	virtual ~CDoor() = default;

private:
	bool	m_bLocked = false;


public:
	virtual HRESULT	Interact(CGameObject* _pInteractor);
protected:
	virtual	HRESULT	OnMoveFrame();
	virtual HRESULT	OnLoadData();
private:
	void	UnLock();
	void	Lock();
};
END
