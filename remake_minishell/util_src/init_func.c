#include "../minishell.h"

void	init_envl(t_data *data, char **envp, char *rootfile)
{
	data->envl = NULL;
	data->envp = NULL;
	envp_to_envl(data, envp, rootfile);
	update_envp(data, data->envl);
}

void    envp_to_envl(t_data *data, char **envp, char *rootfile)
{
    int     i;
    char    *key;
    char    *value;
	t_envl	*new;

    i = 0;
    while (envp[i])
    {
        key = ft_strndup(envp[i], ft_strchr(envp[i], '=') - envp[i]);
		if (ft_strcmp(key, "SHELL") == 0)
			value = ft_strdup(rootfile);
		else
    	    value = ft_strdup(ft_strchr(envp[i], '=') + 1);
		add_env(data, key, value);
        i++;
    }
	add_env(data, "OLDPWD", NULL);
}

void	update_envp(t_data *data, t_envl *cur)
{
	int		i;
	char	*temp;
	printf("update_envp func\n");
	i = 0;
	data->envp = malloc(sizeof(char *) * (get_lstsize(cur) + 1));
	while (cur != NULL)
	{
		if (cur->value == NULL)
			data->envp[i] = ft_strdup(cur->key);
		else if (cur->value[0] == '\0')
			data->envp[i] = ft_strjoin(cur->key, "=");
		else
		{
			temp = ft_strjoin(cur->key, "=");
			data->envp[i] = ft_strjoin(temp, cur->value);
			free(temp);
		}
		cur = cur->next;
		i++;
	}
	data->envp[i] = NULL;
}

void	every_init(t_info *info, t_data *data)
{
	info->buff = NULL;
	info->head = NULL;
	info->content = NULL;
	data->pre_flag = 0;
	data->cmd_node_head = NULL; 
	data->cmd_node_last = NULL;
	data->args_i = 0;
	data->node_open_flag = 0;
}

void	init_pipe(t_data *data, t_pipe *pipe_data)
{
	data->last_exit_code = 0;
	pipe_data->cmd_idx = -1;
	pipe_data->pipe_cnt = cnt_pipe(data->cmd_node_head);
	pipe_data->heredoc_f = 0;
	pipe_data->all_path = get_all_path(data->envp);
	pipe_data->cur_cmd_path = NULL;
	pipe_data->in_out_fd[0] = dup(0);
	pipe_data->in_out_fd[1] = dup(1);
}