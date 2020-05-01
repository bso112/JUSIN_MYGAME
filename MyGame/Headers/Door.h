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
	virtual void OnCollisionEnter(CGameObject* _pOther) override;

protected:
	virtual	HRESULT	OnMoveFrame();
	virtual HRESULT	OnLoadData();
private:
	void	UnLock();
	void	Lock();

public:
	static CDoor* Create(PDIRECT3DDEVICE9 _pGraphic_Device, TERRAIN _tData, const _tchar* _pTextureTag, SCENEID _eTextureScene, _tchar* _pFilePath = nullptr);
	CDoor*	Clone(void* _pArg);
};
END
