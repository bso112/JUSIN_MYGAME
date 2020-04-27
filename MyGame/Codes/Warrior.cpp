#include "stdafx.h"
#include "..\Headers\Warrior.h"
#include "Renderer.h"

USING(MyGame)


CWarrior * CWarrior::Create(PDIRECT3DDEVICE9 _pGraphic_Device, _tchar * _pFilePath)
{
	CWarrior* pInstance = new CWarrior(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype(_pFilePath)))
	{
		MSG_BOX("Fail to create CWarrior");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CGameObject * CWarrior::Clone(void * _param)
{
	CWarrior* pInstance = new CWarrior(*this);
	if (FAILED(pInstance->Initialize(_param)))
	{
		MSG_BOX("Fail to create CWarrior");
		Safe_Release(pInstance);

	}
	return pInstance;
}


HRESULT CWarrior::Initialize_Prototype(_tchar * _pFilePath)
{
	return S_OK;
}

HRESULT CWarrior::Initialize(void * _param)
{
	return S_OK;
}

HRESULT CWarrior::KeyCheck()
{
	CHero::KeyCheck();

	return S_OK;
}

_int CWarrior::Update(_double _timeDelta)
{
	//목적지가 있을 경우 목적지로 이동
	MoveToDst(m_vDst, _timeDelta);

	return 0;
}

_int CWarrior::LateUpate(_double _timeDelta)
{
	if (nullptr == m_pRenderer)
		return -1;

	if (FAILED(m_pRenderer->Add_To_RenderGrop(this, CRenderer::RENDER_YSORT)))
		return -1;

	return 0;
}

HRESULT CWarrior::Render()
{
	return S_OK;
}


void CWarrior::Scene_Change()
{
}

void CWarrior::Process()
{
}

void CWarrior::Update_State()
{
}

void CWarrior::OnDead()
{
}

void CWarrior::OnTakeDamage()
{
}

void CWarrior::Free()
{
	CGameObject::Free();
}

