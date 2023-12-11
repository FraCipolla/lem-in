#include "utility.h"

#include <unistd.h>
#include <stdlib.h>

int ft_strlen(char *str)
{
    char *ptr = str;
    while (*str)
        str++;
    return (str - ptr);
}

void ft_error(char *str)
{
    write(1, str, ft_strlen(str));
    exit(1);
}

int ft_atoi(char *str)
{
    int ret = 0;
    int sign = 1;

    if (str[0] == '-') {
        sign = -1;
        str++;
    }
    while (*str >= '0' && *str <= '9') {
        ret = ret * 10 + (*str - 48);
        str++;
    }
    if (*str != 0 && *str != '\n')
        ft_error("Error, number of ants is not a number\n");
    return (ret * sign);
}