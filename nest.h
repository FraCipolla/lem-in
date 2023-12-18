#pragma once

#include "lem-in.h"

typedef struct s_nest {
    char *name;
    enum Type type;
    size_t n_nodes;
    int ant_id;
    int dist;
    struct s_nest **nodes;
}   t_nest;

t_nest *build_nest(t_data **data);