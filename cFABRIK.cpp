/*
 * cFABRIK.cpp

 *
 *  Created on: Jan 25, 2013
 *      Author: Gert Kanter
 */

#include "cFABRIK.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

namespace cFABRIK
{
	cFABRIK::cFABRIK()
	{
		cFABRIK::pts = new point[0];
		cFABRIK::size = 0;
	}

	cFABRIK::cFABRIK(point points[], int size)
	{
		// constructor
		cFABRIK::setpts(points, size);
	}

	cFABRIK::~cFABRIK()
	{
		// deconstructor
		delete [] cFABRIK::pts;
	}

	int cFABRIK::setpts(point points[], int size)
	{
		cFABRIK::pts = new point[size];
		cFABRIK::size = size;
		for(int i=0;i<size;i++)
		{
			cFABRIK::pts[i] = points[i];
		}
		return(0);
	}

	point cFABRIK::makept(double x, double y, double z)
	{
		point *retval = new point;
		retval->x = x;
		retval->y = y;
		retval->z = z;
		return(*retval);
	}

	int cFABRIK::getpts(point** points)
	{
		if(cFABRIK::size > 0)
		{
			for(int i=0;i<cFABRIK::size;i++)
			{
				points[i] = &cFABRIK::pts[i];
			}
			return(0);
		}
		else
		{
			return(-1);
		}
	}

	double cFABRIK::ptdifflen(point pt1, point pt2)
	{
		return((double) (sqrt((pow(pt2.x-pt1.x, 2) + pow(pt2.y-pt1.y, 2) + pow(pt2.z-pt1.z, 2)))));
	}

	int cFABRIK::iterate(point target)
	{
		double* d = new double[cFABRIK::size-1];
		double totaldist = 0;

		for(int i=0;i<cFABRIK::size-1;i++)
		{
			d[i] = cFABRIK::ptdifflen(cFABRIK::pts[i+1], cFABRIK::pts[i]);
			totaldist += d[i];
		}
		// distance between root and target
		if(cFABRIK::ptdifflen(cFABRIK::pts[0], target) > totaldist)
		{
			// target is unreachable
			double* dist = new double[cFABRIK::size-1];
			double* l = new double[cFABRIK::size-1];

			for(int i=0;i<cFABRIK::size-1;i++)
			{
				// find the distance between the target and the joint position
				dist[i] = cFABRIK::ptdifflen(target, cFABRIK::pts[i]);
				l[i]  = d[i] / dist[i];
				// find the new joint positions
				//cFABRIK::pts[i+1] = (1 - l[i])
			}

			delete [] dist;
			delete [] l;
			delete [] d;
			return(0);
		}
		else
		{
			// target is reachable; thus, set b as the initial position of the joint pts[0]

			delete [] d;
			return(0);
		}


	}


}
