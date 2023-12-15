#include "lem-in.h"
#include "utility.h"

t_data *init_data() {
    t_data *ret = malloc(sizeof(t_data));
    ret->n_rooms = 0;
    ret->n_ants = 0;
    ret->n_links = 0;
    ret->rooms = NULL;
    ret->input = NULL;
    return ret;
}

void add_room(t_room **rooms, char **args, int *n_rooms, enum Type type)
{
    if (!args[1])
        return ;
    (*n_rooms)++;
    t_room *new = malloc(sizeof(t_room));
    new->name = malloc(sizeof(ft_strlen(args[0])) + 1);
    for (int i = 0; i < ft_strlen(args[0]); i++) {
        new->name[i] = args[0][i];
    }
    new->coord_x = ft_atoi(args[1]);
    new->coord_y = ft_atoi(args[2]);
    new->next = NULL;
    new->type = type;
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

void add_link(t_links **link, char **args, int *n_links)
{
    if (!args[1])
        return ;
    (*n_links)++;
    t_links *new = malloc(sizeof(t_links));
    new->name1 = ft_strdup(args[0]);
    new->name2 = ft_strdup(args[1]);
    new->next = NULL;
    if (*link == NULL) {
        *link = new;
    } else {
        t_links *tmp = *link;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}

char **check_case(char *str, int *s)
{
    if (!ft_strcmp(str, "##start")) {
        *s = 0;
        return NULL;
    }
    else if (!ft_strcmp(str, "##end")) {
        *s = 1;
        return NULL;
    }
    else if (str[0] == '#' || str[0] == 'L') {
        *s = 2;
        return NULL;
    }
    char **splitted = ft_split(str, ' ');
    if (splitted[1] && splitted[2]) {
        if (atoi(splitted[1]) && atoi(splitted[2])) {
            *s = 3;
            return splitted;
        }
    }
    free_matrix(splitted);
    splitted = ft_split(str, '-');
    if (splitted[0] && splitted[1]) {
        *s = 4;
        return splitted;
    }
    free_matrix(splitted);
    *s = -1;
    return NULL;
}

t_data *read_map()
{
    char buff[128];
    int n_bytes = 0;
    for (int i = 0; ; i++) {
        n_bytes = read(0, buff + i, 1);
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
    for (int i = 0; i < n_bytes; i++)
        buff[i] = 0;
    int is_start = 0;
    int is_end = 0;
    for (int i = 0; ; i++) {
        n_bytes = read(0, buff + i, 1);
        if (buff[i] == '\0' || n_bytes <= 0)
            break ;
        else if (buff[i] == '\n') {
            buff[i] = 0;
            int s = 0;
            char **args = check_case(buff, &s);
            switch (s)
            {
            case 0: // ##start
                is_start = 1;
                break;
            case 1: // ##end
                is_end = 1;
                break;
            case 2: // comment
                break;
            case 3: // room
                if (is_start) {
                    add_room(&data->rooms, args, &data->n_rooms, START);
                    is_start = 0;
                } else if (is_end) {
                    add_room(&data->rooms, args, &data->n_rooms, END);
                    is_end = 0;
                } else {
                    add_room(&data->rooms, args, &data->n_rooms, ROOM);
                }
                break;
            case 4: // link
                add_link(&data->links, args, &data->n_links);
                break;
            default:
                break;
            }
            add_line(&head, buff);
            for (int j = 0; j < 128; j++) {
                buff[j] = 0;
            }
            i = -1;
        }
    }
    add_line(&head, buff);
    data->input = head;
    return data;
}