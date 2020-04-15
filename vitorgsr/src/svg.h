#ifndef SVG_H
#define SVG_H

void svg_set_view_box(float* X, float* Y, float* W, float* H, char* commands[][8], int geo_lines_count);

void svg_append_content_to_final_document(char* content, char* *finalDocument);

void getFileName(char* fileName, int fileNameLen, char* *fileFinalName, int stopAtDot);

void buildSvgPath(Parameter *parameter);

void buildSvgQryPath(Parameter *parameter);

#endif