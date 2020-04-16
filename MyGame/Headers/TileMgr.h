#pragma once
#include "Base.h"

BEGIN(MyGame)

class CTile;
class CTileMgr final : public CBase
{
	DECLARE_SINGLETON(CTileMgr)
private:
	explicit CTileMgr();
	virtual ~CTileMgr() = default;

private:
	vector<CTile*> m_vecTile;

public:
	HRESULT	Initialize() ;
	_int	Update();
	HRESULT Render(HDC _DC);

	


	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;

};
END
