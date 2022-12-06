#include "light.h"

float d = 1.0, e = 1.0, m = 0.2, p = 1.0, s = 1.0;

float lightAmb[] = {0,0,0,0};
float lightDif0[] = { d, d, d, 1.0 };
float lightSpec0[] = { e, e, e, 1.0 };
float lightPos0[] = { 0.0, 0.0, 0.0, p };
float lightDifAndSpec1[] = { 0.0, 1.0, 0.0, 1.0 };
float lightPos1[] = { 1.0, 2.0, 0.0, 1.0 };
float globAmb[] = { m, m, m, 1.0 };