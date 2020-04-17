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
	//��� ������ü�� enum���� ã������ ������ �����Ѵ�.
	map<MODULE, CModule*> m_mapPrototypes[SCENE_END];

public:
	//��� ������Ÿ���� �߰��Ѵ�.
	HRESULT		Add_Module(MODULE _ePrototypeID, SCENEID _ePrototypeSceneID, CModule* _pModule);
	//�������κ��� ������ ����� �Ѱ��ش�.
	CModule*	Get_Module(MODULE _ePrototypeID, SCENEID _ePrototypeSceneID);
private:
	CModule*	Find_Module(MODULE _ePrototypeID, SCENEID _ePrototypeSceneID);

public:
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;
};
END
