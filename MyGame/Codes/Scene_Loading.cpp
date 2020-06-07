#include "stdafx.h"
#include "..\Headers\Scene_Loading.h"
#include "Loading.h"
#include "ObjMgr.h"
#include "Image.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
USING(MyGame)

CScene_Loading::CScene_Loading(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CScene(_pGraphic_Device)
{
	ZeroMemory(m_pImgArc1, sizeof(m_pImgArc1));
}

HRESULT CScene_Loading::Initialize()
{
	if (nullptr == m_pObjMgr)
		return E_FAIL;

	CSoundMgr::Get_Instance()->StopAll();

	CImage* pImage = (CImage*)m_pObjMgr->Add_GO_To_Layer(L"Loading", SCENE_LOADING, CImage::Create(m_pGraphic_Device, Vector2((float)(g_iWinCX >> 1), float(g_iWinCY >>1)), Vector2((float)g_iWinCX, (float)g_iWinCY), L"loading", SCENE_STATIC));
	pImage->Set_UI(true);
	m_pLoading = CLoading::Create(m_pGraphic_Device, SCENE_STAGE);

#pragma region ��׶����غ�

	for (int i = 0; i < ARC1Y; ++i)
	{
		for (int j = 0; j < ARC1X; ++j)
		{
			m_pImgArc1[i][j] = CImage::Create(m_pGraphic_Device, Vector4((float)(ARC1CX >> 1) + ARC1CX * j, (float)(ARC1CY >> 1) + ARC1CY * i), Vector2(ARC1CX, ARC1CY), L"block", SCENE_STATIC);
		}
	}



#pragma endregion

	
	return S_OK;
}

_int CScene_Loading::Update(_double _timeDelta)
{

	CScene::Update(_timeDelta);

	if (m_pLoading->IsFinish())
	{
		CSceneMgr::Get_Instance()->Scene_Change(SCENE_STAGE, m_pGraphic_Device);
	}

	for (int i = 0; i < ARC1Y; ++i)
	{
		for (int j = 0; j < ARC1X; ++j)
		{
			CTransform* pTransform = (CTransform*)(m_pImgArc1[i][j]->Get_Module(L"Transform"));

			if (pTransform == nullptr)
				return -1;


			//���� ���翭�� �ٴ��� õ�忡 ������ �����ϴ� ���� �ٷ� ������ ��ġ�� �����Ѵ�.
			//0���� ���������� ������ �̵��Ѵ�.

			if (pTransform->Get_Position().y + (ARC1CY >> 1) < 0)
			{
				CTransform* pLastArcTransform = nullptr;

				if (i == 0)
					pLastArcTransform = (CTransform*)(m_pImgArc1[ARC1Y - 1][j]->Get_Module(L"Transform"));
				else
					pLastArcTransform = (CTransform*)(m_pImgArc1[i - 1][j]->Get_Module(L"Transform"));

				if (pLastArcTransform == nullptr)
					return -1;

				Vector3 vLastArcPos = pLastArcTransform->Get_Position();
				pTransform->Set_Position(Vector3(vLastArcPos.x, vLastArcPos.y + ARC1CY));
			}

			pTransform->MoveToDir(Vector3(0, -1), _timeDelta, 100.f);
			m_pImgArc1[i][j]->Update(_timeDelta);
			pTransform->Update_Transform();
		}
	}


	return 0;
}

HRESULT CScene_Loading::Render()
{
	CScene::Render();
	
	for (int i = 0; i < ARC1Y; ++i)
	{
		for (int j = 0; j < ARC1X; ++j)
		{
			m_pImgArc1[i][j]->Render();
		}
	}
	
	g_pFontX2->DrawText(NULL, L"����������...", -1, &Make_Rect(Vector2(g_iWinCX >> 1, g_iWinCY >>1), Vector2(500.f,100.f)), DT_CENTER | DT_VCENTER, 0xffffffff);
	
	return S_OK;
}




CScene_Loading * CScene_Loading::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CScene_Loading* pInstance = new CScene_Loading(_pGraphic_Device);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Fail to Create Loading Scene");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CScene_Loading::Free()
{
	for (int i = 0; i < ARC1Y; ++i)
	{
		for (int j = 0; j < ARC1X; ++j)
		{
			Safe_Release(m_pImgArc1[i][j]);
		}
	}


	Safe_Release(m_pLoading);
	//���� ������Ʈ ������Ÿ�� �����, ���� ������Ʈ �ν��Ͻ��� ���� ���۷��� ����, ��� �ν��Ͻ� �����
	if (FAILED(CObjMgr::Get_Instance()->Clear_Scene(SCENEID::SCENE_LOADING)))
		MSG_BOX("Fail to Clear GameObject Prototypes");

	//��� ������Ÿ�� �����
	if (FAILED(CModuleMgr::Get_Instance()->Clear_Scene(SCENEID::SCENE_LOADING)))
		MSG_BOX("Fail to Clear Module Prototypes");

	//���� ������Ʈ �ν��Ͻ� �����
	if (FAILED(CRenderer::Get_Instance()->Clear_RenderGroup()))
		MSG_BOX("Fail to Clear Module Prototypes");



	CScene::Free();
}
