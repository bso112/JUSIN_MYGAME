#include "stdafx.h"
#include "..\Headers\DialogMgr.h"
#include "MyDialog.h"
#include "ObjMgr.h"
USING(MyGame)

IMPLEMENT_SINGLETON(CDialogMgr)
CDialogMgr::CDialogMgr()
{

}


HRESULT CDialogMgr::Initialize(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	m_pMainDialog = (CMyDialog*)pObjMgr->Add_GO_To_Layer(L"UI", SCENE_STAGE, CMyDialog::Create(_pGraphic_Device));
	if (nullptr == m_pMainDialog)
		return E_FAIL;
	Safe_AddRef(m_pMainDialog);

	return S_OK;
}

HRESULT CDialogMgr::Log_Main(wstring* _pLog)
{
	if (nullptr == m_pMainDialog)
		return E_FAIL;
	m_pMainDialog->Log(_pLog);
	return S_OK;
}

void CDialogMgr::Free()
{
	Safe_Release(m_pMainDialog);
}
