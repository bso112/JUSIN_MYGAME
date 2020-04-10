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
	프로토타입 패턴
	몬스터를 만들때, 그 몬스터를 구성하는 체력, 힘 같은 정보는 따로 파일이나 데이터베이스에서 가져오는게 보통이다.
	하지만 몬스터를 만들때마다 외부파일에 접근하는 것은 시간이 많이 든다.
	따라서 미리 다 만들어 놓은 다음, 필요할때 그 원본을 복사해서 사용한다.
	*/
	//프로토타입 맵에 원형객체를 넣는다.
	HRESULT			Add_Prototype(const wchar_t* _pPrototypeKey, SCENEID _ePrototypeSceneID, CGameObject* _pGO);
	//프로토타입을 복사해 객체를 생성한다. 생성한 객체는 레이어맵에 넣는다. 만약 해당 레이어가 없으면 새로 만든다.
	HRESULT			Add_GO_To_Layer(const wchar_t* _pPrototypeKey, SCENEID _ePrototypeSceneID, const wchar_t* _pLayerKey, SCENEID _eLayerSceneID);
	CGameObject*	Find_Prototype(const wchar_t* _pPrototypeKey, SCENEID _ePrototypeSceneID);
	CLayer*			Find_Layer(const wchar_t* _pLayerKey, SCENEID _eLayerSceneID);


private:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;
};

END
