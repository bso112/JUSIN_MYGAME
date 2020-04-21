#pragma once
#include "Scene.h"

BEGIN(MyGame)

#define ARC1X 5
#define ARC1Y 3
#define ARC1CX 200
#define ARC1CY 200
#define ARC2X 5
#define ARC2Y 5
#define ARC2CX 100
#define ARC2CY 100

class CMyButton;
class CImage;
class CGameObject;
class CMenu final : public CScene
{
private:
	explicit CMenu(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CMenu() = default;
	
private:
	//ĵ���� ������ ��. ���� �߰��Ѱ� ���� ������
	vector<CGameObject*>	m_vecCanvas[2];
	_int					m_iCurrCanvas = 0;

	//���
	CImage*					m_pImgArc1[ARC1X][ARC1Y];
	CImage*					m_pImgArc2[ARC2X][ARC2Y];

	//�����׷�1
	CImage*					m_pImgLogo = nullptr;
	vector<CMyButton*>		m_vecMenuBtn;
	
	//�����׷�2
	CImage*					m_pImgCharSelectBanner = nullptr;
	vector<CMyButton*>		m_vecCharSelectBtn;

	
public:
	virtual HRESULT Initialize() override;
	virtual _int Update(_double _timeDelta) override;
	virtual HRESULT Render() override;

private:
	HRESULT	Load_Textures();

public:
	static CMenu* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	// CScene��(��) ���� ��ӵ�
	virtual void Free() override;

};

END