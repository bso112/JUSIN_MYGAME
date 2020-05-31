#pragma once
#include "GameObject.h"
BEGIN(MyGame)
class CTransform;
class CVIBuffer;
class CTexture;
class CHero;
class CShader;
//안개가 렌더하지 않는 공간에 대한 정보를 가지고 있음.
class CFog : public CGameObject
{
protected:
	explicit CFog(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CFog(CFog& _rhs);
	virtual ~CFog() = default;

private:
	CTransform*	m_pTransform = nullptr;
	CVIBuffer*	m_pVIBuffer = nullptr;
	CTexture*	m_pTexture = nullptr;
	CShader*	m_pShader = nullptr;
private:
	CTransform*	m_pHeroTransform = nullptr;
public:
	virtual HRESULT	Initialize_Prototype(_tchar* _pFilePath = nullptr);
	virtual HRESULT Initialize(void * _pArg = nullptr);
	virtual _int	Update(_double _timeDelta);
	virtual _int	LateUpate(_double _timeDelta);
	virtual HRESULT	Render();

public:
	static	CFog* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual CGameObject * Clone(void * _pArg = nullptr) override;
	void	Free();
};
END
