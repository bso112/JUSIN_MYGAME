#pragma once

#define BEGIN(NAMESPACE) namespace NAMESPACE {
#define END }

#define USING(NAMESPACE) using namespace NAMESPACE;


#define MSG_BOX(MESSAGE) MessageBox(0, TEXT(MESSAGE), TEXT("System Error"), MB_OK)



#define DECLARE_SINGLETON(CLASSNAME)										\
	public: static CLASSNAME* Get_Instance();								\
	public: static unsigned long Destroy_Instance();						\
	private:	static CLASSNAME* m_pInstance;

#define IMPLEMENT_SINGLETON(CLASSNAME)										\
	CLASSNAME* CLASSNAME::m_pInstance = nullptr;							\
	CLASSNAME* CLASSNAME::Get_Instance() {												\
	if(nullptr == m_pInstance) {											\
	m_pInstance = new CLASSNAME; }											\
	return m_pInstance;														\
	}																		\
	unsigned long CLASSNAME::Destroy_Instance() {										\
	unsigned long dwRefCnt = 0;												\
	if(nullptr != m_pInstance) {											\
	dwRefCnt = m_pInstance->Release();										\
	if(0 == dwRefCnt) m_pInstance = nullptr;								\
	}																		\
	return dwRefCnt;														\
	}					





#define ALPHATEST															\
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			\
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHAREF, 0);					\
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


#define ALPHABLEND															\
	m_pGraphic_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);		\
	m_pGraphic_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	\
	m_pGraphic_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
