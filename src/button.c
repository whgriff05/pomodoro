#include "include/button.h"

void check_button(Button *button) {
  Vector2 mouse_pos = GetMousePosition();
  
  if (CheckCollisionPointRec(mouse_pos, button->rect)) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) button->state = 2;
    else button->state = 1;

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) button->action = 1;
  } else {
	  button->state = 0;
  }

  if (button->state == 0) {
	  button->color = button->unselect;
  } else if (button->state == 1) {
	  button->color = button->hover;
  } else {
	  button->color = button->click;
  }
}

