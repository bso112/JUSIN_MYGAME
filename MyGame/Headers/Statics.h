#pragma once
#include "Base.h"

BEGIN(MyGame)


class CStatics : public CBase
{
	DECLARE_SINGLETON(CStatics)
private:
	explicit CStatics() {};
	virtual ~CStatics() = default;

public:
	enum SELECTED_HERO { HERO_WARRIOR = 0, HERO_MAGE, HERO_HUNTRESS, HERO_ROUGUE, HERO_END };

public:
	static SELECTED_HERO m_eSelectedHero;

public:
	static HRESULT Set_SelectedHero(SELECTED_HERO _eSelectedHero) 
	{
		if (HERO_END <= _eSelectedHero)
			return E_FAIL;
		m_eSelectedHero = _eSelectedHero;
		return S_OK;
	}
	static SELECTED_HERO Get_SelectedHero() { return m_eSelectedHero; }
	
public:
	virtual void Free() override;
};

END