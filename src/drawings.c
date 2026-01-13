#include "include/drawings.h"
#include "include/raylib.h"

void draw_centered_text(Font font, const char *text, float font_size,
                        float spacing, Color tint) {
	Vector2 text_measure = MeasureTextEx(font, text, font_size, spacing);

	Vector2 start_position = {GetScreenWidth() / 2 - text_measure.x / 2, GetScreenHeight() / 2 - text_measure.y / 2};

	DrawTextEx(font, text, start_position, font_size, spacing, tint);
}

void draw_button(Button button, Font font, float font_size, float spacing, Color tint) {
	DrawRectangleRec(button.rect, button.color);
	if (button.text) {
		Vector2 text_measure = MeasureTextEx(font, button.text, font_size, spacing);
		Vector2 start_position = {button.rect.width / 2 - text_measure.x / 2 + button.rect.x, button.rect.height / 2 - text_measure.y / 2 + button.rect.y};
		DrawTextEx(font, button.text, start_position, font_size, spacing, tint);
	}
}

void draw_timer_screen(Button settings, Button control, Time time, Pomodoro pomodoro, char* percentage) {
	draw_button(settings, GetFontDefault(), 30, 4, BLACK);
	draw_button(control, GetFontDefault(), 30, 4, BLACK);

	DrawTextEx(GetFontDefault(), percentage, (Vector2){8, 8}, 30, 4, BLACK);

	char label_text[20];
	switch(pomodoro.step) {
	case 0: {
		strcpy(label_text, "Pomodoro Timer");
	} break;
		
	case 1:
	case 3:
	case 5:
	case 7: {
		strcpy(label_text, "Work Time");
	} break;
		
	case 2:
	case 4:
	case 6: {
		strcpy(label_text, "Short Break Time");
	} break;
		
	case 8: {
		strcpy(label_text, "Long Break Time");
	} break;
	}
	Vector2 text_measure = MeasureTextEx(GetFontDefault(), label_text, 30, 4);
	Vector2 start_position = {GetScreenWidth() / 2 - text_measure.x / 2, GetScreenHeight() / 2 - text_measure.y / 2 - 50};
	
	DrawTextEx(GetFontDefault(), label_text, start_position, 30, 4, BLACK);
	draw_centered_text(GetFontDefault(), time.text, 40, 4, BLACK);
}

void draw_settings_screen(Button settings, Button increment, Button decrement, Button up, Button down, Button save, Pomodoro* pomodoro) {
	char current_text[16];
	char label_text[20];
	int minutes, seconds;
	switch(pomodoro->step) {
	case 0: {
		minutes = pomodoro->work_time / 60;
		seconds = pomodoro->work_time % 60;
		strcpy(label_text, "Work Time");
	} break;
	case 1: {
		minutes = pomodoro->short_break_time / 60;
		seconds = pomodoro->short_break_time % 60;
		strcpy(label_text, "Short Break Time");
	} break;
	case 2: {
		minutes = pomodoro->long_break_time / 60;
		seconds = pomodoro->long_break_time % 60;
		strcpy(label_text, "Long Break Time");
	} break;
	}

	sprintf(current_text, "%02d:%02d", minutes, seconds);
	Vector2 text_measure = MeasureTextEx(GetFontDefault(), label_text, 30, 4);
	Vector2 start_position = {GetScreenWidth() / 2 - text_measure.x / 2, GetScreenHeight() / 2 - text_measure.y / 2 - 50};
	DrawTextEx(GetFontDefault(), label_text, start_position, 30, 4, BLACK);
	
	draw_centered_text(GetFontDefault(), current_text, 40, 4, BLACK);

	draw_button(settings, GetFontDefault(), 30, 4, BLACK);
	draw_button(increment, GetFontDefault(), 30, 4, BLACK);
	draw_button(decrement, GetFontDefault(), 30, 4, BLACK);
	draw_button(up, GetFontDefault(), 30, 4, BLACK);
	draw_button(down, GetFontDefault(), 30, 4, BLACK);
	draw_button(save, GetFontDefault(), 30, 4, BLACK);

	
}
