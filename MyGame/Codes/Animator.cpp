#include "stdafx.h"
#include "..\Headers\Animator.h"
#include "Shader.h"

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

_int CAnimator::Render(CShader* _pShader)
{
	if (nullptr == m_pCurrAnim)
		return -1;

	//현재 애니메이션이 끝나면 다음에 설정된 애니메이션으로 넘어간다.
	CAnimation* next = m_pCurrAnim->Render(_pShader);
	if (nullptr != next)
	{
		next->Play();
		m_pCurrAnim = next;
	}
	return 0;
}

HRESULT CAnimator::Play(const _tchar* _pTag)
{
	auto& iter = find_if(m_mapAnim.begin(), m_mapAnim.end(), CFinder_Tag(_pTag));
	if (iter == m_mapAnim.end())
		return E_FAIL;

	m_pCurrAnim = iter->second;

	m_pCurrAnim->Play();

	return S_OK;
}

_bool CAnimator::IsEndAnim(const _tchar * _pAnimTag)
{
	auto& iter = find_if(m_mapAnim.begin(), m_mapAnim.end(), CFinder_Tag(_pAnimTag));
	if (iter == m_mapAnim.end())
		return false;
	return (*iter).second != m_pCurrAnim;
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
