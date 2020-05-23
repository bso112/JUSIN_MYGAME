#pragma once
#include "Base.h"

BEGIN(MyGame)
class CGameObject;
class CRenderer final :public CBase
{
	DECLARE_SINGLETON(CRenderer)

public:
	enum RENDER_GROUP { RENDER_PRIOR, RENDER_YSORT, RENDER_PARTICLE, RENDER_UI, RENDER_END};
private:
	CRenderer();
	virtual ~CRenderer();

private:
	list<CGameObject*> m_listGO[RENDER_END];

public:
	HRESULT Add_To_RenderGrop(CGameObject* _obj, RENDER_GROUP _eGroup);
	HRESULT Render();

	HRESULT Clear_RenderGroup();

private:
	HRESULT Render_Prior();
	HRESULT Render_YSort();
	HRESULT Render_Effect();
	HRESULT Render_UI();


		
	// CBase을(를) 통해 상속됨
	virtual void Free() override;

};

END
