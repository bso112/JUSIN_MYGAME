#pragma once
#include "Base.h"
BEGIN(MyGame)
class CTerrain;
class CTileLoader :
	public CBase
{
public:
	CTileLoader();
	virtual ~CTileLoader();

public:
	static HRESULT CreateTilePrototype(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eSceneID, vector<CTerrain*>* container = nullptr);

};
END
