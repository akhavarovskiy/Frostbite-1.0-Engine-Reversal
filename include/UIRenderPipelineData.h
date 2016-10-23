#ifndef __FB_UI_RENDERPIPELINEDATA_H__
#define __FB_UI_RENDERPIPELINEDATA_H__

#pragma warning ( push )
#pragma warning( disable : 4099 )

namespace fb
{
	enum StencilMaskState
	{
		SmsNone = 0x0,
		SmsWrite = 0x1,
		SmsRead = 0x2
	};
	
	enum UIBlendMode
	{
		UIBlendMode_Alpha = 0x0,
		UIBlendMode_Additive = 0x1,
		UIBlendMode_Count = 0x2
	};
	
	enum UIRenderGroup
	{
		UIRenderGroup_3D = 0x1,
		UIRenderGroup_Movie = 0x2,
		UIRenderGroup_Default = 0x4,
		UIRenderGroup_AlphaMask = 0x8,
		UIRenderGroup_Overlay = 0x10,
		UIRenderGroup_ScreenAdjust = 0x20,
		UIRenderGroup_ExternalAlpha = 0x40,
		UIRenderGroup_CrossHair = 0x80,
		UIRenderGroup_All = 0xFF
	};

	enum UIFontRenderStyle
	{
		UIFontRenderStyle_Undefined = 0x0,
		UIFontRenderStyle_Normal = 0x1,
		UIFontRenderStyle_DropShadow = 0x2,
		UIFontRenderStyle_Outline = 0x4,
		UIFontRenderStyle_Gradient = 0x8,
		UIFontRenderStyle_Pattern = 0x10
	};

	enum UIFontAlignment
	{
		UIFontAlignment_Left = 0x0,
		UIFontAlignment_Center = 0x1,
		UIFontAlignment_Right = 0x2
	};

	enum PrimitiveType
	{
		PtPointList = 0x0,
		PtLineList = 0x1,
		PtLineStrip = 0x2,
		PtTriangleList = 0x3,
		PtTriangleStrip = 0x5,
		PtQuadList = 0x7,
		PtXenonRectList = 0x6
	};
	
	class UIRenderPipelineData
	{
	public:
		enum BlockType	
		{
			BlockType_Undefined = 0x0,
			BlockType_Primitive = 0x1,
			BlockType_Text = 0x2,
			BlockType_Icon = 0x3,
			BlockType_Quad = 0x4,
			BlockType_Bink = 0x5,
			BlockType_TriangleSoup = 0x6
		};

		struct Block
		{
			UIRenderPipelineData::BlockType  m_blockType; // this + 0x0 Length = 0x4
			UIRenderGroup  m_group; 					  // this + 0x4 Length = 0x4
		};

		struct Primitive : public UIRenderPipelineData::Block
		{
			int m_maskOperation; // this + 0x8 
			int m_maskDepth;     // this + 0xC
			unsigned int m_vertexOffset;  // this + 0x10
			unsigned int m_numPrimitives; // this + 0x14
			Mat4  m_transformation; 		 // this + 0x20 Length = 0x40
			Mat4  m_textureTransformation;   // this + 0x60 Length = 0x40
			Vec4  m_color; 				     // this + 0xA0 Length = 0x10
			Vec4  m_colorScale; 			 // this + 0xB0 Length = 0x10
			Vec4  m_colorTranslate; 		 // this + 0xC0 Length = 0x10
			PrimitiveType  m_type; 		     // this + 0xD0 Length = 0x4
			SmartRef< class ITexture const >  m_texture; // this + 0xD4
			bool m_overrideGlobalFade; 					 // this + 0xD8
			float m_brightness;						     // this + 0xDC
			float m_contrast; 							 // this + 0xE0
			float m_externalAlpha;						 // this + 0xE4
			UIBlendMode  m_blendMode; 					 // this + 0xE8 Length = 0x4
		};

		struct Text : public UIRenderPipelineData::Block
		{
			int m_maskOperation; 	// this + 0x8 
			float m_gradientOffset; // this + 0xC 
			float m_gradientHeight; // this + 0x10 
			Mat4  m_transformation; // this + 0x20 
			Vec4  m_color; 		    // this + 0x60 
			Vec4  m_shadowColor;    // this + 0x70
			Vec4  m_gradientStartColor; // this + 0x80
			Vec4  m_gradientEndColor;   // this + 0x90
			Vec4  m_outlineColor;       // this + 0xA0 
			Vec2  m_position;           // this + 0xB0
			Vec2  m_shadowOffset;       // this + 0xB8
			Vec4  m_glowColor;          // this + 0xC0
			SmartRef< class IFont >  m_font;  // this + 0xD0
			UIFontRenderStyle  m_renderStyle; // this + 0xD4 
			UIFontAlignment    m_alignment;     // this + 0xD8
			eastl::list< class UITextRow >  m_text; // this + 0xDC
			float m_right; 							// this + 0xE8
			float m_bottom; 						// this + 0xEC
			float m_tracking; 						// this + 0xF0 
			float m_externalAlpha; 					// this + 0xF4
			StencilMaskState  m_stencilState; 		// this + 0xF8 Length = 0x4
			unsigned char m_stencilMask; 			// this + 0xFC
			bool m_overrideGlobalFade; 				// this + 0xFD Length = 0x1
			bool m_glow; 							// this + 0xFE Length = 0x1
			bool m_fullViewport; 					// this + 0xFF Length = 0x1
		};

