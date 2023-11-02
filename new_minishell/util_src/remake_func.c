#include "../minishell.h"


//앞의 플래그가 리다렉이면 현재 노드의 args[0]을 파일이름으로 생각하고
//리다렉이 아니면 args[0] ~ 현재 노드의 args끝까지를 커맨드로 생각한다.
void	remake_arvl(t_info *info, t_data *data)
{
	t_arvl	*cur;
	t_cmd	*cmd;
	int		i;

	//인덱스로 커맨드 <-> 노드 연결은 너무 복잡할것같으니 t_cmd에 redi 연결리스트 데이터를 넣어주자.
	cur = info->head;
	while (cur)
	{
		cmd = (t_cmd *)cur->content;
		i = 0;
		while (cmd->args[i])
		{
			cmd->args[i] = ft_set_buff(cmd, cur, i, data->envp);
			i++;
		}
		cur = cur->next;
	}<< limiter cat -e > file | ls | wc > outfile
	//info->head free and NULL
}