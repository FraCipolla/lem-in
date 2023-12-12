#include "lem-in.h"
#include "utility.h"

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
    printf("start: %s\n", data->start->name);
    printf("end:   %s\n", data->end->name);
    return 0;
}