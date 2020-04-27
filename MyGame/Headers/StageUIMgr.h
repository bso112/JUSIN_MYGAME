#pragma once
#include "Base.h"

BEGIN(MyGame)
class CObjMgr;
class CStageUIMgr : public CBase
{
	DECLARE_SINGLETON(CStageUIMgr)
private:
	explicit CStageUIMgr();
	virtual ~CStageUIMgr() = default;

private:
	CObjMgr*			m_pObjMgr;
public:
	HRESULT	Initialize(LPDIRECT3DDEVICE9 _pGraphic_Device);
	HRESULT Update();
	HRESULT Render();

private:
	HRESULT Initialize_Prototype(LPDIRECT3DDEVICE9 pGraphic_Device);

public:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;
};


END