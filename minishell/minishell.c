#include "minishell.h"

int		g_exit_code = 0;

void	print_data_cmd(t_data *data)
{
	t_cmd_node	*cur;
	t_redi		*redi;
	int			idx = 1;
	int			i;
	cur = data->cmd_node_head;
	while (cur != NULL)
	{
		redi = cur->redi;
		printf("node %d:\n", idx++);
		while (redi != NULL)
		{
			printf("file_name:%s\tredi->flag : %d\n", redi->file_name, redi->flag);
			redi = redi->next;
		}
		if (cur->args != NULL)
		{
			i = 0;
			while (cur->args[i])
			{
				printf("args[%d]:%s \n", i, cur->args[i]);
				i++;
			}
		}
		printf("\n");
		cur = cur->next;
	}
}

void a()
{
    system("leaks minishell");
}

int main(int arc, char **arv, char **envp)
{
	t_info	info;
	t_data	data;
    char    *line;

	if (arv[1] != NULL)
		exit_error("Too Many Argument", arv[1], 127);
	init_envl(&data, envp, arv[0]);
    while(1)
    {
		set_signal(PARENT);
        line = readline("minishell$ ");
		if (line == NULL)
			break ;
	    add_history(line);
		every_init(&info, &data);
		parsing(&info, line, data.envp);
		if (info.parsing_failed == SUCCESS)//syntax 에러 처리 잘 안되네 ..
		{
			remake_arvl(&info, &data);
			exe_data(&data, arv[0]);
		}
		free_every(&data, &info, &line);
    }
	free_double(&data.envp);
	clear_t_envl_node(&data.envl);
	// atexit(a);
}
