#ifndef _ALVISOFT_COMMONS_H
#define _ALVISOFT_COMMONS_H

#define MOUSE_BUTTON_1                  1
#define MOUSE_BUTTON_2                  2

#define MOUSE_BUTTON_1_IO               12
#define MOUSE_BUTTON_2_IO               11

#define MOUSE_CLICK_INTERVAL            200
#define MOUSE_DCLICK_INTERVAL           500
#define MOUSE_REFRESH_RATE_MILLIS       25

//The analog axis center boundary is the zone where joystick is considered centered.
 
#define AN_AXIS_CENTER_LOWER_BOUNDARY   492  
#define AN_AXIS_CENTER_HIGHER_BOUNDARY  532
#define MAX_COMPONENTS                  32

#define DEBUG                           false

// Display Hardware constants
#define TFT_DISP_CS                     10
#define TFT_DISP_DC                     9
#define TFT_DISP_RST                    8
#define SCREEN_REFRESH_RATE_MILLIS      50


#endif
