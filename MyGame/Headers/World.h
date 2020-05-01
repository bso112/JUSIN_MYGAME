#pragma once

#include "Base.h"

BEGIN(MyGame)

#define WORLDX 100
#define WORLDY 100

class CTerrain;
class CTransform;
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

private:
	//어느 씬의 월드인가
	SCENEID		m_eSceneID = SCENE_END;
	

public:
	HRESULT	Initialize(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eTextureScene, _tchar* _pFilePath = nullptr);
	HRESULT Render();

public:
	HRESULT	Set_Terrain(CTerrain* _pTerrain, POINT& _pt);
	HRESULT	Get_TerrainPos(POINT _dst, Vector3& _out);

public:
	HRESULT	Save_World(const _tchar* _filePath);
	//지형의 프로토타입이 있다고 가정하고 로드한다.
	HRESULT	Load_World(const _tchar* _filePath, SCENEID _eSceneID);

private:
	HRESULT	Initalize_Prototypes(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eSceneID);
public:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;

};
END
