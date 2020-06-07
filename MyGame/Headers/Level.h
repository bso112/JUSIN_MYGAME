#pragma once

#include "Base.h"

BEGIN(MyGame)



class CTerrain;
class CTransform;
class CGameObject;
class CPipline;
//���� �ϳ��� ���� ������ ��� �ִ� Ŭ����
class CLevel final : public CBase
{
private:
	explicit CLevel(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CLevel() = default;

private:
	//��ü�� �ƴ� �����ͷ� ������ �����Ѵ�. (������ �ִ� �ε����� ä������. �������� nullptr)
	CTerrain*	m_pTerrains[WORLDY][WORLDX];
	CPipline*	m_pPipline = nullptr;
	//�浹ó���� ���� ����Ʈ�μ���
	list<CGameObject*> m_listCollidable;

	vector<CTerrain*> m_vecMask;
	list<CTerrain*> m_listVisited;
private:

	//�ε� ���ϰ��
	const _tchar* m_pLoadfilePath = L"../Bin/Data/level1.dat";
private:
	//��� ���� �����ΰ�
	SCENEID		m_eSceneID = SCENE_END;
	PDIRECT3DDEVICE9 m_pGraphic_Device = nullptr;
	//�÷��̾ �����Ǵ� ��ġ
	Vector3		m_vPlayerSpawnPos;
	//���� ���� ������ ��ġ
	Vector3		m_vPlayerLastPos;
public:
	HRESULT	Initialize(SCENEID _eSceneID, _tchar* _pLoadFilePath = nullptr);
	HRESULT Render_ForEditor();


public:
	HRESULT	Set_Terrain(CTerrain* _pTerrain, POINT& _pt);
	HRESULT	Fill_Terrain(CTerrain* _pTerrain, POINT& _pt);
	HRESULT	Erase_Mask(POINT& _pt);
	HRESULT	Get_TerrainPos(POINT _dst, Vector3& _out);
	//A* �˰����� ������ ��θ� ��ȯ�Ѵ�.
	//���Ϳ�
	HRESULT	Get_Route(Vector3 _src, Vector3 _dst, vector<CTerrain*>& _out, CTransform* _pMover);
	//�÷��̾��
	HRESULT	Get_Route(Vector3 _src, POINT& _dst, vector<CTerrain*>& _out, CTransform* _pMover);

	//�ش� ���콺��ġ�� �ִ� Ÿ���� �˷��ش�.(���콺��ǥ ����)
	CTerrain* Pick_Tile(POINT& _pt);
	//�ش� ��ġ�� �ִ� Ÿ���� �˷��ش�.
	CTerrain* Pick_Tile(Vector3& dst);

	Vector3	Get_RandomPos();
	//vOrigin�� �߽����� _range ���� ���� ������������ �����Ѵ�.
	Vector3	Get_RandomPos(Vector3 _vPos, _int _iRange);

	//�÷��̾� ���� ��ġ�� �����´�.
	Vector3 Get_PlayerSpawnPos();
	Vector3	Get_PlayerLastPos();

	//list<CGameObject*>* Get_Movable() { return &m_listMovable; }

	void	SetActive(_bool _bActive);
	HRESULT	Set_Visuable(Vector3 _vPlayerPos, _int _iRange);
	HRESULT	Explore(Vector3 _vPos);
public:
	HRESULT	Save_World(const _tchar* _filePath);
	//������ ������Ÿ���� �ִٰ� �����ϰ� �ε��Ѵ�.
	HRESULT	Load_World(SCENEID _eSceneID);


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
