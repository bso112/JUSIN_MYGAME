#pragma once
#include "Base.h"
#include "Target.h"
BEGIN(MyGame)
class CTarget;
class CTargetMgr : public CBase
{
	DECLARE_SINGLETON(CTargetMgr)
private:
	explicit CTargetMgr();
	virtual ~CTargetMgr() = default;

private:
	map<const _tchar*, CTarget*> m_mapTarget;

public:
	HRESULT		Set_RenderTarget(const _tchar* _pTag, _uint _iIndex);
	HRESULT		Release_RenderTarget(const _tchar* _pTag);
	HRESULT		Add_RenderTarget(PDIRECT3DDEVICE9 pGraphic_Device, const _tchar* _pTag, _int iCX, _int iCY, D3DFORMAT _eFormat);
	HRESULT		Clear_RenderTarget(const _tchar* _pTag);
	CTarget*	Find_Target(const _tchar* _pTag);

public:
	LPDIRECT3DTEXTURE9	Get_Texture(const _tchar* _pTag);

public:
	virtual void Free() override;

};
END
