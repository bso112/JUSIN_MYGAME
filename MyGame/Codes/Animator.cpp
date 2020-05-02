#include "stdafx.h"
#include "..\Headers\Animator.h"

USING(MyGame)


CAnimator::CAnimator(CAnimator & _rhs)
	:CModule(_rhs)
{

}

HRESULT CAnimator::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CAnimator::Initialize(void * _pArg)
{
	return S_OK;
}

HRESULT CAnimator::Add_Animation(const _tchar* _pTag, CAnimation * _pAnimation)
{
	if (nullptr == _pAnimation)
		return E_FAIL;

	m_mapAnim.emplace(_pTag, _pAnimation);

	return S_OK;
}

HRESULT CAnimator::Play(const _tchar* _pTag)
{
	auto& iter = find_if(m_mapAnim.begin(), m_mapAnim.end(), CFinder_Tag(_pTag));
	if (iter == m_mapAnim.end())
		return E_FAIL;

	iter->second->Play();

	return S_OK;
}

CAnimator * CAnimator::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CAnimator* pInstance = new CAnimator(_pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Fail to create CAnimator");
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

CModule * CAnimator::Clone(void * _pArg)
{
	CAnimator* pInstance = new CAnimator(*this);

	if (FAILED(pInstance->Initialize(_pArg)))
	{
		MSG_BOX("Fail to clone CAnimator");
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}



void CAnimator::Free()
{
	for (auto& pAnim : m_mapAnim)
	{
		Safe_Release(pAnim.second);
	}

	CModule::Free();
}
