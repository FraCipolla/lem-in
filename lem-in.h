#pragma once

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

typedef struct s_room {
    char *name;
    int coord_x;
    int coord_y;
    int is_free;
    struct s_room *next;
    struct s_room *exit;
}   t_room;

typedef struct s_links {
    char *name1;
    char *name2;
    struct s_room *next;
}   t_links;

int parse_file(char *path, t_room *rooms, t_links *links);