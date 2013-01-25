/*
 * cFABRIK.h
 *
 *  Created on: Jan 25, 2013
 *      Author: Gert Kanter
 */

#ifndef CFABRIK_H_
#define CFABRIK_H_

namespace cFABRIK
{
	typedef struct point
	{
		float x;
		float y;
		float z;
	} point;

	class cFABRIK
	{
	public:
		__declspec(dllexport) __stdcall cFABRIK();
		__declspec(dllexport) static double __stdcall test(point* a, point* b);
	private:
		point pts;
	};

}

#endif /* CFABRIK_H_ */
