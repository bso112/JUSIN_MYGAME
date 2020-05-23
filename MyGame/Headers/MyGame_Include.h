#pragma once

#include <d3d9.h>
#include <d3dx9.h>

//#pragma comment (lib, "d3d9.lib")

#include <vector>
#include <list>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <functional>
#include <ctime>

using namespace std;


#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif
#endif

#include "MyGame_Mecro.h"
#include "MyGame_Constant.h"
#include "MyGame_Function.h"
#include "MyGame_Typedef.h"
#include "MyGame_Struct.h"


extern HWND g_hWnd;
extern ID3DXFont* g_pFont;
extern ID3DXFont* g_pFontX2;

//전역함수
extern RECT Make_Rect(D3DXVECTOR4 _vPos, D3DXVECTOR4 _vSize);