all: cFABRIK

clean:
	del cFABRIK.obj cFABRIK.dll cFABRIK.lib

cFABRIK: cFABRIK.dll cFABRIK.lib

cFABRIK.lib:
	lib cFABRIK.obj /OUT:cFABRIK.lib

cFABRIK.dll: cFABRIK.obj
	link /LIBPATH:"C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\lib" /dll /OUT:cFABRIK.dll cFABRIK.obj

cFABRIK.obj:
	cl /c /EHsc cFABRIK.cpp 