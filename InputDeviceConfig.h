/*****************************************************************************
Written by Sergio Alves. Copyright (c) 2015, all rights reserved.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

#ifndef _INPUTDEVICE_CONFIG_h
#define _INPUTDEVICE_CONFIG_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

/* mask ids */
#define MOUSE_BUTTON_1                  1
#define MOUSE_BUTTON_2                  2

/* Physical pin */
#define MOUSE_BUTTON_1_IO               12
#define MOUSE_BUTTON_2_IO               11

#define MOUSE_BUTTON_1_INPUT_INVERTED	true
#define MOUSE_BUTTON_2_INPUT_INVERTED	true

/* delays to trigger a valid click / dbl click */
#define MOUSE_CLICK_INTERVAL            200
#define MOUSE_DCLICK_INTERVAL           500

/* The analog axis center boundary is the zone where joystick is considered centered. (analog read is a 10 bits value) */
#define AN_AXIS_CENTER_LOWER_BOUNDARY   492  
#define AN_AXIS_CENTER_HIGHER_BOUNDARY  532

#endif