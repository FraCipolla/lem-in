#include "lem-in.h"
#include "utility.h"
#include "nest.h"
#include <limits.h>

void migrate(t_nest **start, int n_ants)
{
    int end = 0;
    t_ant ants[n_ants];
    t_nest *min = NULL;

    for (int i = 0; i < n_ants; i++) {
        ants[i].current = (*start);
        ants[i].id = i;
    }
    for (; end < n_ants;) {
        for (int i = 0; i < n_ants; i++) {
            if (ants[i].current->type == END)
                continue;
            t_nest **sub_nest = ants[i].current->nodes;
            int n_nodes = (int)ants[i].current->n_nodes;
            min = NULL;
            int k = -1;
            while (++k < n_nodes) {
                if (sub_nest[k]->dist == -1) {
                    continue;
                }
                if (sub_nest[k]->type == END) {
                    min = sub_nest[k];
                    break;
                }
                if (!min && sub_nest[k]->ant_id == -1) {
                    min = sub_nest[k];
                    min->waiting_list++;
                } else if (min && sub_nest[k]->ant_id == -1 && sub_nest[k]->dist <= min->dist) {
                    min->waiting_list--;
                    sub_nest[k]->waiting_list++;
                    min = sub_nest[k];
                } else if (min && (sub_nest[k]->dist + sub_nest[k]->waiting_list) < min->dist) {
                    min->waiting_list--;
                    min = sub_nest[k];
                    min->waiting_list++;
                    k = -1;
                }
            }
            if (!min) {
                continue;
            }
            if (min->type == END) {
                printf("L%d-%s ",ants[i].id, min->name);
                ++end;
                ants[i].current->ant_id = -1;
                ants[i].current->waiting_list = 0;
                ants[i].current = min;
            } else if (min->ant_id == -1) {
                printf("L%d-%s ",ants[i].id, min->name);
                ants[i].current->ant_id = -1;
                ants[i].current->waiting_list = 0;
                min->ant_id = ants[i].id;
                ants[i].current = min;
            }
        }
        printf("\n");
    }
    for (int i = 0; i < n_ants; i++)
        printf("ants n %d room %s\n", ants[i].id, ants[i].current->name);
}

int main()
{
    t_data *data = read_map();
    t_file* tmp = data->input;
    while (tmp) {
        printf("%s\n", tmp->line);
        tmp = tmp->next;
    }
    t_nest *nest = build_nest(&data);
    printf("\n");
    migrate(&nest, data->n_ants);
    return 0;
}