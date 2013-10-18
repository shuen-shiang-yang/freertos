#include "fio.h"
#include "shell.h"
#include "strfun.h"
#include "FreeRTOS.h"
#include "task.h"



enum {
	CMD_ECHO, 
	CMD_HELP,
	CMD_HELLO,
	CMD_COUNT,
	CMD_PS
} CMD_TYPE;


typedef struct {
	char cmd[MAX_CMDNAME + 1];
	void (*func)();
	char description[MAX_CMDHELP + 1];
} hcmd_entry;

const hcmd_entry cmd_data[CMD_COUNT] = {
	[CMD_HELP] = {.cmd = "help", .func = help, .description = "List all commands you can use."},
	[CMD_HELLO] = {.cmd = "hello", .func = hello, .description = "print 'Hello World'."},
	
};

void help();
void hello();
void ps();



void shell_printf(char *buf, int count){
	char msg[] = "\n\r";

	fio_write(1, msg, sizeof(msg) );
	fio_write(1, buf, count);
}

void check_keyword(char *msg, char *msg_size)
{
	int i;
	for (i = 0; i < CMD_COUNT; i++) {
		if (!strcmp(msg, cmd_data[i].cmd)) {
			cmd_data[i].func();
			break;
		}
	}
	if (i == CMD_COUNT) {
		fio_write(1, "\n\r: command not found\n\r", 23);
	}
}

void help(){
	const char help_desp[] = "\n\rOffer these funcs : ";
	int i;

	fio_write(1, &help_desp, sizeof(help_desp));
	for (i = 1; i < CMD_COUNT; i++) {
		fio_write(1, "\n\r", 2);
		fio_write(1, cmd_data[i].cmd, strlen(cmd_data[i].cmd) + 1);
		fio_write(1, ": ", 3);
		fio_write(1, cmd_data[i].description, strlen(cmd_data[i].description) + 1);
	}
}

void hello(){
fio_write(1, "\n\r: 'Hello World'\n\r", 19) ;
}


/*void ps(){
        signed char buf[1024];
        vTaskList(buf);
        fio_write(1, buf, strlen((char*)buf));       
}*/

