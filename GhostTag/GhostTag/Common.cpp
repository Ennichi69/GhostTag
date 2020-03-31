#include "Common.hpp"

int Player0_ButtonDown() {
	return KeySpace.down();
}
int Player0_JoyStick_Direction() {
	if (KeyA.pressed())return 1;
	if (KeyW.pressed())return 2;
	if (KeyD.pressed())return 3;
	if (KeyS.pressed())return 4;
	return 0;
}
int Player1_ButtonDown() {
	return KeyEnter.down();
}
int Player1_JoyStick_Direction() {
	if (KeyLeft.pressed())return 1;
	if (KeyUp.pressed())return 2;
	if (KeyRight.pressed())return 3;
	if (KeyDown.pressed())return 4;
	return 0;
}