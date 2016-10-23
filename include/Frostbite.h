/*
------------------------------------------------
|   Frostbite v1 - MOH Reversal by AlexAk92	   |
------------------------------------------------
    -Reversal is largly based on BC2 Server pdb files. 
*/

#ifndef __FB_MOH_H__
#define __FB_MOH_H__

#include <Windows.h>
#include <string>

#pragma warning( push )
#pragma warning ( disable : 4005 )
#include <d3d9.h>
#include <d3d11.h>
#pragma warning( pop )

#define FB_GAME "Medal of Honor 2010"  

/* Virtual Address offcets */
#define VA_DXRENDERER9         0x0165FC50
#define VA_DXRENDERER11        0x0165FC64

#define VA_UI_BASE			   0x01C0E0F8
#define VA_GAME_RENDERER       0x01634FCC
#define VA_CLIENT_GAME_CONTEXT 0x00585B50 


/* fb_common.h
	-----------------------------------------
	Your basic geometrical vectors & matricis.
*/
#include "Common.h"

/* 
	DxRenderer.h
	-----------------------------------------
*/
#include "Dx9Renderer.h"
#include "Dx11Renderer.h"
/* 
	GameRenderer.h
	-----------------------------------------
*/
#include "GameRenderer.h"
/*
	UIBase.h
	-----------------------------------------
*/
#include"UIBase.h"

/* 
	clientgamecontext.h
	-----------------------------------------
*/
#include "ClientGameContext.h"

#endif	/* _FB_MOH_H_ */
