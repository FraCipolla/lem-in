#include <unistd.h>
#include <stdlib.h>
#include "lem-in.h"
#include "utility.h"

void print_grid(t_data **data)
{
    t_data *cpy = (*data);
    int max_x = 0, max_y = 0;
    for (t_room *tmp = cpy->rooms; tmp; tmp = tmp->next) {
        if (tmp->coord_x > max_x)
            max_x = tmp->coord_x;
        if (tmp->coord_y > max_y)
            max_y = tmp->coord_y;
    }
    max_x++;
    max_y++;
    char matrix[max_y][max_x];
    for (int y = 0; y < max_y; y++) {
        for (int x = 0; x < max_x; x++) {
            matrix[y][x] = '.';
        }
    }
    for (t_room *tmp = cpy->rooms; tmp; tmp = tmp->next) {
        matrix[tmp->coord_y][tmp->coord_x] = tmp->name[0];
    }
    for (int y = 1; y < max_y; y++) {
        for (int x = 1; x < max_x; x++) {
            printf("%c", matrix[y][x]);
        }
        printf("\n");
    }
}

int main() {
    printf("\n\n-----visualizer-----\n");
    t_data *data = read_map();
    t_file* tmp = data->input;
    while (tmp) {
        printf("%s\n", tmp->line);
        tmp = tmp->next;
    }

    print_grid(&data);
}