#pragma once

#include "Base.h"

BEGIN(MyGame)

#define WORLDX 100
#define WORLDY 100

class CTerrain;
class CTransform;
class CGameObject;
class CWorld final : public CBase
{
	DECLARE_SINGLETON(CWorld)
private:
	explicit CWorld();
	virtual ~CWorld() = default;

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


public:
	HRESULT	Initialize(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eTextureScene, _tchar* _pFilePath = nullptr);
	_int	Update();
	HRESULT Render();

public:
	HRESULT	Set_Terrain(CTerrain* _pTerrain, POINT& _pt);
	HRESULT	Get_TerrainPos(POINT _dst, Vector3& _out);
	//A* �˰����� ������ ��θ� ��ȯ�Ѵ�.
	HRESULT	Get_Route(Vector3 _src, POINT _dst, vector<Vector3>& _out, CTransform* _pMover);
	HRESULT	Get_Route(Vector3 _src, Vector3 _dst, vector<Vector3>& _out, CTransform* _pMover);
	HRESULT	Get_Route(Vector3 _src, Vector3 _dst, vector<CTerrain*>& _out, CTransform* _pMover);


	Vector3	Get_RandomPos();


public:
	HRESULT	Save_World(const _tchar* _filePath);
	//������ ������Ÿ���� �ִٰ� �����ϰ� �ε��Ѵ�.
	HRESULT	Load_World(const _tchar* _filePath, SCENEID _eSceneID);

private:
	HRESULT	Initalize_Prototypes(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eSceneID);

public:
	//������ �浹ó��
	HRESULT	Collision_Terrain(CGameObject* _pObj);
	HRESULT Collision_Terrain(list<CGameObject*> _pObjlist);
public:
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;

};
END
