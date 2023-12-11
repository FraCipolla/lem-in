#include "lem-in.h"
#include "utility.h"

int main(int argc, char **argv)
{
    if (argc != 2)
        ft_error("error: needs 1 arguments\n");
    
    t_room rooms;
    t_links links;
    parse_file(argv[1], &rooms, &links);
    return 0;
}