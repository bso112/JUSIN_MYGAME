#pragma once

#include "VIBuffer.h"
#include "Texture.h"
#include "Transform.h"

BEGIN(MyGame)
class CModuleMgr : public CBase
{
	DECLARE_SINGLETON(CModuleMgr)

private:
	explicit CModuleMgr() {};
	virtual ~CModuleMgr() = default;

private:
	//��� ������ü�� enum���� ã������ ������ �����Ѵ�.
	map<const _tchar*, CModule*> m_mapPrototypes[SCENE_END];


public:
	//��� ������Ÿ���� �߰��Ѵ�.
	HRESULT		Add_Module(const _tchar* _pTag, SCENEID _ePrototypeSceneID, CModule* _pModule);
	//�������κ��� ������ ����� �Ѱ��ش�.
	CModule*	Get_Module(const _tchar* _pTag, SCENEID _ePrototypeSceneID, void* _pArg = nullptr);
	//���� �����ϴ� ��� ������Ÿ�Ե��� Ŭ�����Ѵ�.
	HRESULT		Clear_Scene(SCENEID _eSceneID);
private:
	CModule*	Find_Module(const _tchar* _pTag, SCENEID _ePrototypeSceneID);

public:
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;
};
END
