#include "lem-in.h"
#include "utility.h"
#include "nest.h"

int main()
{
    t_data *data = read_map();
    t_file* tmp = data->input;
    while (tmp) {
        printf("%s\n", tmp->line);
        tmp = tmp->next;
    }
    build_nest(&data);
    return 0;
}