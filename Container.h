#ifndef _ALVISOFT_CONTAINER_H
#define _ALVISOFT_CONTAINER_H
#include "Graphics.h"
#include "Component.h"
#include "Commons.h"

class Container : public Component {
public:
	Container();
	byte append(Component *);
	Component * getComponent(byte);
	byte getComponentsCount();

	//enherited from Component
	void paint(Graphics *);
	
protected:
	void calcBounds(void);
	
private:
	byte componentsCounter;
	Component * components[MAX_COMPONENTS];
};

#endif
