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
	//할 수 있는 행동을 정한다.
	CItem::Initialize(_param);
	m_vecActions.push_back(AC_EAT);

	Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform, L"Transform", &CTransform::STATEDESC(300.0, 300.0));
	Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer);
	Set_Module(L"Texture_Food", SCENE_STAGE, (CModule**)&m_pTexture);
	m_pTextureTag = L"Texture_Food";

	m_pTransform->Set_ColliderSize(COLLIDER_SIZE);
	return S_OK;
}



HRESULT CFood::Use(CHero * _pHero, const _tchar ** _pAction)
{
	//이거 하면 인벤토리 닫힐때 액티브 false되서 작동안함
	//if (!m_bActive)
	//	return 0;

	if (0 == lstrcmp(*_pAction, AC_EAT))
	{
		//먹기
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
