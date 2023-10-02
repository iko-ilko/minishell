#include "../minishell.h"

void    save_history(t_vars *vars, char *line)
{
    add_history(line);
    //구조체안에 저장하는 로직
}