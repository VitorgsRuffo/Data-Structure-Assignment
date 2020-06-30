#ifndef GEO_H
#define GEO_H

void geo_build_circ_tag(char* tag, char* i, char* rad, char* x, char* y, char* corb, char* corp);

void geo_build_rect_tag(char* tag, char* i, char* w, char* h, char* x, char* y, char* corb, char* corp);

void geo_build_txt_tag(char* tag, char* i, char* x, char* y, char* corb, char* corp, char* txt);


void geo_interpret_command(char* command, char* commands[][8], int i);

void geo_draw(char* commands[][8], int geo_lines_count, char* *svgFinalDocument);

#endif