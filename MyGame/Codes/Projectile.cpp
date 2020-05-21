#include "stdafx.h"
#include "..\Headers\Projectile.h"

USING(MyGame)


CProjectile::CProjectile(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CItem(_pGraphic_Device)
{
}

CProjectile::CProjectile(CProjectile & _rhs)
	: CItem(_rhs)
{
}

HRESULT CProjectile::Initialize_Prototype(_tchar * _pFilePath)
{
	return S_OK;
}

HRESULT CProjectile::Initialize(void * _param)
{
	//할 수 있는 행동을 정한다.
	CItem::Initialize();

	if (nullptr != _param)
		memcpy(&m_tDesc, _param, sizeof(BASEDESC));

	Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform);
	Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer);

	m_pTransform->Set_Position(m_tDesc.vPos);
	m_pTransform->Set_Size(m_tDesc.vSize);

	return S_OK;
}

_int CProjectile::Update(_double _timeDelta)
{
	return 0;
}

_int CProjectile::LateUpate(_double _timeDelta)
{
	return 0;
}

HRESULT CProjectile::Render()
{
	return S_OK;
}

HRESULT CProjectile::Use(CHero * _pHero, const _tchar * _pAction)
{
	return S_OK;
}

void CProjectile::OnCollisionEnter(CGameObject * _pOther)
{
}


void CProjectile::Free()
{
	CItem::Free();
}
