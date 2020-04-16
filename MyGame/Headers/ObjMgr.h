#pragma once
#include "Base.h"

BEGIN(MyGame)
class CGameObject;
class CLayer;
class CHero;
class CObjMgr final : public CBase
{
	DECLARE_SINGLETON(CObjMgr)

public:
	enum PrototypeID	{ PROTOTYPE_BACKGROUND, PROTOTYPE_PLAYER, PROTOTYPE_MONSTER, PROTOTYPE_END};
	enum LayerID		{ LAYER_BACKGROUND, LAYER_PLAYER, LAYER_MONSTER, LAYER_END};
private:
	CObjMgr();
	virtual ~CObjMgr();

private:
	map<PrototypeID, CGameObject*>	m_mapPrototype[SCENE_END];
	map<LayerID, CLayer*>			m_mapLayer[SCENE_END];

public:
	_int Update(_double _timeDelta);
	
public:
	/*
	������Ÿ�� ����
	���͸� ���鶧, �� ���͸� �����ϴ� ü��, �� ���� ������ ���� �����̳� �����ͺ��̽����� �������°� �����̴�.
	������ ���͸� ���鶧���� �ܺ����Ͽ� �����ϴ� ���� �ð��� ���� ���.
	���� �̸� �� ����� ���� ����, �ʿ��Ҷ� �� ������ �����ؼ� ����Ѵ�.
	*/
	//������Ÿ�� �ʿ� ������ü�� �ִ´�.
	HRESULT			Add_Prototype(PrototypeID _ePrototypeID, SCENEID _ePrototypeSceneID, CGameObject* _pGO);
	//������Ÿ���� ������ ��ü�� �����Ѵ�. ������ ��ü�� ���̾�ʿ� �ִ´�. ���� �ش� ���̾ ������ ���� �����.
	HRESULT			Add_GO_To_Layer(PrototypeID _ePrototypeID, SCENEID _ePrototypeSceneID, LayerID _eLayerID, SCENEID _eLayerSceneID);
	CGameObject*	Find_Prototype(PrototypeID _ePrototypeID, SCENEID _ePrototypeSceneID);
	CLayer*			Find_Layer(LayerID _eLayerID, SCENEID _eLayerSceneID);
	CGameObject*	Get_Player(SCENEID _eLayerSceneID);
	

private:
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;
};

END
