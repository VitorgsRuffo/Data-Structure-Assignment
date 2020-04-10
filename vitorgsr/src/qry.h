#ifndef QRY_H
#define QRY_H

void qry_create_txt(char* *txtFinalContent, Parameter *parameter);


void qry_build_o_rect_tag(char* *tag, float w, float h, float x, float y, int isThereCollision);

float qry_rect_point_next_to_circ_center(float min, float max, float value);

void qry_o(char* *qryCommand, char* commands[][8], int geo_lines_count, char* *svgFinalDocumentQry, char* *txtFinalContent);


void qry_build_i_dot_line_tag(char* *tag, float pX, float pY, float cmX, float cmY, int isInside);

void qry_i(char* *qryCommand, char* commands[][8], int geo_lines_count, char* *svgFinalDocumentQry, char* *txtFinalContent);


void qry_delf(char* *qryCommand, char* *svgFinalDocumentQry, char* *txtFinalContent, char* commands[][8], int geo_lines_count);

void qry_delf2(char* *qryCommand, char* *svgFinalDocumentQry, char* *txtFinalContent, char* commands[][8], int geo_lines_count);


void qry_pnt(char* *qryCommand, char* commands[][8], int geo_lines_count, char* *svgFinalDocumentQry, char* *txtFinalContent, char* *pnt2);

void qry_pnt2(char* *qryCommand, char* commands[][8], int geo_lines_count, char* *svgFinalDocumentQry, char* *txtFinalContent);

#endif