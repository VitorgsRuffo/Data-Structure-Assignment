#ifndef QRY_H
#define QRY_H


void qry_create_txt(char* *txtFinalContent, Parameter *parameter);

void getDrawingInfo(char* jDrawing[], char* kDrawing[], char* commands[][8], int geo_lines_count, char* J, char* K);



float qry_o_rect_point_next_to_circ_center(float min, float max, float value);


int qry_o_circ_circ_collision(float jRadius, float jX, float jY, float kRadius, float kX, float kY);

void qry_o_get_circCirc_rect_info(float jRadius, float jX, float jY, float kRadius, float kX, float kY, float *rectX, float *rectY, float *rectW, float *rectH);


int qry_o_rect_rect_collision(float jX, float jY, float jW, float jH, float kX, float kY, float kW, float kH);

void qry_o_get_rectRect_rect_info(float jX, float jY, float jW, float jH, float kX, float kY, float kW, float kH, float *rectX, float *rectY, float *rectW, float *rectH);


int qry_o_circ_rect_collision(float jRadius, float jX, float jY, float kX, float kY, float kW, float kH);

void qry_o_get_circRect_rect_info(float jRadius, float jX, float jY, float kX, float kY, float kW, float kH, float *rectX, float *rectY, float *rectW, float *rectH);


int qry_o_rect_circ_collision(float jX, float jY, float jW, float jH, float kRadius, float kX, float kY);

void qry_o_get_rectCirc_rect_info(float jX, float jY, float jW, float jH, float kRadius, float kX, float kY, float *rectX, float *rectY, float *rectW, float *rectH);


void qry_o_build_rect_tag(char* *tag, float w, float h, float x, float y, int isThereCollision);

void qry_o(char* *qryCommand, char* commands[][8], int geo_lines_count, char* *svgFinalDocumentQry, char* *txtFinalContent);



void qry_i_build_dot_line_tag(char* *tag, float pX, float pY, float cmX, float cmY, int isInside);

void qry_i(char* *qryCommand, char* commands[][8], int geo_lines_count, char* *svgFinalDocumentQry, char* *txtFinalContent);



void qry_delf(char* *qryCommand, char* *svgFinalDocumentQry, char* *txtFinalContent, char* commands[][8], int geo_lines_count);

void qry_delf2(char* *qryCommand, char* *svgFinalDocumentQry, char* *txtFinalContent, char* commands[][8], int geo_lines_count);



void qry_pnt(char* *qryCommand, char* commands[][8], int geo_lines_count, char* *svgFinalDocumentQry, char* *txtFinalContent, char* *pnt2);

void qry_pnt2(char* *qryCommand, char* commands[][8], int geo_lines_count, char* *svgFinalDocumentQry, char* *txtFinalContent);

#endif