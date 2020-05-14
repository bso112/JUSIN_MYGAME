#pragma once
#include "Terrain.h"

BEGIN(MyGame)
class CStair final: public CTerrain
{
public:
	enum TYPE { TYPE_UP = 0, TYPE_DOWN, TYPE_END};
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
	virtual	HRESULT	OnMoveFrame() override;
	virtual HRESULT	OnLoadData() override;

public:
	TYPE	Get_Type() { return m_eType; }

protected:
	virtual void OnCollisionEnterTerrain(CGameObject* _pOther);

public:
	static CStair*	Create(PDIRECT3DDEVICE9 _pGraphic_Device, TERRAIN _tData, const _tchar* _pTextureTag, SCENEID _eTextureScene, const _tchar* _pLayerTag, _tchar* _pFilePath = nullptr);
	virtual CGameObject* Clone(void * _param = nullptr) override;

};
END
