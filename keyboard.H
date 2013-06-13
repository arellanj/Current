#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__
#include <string>
class Keyboard
{
	public:
	bool keys[400];
	Keyboard()
	{
		for( int i = 0 ; i < 400 ; i++ )
		{
			keys[i] = false;
		}
	}
	void setKey(int key, bool val)
	{
		if( key < 0 || key >= 400)
		{
			return;
		}
		keys[key] = val;
	}
	bool isKeyDown(int key) const
	{
		if( key < 0 || key >= 400)
		{
			return false;
		}
		return keys[key];
	}

};

#endif //__KEYBOARD_H__
