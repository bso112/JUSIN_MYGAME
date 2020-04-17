#pragma once

#include "VIBuffer.h"
#include "Textrue.h"
BEGIN(MyGame)
class CModuleMgr : public CBase
{
	DECLARE_SINGLETON(CModuleMgr)

private:
	explicit CModuleMgr() {};
	virtual ~CModuleMgr() = default;

private:
	//모듈 원본객체를 enum으로 찾기위해 맵으로 관리한다.
	map<MODULE, CModule*> m_mapPrototypes[SCENE_END];

public:
	//모듈 프로토타입을 추가한다.
	HRESULT		Add_Module(MODULE _ePrototypeID, SCENEID _ePrototypeSceneID, CModule* _pModule);
	//원본으로부터 복사한 모듈을 넘겨준다.
	CModule*	Get_Module(MODULE _ePrototypeID, SCENEID _ePrototypeSceneID);
private:
	CModule*	Find_Module(MODULE _ePrototypeID, SCENEID _ePrototypeSceneID);

public:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;
};
END
