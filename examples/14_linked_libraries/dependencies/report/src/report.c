#include "report.h"
#include "shapes.h"
#include <stdio.h>

void ReportArea(int side)
{
    printf("The DYNAMIC LIBRARY says a square of %d has an area of %d.\n", side, ShapesSquareArea(side));
}
