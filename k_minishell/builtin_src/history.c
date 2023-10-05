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

	//exit ㅎㅏㅁ수에도 쓰쓰일  check_arv_number() 함수 만들어서 쓰자
	//check_arv_number() 는 숫자인지 체크하고 long long 범위 안넘는지 체크
	if (arvs[1] != NULL)
		parent_error("too many arguments", "history");
	cur = vars->hisl;
	while (cur != NULL)
	{
		printf("%d %s\n", cur->index, cur->line);<- 형식 지정자 잘 쓰거나 write로 잘 때려박거나₩
		cur = cur->next;
	}
}