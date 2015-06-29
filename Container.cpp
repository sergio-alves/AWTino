#include "Container.h"

Container::Container() : Component(){
	componentsCounter = 0;
}

Component * Container::getComponent(byte index) {
	if (index < componentsCounter)
		return components[index];
	else
		return NULL;
}

byte Container::append(Component * c)
{
	if (componentsCounter < MAX_COMPONENTS) {
		components[componentsCounter++] = c;
		c->setParent(this);

		if(DEBUG)
			Serial.println(F("Component added"));
	
		return componentsCounter - 1;
	}
		
	if (DEBUG) {
		Serial.print(F("Component not added. counter value : "));
		Serial.println(componentsCounter);
		Serial.flush();
	}

	return -1;
}

void Container::paint(Graphics * g)
{
	
	//draws components
	for (byte i = 0; i < componentsCounter; i++)
	{
		components[i]->paint(g);
	}
}

byte Container::getComponentsCount() {
	return componentsCounter;
}

void Container::calcBounds(void) {
	//nothing to do for a container
};
