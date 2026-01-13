#include "include/config.h"

int import_config(Config* config) {

	FILE* fp = fopen("config/config.pom", "r");
	if (!fp) {
		return 0;
	}

	int work, sb, lb;

	fscanf(fp, "%d %d %d", &work, &sb, &lb);
	fclose(fp);

	config->pomodoro.work_time = work;
	config->pomodoro.short_break_time = sb;
	config->pomodoro.long_break_time = lb;



	return 1;
}

void export_config(Config config) {
	FILE* fp = fopen("config/config.pom", "w");

	char output_string[30];
	sprintf(output_string, "%d %d %d", config.pomodoro.work_time, config.pomodoro.short_break_time, config.pomodoro.long_break_time);
	printf("SAVING: %s\n", output_string);

	fputs(output_string, fp);

	fclose(fp);
	
}
