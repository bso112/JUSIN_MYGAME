#pragma once
#include "Terrain.h"
BEGIN(MyGame)
class Effect;
class CTrap : public CTerrain
{
public:
	enum TYPE{ TYPE_EMPTY, TYPE_FIRE ,TYPE_END};
private:
	explicit CTrap(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CTrap(CTrap& _rhs);
	virtual ~CTrap() = default;

private:
	TYPE		m_eType = TYPE_END;

public:
	virtual	_int	Interact(CGameObject* _pOther);

protected:
	//여기서 함정의 타입을 정한다.
	HRESULT	OnLoadData() override;

public:
	static CTrap * CTrap::Create(PDIRECT3DDEVICE9 _pGraphic_Device, TERRAIN _tData, const _tchar* _pTextureTag, SCENEID _eTextureScene, _tchar* _pFilePath = nullptr)
	{
		CTrap* pInstance = new CTrap(_pGraphic_Device);
		if (FAILED(pInstance->Initialize_Prototype(_tData, _pTextureTag, _eTextureScene, _pTextureTag, _pFilePath)))
		{
			MSG_BOX("Fail to create CDoor");
			Safe_Release(pInstance);

		}
		return pInstance;
	}

	CGameObject * CTrap::Clone(void * _param)
	{
		CTrap* pInstance = new CTrap(*this);
		if (FAILED(pInstance->Initialize()))
		{
			MSG_BOX("Fail to clone CDoor");
			Safe_Release(pInstance);

		}
		return pInstance;
	}

protected:
	virtual void OnCollisionEnterTerrain(CGameObject* _pOther);


};
END
