#pragma once
#include "Base.h"

BEGIN(MyGame)
class CGameObject;
class CLayer;
class CHero;
class CObjMgr final : public CBase
{
	DECLARE_SINGLETON(CObjMgr)

private:
	CObjMgr();
	virtual ~CObjMgr();

private:
	map<const _tchar*, CGameObject*>	m_mapPrototype[SCENE_END];
	map<const _tchar*, CLayer*>			m_mapLayer[SCENE_END];

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
	HRESULT			Add_Prototype(const _tchar* _ePrototypeID, SCENEID _ePrototypeSceneID, CGameObject* _pGO);
	//������Ÿ���� ������ ��ü�� �����Ѵ�. ������ ��ü�� ���̾�ʿ� �ִ´�. ���� �ش� ���̾ ������ ���� �����.
	CGameObject*	Add_GO_To_Layer(const _tchar* _ePrototypeID, SCENEID _ePrototypeSceneID, const _tchar* _eLayerID, SCENEID _eLayerSceneID, void* _pArg = nullptr);
	//������Ʈ�� ���̾ ����Ѵ�.
	HRESULT			Add_GO_To_Layer(const _tchar* _eLayerID, SCENEID _eLayerSceneID, CGameObject* _pObj);
	CGameObject*	Find_Prototype(const _tchar* _ePrototypeID, SCENEID _ePrototypeSceneID);
	CLayer*			Find_Layer(const _tchar* _eLayerID, SCENEID _eLayerSceneID);
	CGameObject*	Get_Player(SCENEID _eLayerSceneID);
	//���� �����ϴ� ������Ÿ�Ե�� ���̾���� Ŭ�����Ѵ�.
	HRESULT			Clear_Scene(SCENEID _eSceneID);
	

private:
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;
};

END
