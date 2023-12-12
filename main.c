#include "lem-in.h"
#include "utility.h"
#include "nest.h"

int main(int argc, char **argv)
{
    if (argc != 2)
        ft_error("error: needs 1 arguments\n");
    t_data *data = parse_file(argv[1]);
    t_file* tmp = data->input;
    while (tmp) {
        printf("%s\n", tmp->line);
        tmp = tmp->next;
    }
    // printf("start:   %s\n", data->start->name);
    // printf("end:     %s\n", data->end->name);
    // printf("n_rooms: %d\n", data->n_rooms);
    // printf("n_ants:  %d\n", data->n_ants);
    // printf("n_links: %d\n", data->n_links);
    // t_room *rooms = data->rooms;
    // while (rooms) {
    //     printf("room:\nname:%s x:%d y:%d\n", rooms->name, rooms->coord_x, rooms->coord_y);
    //     rooms = rooms->next;
    // }
    // printf("\n");
    // t_links *links = data->links;
    // while (links) {
    //     printf("link1: %s link2: %s\n", links->name1, links->name2);
    //     links = links->next;
    // }
    return 0;
}