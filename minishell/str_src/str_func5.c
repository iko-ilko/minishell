#include "../minishell.h"

int ft_atoi(const char *str)
{
        int     result;
        int     minus;

        while ((*str >= 9 && *str <= 13) || *str == 32)
                str++;
        minus = 1;
        if (*str == '-' || *str == '+')
        {
                if (*str == '-')
                        minus = -1;
                str++;
        }
        result = 0;
        while (*str >= '0' && *str <= '9')
                result = result * 10 + *(str++) - '0';
        return (result * minus);
}