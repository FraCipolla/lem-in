#include "lem-in.h"
#include "utility.h"

int main(int argc, char **argv)
{
    if (argc != 2)
        ft_error("error: needs 1 arguments\n");
    
    t_room *rooms = NULL;
    t_links *links = NULL;
    parse_file(argv[1], rooms, links);
    for (t_room *tmp = rooms; tmp; tmp = tmp->next)
        printf("%s\n", tmp->name);
    return 0;
}