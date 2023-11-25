#include "../minishell.h"

char	*ft_strtok(char *str, char sepa) {
    static char	*stock = NULL;
    char		*p;

    if (str != NULL)
        stock = str;

    if (stock == NULL || *stock == '\0')
        return (NULL);

    p = stock;

    // 토큰을 찾을 때까지 진행
    while (*stock != sepa && *stock != '\0')
        stock++;

    // 토큰을 찾은 경우 NULL로 만들고 다음 위치로 이동
    if (*stock == sepa) {
        *stock = '\0';
        stock++;
    } else {
        stock = NULL; // 토큰 끝에 도달한 경우 NULL로 설정하여 더 이상 토큰이 없음을 나타냄
    }

    return (p);
}