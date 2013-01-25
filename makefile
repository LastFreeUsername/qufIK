all: cFABRIK

clean:
	del cFABRIK.obj cFABRIK.dll cFABRIK.lib

cFABRIK: cFABRIK.obj cFABRIK.lib
	link /nologo /DEF:cFABRIK.def /LIBPATH:"C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\lib" /LIBPATH:"C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A\Lib" /dll /OUT:cFABRIK.dll cFABRIK.obj
	
cFABRIK.lib:
	lib /nologo /verbose cFABRIK.obj /OUT:cFABRIK.lib

cFABRIK.obj:
	cl /nologo /c "/IC:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\include" cFABRIK.cpp 