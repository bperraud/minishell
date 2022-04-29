

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
		cmd->exit_value = command(cmd, prev_cmd, envp);
		printf("exit status = %i\n", cmd->exit_value);
		print_list(cmd->cmd);
		print_cmd_args(cmd);
		free_t_cmd(prev_cmd);
		prev_cmd = cmd;
	}
	free_t_cmd(prev_cmd);
}

void	start_shell(char **envp)
{
	char	*str;
	t_cmd	*cmd;

	while (1)
	{
		str = readline("\033[33m               __\n              /o_)\n     \
_/\\/\\/\\_/ /\n   _|minishell/\n _|  (  | (  |\n/__.-'|_|--|_| ~ \033[0m");
		if (!str || !ft_strncmp(str, "exit", 5))
		{
			free(str);
			break ;
		}
		sh(str, envp);
		free(str);
	}
}