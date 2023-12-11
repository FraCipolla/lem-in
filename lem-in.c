#include "lem-in.h"
#include "utility.h"

void add_room(t_room *rooms, char **args)
{
    t_room *new = malloc(sizeof(t_room));
    new->name = malloc(sizeof(ft_strlen(args[0])) + 1);
    for (int i = 0; i < ft_strlen(args[0]); i++) {
        new->name[i] = args[0][i];
    }
    new->coord_x = ft_atoi(args[1]);
    new->coord_y = ft_atoi(args[2]);
    new->is_free = 1;
    new->next = NULL;
    new->exit = NULL;

    if (!rooms) {
        rooms = new;
    } else {
        t_room *tmp = rooms;
        while (tmp->next) {
            tmp = tmp->next;
        }
        tmp->next = new;
    }
}

int parse_file(char *path, t_room *rooms, t_links *links)
{
    int fd = open(path, O_RDONLY);
    char buff[128];
    int n_bytes = 0;
    for (int i = 0; ; i++) {
        n_bytes = read(fd, buff + i, 1);
        if (buff[i] == '\n' || buff[i] == '\0' || n_bytes <= 0)
            break;   
    }
    if (n_bytes <= 0)
        ft_error("read: failed\n");
    int n_ants = ft_atoi(buff);
    printf("%d\n", n_ants);
    if (n_ants <= 0) 
        ft_error("error: number of ants should be positive\n");
    for (int i = 0; i < sizeof(buff); i++) {
        buff[i] = 0;
    }
    for (int i = 0; ; i++) {
        n_bytes = read(fd, buff + i, 1);
        if (buff[i] == '\0' || n_bytes <= 0)
            break ;
        else if (buff[i] == '\n') {
            printf("%s", buff);
            char **splitted = ft_split(buff, ' ');
            if (splitted) {
                add_room(rooms, splitted);
            }
            for (int j = 0; j < 128; j++) {
                buff[j] = 0;
            }
            i = -1;
        }
    }
    printf("%s\n", buff);
    t_room *tmp = rooms;
    close(fd);
    return 0;
}