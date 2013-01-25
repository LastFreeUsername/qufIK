/*
 * cFABRIK.h
 *
 *  Created on: Jan 25, 2013
 *      Author: gert
 */

#ifndef CFABRIK_H_
#define CFABRIK_H_


namespace cFABRIK
{
	class cFABRIK
	{
	public:
		__declspec(dllexport) __stdcall cFABRIK();
		__declspec(dllexport) static double __stdcall test(double a, double b);
	};

}



#endif /* CFABRIK_H_ */
