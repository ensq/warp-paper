#include <stdafx.h>

#include "UtilWin.h"

void GetLastErrorAndTerminateProcess( LPTSTR p_function ) {
	// Retrieve the system error message for the last-error code:
	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError(); 

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
		(LPTSTR)&lpMsgBuf,
		0, 
		NULL );

	// Display the error message:
	lpDisplayBuf = (LPVOID)LocalAlloc(
		LMEM_ZEROINIT, 
		( lstrlen( (LPCTSTR)lpMsgBuf) + lstrlen( (LPCTSTR)p_function) + 40 ) * sizeof(TCHAR) ); 
	StringCchPrintf( (LPTSTR)lpDisplayBuf, 
		LocalSize( lpDisplayBuf ) / sizeof( TCHAR ),
		TEXT( "%s failed with error %d: %s" ),
		p_function, 
		dw, 
		lpMsgBuf ); 
	MessageBox( NULL, (LPCTSTR)lpDisplayBuf, TEXT( "Error" ), MB_OK ); 

	// Don't forget to clean up:
	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);

	// Finally, exit the responsible process:
	ExitProcess(dw); 
}
// http://msdn.microsoft.com/en-us/library/windows/desktop/ms680582%28v=vs.85%29.aspx