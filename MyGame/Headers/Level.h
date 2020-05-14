#pragma once

#include "Base.h"

BEGIN(MyGame)

#define WORLDX 100
#define WORLDY 100

class CTerrain;
class CTransform;
class CGameObject;
//���� �ϳ��� ���� ������ ��� �ִ� Ŭ����
class CLevel final : public CBase
{
private:
	explicit CLevel(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CLevel() = default;

private:
	//��ü�� �ƴ� �����ͷ� ������ �����Ѵ�. (������ �ִ� �ε����� ä������. �������� nullptr)
	CTerrain* m_pTerrains[WORLDY][WORLDX];

private:
	//���η�Ÿ�Ե�
	CTerrain*	m_Water;
	CTerrain*	m_Wall;
	CTerrain*	m_Grass;
	
private:
	//��� ���� �����ΰ�
	SCENEID		m_eSceneID = SCENE_END;
	PDIRECT3DDEVICE9 m_pGraphic_Device = nullptr;
	Vector3		m_vPlayerSpawnPos;
public:
	HRESULT	Initialize(SCENEID _eSceneID, _tchar* _pFilePath = nullptr);
	HRESULT Render_ForEditor();
	

public:
	HRESULT	Set_Terrain(CTerrain* _pTerrain, POINT& _pt);
	HRESULT	Get_TerrainPos(POINT _dst, Vector3& _out);
	//A* �˰����� ������ ��θ� ��ȯ�Ѵ�.
	HRESULT	Get_Route(Vector3 _src, POINT _dst, vector<Vector3>& _out, CTransform* _pMover);
	HRESULT	Get_Route(Vector3 _src, Vector3 _dst, vector<Vector3>& _out, CTransform* _pMover);
	HRESULT	Get_Route(Vector3 _src, Vector3 _dst, vector<CTerrain*>& _out, CTransform* _pMover);

	Vector3	Get_RandomPos();
	//�÷��̾� ���� ��ġ�� �����´�.
	Vector3 Get_PlayerSpawnPos();


public:
	HRESULT	Save_World(const _tchar* _filePath);
	//������ ������Ÿ���� �ִٰ� �����ϰ� �ε��Ѵ�.
	HRESULT	Load_World(const _tchar* _filePath, SCENEID _eSceneID);

public:
	HRESULT	Next_Level();
	HRESULT Prv_Level();

private:
	HRESULT	Initalize_Prototypes(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eSceneID);

public:
	//������ �浹ó��
	HRESULT	Collision_Terrain(CGameObject* _pObj);
	HRESULT Collision_Terrain(list<CGameObject*> _pObjlist);
public:
	static CLevel* Create(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eSceneID, _tchar* _pFilePath);
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;

};
END
