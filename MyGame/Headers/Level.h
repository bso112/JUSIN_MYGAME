#pragma once

#include "Base.h"

BEGIN(MyGame)

#define WORLDX 100
#define WORLDY 100

class CTerrain;
class CTransform;
class CGameObject;
//레벨 하나에 대한 정보를 담고 있는 클래스
class CLevel final : public CBase
{
private:
	explicit CLevel(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CLevel() = default;

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
	PDIRECT3DDEVICE9 m_pGraphic_Device = nullptr;
	Vector3		m_vPlayerSpawnPos;
public:
	HRESULT	Initialize(SCENEID _eSceneID, _tchar* _pFilePath = nullptr);
	HRESULT Render_ForEditor();
	

public:
	HRESULT	Set_Terrain(CTerrain* _pTerrain, POINT& _pt);
	HRESULT	Get_TerrainPos(POINT _dst, Vector3& _out);
	//A* 알고리즘을 적용해 경로를 반환한다.
	HRESULT	Get_Route(Vector3 _src, POINT _dst, vector<Vector3>& _out, CTransform* _pMover);
	HRESULT	Get_Route(Vector3 _src, Vector3 _dst, vector<Vector3>& _out, CTransform* _pMover);
	HRESULT	Get_Route(Vector3 _src, Vector3 _dst, vector<CTerrain*>& _out, CTransform* _pMover);

	Vector3	Get_RandomPos();
	//플레이어 스폰 위치를 가져온다.
	Vector3 Get_PlayerSpawnPos();


public:
	HRESULT	Save_World(const _tchar* _filePath);
	//지형의 프로토타입이 있다고 가정하고 로드한다.
	HRESULT	Load_World(const _tchar* _filePath, SCENEID _eSceneID);

public:
	HRESULT	Next_Level();
	HRESULT Prv_Level();

private:
	HRESULT	Initalize_Prototypes(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eSceneID);

public:
	//지형과 충돌처리
	HRESULT	Collision_Terrain(CGameObject* _pObj);
	HRESULT Collision_Terrain(list<CGameObject*> _pObjlist);
public:
	static CLevel* Create(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eSceneID, _tchar* _pFilePath);
	// CBase을(를) 통해 상속됨
	virtual void Free() override;

};
END
