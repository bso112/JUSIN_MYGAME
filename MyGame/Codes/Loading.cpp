#include "stdafx.h"
#include "..\Headers\Loading.h"
#include "TextureLoader.h"
#include "LevelMgr.h"
#include "ObjMgr.h"
#include "Camera.h"
#include "TargetMgr.h"

USING(MyGame)
CLoading::CLoading(PDIRECT3DDEVICE9 _pGraphic_Device)
	:m_pGraphic_Device(_pGraphic_Device)
{
}

_uint APIENTRY Theared_Main(void* _pArg)
{
	
	if (nullptr == _pArg)
		return -1;
	CLoading* pLoading = (CLoading*)_pArg;

	HRESULT hr = 0;
	//���⼭���� �Ӱ迵��
	EnterCriticalSection(&pLoading->Get_CriticalSection());

	//�����ͷε�
	switch (pLoading->Get_SceneID())
	{
	case SCENE_MENU:
		break;
	case SCENE_STAGE:
		pLoading->Initialize_Stage();
		break;

	}

	//�Ӱ迵���� �������´�.
	LeaveCriticalSection(&pLoading->Get_CriticalSection());


	pLoading->Set_Finish();
	if (FAILED(hr))
		return -1;

	return 0;

}



HRESULT CLoading::Initialize(SCENEID _eSceneID)
{
	m_eSceneID = _eSceneID;
	/*
	@ ũ��Ƽ�� ����
	�Ӱ迵�� ��ü�� ���ϱ⵵�ϰ�, ���� �Ŵ� ����� �ǹ��ϱ⵵ �Ѵ�.
	m_CriticalSection�� �Ӱ迵���� ���� ���� Key�� �ǹ��Ѵ�. �� Key�� �־�� �Ӱ迵���� �� �� �ִ�.

	�Ӱ迵���� ���� ���� �����Ϳ����� �ǹ��Ѵ�.
	��� ������� �� ���� �����Ϳ����� �����ϰ�, ���� ������ ���ÿ����� ���´�.

	������ ���� ��Ƽ������� ��Ƽ���μ����� �ƴ϶�� ���̴�.
	���ͺ��� ��Ƽ������� �ڵ��� �帧�� �������� ��ó�� ��������, 
	�װ��� �ϳ��� cpu �ھ ���� �����带 �Űܰ��� ������ �����ϴ� �ú��ҹ���̱� ������ �׷��� ���̴� �� ���̴�.
	�������� �ڵ��� �帧�� �������� ���� ��Ƽ�ھ� cpu�� ��Ƽ���μ��� ���α׷��� �������̴�.
	*/
	InitializeCriticalSection(&m_CriticalSection);
	
	/*
	�����带 �����.
	unsigned stack_size	: �����尡 ����� ���ÿ����� ������. 0�� �ָ� 1����Ʈ�� ���õȴ�. (���ÿ����� ������ �ڵ����� �������� ������ ũ�Ⱑ �ʿ䰡 ����)
	unsigned ( __clrcall *start_address )( void * ) : �������� ������(�����Լ�)
	
	*/
	m_Handle = (HANDLE)_beginthreadex(nullptr, 0, Theared_Main, this, 0, nullptr);
	return S_OK;
}

HRESULT CLoading::Initialize_Stage()
{
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	if (nullptr == pObjMgr)
		return E_FAIL;

	CTextureLoader* pLoader = CTextureLoader::Get_Instance();
	if (nullptr == pLoader)

		return E_FAIL;

	Safe_AddRef(pLoader);

	//�ؽ��Ļ���
	pLoader->Create_Textrues_From_Folder(m_pGraphic_Device, SCENE_STAGE, L"../Bin/Resources/Textures/UI/Stage/");
	pLoader->Create_Textrues_From_Folder(m_pGraphic_Device, SCENE_STAGE, L"../Bin/Resources/Textures/UI/icon/");
	pLoader->Create_Textrues_From_Folder_Anim(m_pGraphic_Device, SCENE_STAGE, L"../Bin/Resources/Textures/Terrain/level_one/");
	pLoader->Create_Textrues_From_Folder_Anim(m_pGraphic_Device, SCENE_STAGE, L"../Bin/Resources/Textures/Effect/");


	Safe_Release(pLoader);

	CLevelMgr* pLevelMgr = CLevelMgr::Get_Instance();

	//������ �ʿ��� ���η�Ÿ�� ����
	if (FAILED(pLevelMgr->Initialize_Prototypes(m_pGraphic_Device)))
		return E_FAIL;



	//ī�޶� ���η�Ÿ�� ����
	pObjMgr->Add_Prototype(L"MainCamera", SCENE_STAGE, CCamera::Create(m_pGraphic_Device));


	
	//����Ÿ�� ����
	CTargetMgr* pTargetMgr = CTargetMgr::Get_Instance();
	RETURN_FAIL_IF_NULL(pTargetMgr);
	pTargetMgr->Add_RenderTarget(m_pGraphic_Device, L"Portrait", 100.f, 100.f, D3DFMT_A8R8G8B8);
	pTargetMgr->Add_RenderTarget(m_pGraphic_Device, L"fog", g_iWinCX, g_iWinCY, D3DFMT_A8R8G8B8);


	return S_OK;

}



CLoading * CLoading::Create(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eSceneID)
{
	CLoading* pInstance = new CLoading(_pGraphic_Device);
	if (FAILED(pInstance->Initialize(_eSceneID)))
	{
		MSG_BOX("Fail to create Loading");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLoading::Free()
{
	//�������� ���൵�߿� �����带 ������ �޸𸮸��� �� �� �ִ�. ���� ���������� ��ٸ���.
	WaitForSingleObject(m_Handle, INFINITE);

	DeleteCriticalSection(&m_CriticalSection);

	CloseHandle(m_Handle);

	Safe_Release(m_pGraphic_Device);
}
