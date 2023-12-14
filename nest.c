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

t_nest *add_node(t_nest **nest, t_room **rooms, size_t l_size, char *name, int dist)
{
    t_room *find = (*rooms);
    while (find->next) {
        if (!ft_strcmp(find->name, name))
            break ;
    }
    if (!find->next)
        return NULL;
    t_nest *new = malloc(sizeof(t_nest));
    new->name = ft_strdup(find->name);
    new->type = ROOM;
    new->is_free = 0;
    new->dist = dist;
    new->nodes = malloc(sizeof(t_nest *) * l_size + 1);
    for (size_t i = 0; i < l_size; i++) {
        new->nodes[i] = malloc(sizeof(t_nest));
    }
    new->nodes[l_size] = NULL;
    rm_room(rooms, find->name);
    return new;
}

t_nest *room_exist(t_nest **nest, char *name)
{
    t_nest **n = (*nest)->nodes;
    for (int i = 0; n[i]; i++) {
        if (!ft_strcmp(n[i]->name, name)) {
            return n[i];
        }
        room_exist(&nest[i], name);
    }
    return NULL;
}

void fill_nodes(t_nest **nest, t_nest **start, t_room **rooms, t_links **links, int dist)
{
    t_nest **nodes = (*nest)->nodes;
    for (int i = 0; nodes[i]; i++) {
        for (t_links *l = (*links); l; l = l->next) {
            if (!ft_strcmp(nodes[i]->name, l->name1)) {
                if (!ft_strcmp(l->name2, (*start)->name)) {
                    nodes[i] = (*start);
                } else {
                    t_nest *n = room_exist(nest, l->name2); 
                    if (!n)
                        nodes[i] = add_node(nest, rooms, get_n_links(l->name2, links), l->name2, dist + 1);
                    else {
                        nodes[i] = n;
                    }
                }
            } else if (!ft_strcmp(nodes[i]->name, l->name2)) {
                if (!ft_strcmp(l->name1, (*start)->name)) {
                    nodes[i] = (*start);
                } else {
                    t_nest *n = room_exist(nest, l->name1); 
                    if (!n)
                        nodes[i] = add_node(nest, rooms, get_n_links(l->name1, links), l->name1, dist + 1);
                    else {
                        nodes[i] = n;
                    }
                }
            }
        }
    }
}

// We start from the end because is easier to calculate time complexity
t_nest *init_end(t_room **end, size_t l_size)
{
    t_nest *new = malloc(sizeof(t_nest));
    new->name = ft_strdup((*end)->name);
    new->type = END;
    new->is_free = 0;
    new->dist = 0;
    new->nodes = malloc(sizeof(t_nest *) * l_size + 1);
    for (size_t i = 0; i < l_size; i++) {
        new->nodes[i] = malloc(sizeof(t_nest));
    }
    new->nodes[l_size] = NULL;
    return new;
}

t_nest *init_start(t_room **start, size_t l_size)
{
    t_nest *new = malloc(sizeof(t_nest));
    new->name = ft_strdup((*start)->name);
    new->type = START;
    new->is_free = 0;
    new->dist = 0;
    new->nodes = malloc(sizeof(t_nest *) * l_size + 1);
    for (size_t i = 0; i < l_size; i++) {
        new->nodes[i] = malloc(sizeof(t_nest));
    }
    new->nodes[l_size] = NULL;
    return new;
}


t_nest *build_nest(t_data **data)
{
    t_data *cpy = *data;
    t_nest *end = init_end(&cpy->end, get_n_links(cpy->end->name, &cpy->links));
    t_nest *start = init_start(&cpy->start, get_n_links(cpy->start->name, &cpy->links));
    return end;
}