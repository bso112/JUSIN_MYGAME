#pragma once

#include "Base.h"

BEGIN(MyGame)



class CTerrain;
class CTransform;
class CGameObject;
class CPipline;
//레벨 하나에 대한 정보를 담고 있는 클래스
class CLevel final : public CBase
{
private:
	explicit CLevel(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CLevel() = default;

private:
	//객체가 아닌 포인터로 지형을 구성한다. (지형이 있는 인덱스만 채워진다. 나머지는 nullptr)
	CTerrain*	m_pTerrains[WORLDY][WORLDX];
	CPipline*	m_pPipline = nullptr;
	//충돌처리를 위해 리스트로선언
	list<CGameObject*> m_listCollidable;

	vector<CTerrain*> m_vecMask;
	list<CTerrain*> m_listVisited;
private:

	//로드 파일경로
	const _tchar* m_pLoadfilePath = L"../Bin/Data/level1.dat";
private:
	//어느 씬의 월드인가
	SCENEID		m_eSceneID = SCENE_END;
	PDIRECT3DDEVICE9 m_pGraphic_Device = nullptr;
	//플레이어가 스폰되는 위치
	Vector3		m_vPlayerSpawnPos;
	//이전 층의 마지막 위치
	Vector3		m_vPlayerLastPos;
public:
	HRESULT	Initialize(SCENEID _eSceneID, _tchar* _pLoadFilePath = nullptr);
	HRESULT Render_ForEditor();


public:
	HRESULT	Set_Terrain(CTerrain* _pTerrain, POINT& _pt);
	HRESULT	Fill_Terrain(CTerrain* _pTerrain, POINT& _pt);
	HRESULT	Erase_Mask(POINT& _pt);
	HRESULT	Get_TerrainPos(POINT _dst, Vector3& _out);
	//A* 알고리즘을 적용해 경로를 반환한다.
	//몬스터용
	HRESULT	Get_Route(Vector3 _src, Vector3 _dst, vector<CTerrain*>& _out, CTransform* _pMover);
	//플레이어용
	HRESULT	Get_Route(Vector3 _src, POINT& _dst, vector<CTerrain*>& _out, CTransform* _pMover);

	//해당 마우스위치에 있는 타일을 알려준다.(마우스좌표 한정)
	CTerrain* Pick_Tile(POINT& _pt);
	//해당 위치에 있는 타일을 알려준다.
	CTerrain* Pick_Tile(Vector3& dst);

	Vector3	Get_RandomPos();
	//vOrigin을 중심으로 _range 영역 안의 랜덤포지션을 리턴한다.
	Vector3	Get_RandomPos(Vector3 _vPos, _int _iRange);

	//플레이어 스폰 위치를 가져온다.
	Vector3 Get_PlayerSpawnPos();
	Vector3	Get_PlayerLastPos();

	//list<CGameObject*>* Get_Movable() { return &m_listMovable; }

	void	SetActive(_bool _bActive);
	HRESULT	Set_Visuable(Vector3 _vPlayerPos, _int _iRange);
	HRESULT	Explore(Vector3 _vPos);
public:
	HRESULT	Save_World(const _tchar* _filePath);
	//지형의 프로토타입이 있다고 가정하고 로드한다.
	HRESULT	Load_World(SCENEID _eSceneID);


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
