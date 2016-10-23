#ifndef __DX9_RENDER_TARGET_SET_H__
#define __DX9_RENDER_TARGET_SET_H__

#include "RefCountImpl.h"
#include "IRenderTargetSet.h"

#include "EASTL\string.h"

namespace fb 
{
	enum TextureFormat
	{
		TfDXT1 = 0x0,
		TfDXT3 = 0x1,
		TfDXT5 = 0x2,
		TfDXT5A = 0x3,
		TfDXN = 0x4,
		TfRGB565 = 0x5,
		TfRGB888 = 0x6,
		TfARGB1555 = 0x7,
		TfARGB4444 = 0x8,
		TfARGB8888 = 0x9,
		TfL8 = 0xA,
		TfL16 = 0xB,
		TfABGR16 = 0xC,
		TfABGR16F = 0xD,
		TfABGR32F = 0xE,
		TfR16F = 0xF,
		TfR32F = 0x10,
		TfNormalDXN = 0x11,
		TfNormalDXT1 = 0x12,
		TfNormalDXT5 = 0x13,
		TfNormalDXT5RGA = 0x14,
		TfRGBE_8888 = 0x15,
		TfRGBE_DXT5 = 0x16,
		TfGR16 = 0x17,
		TfGR16F = 0x18,
		TfD16F = 0x19,
		TfD24F = 0x1A,
		TfDRAWZ = 0x1B,
		TfDINTZ = 0x1C,
		TfNull = 0x1D,
		TfD16 = 0x1E,
		TfD24S8 = 0x1F,
		TfD24FS8 = 0x20,
		TfD24X8 = 0x21
	};

	struct RenderTargetSetCreateDesc
	{
		eastl::basic_string<char, eastl::allocator>  name; // Offset = this + 0x0 Length = 0xC
		eastl::basic_string<char, eastl::allocator>  groupName; // Offset = this + 0xC Length = 0xC
		unsigned int width; // Offset = this + 0x18 Length = 0x4
		unsigned int height; // Offset = this + 0x1C Length = 0x4
		unsigned int depth; // Offset = this + 0x20 Length = 0x4
		unsigned int mipmapCount; // Offset = this + 0x24 Length = 0x4
		TextureFormat  colorFormat; // Offset = this + 0x28 Length = 0x4
		TextureFormat  depthFormat; // Offset = this + 0x2C Length = 0x4
		unsigned int flags; // Offset = this + 0x30 Length = 0x4
		unsigned int memoryFlags; // Offset = this + 0x34 Length = 0x4
		bool m_unk1; // Offset = this + 0x38 Length = 0x4
	};

	class Dx9RenderTargetSetCreateDesc : public RenderTargetSetCreateDesc
	{
	public:

		_D3DMULTISAMPLE_TYPE  multiSampleType; // Offset = this + 0x3C Length = 0x4
		unsigned long multiSampleQuality; // Offset = this + 0x40 Length = 0x4
		bool renderToVertexBuffer; // Offset = this + 0x44 Length = 0x1
	};

	class Dx9RenderTargetSet : public fb::RefCountImpl<fb::IRenderTargetSet>
	{
	public:
		virtual unsigned int getDepth();

		fb::RenderTargetSetCreateDesc   m_desc; // Offset = this + 0x8 Length = 0x3C
		class Dx9Texture*				m_texture[4]; // Offset = this + 0x44 Length = 0x10
		interface IDirect3DSurface9*    m_surface[4]; // Offset = this + 0x54 Length = 0x10
		class Dx9Texture*               m_depthTexture; // Offset = this + 0x64 Length = 0x4
		interface IDirect3DSurface9*    m_dx9DepthSurface; // Offset = this + 0x68 Length = 0x4
	};
}

#endif