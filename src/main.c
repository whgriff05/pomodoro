#include "include/pomodoro.h"

int main(void) {
	WindowDimensions window_dimensions= {640, 480, 150, 150, 900, 600};

	int window_width = window_dimensions.current_width;
    int window_height = window_dimensions.current_height;
	
	Color bkg_color = RED;

	Button settings_button = {{0, window_height - 50, 50, 50}, 0, 0, WHITE, WHITE, GRAY, BLACK, strdup("#")};
	Button control_button = {{window_width / 3, window_height - 200, window_width / 3, 50}, 0, 0, WHITE, WHITE, GRAY, BLACK, strdup("START")};
	
	Button increment_button = {{window_width / 2 - 75, window_height - 50, 50, 50}, 0, 0, WHITE, WHITE, GRAY, BLACK, strdup("+")};
	Button decrement_button = {{window_width / 2 - 150, window_height - 50, 50, 50}, 0, 0, WHITE, WHITE, GRAY, BLACK, strdup("-")};
	Button up_button = {{window_width / 2 + 25, window_height - 50, 50, 50}, 0, 0, WHITE, WHITE, GRAY, BLACK, strdup("<")};
	Button down_button = {{window_width / 2 + 100, window_height - 50, 50, 50}, 0, 0, WHITE, WHITE, GRAY, BLACK, strdup(">")};
	Button save_button = {{window_width - 50, window_height - 50, 50, 50}, 0, 0, WHITE, WHITE, GRAY, BLACK, strdup("S")};

	Config config = {{0, 0, 0, 0}};
	Pomodoro current = {500, 500, 500, 0};
	if (!import_config(&config)) {
		printf("Config file not found. Error has occurred.\n");
		return 1;
	}
	current = config.pomodoro;
	
	Time timer = {3600, 0, strdup("00:00")};

	initialize_timer(&timer, current);

	int current_screen = 0; // 0 = timer screen, 1 = settings screen
	
	float delta = 0;
	int second_flag = 0;

	float total_possible_time = 0;
	float total_completed_time = 0;
	char completion_percentage[16];
	int pcg;

	// Calculate Total Possible Time
	total_possible_time = current.work_time * 4 + current.short_break_time * 3 + current.long_break_time;
	
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(window_width, window_height, "Pomodoro");
	SetTargetFPS(60);
	SetWindowMinSize(window_dimensions.min_width, window_dimensions.min_height);
	SetWindowMaxSize(window_dimensions.max_width, window_dimensions.max_height);

	while (!WindowShouldClose()) {
		/* Incrementing seconds */
		if (second_flag == 1) {
			second_flag = 0;
			timer.current_time += 1;
			total_completed_time += 1;
		}
		if (!strcmp(control_button.text, "PAUSE")) delta += GetFrameTime();
		if (delta >= 1) {
			delta = 0;
			second_flag = 1;
		}

		/* Pomodoro Step Functionality */
		// Timer Reset and Step Movement
		if (timer.current_time >= timer.initial_time) {
			// Increment Pomodoro step
			current.step += 1;
			if (current.step > 8) {
				current.step = 0;
				total_completed_time = 0;
			}
			
			// Change button text and stop countdown
			free(control_button.text);
			control_button.text = strdup("START");
			delta = 0;

			// Reset timer with new time
			initialize_timer(&timer, current);
			printf("Step: %d\n", current.step);
		}

		// Background for steps
		if (current_screen == 0) {
			switch(current.step) {
			case 0: {
				bkg_color = (Color){234, 221, 237, 255};
			} break;

			
			case 1:
			case 3:
			case 5:
			case 7: {
				bkg_color = (Color){86, 156, 154, 255};
			} break;

			case 2:
			case 4:
			case 6: {
				bkg_color = RED;
			} break;

			case 8: {
				bkg_color = (Color){178, 73, 201, 255};
			} break;
			}
		} else {
			switch(current.step) {
			case 0: {
				bkg_color = (Color){86, 156, 154, 255};
			} break;
				
			case 1: {
				bkg_color = RED;
			} break;
				
			case 2: {
				bkg_color = (Color){178, 73, 201, 255};
			} break;
			}
		}
		
		/* Button Functionality */
		check_button(&settings_button);
		check_button(&control_button);
		check_button(&increment_button);
		check_button(&decrement_button);
		check_button(&up_button);
		check_button(&down_button);
		check_button(&save_button);

		calculate_time(&timer);

		if (settings_button.action) {
			current_screen = current_screen ? 0 : 1;
			current.step = 0;
			initialize_timer(&timer, current);
			total_completed_time = 0;
			settings_button.action = 0;
		}

		if (current_screen == 0 && control_button.action) {
			if (!strcmp(control_button.text, "START")) {
				free(control_button.text);
				control_button.text = strdup("PAUSE");
			} else {
				free(control_button.text);
				control_button.text = strdup("START");
			}

			if (current.step == 0) current.step = 1;
			control_button.action = 0;
		}

		if (current_screen == 1) {
			// Down Button
			if (down_button.action) {
				current.step += 1;
				if (current.step > 2) current.step = 0;
				down_button.action = 0;
			}
			// Up Button
			if (up_button.action) {
				current.step -= 1;
				if (current.step < 0) current.step = 2;
				up_button.action = 0;
			}
			// Increment Button
			if (increment_button.action) {
				switch(current.step) {
				case 0: {current.work_time += current.work_time + 60 > 5940 ? 0 : 60;} break;
				case 1: {current.short_break_time += current.short_break_time + 60 > 5940 ? 0 : 60;} break;
				case 2: {current.long_break_time += current.long_break_time + 60 > 5940 ? 0 : 60;} break;
				}
				increment_button.action = 0;
			}
			// Decrement Button
			if (decrement_button.action) {
				switch(current.step) {
				case 0: {current.work_time -= current.work_time - 60 < 60 ? 0 : 60;} break;
				case 1: {current.short_break_time -= current.short_break_time - 60 < 60 ? 0 : 60;} break;
				case 2: {current.long_break_time -= current.long_break_time - 60 < 60 ? 0 : 60;} break;
				}
				decrement_button.action = 0;
			}
			// Save Button
			if (save_button.action) {
				config.pomodoro = current;
				export_config(config);
				save_button.action = 0;
			}
		}

		// Calculate Completion Percentage
		pcg = total_completed_time / total_possible_time * 100;
		sprintf(completion_percentage, "%d%% | %d mins", pcg, (int)(total_completed_time / 60.0));
        
		/* Drawing */
		{
			BeginDrawing();
			ClearBackground(bkg_color);
			if (current_screen == 0) {
				draw_timer_screen(settings_button, control_button, timer, current, completion_percentage);
			} else if (current_screen == 1) {
				draw_settings_screen(settings_button, increment_button, decrement_button, up_button, down_button, save_button, &current);
			}
      
			EndDrawing();
		}

    
	}

	CloseWindow();

    return 0;
}
