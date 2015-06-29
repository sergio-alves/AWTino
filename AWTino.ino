#include "Image.h"
#include "ProgressBar.h"
#include "QuadValue.h"
#include "Button.h"
#include "Label.h"
#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <SD.h>
#include "Bounds.h"
#include "Button.h"
#include "Color.h"
#include "Commons.h"
#include "Component.h"
#include "Container.h"
#include "GfxApplication.h"
#include "Graphics.h"
#include "Label.h"
#include "MouseEvents.h"
#include "MouseState.h"
#include "Point.h"
#include "QuadValue.h"
#include "TestApp.h"

GfxApplication * app = new TestApp();

void setup() {
  app->doSetup();
}

void loop() {
  app->doLoop();
}
