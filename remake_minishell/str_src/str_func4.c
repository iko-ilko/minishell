#include "../minishell.h"

char	*ft_strtok(char *str, char sepa)
{
    char	*stock;
    char		*p;
    int			i;

    i = 0;
    p = NULL;
    if (str != NULL)
        stock = ft_strdup(str);
    while (*stock != '\0')
    {
        if (i == 0 && *stock != sepa)
        {
            i = 1;
            p = stock;
        }
        else if (i == 1 && *stock == sepa)
        {
            *stock = '\0';
            stock += 1;
            break ;
        }
        stock++;
    }
    return (p);
}