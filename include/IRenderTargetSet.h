#ifndef __FB_IRENDER_TARGET_SET_H__
#define __FB_IRENDER_TARGET_SET_H__

namespace fb 
{
	interface IRenderTargetSet /*: public dice::IRefCount*/
	{
	public:
		/*dice::IRefCount inheritance */
		virtual int addRef();	//TODO: Pure Function, update params from non-abstract derived class!
		virtual int release();	//TODO: Pure Function, update params from non-abstract derived class!

		virtual char* getName();	//TODO: Pure Function, update params from non-abstract derived class!
		virtual unsigned int getFlags();	//TODO: Pure Function, update params from non-abstract derived class!
		virtual unsigned int getWidth();	//TODO: Pure Function, update params from non-abstract derived class!
		virtual unsigned int getHeight();	//TODO: Pure Function, update params from non-abstract derived class!
		virtual unsigned int getMipmapCount();	//TODO: Pure Function, update params from non-abstract derived class!
		virtual /*dice::ITexture*/void* getColorTexture();	//TODO: Pure Function, update params from non-abstract derived class!
		virtual /*dice::ITexture*/void* getDepthTexture();	//TODO: Pure Function, update params from non-abstract derived class!
		virtual bool isAlphaBlendingSupported();	//TODO: Pure Function, update params from non-abstract derived class!
	};
}
#endif