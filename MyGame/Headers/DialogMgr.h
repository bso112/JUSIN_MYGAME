#pragma once
#include "Base.h"
BEGIN(MyGame)
class CMyDialog;
class CDialogMgr : public CBase
{
	DECLARE_SINGLETON(CDialogMgr)
private:
	explicit CDialogMgr();
	virtual ~CDialogMgr() = default;

public:
	HRESULT	Initialize(PDIRECT3DDEVICE9 _pGraphic_Device);
private:
	CMyDialog* m_pMainDialog = nullptr;

public:
	HRESULT	Log_Main(wstring* _pLog);

	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;

};
END
