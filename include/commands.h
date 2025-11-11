// commands.h tenThousandHoursProject tthp [Created by DBTow]

#ifndef COMMANDS_H
#define COMMANDS_H

typedef enum {
	CMD_NONE, // No command or invalid command
	CMD_LOG, // Command used to log time entries
	CMD_VIEW, // Command used to view time entry details
} Command;

// Parse the user command from agrv[1]
Command parse_command(const char *cmd_str);

// Execute the given user command
int execute_command(Command cmd, int argc, char **argv);


// Command handler function
// The function ran if the program executes the "log" command
int cmd_log(int argc, char **argv);

// The function ran if the program executes the "view" command
int cmd_view(int argc, char ** argv);

#endif
