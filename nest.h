#pragma once

#include "lem-in.h"

enum Type {
    START,
    ROOM,
    END
};

typedef struct s_nest {
    char *name;
    enum Type type;
    int is_free;
    int dist;
    struct s_nest **nodes;
}   t_nest;

t_nest *build_nest(t_data **data);