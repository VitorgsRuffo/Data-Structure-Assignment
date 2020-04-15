#ifndef MAIN_H
#define MAIN_H

#define command_max_length 100
#define svgFinalDocMaxLen 3000000
#define svgQryFinalDocMaxLen 4000000
#define txtFinalContentMaxLen 300000

int count_file_lines(FILE *file);
int get_nx(FILE *file);

#endif