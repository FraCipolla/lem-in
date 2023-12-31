#pragma once

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

enum Type {
    START,
    ROOM,
    END
};

typedef struct s_room {
    char *name;
    int coord_x;
    int coord_y;
    int n_links;
    enum Type type;
    struct s_room *next;
}   t_room;

typedef struct s_links {
    char *name1;
    char *name2;
    struct s_links *next;
}   t_links;

typedef struct s_ant {
    int id;
    struct s_nest *prev;
    struct s_nest *current;
    struct s_nest *next;
    int wait;
}   t_ant;

typedef struct s_file {
    char *line;
    struct s_file *next;
}   t_file;

typedef struct s_data {
    int n_rooms;
    int n_ants;
    int n_links;
    struct s_room *rooms;
    struct s_file *input;
    struct s_links *links;
}   t_data;

t_data *read_map();