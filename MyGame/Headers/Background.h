#pragma once

#include "GameObject.h"

BEGIN(MyGame)
class CBackground final: public CGameObject
{
private:
	explicit CBackground(PDIRECT3DDEVICE9 _pGraphic_Device) : CGameObject(_pGraphic_Device) {}
	explicit CBackground(CBackground& _rhs);
	virtual ~CBackground() = default;

public:
	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Initialize_Prototype(_tchar* _pFilePath = nullptr) override;
	virtual HRESULT Initalize(void * _param = nullptr) override;
	virtual _int Update(_double _timeDelta) override;
	virtual _int LateUpate(_double _timeDelta) override;
	virtual HRESULT Render() override;


public:
	static CBackground* Create(PDIRECT3DDEVICE9 _pGraphic_Device, _tchar* _pFilePath = nullptr);
	virtual	CGameObject* Clone(void* _param = nullptr)override;
	virtual void Free() override;

};
END
