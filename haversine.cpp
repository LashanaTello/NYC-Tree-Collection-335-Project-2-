/*******************************************************************************
  Title          : haversine.c
  Author         : Stewart Weiss
  Created on     : October 30, 2017
  Description    : Computes distance between two points on earth 
  Purpose        : 
  Usage          : haversine latitude1 longitude1 latitude2 longitude2 in degrees
  Build with     : gcc -o haversine haversine.v -lm
  Modifications  : 
 
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
 
#define R 6372.8
#define TO_RAD (3.1415926536 / 180)
double dist(double th1, double ph1, double th2, double ph2)
{
	double dx, dy, dz;
	ph1 -= ph2;
	ph1 *= TO_RAD, th1 *= TO_RAD, th2 *= TO_RAD;
 
	dz = sin(th1) - sin(th2);
	dx = cos(ph1) * cos(th1) - cos(th2);
	dy = sin(ph1) * cos(th1);
	return asin(sqrt(dx * dx + dy * dy + dz * dz) / 2) * 2 * R;
}

double haversine(  double lat1, double lon1, double lat2, double lon2)
{
    lat1        = TO_RAD * lat1;
    lat2        = TO_RAD * lat2;
    lon1        = TO_RAD * lon1;
    lon2        = TO_RAD * lon2;
    double dLat = (lat2 - lat1)/2;
    double dLon = (lon2 - lon1)/2;
    double a    = sin(dLat);
    double b    = sin(dLon);
    return 2*R * asin(sqrt(a*a + cos(lat1) * cos(lat2) * b*b));
}
