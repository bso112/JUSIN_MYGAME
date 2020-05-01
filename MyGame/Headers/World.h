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
	HRESULT Render();

public:
	HRESULT	Set_Terrain(CTerrain* _pTerrain, POINT& _pt);
	HRESULT	Get_TerrainPos(POINT _dst, Vector3& _out);

public:
	HRESULT	Save_World(const _tchar* _filePath);
	//������ ������Ÿ���� �ִٰ� �����ϰ� �ε��Ѵ�.
	HRESULT	Load_World(const _tchar* _filePath, SCENEID _eSceneID);

private:
	HRESULT	Initalize_Prototypes(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eSceneID);
public:
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;

};
END
