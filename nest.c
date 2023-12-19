#include "nest.h"
# include "utility.h"

size_t get_n_links(char *name, t_links **links)
{
    size_t size = 0;
    for (t_links *l = (*links); l; l = l->next) {
        if (!ft_strcmp(name, l->name1) || !ft_strcmp(name, l->name2))
            size++;
    }
    return size;
}

void rm_room(t_room **rooms, char *name)
{
    t_room *to_del = NULL;
    t_room *tmp = (*rooms);
    if (tmp && !ft_strcmp(tmp->name, name)) {
        to_del = tmp;
        (*rooms) = (*rooms)->next;
    } else {
        while (tmp && tmp->next && ft_strcmp(tmp->next->name, name))
            tmp = tmp->next;
        to_del = tmp->next;
        tmp->next = tmp->next->next;
    }
    if (to_del) {
        free(to_del->name);
        free(to_del);
    }
}

void rm_link(t_links **links, t_links *link)
{
    t_links *to_del = NULL;
    t_links *tmp = (*links);
    if (tmp && !ft_strcmp(tmp->name1, link->name1) && !ft_strcmp(tmp->name2, link->name2)) {
        to_del = tmp;
        (*links) = (*links)->next;
    } else {
        while (tmp && tmp->next && (ft_strcmp(tmp->next->name1, link->name1) || ft_strcmp(tmp->next->name2, link->name2)))
            tmp = tmp->next;
        to_del = tmp->next;
        tmp->next = tmp->next->next;
    }
    if (to_del) {
        free(to_del->name1);
        free(to_del->name2);
        free(to_del);
        to_del = NULL;
    }
}

void print_nest(t_nest **nest_arr)
{
    for (int i = 0; nest_arr[i]; i++) {
        printf("nest name %s\n", nest_arr[i]->name);
        printf("links: ");
        for (int j = 0; nest_arr[i]->nodes[j]; j++) {
            printf("%s ", nest_arr[i]->nodes[j]->name);
        }
        printf("\ncomplexity: %d\n\n", nest_arr[i]->dist);
    }
}

t_nest **nest_init(t_data **data)
{
    t_nest **new = malloc(sizeof(t_nest *) * (*data)->n_rooms + 1);
    if (!new)
        return NULL;
    t_room *rooms = (*data)->rooms;
    int i = 0;
    while (rooms) {
        new[i] = malloc(sizeof(t_nest));
        if (!new[i]) {
            return NULL;
        }
        new[i]->name = ft_strdup(rooms->name);
        new[i]->dist = -1;
        new[i]->ant_id = -1;
        new[i]->waiting_list = 0;
        new[i]->type = rooms->type;
        new[i]->n_nodes = get_n_links(rooms->name, &(*data)->links);
        new[i]->nodes = malloc(sizeof(t_nest **) * new[i]->n_nodes + 1);
        new[i]->nodes[new[i]->n_nodes] = NULL;
        rooms = rooms->next;
        rm_room(&(*data)->rooms, new[i]->name);
        i++;
    }
    new[i] = NULL;
    return new;
}

int check_skip(char ***skip, char *name, int index)
{
    for (int i = 0; i < index; i++) {
        if (!ft_strcmp((*skip)[i], name)) {
            return 1;
        }
    }
    return 0;
}

void calculate_complexity(t_nest **nest, int deep, char ***skip, int index)
{
    if ((*nest)->type == START) {
        return;
    }
    t_nest **nodes = (*nest)->nodes;

    for (int i = 0; nodes[i]; i++) {
        if (check_skip(skip, nodes[i]->name, index)) {
            continue;
        }
        if (nodes[i]->dist == -1 || deep < nodes[i]->dist) {
            nodes[i]->dist = deep;
            (*skip)[index] = ft_strdup(nodes[i]->name);
            index++;
            (*skip)[index] = NULL;
            calculate_complexity(&nodes[i], deep + 1, skip, index);
        }
    }
    // while (--index)
    //     free((*skip)[index]);
}

t_nest **build_nest(t_data **data)
{
    t_data *cpy = *data;
    t_nest **nest_arr = nest_init(data);
    if (!nest_arr) {
        ft_error("malloc error\n");
    }
    t_nest *end;
    for (int i = 0; nest_arr[i]; i++) {
        if (nest_arr[i]->type == END) {
            end = nest_arr[i];
            end->dist = 0;
        }
        int j = 0;
        for (t_links *l = cpy->links; l; l = l->next) {
            if (!ft_strcmp(l->name1, nest_arr[i]->name)) {
                for (int k = 0; nest_arr[k]; k++) {
                    if (!ft_strcmp(l->name2, nest_arr[k]->name)) {
                        nest_arr[i]->nodes[j++] = nest_arr[k];
                        break ;
                    }
                }
            } else if (!ft_strcmp(l->name2, nest_arr[i]->name)) {
                for (int k = 0; nest_arr[k]; k++) {
                    if (!ft_strcmp(l->name1, nest_arr[k]->name)) {
                        nest_arr[i]->nodes[j++] = nest_arr[k];
                        break ;
                    }
                }
            }
        }
    }
    char **names = malloc(sizeof(char *) * cpy->n_rooms + 1);
    names[0] = ft_strdup(end->name);
    calculate_complexity(&end, 1, &names, 1);
    print_nest(nest_arr);
    for (int i = 0; names[i]; i++)
        free(names[i]);
    free(names);
    for (t_links *l = cpy->links; l; l = l->next) {
        rm_link(&cpy->links, l);   
    }
    return nest_arr;
}