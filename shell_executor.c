/* File Name: shell_executor.c */

/**
 * shell_loop - Main shell loop that reads and executes user commands.
 * @info: The parameter & return info struct.
 * @av: The argument vector from main().
 *
 * Return: 0 on success, 1 on error, or an error code.
 */
int shell_loop(info_t *info, char **av)
{
    ssize_t read_ret = 0;
    int builtin_ret = 0;

    while (read_ret != -1 && builtin_ret != -2)
    {
        clear_info(info);
        if (is_interactive(info))
            print_prompt("$ ");
        flush_output_buffer();
        read_ret = read_input(info);
        if (read_ret != -1)
        {
            set_info(info, av);
            builtin_ret = find_builtin(info);
            if (builtin_ret == -1)
                find_command(info);
        }
        else if (is_interactive(info))
            print_newline();
        free_info(info, 0);
    }
    write_history(info);
    free_info(info, 1);
    if (!is_interactive(info) && info->status)
        exit(info->status);
    if (builtin_ret == -2)
    {
        if (info->error_num == -1)
            exit(info->status);
        exit(info->error_num);
    }
    return (builtin_ret);
}

/**
 * find_builtin - Finds a built-in command in the command table.
 * @info: The parameter & return info struct.
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         -2 if builtin signals exit().
 */
int find_builtin(info_t *info)
{
    int i, builtin_ret = -1;
    builtin_table builtintbl[] = {
        {"exit", my_exit},
        {"env", my_env},
        {"help", my_help},
        {"history", my_history},
        {"setenv", my_setenv},
        {"unsetenv", my_unsetenv},
        {"cd", my_cd},
        {"alias", my_alias},
        {NULL, NULL}
    };

    for (i = 0; builtintbl[i].command; i++)
    {
        if (_strcmp(info->argv[0], builtintbl[i].command) == 0)
        {
            info->line_count++;
            builtin_ret = builtintbl[i].func(info);
            break;
        }
    }
    return (builtin_ret);
}

/**
 * find_command - Finds an external command in the PATH directories.
 * @info: The parameter & return info struct.
 *
 * Return: void.
 */
void find_command(info_t *info)
{
    char *path = NULL;
    int i, arg_count;

    info->path = info->argv[0];
    if (info->linecount_flag == 1)
    {
        info->line_count++;
        info->linecount_flag = 0;
    }
    for (i = 0, arg_count = 0; info->arg[i]; i++)
    {
        if (!is_delimiter(info->arg[i], " \t\n"))
            arg_count++;
    }
    if (!arg_count)
        return;

    path = find_command_in_path(info, _getenv(info, "PATH="), info->argv[0]);
    if (path)
    {
        info->path = path;
        execute_command(info);
    }
    else
    {
        if ((is_interactive(info) || _getenv(info, "PATH=")
             || info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
            execute_command(info);
        else if (*(info->arg) != '\n')
        {
            info->status = 127;
            print_error(info, "not found\n");
        }
    }
}

/**
 * execute_command - Forks a child process to execute an external command.
 * @info: The parameter & return info struct.
 *
 * Return: void.
 */
void execute_command(info_t *info)
{
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == -1)
    {
        /* TODO: PUT ERROR FUNCTION */
        perror("Error:");
        return;
    }
    if (child_pid == 0)
    {
        if (execve(info->path, info->argv, get_environ(info)) == -1)
        {
            free_info(info, 1);
            if (errno == EACCES)
                exit(126);
            exit(1);
        }
        /* TODO: PUT ERROR FUNCTION */
    }
    else
    {
        wait(&(info->status));
        if (WIFEXITED(info->status))
        {
            info->status = WEXITSTATUS(info->status);
            if (info->status == 126)
                print_error(info, "Permission denied\n");
        }
    }
}

