#ifndef __DX9_SHADERSYSTEM_H__
#define __DX9_SHADERSYSTEM_H__

namespace fb
{
#ifndef VA_D9XSHADERSYSTEM
#define VA_D9XSHADERSYSTEM 0x16601CC

#endif
	class Dx9ShaderSystem
	{
		typedef Dx9ShaderSystem this_type;
	public:
		static this_type * Singleton( void ){
			return *(this_type**)( VA_D9XSHADERSYSTEM );
		}
	}
}
#endif