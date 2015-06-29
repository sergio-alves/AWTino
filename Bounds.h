#ifndef _ALVISOFT_BOUNDS_H
#define _ALVISOFT_BOUNDS_H

class Bounds
{
  public:  
  int x;
  int y;
  int width;
  int height;
  int rotation; // 0 = vertical, 1 = horizontal

  inline Bounds(int _x, int _y, int w, int h, int r) {
    x = _x;
    y = _y;
    width = w;
    height = h;
    rotation = r;
  }

  inline Bounds(const Bounds & b) {
	  x = b.x;
	  y = b.y;
	  width = b.width;
	  height = b.height;
	  rotation = b.rotation;
  }

  inline void set (const Bounds & b) {
	  x = b.x;
	  y = b.y;
	  width = b.width;
	  height = b.height;
	  rotation = b.rotation;
  }


};

#endif
