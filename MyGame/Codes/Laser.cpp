#include "stdafx.h"
#include "Laser.h"
#include "VIBuffer.h"
#include "Transform.h"
#include "Clock.h"
#include "Texture.h"
#include "Shader.h"
#include "ObjMgr.h"
#include "Camera.h"

USING(MyGame)


CLaser::CLaser(CLaser & _rhs)
	:CGameObject(_rhs)
{
	m_bActive = true;
	ZeroMemory(&m_tDesc, sizeof(STATEDESC));

}



HRESULT CLaser::Initialize(void * _pArg)
{
	if (nullptr != _pArg)
		memcpy(&m_tDesc, _pArg, sizeof(STATEDESC));

	if (FAILED(Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer)))
		return E_FAIL;

	if (FAILED(Set_Module(m_tDesc.m_pTextureTag, m_tDesc.m_eTextureSceneID, (CModule**)&m_pTexture)))
		return E_FAIL;

	if (FAILED(Set_Module(L"Shader", SCENE_STATIC, (CModule**)&m_pShader)))
		return E_FAIL;

	m_pDeadClock = CClock_Delay::Create();

	CTransform::STATEDESC transformDesc;
	transformDesc.speedPerSec = m_tDesc.m_fSpeed;
	transformDesc.radianPerSec = m_tDesc.m_dRadianPerSec;

	if (FAILED(Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform, L"Transform", &transformDesc)))
		return E_FAIL;

	m_pTransform->Set_Position(m_tDesc.m_tBaseDesc.vPos);
	m_pTransform->Set_Size(m_tDesc.m_tBaseDesc.vSize);





	return S_OK;
}

_int CLaser::Update(_double _timeDelta)
{
	if (nullptr == m_pDeadClock)
		return -1;

	if (m_bDead)
		return -1;

	if (!m_bActive)
		return 0;

	//라이프타임이 지나면 죽기
	if (m_pDeadClock->isThreashHoldReached(m_tDesc.m_dLifeTime))
		m_bDead = true;


	if (m_bFadeOut)
	{
		//알파값 점점 줄이기
		m_fAlpha -= (1 / m_tDesc.m_dLifeTime) * _timeDelta;
		if (m_fAlpha <= 0)
			m_fAlpha = 0;
	}



	return 0;
}

_int CLaser::LateUpate(_double _timeDelta)
{
	if (m_bDead)
		return -1;

	if (!m_bActive)
		return 0;

	m_pRenderer->Add_To_RenderGrop(this, CRenderer::RENDER_UI);
	return 0;
}

HRESULT CLaser::Render()
{
	if (!m_bActive)
		return 0;

	if (nullptr == m_pVIBuffer ||
		nullptr == m_pTransform	||
		nullptr == m_pPipline)
		return E_FAIL;


	if (FAILED(m_pVIBuffer->Set_Transform(m_pTransform->Get_Matrix() * m_pPipline->Get_ViewMatrix())))
		return E_FAIL;

	ALPHABLEND;

	_int textureID = m_tDesc.m_iTextureID - 1 < 0 ? 0 : m_tDesc.m_iTextureID - 1;
	if (FAILED(m_pTexture->Set_TextureOnShader(m_pShader, "g_BaseTexture", textureID)))
		return E_FAIL;

	if (FAILED(m_pShader->Begin()))
		return E_FAIL;

	if (FAILED(m_pShader->Begin_Pass(m_tDesc.m_iShaderPass)))
		return E_FAIL;

	if (FAILED(m_pVIBuffer->Render()))
		return E_FAIL;


	if (FAILED(m_pShader->End_Pass()))
		return E_FAIL;

	if (FAILED(m_pShader->End()))
		return E_FAIL;


	ALPHABLEND_END;


	return S_OK;
}

