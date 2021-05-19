#ifndef CAR_PATH_H
#define CAR_PATH_H

#include "../svg.h"
#include "../../elements/urban-elements/city.h"
#include "../input/openInput.h"

/*
*
*/
void findBestCarPath(Svg* minimumPaths, char* command, City Ct, Parameters Param, File txt);

#endif