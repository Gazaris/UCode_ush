#include "ush.h"

void mx_launch_other_builtin(t_shell *shell) {
    char *job_path = NULL;
    char **argv = NULL;
    char *error = NULL;

    printf("\033[1A\r\n");
    if(mx_help_launch_builtin(shell, &job_path, &argv)) {
        pid_t child_pid;
        int shell_is_interactive = isatty(STDIN_FILENO);
        struct termios tty_backup;
        tcgetattr(STDIN_FILENO, &tty_backup);  
        tcsetattr (STDIN_FILENO, TCSANOW, &shell->backup);

        child_pid = fork();
        if (child_pid < 0) {
            perror("error fork");
            exit(1);
        }
        else if (child_pid == 0){
            mx_builtin_child(&job_path, &argv);
        }
        else {
            if (shell_is_interactive) {
                // setpgid (pid, m_s->jobs[job_id]->pgid);
                waitpid(child_pid, NULL, 0);
                tcsetattr(STDIN_FILENO, TCSANOW, &tty_backup);
            }
        }
    }
    else {
        error = get_error(&job_path, argv[0]);
        mx_print_error(error, argv[0]);
        free(error);
        error = NULL;
        shell->exit_code = EXIT_FAILURE;
    }
}
