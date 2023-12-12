#include "nest.h"

# include "utility.h"


void fill_nodes(t_nest *nest, t_room *end, t_links *links)
{
    if (!ft_strcmp(end->name, nest->name)) {
        printf("nest->name: %s\n", nest->name);
        printf("last_node\n");
        return ;
    }
    printf("nest->name: %s\n", nest->name);

    t_links *tmp = links;
    int node_size = 0;
    while (tmp) {
        if (!ft_strcmp(nest->name, tmp->name1))
            node_size++;
        else if (!ft_strcmp(nest->name, tmp->name2))
            node_size++;
        tmp = tmp->next;
    }
    nest->nodes = malloc(sizeof(t_nest *) * node_size + 1);
    nest->nodes[node_size] = NULL;
    int i = 0;
    tmp = links;
    while (i < node_size) {
        while (tmp) {
            if (!ft_strcmp(nest->name, tmp->name1)) {
                nest->nodes[i] = malloc(sizeof(t_nest));
                nest->nodes[i]->name = ft_strdup(tmp->name2);
                nest->nodes[i]->is_free = 0;
                nest->nodes[i]->longest = 0;
                nest->nodes[i]->shortest = 0;
                fill_nodes(nest->nodes[i], end, links->next);
                ++i;
            } else if (!ft_strcmp(nest->name, tmp->name2)) {
                nest->nodes[i] = malloc(sizeof(t_nest));
                nest->nodes[i]->name = ft_strdup(tmp->name1);
                nest->nodes[i]->is_free = 0;
                nest->nodes[i]->longest = 0;
                nest->nodes[i]->shortest = 0;
                fill_nodes(nest->nodes[i], end, links->next);
                ++i;
            }
            tmp = tmp->next;
        }
    }
}

t_nest *build_nest(t_data **data)
{
    t_data *cpy = *data;
    t_nest *nest = malloc(sizeof(t_nest));
    nest->name = ft_strdup(cpy->start->name);
    nest->is_free = 0;
    fill_nodes(nest, cpy->end, cpy->links);
    // t_links *links = cpy->links;
    // int node_size = 0;
    // while (links) {
    //     if (!ft_strcmp(nest->name, links->name1))
    //         node_size++;
    //     links = links->next;
    // }
    // nest->nodes = malloc(sizeof(t_nest *) * node_size + 1);
    // nest->nodes[node_size] = NULL;
    // int i = 0;
    // links = cpy->links;
    // while (i < node_size) {
    //     while (links) {
    //         if (!ft_strcmp(nest->name, links->name1)) {
    //             nest->nodes[i] = malloc(sizeof(t_nest));
    //             nest->nodes[i]->name = ft_strdup(links->name1);
    //             nest->nodes[i]->is_free = 0;
    //             nest->nodes[i]->longest = 0;
    //             nest->nodes[i]->shortest = 0;
    //             ++i;
    //         }
    //         links = links->next;
    //     }
    // }
    return nest;
}