#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
int main(void) {
	STARTUPINFO si; // new process의 특성
	PROCESS_INFORMATION pi; // new process/thread에 대한 핸들/식별자
	
	ZeroMemory( &si, sizeof(si) ); /* allocate memory */
	si.cb = sizeof( si );
	ZeroMemory( &pi, sizeof(pi) );

	/* create child process */
		if ( !CreateProcess( NULL, /* use command line */
		"C:∖∖WINDOWS∖∖system32∖∖mspaint.exe", /* command */
		NULL, /* don’t inherit process handle */
		NULL, /* don’t inherit thread handle */
		FALSE, /* disable handle inheritance */
		0, /* no creation flags */
		NULL, /* use parent’s environment block */
		NULL, /* use parent’s existing directory */
		&si, &pi) ){
			fprintf(stderr, "Create Process Failed");
			return -1;
		}

	/* parent will wait for the child to complete */
	WaitForSingleObject( pi.hProcess, INFINITE ); // wait() system call 과 동일
	printf("Child Complete");

	/* close handles */
	CloseHandle(pi.hProcess); // new process에 대한 핸들 닫기
	CloseHandle(pi.hThread); // new thread에 대한 핸들 닫기

	return 0;
}