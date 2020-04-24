#include "stdafx.h"
#include "..\Headers\Text.h"

USING(MyGame)
CText::CText(LPDIRECT3DDEVICE9 _pGraphic_Device)
	:CModule(_pGraphic_Device)
{
	
}

CText::CText(CText & _module)
	: CModule(_module)
{
	
}

HRESULT CText::Initialize_Prototype()
{
	return S_OK;
}
HRESULT CText::Initialize(void * _pArg)
{
	return S_OK;
}
CModule * CText::Clone(void * _pArg)
{
	return nullptr;
}
void CText::Free()
{
	CModule::Free();
}

