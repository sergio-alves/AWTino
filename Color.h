// Color.h

#ifndef _ALVISOFT_COLOR_H
#define _ALVISOFT_COLOR_H

#include "Arduino.h"

class Color
{
  public:
    byte r;
    byte g;
    byte b;
    
    static Color Black;
    static Color White;
    static Color LightGrey;
    static Color Grey;    
    static Color DarkGrey;
	static Color Red;
	static Color Green;
	static Color Blue;

    inline Color(const Color& c)
    {
      r = c.r;
      g = c.g;
      b = c.b;
    }
        
    inline Color(byte _r, byte _g, byte _b) {
      r=_r;
      g=_g; 
      b=_b;
     }    

    inline uint16_t toAdafruitColor() {
      return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
    }   

	inline void set(const Color& c)
	{
		r = c.r;
		g = c.g;
		b = c.b;
	}
};
#endif
