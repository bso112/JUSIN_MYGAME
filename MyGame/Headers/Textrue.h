#pragma once
#include "Module.h"

BEGIN(MyGame)
//�ؽ���Ŭ������ �������� �ؽ��ĸ� ������ �� �ִ�. 
//�ִϸ��̼� Ŭ��ó���� �� �� �ִ�.
class CTextrue final : public CModule
{
private:
	explicit CTextrue(PDIRECT3DDEVICE9 _pGraphic_Device) : CModule(_pGraphic_Device) {};
	explicit CTextrue(CTextrue& _rhs);
	virtual ~CTextrue() = default;

private:
	vector<LPDIRECT3DTEXTURE9> m_vecTexture;
public:
	virtual HRESULT Initialize_Prototype(const _tchar* _pFilePath, _uint _iCnt);
	virtual HRESULT Initialize(void* _pArg);

public:
	HRESULT Set_Textrue(_uint _iIndex);

public:
	static CTextrue* Create(PDIRECT3DDEVICE9 _pGraphic_Device, _tchar* _pFilePath, _uint _iCnt = 1);
	virtual CModule * Clone(void * _pArg = nullptr) override;
	virtual void Free();
};
END
