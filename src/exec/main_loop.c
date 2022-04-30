
#include "minishell.h"

static int	command(t_cmd *cmd, t_cmd *prev_cmd, char **envp)
{
	if ((prev_cmd->mode == AND && !prev_cmd->exit_value)
		|| (prev_cmd->mode == OR && prev_cmd->exit_value))
		return (single_cmd(cmd, envp));
	else if (cmd->mode == NONE)	// last cmd
		return (-1);
	return (-1);
}

void	sh(char *str, char **envp)
{
	t_cmd	*cmd;
	t_cmd	*prev_cmd;

	prev_cmd = malloc(sizeof(t_cmd));
	prev_cmd->exit_value = 0;
	prev_cmd->mode = AND;
	while (*str)
	{
		cmd = sh_split(&str);
		//printf("exit status = %i\n", cmd->exit_value);
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
			str = readline(print_prompt());
		else
			str = str_c;
		if (!str || !ft_strncmp(str, "exit", 5))
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
		//printf("error errno code is \033[32m%d\033[0m\n", g_error);
		if (str_c)
			return ;
		free(str);
	}
}
