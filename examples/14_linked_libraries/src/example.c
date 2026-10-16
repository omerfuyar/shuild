#include "report.h"
#include "shapes.h"
#include <stdio.h>

int main(void)
{
    printf("Hello from 14_linked_libraries example!\n");

    printf("The STATIC LIBRARY says a square of 5 has an area of %d.\n", ShapesSquareArea(5));
    ReportArea(7);
}
