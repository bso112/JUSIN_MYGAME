#pragma once

#include "Base.h"

BEGIN(MyGame)

#define WORLDX 100
#define WORLDY 100

class CTerrain;
class CWorld final : public CBase
{
	DECLARE_SINGLETON(CWorld)
private:
	explicit CWorld();
	virtual ~CWorld() = default;

private:
	//객체가 아닌 포인터로 지형을 구성한다. (지형이 있는 인덱스만 채워진다. 나머지는 nullptr)
	CTerrain* m_pTerrains[WORLDY][WORLDX];

private:
	//프로로타입들
	CTerrain*	m_Water;
	CTerrain*	m_Wall;
	CTerrain*	m_Grass;
	

public:
	HRESULT	Initialize(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eTextureScene, _tchar* _pFilePath = nullptr);
	HRESULT Render();

public:
	HRESULT	Set_Terrain(CTerrain* _pTerrain, POINT& _pt);


public:
	HRESULT	Save_World();
	HRESULT	Load_World();


public:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;

};
END
