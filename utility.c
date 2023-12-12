#include "utility.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char *ft_strdup(char *str)
{
    char *ret = malloc(sizeof(char) * ft_strlen(str) + 1);
    int i = 0;
    while (str[i] && str[i] != '\n') {
        ret[i] = str[i];
        ++i;
    }
    ret[i] = 0;
    return ret;
}

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

char **ft_split(char const *str, int sep)
{
    int size = 1;
    for (int i = 0; str[i] == sep; i++)
        ;
    for (int i = 0; str[i]; i++) {
        if (str[i] == sep) {
            ++size;
            while (str[i] == sep)
                i++;
            i--;
        }
    }
    if (size == 1)
        return NULL;
    char **ret = malloc(sizeof(char *) * size + 1);
    ret[size] = NULL;
    int index = 0;
    for (int i = 0; str[i] == sep; i++)
        ;
    for (int i = 0; str[i]; i++) {
        if (str[i] != sep) {
            int j = i;
            while (str[j] != sep)
                j++;
            ret[index] = malloc(sizeof(char) * j + 1);
            ret[index][j] = 0;
            for (int k = 0; i < j; i++, k++) {
                ret[index][k] = str[i];
            }
            i--;
            index++;
            if (index == size)
                break;
        }
    }
    return ret;
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

int ft_strcmp(char *s1, char *s2)
{
    while (*s1 && *s2) {
        if (*s1 != *s2)
            return *s1 - *s2;
        s1++;
        s2++;
    }
    return 0;
}