HRESULT CLaser::Beam(Vector2 _vOrigin, POINT _pt)
{
	if (nullptr == m_pTransform)
		return E_FAIL;

	//마우스 좌표 변환
	Vector4 vDst = Vector4(_pt.x, _pt.y, 0.f, 1.f);
	D3DXVec4Transform(&vDst, &vDst, &m_pPipline->Get_CameraMatrix_inverse());

	Vector4 vDir = vDst - _vOrigin;
	vDir.z = 0;
	vDir.w = 1;
	//레이저의 X사이즈는 vOrigin에서 _vDst로 향하는 벡터의 길이다.
	float vSizeX = vDir.magnitude();

	//Vector4(1.f, 0.f, 0.f, 1.f) 는 Dir과 내적할 벡터 즉, 사이각을 구할 벡터다.
	//이미지가 오른쪽을 바라보고 있으므로 Vector4(1.f, 0.f, 0.f, 1.f)를 기준으로 했다.
	//회전각 구하기
	float fCosTheta = D3DXVec4Dot(&vDir.Nomalize(), &Vector4(1.f, 0.f, 0.f));
	float fRadian = 0.f;

	if (vDst.y >= _vOrigin.y)
		fRadian = acosf(fCosTheta);
	else
		fRadian = D3DXToRadian(360.0f) - acosf(fCosTheta);

	//쏘는 원점을 피봇으로 한다.
	m_pTransform->Set_Pivot(Vector2(vSizeX * 0.5f, 0.f));
	m_pTransform->Set_Position(Vector2(_vOrigin.x, _vOrigin.y));
	m_pTransform->Set_Size(Vector2(vSizeX, LASER_SIZEY, 1.f));
	m_pTransform->Set_Rotation(Vector3(0.f, 0.f, fRadian));

	//카메라 흔들기
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	RETURN_FAIL_IF_NULL(pObjMgr);
	CCamera* pMainCam = dynamic_cast<CCamera*>(pObjMgr->Get_ObjectOnFront(L"Camera", SCENE_STAGE));
	RETURN_FAIL_IF_NULL(pMainCam);
	pMainCam->Shake_Camera(0.2f);

	return S_OK;
}

HRESULT CLaser::Beam(Vector2 _vOrigin, Vector2 _vDst)
{
	if (nullptr == m_pTransform)
		return E_FAIL;

	Vector2 vDir = _vDst - _vOrigin;
	float vSizeX = vDir.magnitude();

	//회전각 구하기
	float fCosTheta = D3DXVec4Dot(&vDir.Nomalize(), &Vector4(1.f, 0.f, 0.f, 0.f));
	float fRadian = 0.f;

	if (_vDst.y >= _vOrigin.y)
		fRadian = acosf(fCosTheta);
	else
		fRadian = D3DXToRadian(360.0f) - acosf(fCosTheta);


	m_pTransform->Set_Pivot(Vector2(vSizeX * 0.5f, 0.f));
	m_pTransform->Set_Position(Vector2(_vOrigin.x + vSizeX, _vOrigin.y));
	m_pTransform->Set_Size(Vector2(vSizeX, m_tDesc.m_tBaseDesc.vSize.y));
	m_pTransform->Set_Rotation(Vector3(0.f, 0.f, fRadian));
	
	return S_OK;
}


CLaser * CLaser::Create(PDIRECT3DDEVICE9 _pGraphic_Device, STATEDESC& _tDesc)
{
	CLaser* pInstance = new CLaser(_pGraphic_Device);
	if (FAILED(pInstance->Initialize(&_tDesc)))
	{
		MSG_BOX("Fail to create CParicle");
		Safe_Release(pInstance);

	}
	return pInstance;
}



void CLaser::Free()
{
	Safe_Release(m_pDeadClock);
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pTransform);
	Safe_Release(m_pShader);
	Safe_Release(m_pTexture);

	CGameObject::Free();
}

CGameObject * CLaser::Clone(void * _pArg)
{
	return nullptr;
}

