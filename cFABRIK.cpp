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

	point cFABRIK::ptscale(point pt, double scale)
	{
		point *retval = new point;

		retval->x = pt.x * scale;
		retval->y = pt.y * scale;
		retval->z = pt.z * scale;

		return(*retval);
	}

	point cFABRIK::ptadd(point pt1, point pt2)
	{
		point *retval = new point;

		retval->x = pt1.x + pt2.x;
		retval->y = pt1.y + pt2.y;
		retval->z = pt1.z + pt2.z;

		return(*retval);
	}

	int cFABRIK::solve(point target)
	{
		double* d = new double[cFABRIK::size-1];
		double totaldist = 0;

		int count = 0;

		for(int i=0;i<=cFABRIK::size-2;i++)
		{
			d[i] = cFABRIK::ptdifflen(cFABRIK::pts[i+1], cFABRIK::pts[i]);
			totaldist += d[i];
		}
		// distance between root and target
		if(cFABRIK::ptdifflen(cFABRIK::pts[0], target) > totaldist)
		{
			// target is unreachable
			double* r = new double[cFABRIK::size-1];
			double* l = new double[cFABRIK::size-1];

			for(int i=0;i<=cFABRIK::size-2;i++)
			{
				// find the distance between the target and the joint position
				r[i] = cFABRIK::ptdifflen(target, cFABRIK::pts[i]);
				l[i]  = d[i] / r[i];
				// find the new joint positions
				cFABRIK::pts[i+1] = cFABRIK::ptadd(cFABRIK::ptscale(cFABRIK::pts[i], (1 - l[i])), cFABRIK::ptscale(target, l[i]));
			}

			delete [] r;
			delete [] l;
			delete [] d;
			return(-1);
		}
		else
		{
			// target is reachable; thus, set b as the initial position of the joint pts[0]
			point *b = new point;

			double* r = new double[cFABRIK::size-1];
			double* l = new double[cFABRIK::size-1];
			int i = 0;

			*b = cFABRIK::pts[0];
			// check whether the distance between the end effector pts[size-1] and the target is greater than a tolerance
			double EEdiff = cFABRIK::ptdifflen(cFABRIK::pts[cFABRIK::size-1], target);

			while(EEdiff > 0.001)
			{
				count++;
				// STAGE 1: FORWARD REACHING
				// Set the end effector pts[size-1] as target t
				cFABRIK::pts[cFABRIK::size-1] = target;

				for(i=cFABRIK::size-2;i>=0;i--)
				{
					// find the distance r_i between the new joint position pts_i+1 and the joints pts_i
					r[i] = cFABRIK::ptdifflen(cFABRIK::pts[i+1], cFABRIK::pts[i]);
					l[i]  = d[i] / r[i];
					// find the new joint positions pts_i
					cFABRIK::pts[i] = cFABRIK::ptadd(cFABRIK::ptscale(cFABRIK::pts[i+1], (1 - l[i])), cFABRIK::ptscale(cFABRIK::pts[i], l[i]));
				}
				// STAGE 2: BACKWARD REACHING
				// set the root pts[0] its initial position
				cFABRIK::pts[0] = *b;

				for(i=0;i<=cFABRIK::size-2;i++)
				{
					// find the distance r_i between the new joint position pts_i and the joint pts_i+1
					r[i] = cFABRIK::ptdifflen(cFABRIK::pts[i+1], cFABRIK::pts[i]);
					l[i]  = d[i] / r[i];
					// find the new joint positions pts_i
					cFABRIK::pts[i+1] = cFABRIK::ptadd(cFABRIK::ptscale(cFABRIK::pts[i], (1 - l[i])), cFABRIK::ptscale(cFABRIK::pts[i+1], l[i]));
				}

				EEdiff = cFABRIK::ptdifflen(cFABRIK::pts[cFABRIK::size-1], target);
			}


			delete [] r;
			delete [] l;
			delete [] d;
			return(count);
		}


	}


}
