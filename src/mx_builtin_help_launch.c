#include "ush.h"

bool mx_help_launch_builtin(t_shell *shell, char **job_path, char ***argv) {
    char **arr = mx_strsplit(getenv("PATH"), ':');
    char **words = mx_strsplit(shell->command_now, ' ');
    *argv = malloc(sizeof(char**));
    int words_count = 1;
    (*argv)[0] = strdup(words[0]);

    int backslash = 0;
    int quote = 0;
    char p[2];
    char *result = NULL;
    for (int i = 1; words[i]; i++) {
        for (int j = 0; words[i][j]; j++) {
            if (words[i][j] == '\\') {
                if (backslash < 2)
                    backslash++;
                if (backslash == 2 && (!words[i][j + 1])) {
                    backslash = 0;
                    result = mx_strrejoin(result, "\\");
                }
                continue;
            }
            if (words[i][j] == '"' || words[i][j] == '\'') {
                if (backslash == 1) {
                    MX_C_TO_P(words[i][j], p);
                    result = mx_strrejoin(result, p);
                    backslash = 0;
                    continue;
                }
                else {
                    quote++;
                    continue;
                }
            }
            MX_C_TO_P(words[i][j], p);
            result = mx_strrejoin(result, p);
        }
        if (backslash == 1 || quote % 2 == 1) {
            result = mx_strrejoin(result, " ");
            backslash = 0;
        }
        else {
            char **temp = malloc(sizeof(char**) * words_count + 1);
            for (int k = 0; k < words_count; k++) {
                temp[k] = strdup((*argv)[k]);
                free((*argv)[k]);
            }
            free(*argv);
            *argv = malloc(sizeof(char**) * words_count + 1);
            for (int k = 0; k < words_count; k++) {
                (*argv)[k] = strdup(temp[k]);
                free(temp[k]);
            }
            free(temp);
            (*argv)[words_count] = strdup(result);
            mx_strdel(&result);
            words_count++;
        }
    }
    char **temp = malloc(sizeof(char**) * words_count + 1);
    for (int k = 0; k < words_count; k++) {
        temp[k] = strdup((*argv)[k]);
        free((*argv)[k]);
    }
    free(*argv);
    *argv = malloc(sizeof(char**) * words_count + 1);
    for (int k = 0; k < words_count; k++) {
        (*argv)[k] = strdup(temp[k]);
        free(temp[k]);
    }
    free(temp);
    (*argv)[words_count] = NULL;
    mx_free_words(words);
    if (quote % 2 != 0) {
        printf("quote doesn't close\n\r");
        mx_strdel(&result);
        mx_free_words(*argv);
        exit(EXIT_FAILURE);
        return false;
    }
    bool bin_exist = check_path(arr, (*argv)[0], job_path);
    mx_del_strarr(&arr);
    return bin_exist;
}
