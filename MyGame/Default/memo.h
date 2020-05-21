//#pragma once
//#include "GameObject.h"
//BEGIN(MyGame)
//class CTransform;
//class CVIBuffer;
//class CTexture;
//class CShader;
//class CProjectile abstract : public CGameObject
//{
//private:
//	explicit CProjectile(PDIRECT3DDEVICE9 _pGraphic_Device);
//	explicit CProjectile(CProjectile& _rhs);
//	virtual ~CProjectile() = default;
//
//protected:
//	CTransform* m_pTransform = nullptr;
//	CVIBuffer*	m_pVIBuffer = nullptr;
//	CTexture*	m_pTexture = nullptr;
//	CShader*	m_pShader = nullptr;
//public:
//	virtual HRESULT	Initialize_Prototype(_tchar* _pFilePath = nullptr);
//	virtual HRESULT Initialize(void * _pArg = nullptr);
//	virtual _int	Update(_double _timeDelta);
//	virtual _int	LateUpate(_double _timeDelta);
//	virtual HRESULT	Render();
//
//protected:
//	virtual	HRESULT	OnRender();
//public:
//	virtual	void Free() override;
//
//
//};
//END
//
//
//
//#include "stdafx.h"
//#include "..\Headers\Projectile.h"
//#include "VIBuffer.h"
//#include "Transform.h"
//#include "Shader.h"
//#include "Texture.h"
//
//USING(MyGame)
//
//
//CProjectile::CProjectile(PDIRECT3DDEVICE9 _pGraphic_Device)
//	:CGameObject(_pGraphic_Device)
//{
//}
//
//CProjectile::CProjectile(CProjectile & _rhs)
//	: CGameObject(_rhs)
//{
//}
//
//HRESULT CProjectile::Initialize_Prototype(_tchar * _pFilePath)
//{
//	return S_OK;
//}
//
//HRESULT CProjectile::Initialize(void * _pArg)
//{
//	return S_OK;
//}
//
//_int CProjectile::Update(_double _timeDelta)
//{
//	return _int();
//}
//
//_int CProjectile::LateUpate(_double _timeDelta)
//{
//	return _int();
//}
//
//HRESULT CProjectile::Render()
//{
//	if (!m_bActive)
//		return 0;
//
//	if (nullptr == m_pVIBuffer ||
//		nullptr == m_pTexture ||
//		nullptr == m_pTransform)
//		return E_FAIL;
//
//
//	ALPHABLEND;
//
//	if (FAILED(m_pVIBuffer->Set_Transform(m_pTransform->Get_Matrix() * m_pPipline->Get_ViewMatrix())))
//		return E_FAIL;
//
//	if (FAILED(m_pTexture->Set_TextureOnShader(m_pShader, "g_BaseTexture", m_tDesc.m_iTextureID - 1)))
//		return E_FAIL;
//	if (FAILED(m_pShader->Begin()))
//		return E_FAIL;
//	if (FAILED(m_pShader->Begin_Pass(0)))
//		return E_FAIL;
//
//	if (FAILED(m_pVIBuffer->Render()))
//		return E_FAIL;
//
//	//하위클래스의 렌더
//	OnRender();
//
//	if (FAILED(m_pShader->End_Pass()))
//		return E_FAIL;
//	if (FAILED(m_pShader->End()))
//		return E_FAIL;
//
//	ALPHABLEND_END;
//
//
//
//}
//
//
//HRESULT CProjectile::OnRender()
//{
//	return S_OK;
//}
//
//void CProjectile::Free()
//{
//	CGameObject::Free();
//}
//
