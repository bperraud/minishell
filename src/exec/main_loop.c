
#include "minishell.h"

static int	command(t_cmd *cmd, t_cmd *prev_cmd, char **envp)
{
	if ((prev_cmd->mode == AND && !prev_cmd->exit_value)
		|| (prev_cmd->mode == OR && prev_cmd->exit_value))
		return (launch_cmd(cmd, envp));
	return (-1);
}

void	print_cmd(t_list_cmd *list_cmd)
{
	int	i;

	if (!list_cmd)
	{
		printf("list is empty.\n");
		return ;
	}
	i = 0;
	while (list_cmd)
	{
		printf("list command : %s\n", list_cmd->command->cmd[0]);
		list_cmd = list_cmd->next;
	}
}

t_list_cmd	*lst_last(t_list_cmd *list_cmd)
{
	if (!list_cmd)
		return (NULL);
	while (list_cmd->next)
		(list_cmd = list_cmd->next);
	return (list_cmd);
}

void	add_back(t_list_cmd **list_cmd, t_cmd *new)
{
	t_list_cmd	*t;
	t_list_cmd	*last;

	if (!*list_cmd)
		;
	else
	{
		t = malloc(sizeof(t_list_cmd));
		t->command = new;
		t->next = NULL;
		last = lst_last(*list_cmd);
		last->next = t;
	}
}

void	sh(char *str, char **envp)
{
	t_cmd	*cmd;
	t_cmd	*prev_cmd;

	prev_cmd = malloc(sizeof(t_cmd));
	prev_cmd->exit_value = 0;
	prev_cmd->mode = AND;
	prev_cmd->cmd = NULL;

	t_list_cmd	*list_cmd;

	while (*str)
	{
		printf("ici");

		cmd = sh_split(&str);
		if (cmd->mode == PIPE)
		{
			list_cmd = malloc(sizeof(t_list_cmd));
			list_cmd->next = NULL;
			list_cmd->command = cmd;
			// cmd = premiere commande avt le premier pipe
			cmd = sh_split(&str);
			// au moins une commande apres
			while (cmd->mode == PIPE)
			{
				// créer une liste des commandes jusqu'à la dernière qui n'est pas un PIPE;
				// sh_split jusqu'à last + éxecuter
				// cmd doit contenir la prochaine commande.
				add_back(&list_cmd, cmd);
				cmd = sh_split(&str);
			}
			add_back(&list_cmd, cmd);
			print_cmd(list_cmd);
			multiple_cmd(list_cmd, envp);
		}
		else
		{
			cmd->exit_value = command(cmd, prev_cmd, envp);
			printf("exit status = %i\n", cmd->exit_value);
			print_list(cmd->cmd);
			print_cmd_args(cmd);
			free_t_cmd(prev_cmd);
			prev_cmd = cmd;
		}
	}
	free_t_cmd(prev_cmd);
}

void	start_shell(char **envp)
{
	char	*str;

	while (1)
	{
		printf("               __\n              /o_)\n");
		printf("      _/\\/\\/\\_/ /\n   _|minishell/\n _|  (  | (  |\n");
		str = readline("/__.-'|_|--|_| ~ ");
		if (!str || !ft_strncmp(str, "exit", 5))
		{
			free(str);
			break ;
		}
		sh(str, envp);
		free(str);
	}
}
