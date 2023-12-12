#pragma once

#include "lem-in.h"

typedef struct s_nest {
    char *name;
    int is_free;
    int shortest;
    int longest;
    struct s_nest **nodes;
}   t_nest;

t_nest *build_nest(t_data **data);