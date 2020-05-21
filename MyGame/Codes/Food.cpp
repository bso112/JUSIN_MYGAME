#include "stdafx.h"
#include "..\Headers\Food.h"
#include "Hero.h"
#include "InventoryUIMgr.h"
USING(MyGame)


CFood::CFood(CFood & _rhs)
	:CItem(_rhs)
{
	ZeroMemory(&m_tDesc, sizeof(STATEDESC));

}



HRESULT CFood::Initialize(void * _param)
{
	//�� �� �ִ� �ൿ�� ���Ѵ�.
	CItem::Initialize();
	m_vecActions.push_back(AC_EAT);
	
	//������� ����Ŭ�������� ����
	if (nullptr != _param)
		m_tDesc.tBaseDesc.vPos = ((BASEDESC*)_param)->vPos;


	Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform);
	Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer);
	Set_Module(L"Texture_Food", SCENE_STAGE, (CModule**)&m_pTexture);
	m_pTextureTag = L"Texture_Food";

	m_pTransform->Set_Position(m_tDesc.tBaseDesc.vPos);
	m_pTransform->Set_Size(m_tDesc.tBaseDesc.vSize);
	m_pTransform->Set_ColliderSize(m_tDesc.tBaseDesc.vSize);


	return S_OK;
}





CFood * CFood::Create(PDIRECT3DDEVICE9 _pGrahic_Device, _tchar* _pFilePath)
{
	CFood* pInstance = new CFood(_pGrahic_Device);
	if (FAILED(pInstance->Initialize_Prototype(_pFilePath)))
	{
		MSG_BOX("Fail to create CFood");
		Safe_Release(pInstance);

	}
	return pInstance;
}



CGameObject * CFood::Clone(void * _param)
{
	CFood* pInstance = new CFood(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to create CFood");
		Safe_Release(pInstance);

	}
	return pInstance;
}


HRESULT CFood::Use(CHero * _pHero, const _tchar * _pAction)
{
	//�̰� �ϸ� �κ��丮 ������ ��Ƽ�� false�Ǽ� �۵�����
	//if (!m_bActive)
	//	return 0;

	if (0 == lstrcmp(_pAction, AC_EAT))
	{
		//�Ա�
		_pHero->Heal(m_tDesc.fHealAmount);
		m_bUsed = true;
		m_bDead = true;
	}

	return CItem::Use(_pHero, _pAction);
}


void CFood::Free()
{
	CItem::Free();
}
