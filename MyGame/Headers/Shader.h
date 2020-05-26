#pragma once
#include "Module.h"


BEGIN(MyGame)

class CShader final : public CModule
{
protected:
	explicit CShader(LPDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CShader(CShader& _module);
	virtual ~CShader() = default;

private:
	LPD3DXEFFECT			m_pEffect = nullptr;

public:
	virtual HRESULT Initialize_Prototype(_tchar* pFilePath);
	virtual HRESULT Initialize(void* _pArg);

public:
	HRESULT Set_Texture(D3DXHANDLE hParameter, LPDIRECT3DTEXTURE9 pTexture);
	HRESULT Set_Value(D3DXHANDLE hParameter, void* _pValue, _uint _iSize);
	HRESULT	CommitChage() { return m_pEffect->CommitChanges(); }
public:
	HRESULT Begin();
	HRESULT	End();
	HRESULT Begin_Pass(_uint _iIndex);
	HRESULT	End_Pass();


public:
	static CShader* Create(LPDIRECT3DDEVICE9 _pGraphic_Device, _tchar* pFilePath);
	virtual CModule * Clone(void * _pArg = nullptr) override;
	virtual void Free() override;
};

END