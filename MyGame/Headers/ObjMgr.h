#pragma once
#include "Base.h"

BEGIN(MyGame)
class CGameObject;
class CLayer;
class CObjMgr final : public CBase
{
	DECLARE_SINGLETON(CObjMgr)
private:
	CObjMgr();
	virtual ~CObjMgr();

private:
	map<const wchar_t*, CGameObject*>	m_mapPrototype[SCENE_END];
	map<const wchar_t*, CLayer*>			m_mapLayer[SCENE_END];

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
	HRESULT			Add_Prototype(const wchar_t* _pPrototypeKey, SCENEID _ePrototypeSceneID, CGameObject* _pGO);
	//������Ÿ���� ������ ��ü�� �����Ѵ�. ������ ��ü�� ���̾�ʿ� �ִ´�. ���� �ش� ���̾ ������ ���� �����.
	HRESULT			Add_GO_To_Layer(const wchar_t* _pPrototypeKey, SCENEID _ePrototypeSceneID, const wchar_t* _pLayerKey, SCENEID _eLayerSceneID);
	CGameObject*	Find_Prototype(const wchar_t* _pPrototypeKey, SCENEID _ePrototypeSceneID);
	CLayer*			Find_Layer(const wchar_t* _pLayerKey, SCENEID _eLayerSceneID);


private:
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;
};

END
