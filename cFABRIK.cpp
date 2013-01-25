/*
 * cFABRIK.cpp

 *
 *  Created on: Jan 25, 2013
 *      Author: Gert Kanter
 */

#include "cFABRIK.h"

#include <stdio.h>


namespace cFABRIK
{
	cFABRIK::cFABRIK(void)
	{
		printf("constructor!");
	}

	double cFABRIK::test(point* a, point* b)
	{
		printf("test test");
		return (a->x+b->x);
	}

}
