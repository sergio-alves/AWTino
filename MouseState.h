#ifndef _ALVISOFT_MOUSESTATE_H
#define _ALVISOFT_MOUSESTATE_H

class MouseState
{
  public:
    boolean b1;
    boolean b2;
    int x;
    int y;
	MouseState() {
		b1 = false;
		b2 = false;
		x = 0;
		y = 0;
	}

	MouseState(const MouseState & ms) {
		x = ms.x;
		y = ms.y;
		b1 = ms.b1;
		b2 = ms.b2;
	}
	
    MouseState(int _x, int _y, boolean _b1, boolean _b2) 
    {
      x = _x;
      y = _y;
      b1 = _b1;
      b2 = _b2;
    }  
    
    void set(MouseState * ms)
    {
      x = ms->x;
      y = ms->y;
      b1 = ms->b1;
      b2 = ms->b2;
    }

	void set(const MouseState & ms)
	{
		x = ms.x;
		y = ms.y;
		b1 = ms.b1;
		b2 = ms.b2;
	}

};

#endif
