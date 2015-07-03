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
#include "MousePointer.h"

MousePointer::MousePointer(const Bounds & b) : InputDevice(b) {
}

void MousePointer::doSetup() {
	pinMode(MOUSE_BUTTON_1_IO, INPUT);           // set pin to input
	digitalWrite(MOUSE_BUTTON_1_IO, HIGH);       // turn on pullup resistors

	pinMode(MOUSE_BUTTON_2_IO, INPUT);           // set pin to input
	digitalWrite(MOUSE_BUTTON_2_IO, HIGH);       // turn on pullup resistors
}

boolean MousePointer::doesMousePositionChanged(int xval, int yval) {
	return !(((xval > AN_AXIS_CENTER_LOWER_BOUNDARY) && (xval < AN_AXIS_CENTER_HIGHER_BOUNDARY)) &&
		((yval > AN_AXIS_CENTER_LOWER_BOUNDARY) && (yval < AN_AXIS_CENTER_HIGHER_BOUNDARY)));
}

void MousePointer::updateMouseCoordinates(int xval, int yval) {
	//Only update if joystick is manipulated
	convertAnalogMouseMoveToPixels(xval, yval);

	/*
	ST7735_TFTWIDTH  128
	ST7735_TFTHEIGHT 160
	*/

	ms->x = (ms->x < 0) ? 0 : ms->x;
	ms->y = (ms->y < 0) ? 0 : ms->y;

	if (displayBounds->rotation) // Display horizontal
	{
		//Horizontal
		ms->x = (ms->x > displayBounds->height - 1) ? displayBounds->height - 1 : ms->x;
		ms->y = (ms->y > displayBounds->width - 1) ? displayBounds->width - 1 : ms->y;
	}
	else
	{
		//Vertical
		ms->x = (ms->x > displayBounds->width - 1) ? displayBounds->width - 1 : ms->x;
		ms->y = (ms->y > displayBounds->height - 1) ? displayBounds->height - 1 : ms->y;
	}
}

void MousePointer::convertAnalogMouseMoveToPixels(int xval, int yval) {
	if (xval < AN_AXIS_CENTER_LOWER_BOUNDARY)
		ms->x -= (int)((AN_AXIS_CENTER_LOWER_BOUNDARY - xval) / 100);
	if (xval > AN_AXIS_CENTER_HIGHER_BOUNDARY)
		ms->x += (int)((xval - AN_AXIS_CENTER_HIGHER_BOUNDARY) / 100);

	if (yval < AN_AXIS_CENTER_LOWER_BOUNDARY)
		ms->y -= (int)((AN_AXIS_CENTER_LOWER_BOUNDARY - yval) / 100);
	if (yval > AN_AXIS_CENTER_HIGHER_BOUNDARY)
		ms->y += (int)((yval - AN_AXIS_CENTER_HIGHER_BOUNDARY) / 100);
}


MouseState * MousePointer::updateMouseState() {
	oldms->set(ms);

	/* Get joystick value from hardware */
	tmp = analogRead(A1);
	xval = tmp >= 0 ? tmp : 0;
	tmp = analogRead(A0);
	yval = tmp >= 0 ? tmp : 0;

	/* Read Buttons state from hardware */
	/* If click corresponds to a low value then set invertedLogicForBx to true */
	ms->b1 = MOUSE_BUTTON_1_INPUT_INVERTED ? !digitalRead(MOUSE_BUTTON_1_IO) : digitalRead(MOUSE_BUTTON_1_IO);
	ms->b2 = MOUSE_BUTTON_2_INPUT_INVERTED ? !digitalRead(MOUSE_BUTTON_2_IO) : digitalRead(MOUSE_BUTTON_2_IO);

	/* Only updates mouse coordinates on change */
	if (doesMousePositionChanged(xval, yval)) {
		updateMouseCoordinates(xval, yval);
	}

	return ms;
}


