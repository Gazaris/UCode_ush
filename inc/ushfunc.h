#pragma once

#include "ushtd.h"

void mx_alias(t_shell*);
// void mx_bg(t_shell*);
void mx_cd(t_shell*);
void mx_chdir(t_shell*);
void mx_echo(t_shell*);
void mx_env(t_shell*);
void mx_exit(t_shell*);
void mx_export(t_shell*);
void mx_false(t_shell*);
void mx_fg(t_shell*);
// void mx_jobs(t_shell*);
void mx_kill(t_shell*);
void mx_pwd(t_shell*);
void mx_true(t_shell*);
void mx_unset(t_shell*);
void mx_which(t_shell*);

t_shell *mx_shell_init();
void     mx_loop(t_shell*);

void mx_command_handler(t_shell*);
void mx_free_words(char**);
void mx_free_shell(t_shell*);

char *mx_get_job_args(t_shell*);
int   mx_get_job_id(t_shell*);
pid_t mx_get_pid_by_job_id(t_shell *shell, int job_id);
char *mx_find_destination(char *path, char *p);
void  mx_launch_other_builtin(t_shell *shell);
void  mx_print_error(char *command, char *error);
char  mx_get_type(struct stat file_stat);
void  mx_builtin_child(char **job_path, char ***argv);
bool mx_help_launch_builtin(t_shell *shell, char **job_path, char ***argv);
char *get_error(char **name, char *command);
bool read_dir(char *dir, char *command, char **name);
bool check_path(char **arr, char *command, char **name);
