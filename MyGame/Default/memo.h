//#include "stdafx.h"
//#include "..\Headers\Effect.h"
//
//USING(MyGame)
//
//CEffect::CEffect(PDIRECT3DDEVICE9 _pGraphic_Device)
//	:CGameObject(_pGraphic_Device)
//{
//}
//
//CEffect::CEffect(CEffect & _rhs)
//	: CGameObject(_rhs)
//{
//}
//
//HRESULT CEffect::Initialize_Prototype(_tchar * _pFilePath)
//{
//	return E_NOTIMPL;
//}
//
//HRESULT CEffect::Initialize(void * _pArg)
//{
//	return E_NOTIMPL;
//}
//
//_int CEffect::Update(_double _timeDelta)
//{
//	return _int();
//}
//
//_int CEffect::LateUpate(_double _timeDelta)
//{
//	return _int();
//}
//
//HRESULT CEffect::Render()
//{
//	return E_NOTIMPL;
//}
//
//
//CEffect * CEffect::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
//{
//	CEffect* pInstance = new CEffect(_pGraphic_Device);
//	if (FAILED(pInstance->Initialize_Prototype()))
//	{
//		MSG_BOX("Fail to create CTerrain");
//		Safe_Release(pInstance);
//
//	}
//	return pInstance;
//}
//
//CGameObject * CEffect::Clone(void * _param)
//{
//	CEffect* pInstance = new CEffect(*this);
//	if (FAILED(pInstance->Initialize(_param)))
//	{
//		MSG_BOX("Fail to clone CTile");
//		Safe_Release(pInstance);
//
//	}
//	return pInstance;
//}
//
//void CEffect::Free()
//{
//	CGameObject::Free();
//}
