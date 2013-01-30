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
		double x;
		double y;
		double z;
	} point;

	class cFABRIK
	{
	public:
		__declspec(dllexport) __stdcall cFABRIK(point points[], int size);
		__declspec(dllexport) __stdcall cFABRIK();
		__declspec(dllexport) __stdcall ~cFABRIK();
		__declspec(dllexport) point __stdcall makept(double x, double y, double z);
		__declspec(dllexport) int __stdcall setpts(point points[], int size);
		__declspec(dllexport) int __stdcall getpts(point** points);
		__declspec(dllexport) int __stdcall solve(point target);
		__declspec(dllexport) double __stdcall ptdifflen(point pt1, point pt2);
		__declspec(dllexport) point __stdcall cFABRIK::ptscale(point pt, double scale);
		__declspec(dllexport) point __stdcall cFABRIK::ptadd(point pt1, point pt2);
	private:
		point* pts;
		int size;
	};

}

#endif /* CFABRIK_H_ */
