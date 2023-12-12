#include "lem-in.h"
#include "utility.h"

void add_room(t_room **rooms, char **args)
{
    t_room *new = malloc(sizeof(t_room));
    new->name = malloc(sizeof(ft_strlen(args[0])) + 1);
    for (int i = 0; i < ft_strlen(args[0]); i++) {
        new->name[i] = args[0][i];
    }
    new->coord_x = ft_atoi(args[1]);
    new->coord_y = ft_atoi(args[2]);
    new->next = NULL;

    if (*rooms == NULL) {
        *rooms = new;
    } else {
        t_room *tmp = *rooms;
        while (tmp->next) {
            tmp = tmp->next;
        }
        tmp->next = new;
    }
}

t_data *init_data() {
    t_data *ret = malloc(sizeof(t_data));
    ret->n_rooms = 0;
    ret->n_ants = 0;
    ret->n_links = 0;
    ret->end = NULL;
    ret->start = NULL;
    ret->rooms = NULL;
    ret->input = NULL;
    return ret;
}

void add_line(t_file **head, char *buff)
{
    t_file *new = malloc(sizeof(t_file));
    new->line = ft_strdup(buff);
    new->next = NULL;
    t_file *tmp = *head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

t_data *parse_file(char *path)
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
    t_data *data = init_data();
    data->n_ants = ft_atoi(buff);
    t_file *head = malloc(sizeof(t_file));
    head->line = ft_strdup(buff);
    if (data->n_ants <= 0) 
        ft_error("error: number of ants should be positive\n");
    for (int i = 0; i < sizeof(buff); i++)
        buff[i] = 0;
    int is_start = 0;
    int is_end = 0;
    for (int i = 0; ; i++) {
        n_bytes = read(fd, buff + i, 1);
        if (buff[i] == '\0' || n_bytes <= 0)
            break ;
        else if (buff[i] == '\n') {
            buff[i] = 0;
            if (is_start) {
                add_room(&data->start, ft_split(buff, ' '));
                is_start = 0;
            }
            if (is_end) {
                add_room(&data->end, ft_split(buff, ' '));
                is_end = 0;
            }
            if (!ft_strcmp(buff, "##start"))
                is_start = 1;
            if (!ft_strcmp(buff, "##end"))
                is_end = 1;
            add_line(&head, buff);
            for (int j = 0; j < 128; j++) {
                buff[j] = 0;
            }
            i = -1;
        }
    }
    add_line(&head, buff);
    data->input = head;
    close(fd);
    return data;
}