		struct Icon : public UIRenderPipelineData::Block
		{
			Mat4  m_transformation; // this + 0x10
			Vec4  m_color; 		    // this + 0x50
			Vec4  m_uvRect; 		// this + 0x60
			SmartRef< class ITexture >  m_texture; // this + 0x70
			StencilMaskState  m_stencilState; 	   // this + 0x74
			unsigned char m_stencilMask; 		   // this + 0x78 Length = 0x1
			bool m_overrideGlobalFade; 			   // this + 0x79 Length = 0x1
			bool m_fullViewport; 				   // this + 0x7A Length = 0x1
		};

		struct Quad : public UIRenderPipelineData::Block
		{

			Mat4  m_transformation; // Offset = this + 0x10 Length = 0x40
			Mat4  m_uvTransform; // Offset = this + 0x50 Length = 0x40
			Vec4  m_color; // Offset = this + 0x90 Length = 0x10
			Vec4  m_uvRect; // Offset = this + 0xA0 Length = 0x10
			SmartRef< class ITexture >  m_texture; // Offset = this + 0xB0 Length = 0x4
			SmartRef< class ITexture >  m_alphaTexture; // Offset = this + 0xB4 Length = 0x4
			SmartRef< class ITexture >  m_detailTexture; // Offset = this + 0xB8 Length = 0x4
			StencilMaskState  m_stencilState; // Offset = this + 0xBC Length = 0x4
			unsigned char m_stencilMask; // Offset = this + 0xC0 Length = 0x1
			bool m_overrideGlobalFade; // Offset = this + 0xC1 Length = 0x1
			unsigned int m_shaderId; // Offset = this + 0xC4 Length = 0x4
		};
		
		struct TriangleSoup : public UIRenderPipelineData::Block
		{

			Mat4  m_worldView; // Offset = this + 0x10 Length = 0x40
			Mat4  m_projection; // Offset = this + 0x50 Length = 0x40
			Vec4  m_color; // Offset = this + 0x90 Length = 0x10
			eastl::vector< class UI3DVertex >  m_vertices; // Offset = this + 0xA0 Length = 0x10
			SmartRef<class ITexture>  m_texture; // Offset = this + 0xB0 Length = 0x4
			StencilMaskState  m_stencilState; // Offset = this + 0xB4 Length = 0x4
			unsigned char m_stencilMask; // Offset = this + 0xB8 Length = 0x1
			bool m_overrideGlobalFade; // Offset = this + 0xB9 Length = 0x1
			unsigned int m_shaderId; // Offset = this + 0xBC Length = 0x4
		};
		
		struct Bink : public UIRenderPipelineData::Block
		{
			SmartRef< class IBinkPlayer>  m_player; // Offset = this + 0x8 Length = 0x4
			SmartRef< class IBinkMemoryPlayer>  m_memoryPlayer; // Offset = this + 0xC Length = 0x4
		};

		SmartRef< class IUIRenderCacheManager>  m_cacheManager; 	// this + 0x0 Length = 0x4
		eastl::list<UIRenderPipelineData::Primitive>  m_primitives; // this + 0x4 Length = 0xC
		eastl::list<UIRenderPipelineData::Text>  m_texts;  			 // this + 0x10 Length = 0xC
		eastl::list<UIRenderPipelineData::Quad>  m_quads;   		 // this + 0x1C Length = 0xC
		eastl::list<UIRenderPipelineData::Icon>  m_icons;   		 // this + 0x28 Length = 0xC
		eastl::list<UIRenderPipelineData::Bink>  m_binks;   		 // this + 0x34 Length = 0xC
		eastl::list<UIRenderPipelineData::TriangleSoup>  m_triangleSoups; // this + 0x40 Length = 0xC
		eastl::vector<UIRenderPipelineData::Block *> m_block[2]; 		  // this + 0x4C Length = 0x20
		unsigned char __pad[0x4];
		Mat4  m_primitiveProjection; 							          // this + 0x70 Length = 0x40
	};
}
#pragma warning ( pop )

#endif