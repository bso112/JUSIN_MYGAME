#pragma once
#include "afxwin.h"
#include "Base.h"
// CControlView 폼 뷰입니다.
BEGIN(MyGame)
class CGameObject;
class CTransform;
class CVIBuffer;
class CGraphic_Device;
class CTexture;
END


class CControlView : public CFormView
{
	DECLARE_DYNCREATE(CControlView)

protected:
	CControlView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CControlView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONTROLVIEW1 };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
private:
	int m_iTileNumX = 0;
	int m_iTileNumY = 0;
	MyGame::CGameObject* m_pSelected = nullptr;

private:
	MyGame::CTransform*			m_pTransform = nullptr;
	MyGame::CVIBuffer*			m_pVIBuffer = nullptr;
	MyGame::CTexture*			m_pTexture = nullptr;
	MyGame::CGraphic_Device*	m_pGraphic_DeviceMgr = nullptr;

public:
	int		Get_TileNumX() { UpdateData(TRUE); return m_iTileNumX; }
	int	Get_SelectedTextureIndex() { return m_Combo.GetCurSel(); }
	void	Set_Selected(MyGame::CGameObject* pSelected) { m_pSelected = pSelected; }
public:
	afx_msg	void CreateTile();
private:
	HRESULT Initialize_Tile();
	CComboBox m_Combo;
	CStatic m_Picture;

public:
	virtual void OnInitialUpdate();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnDestroy();
	virtual void OnDraw(CDC* /*pDC*/);
};


