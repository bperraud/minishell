
#include "minishell.h"

static char **command(t_cmd *cmd, t_cmd *prev_cmd, char **envp)
{
	if ((prev_cmd->mode == AND && !prev_cmd->exit_value)
		|| (prev_cmd->mode == OR && prev_cmd->exit_value))
		return (launch_cmd(cmd, envp));
	else if (cmd->mode == NONE)	// last cmd
		return (envp);
	return (envp);
}

char	**sh(char *str, char **envp)
{
	t_cmd	*cmd;
	t_cmd	*prev_cmd;

	prev_cmd = init_cmd();
	prev_cmd->exit_value = 0;
	prev_cmd->mode = AND;
	while (*str)
	{
		cmd = init_cmd();
		str = get_next_cmd(str, envp, cmd);
		if (!str || !cmd->cmd)
		{
			free_t_cmd(prev_cmd);
			free_t_cmd(cmd);
			return(envp);
		}
		envp = command(cmd, prev_cmd, envp);
		//print_list(cmd->cmd);
		//print_cmd_args(cmd);
		free_t_cmd(prev_cmd);
		prev_cmd = cmd;
	}
	free_t_cmd(prev_cmd);
	free(str);
	return (envp);
}

void	start_shell(char **envp, char *str_c)
{
	char	*str;

	sig_handler();
	term_config();
	while (1)
	{
		if (!str_c)
		{
			printf("exit status = %i\n", g_error);
			str = readline(print_prompt(error_to_color()));
			if (!str)
				break ;
		}
		else
			str = ft_strndup(str_c, ft_strlen(str_c));
		if (!ft_strncmp(str, "exit", 5))
		{
			free(str);
			break ;
		}
		add_history(str);
		if (!check_syntax(str))
			envp = sh(str, envp);
		if (str_c)
			exit (g_error);
	}
}
