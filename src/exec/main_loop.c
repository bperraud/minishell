
#include "minishell.h"

static int	command(t_cmd *cmd, t_cmd *prev_cmd, char **envp)
{
	if ((prev_cmd->mode == AND && !prev_cmd->exit_value)
		|| (prev_cmd->mode == OR && prev_cmd->exit_value))
		return (launch_cmd(cmd, envp));
	else if (cmd->mode == NONE)	// last cmd
		return (-1);
	return (-1);
}

void	sh(char *str, char **envp)
{
	t_cmd	*cmd;
	t_cmd	*prev_cmd;

	prev_cmd = smalloc(sizeof(t_cmd));
	prev_cmd->exit_value = 0;
	prev_cmd->mode = AND;
	prev_cmd->cmd = NULL;
	while (*str)
	{
		cmd = init_cmd();
		cmd = get_next_cmd(&str, envp, cmd);
		if (!cmd->cmd)
		{
			free_t_cmd(cmd);
			exit(EXIT_SUCCESS);
		}
		cmd->exit_value = command(cmd, prev_cmd, envp);
		//print_list(cmd->cmd);
		//print_cmd_args(cmd);
		free_t_cmd(prev_cmd);
		prev_cmd = cmd;
	}
	free_t_cmd(prev_cmd);
}

void	start_shell(char **envp, char *str_c)
{
	char	*str;
	pid_t	pid;
	int		status;

	while (1)
	{
		if (!str_c)
		{
			printf("exit status = %i\n", g_error);
			str = readline(print_prompt(error_to_color()));
		}
		else
			str = ft_strdup(str_c);
		if (!str)
			exit(ENOMEM);
		if (!ft_strncmp(str, "exit", 5))
		{
			free(str);
			break ;
		}
		add_history(str);
		pid = fork();
		if (!pid)
		{
			check_syntax(str);
			sh(str, envp);
			exit(EXIT_SUCCESS);
		}
		else
			waitpid(pid, &status, 0);
		g_error = exit_to_bash_code(WEXITSTATUS(status));
		free(str);
		if (str_c)
			exit (g_error);
	}
}
