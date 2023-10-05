#include "../minishell.h"

void    save_history(t_vars *vars, char *line)
{
	t_hisl	*new;
	t_hisl	*last;

    add_history(line);
    //구조체안에 저장하는 로직
	new = malloc(sizeof(t_hisl));
	new->line = ft_strdup(line);
	new->next = NULL;
	last = find_last_his_node(vars);
	if (last == NULL)
	{
		new->index = 1;
		vars->hisl = new;
	}
	else
	{
		new->index = last->index + 1;
		last->next = new;
	}
}

void	print_history(t_vars *vars, char **arvs)
{
	t_hisl	*cur;

	if (arvs[1] != NULL)
	{
		parent_error("too many arguments", "history");
		return ;
	}
	cur = vars->hisl;
	while (cur != NULL)
	{
		printf("%5d  %2s\n", cur->index, cur->line);
		cur = cur->next;
	}
}