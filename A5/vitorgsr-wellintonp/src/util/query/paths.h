#ifndef PATH_H
#define PATH_H

#include "../svg.h"
#include "../../elements/urban-elements/city.h"
#include "../input/openInput.h"

/*
*
*/
void findBestCarPath(int isSecure, int pathId, Svg* minimumPaths, char* command, City Ct, Parameters Param, File txt);

#endif