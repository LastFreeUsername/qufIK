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

	double cFABRIK::test(double a, double b)
	{
		return (a+b);
	}

}
