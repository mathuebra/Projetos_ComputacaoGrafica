#ifndef _LIGHT_H
#define _LIGHT_H

extern float d, e, m, p, s;

extern bool light0Ligada;
extern bool light1Ligada;
extern bool isLightingOn;

extern float lightAmb[4];
extern float lightDif0[4];
extern float lightSpec0[4];
extern float lightPos0[4];
extern float lightDifAndSpec1[4];
extern float lightPos1[4];
extern float globAmb[4];

#endif