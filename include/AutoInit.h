#ifndef __FB_AUTO_INIT_H__
#define __FB_AUTO_INIT_H__

namespace fb
{
	template < typename T , int val > class AutoInit 
	{
	public:
		AutoInit( void ) 
		{
		   this->m_value = val;
		}
		~AutoInit(void) {}
	private:
		int m_value; // Offset = this + 0x0 Length = 0x4
	};
}
#endif