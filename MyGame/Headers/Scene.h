#pragma once
#include "Base.h"

//���� ������ �����ؾ� �ϱ⶧���� ��� ���� ������ ����
#include "ObjMgr.h"
#include "ModuleMgr.h"
#include "Renderer.h"

BEGIN(MyGame)
class CPipline;
class CScene abstract: public CBase
{
protected:
	explicit CScene(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CScene() = default;

protected:
	PDIRECT3DDEVICE9	m_pGraphic_Device = nullptr;
	CRenderer*			m_pRenderer = nullptr;
	CObjMgr*			m_pObjMgr = nullptr;
	CPipline*			m_pPipline = nullptr;
public:
	virtual HRESULT Initialize();
	virtual _int	Update(_double _timeDelta);
	virtual HRESULT	Render();



protected:
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;

};

END