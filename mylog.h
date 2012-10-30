#ifndef _MY_LOG_H_BD0FC3E9_4D2B_4A51_8935_01522932B969_
#define _MY_LOG_H_BD0FC3E9_4D2B_4A51_8935_01522932B969_


#ifdef XP_WIN
#include <windows.h>
#include <windowsx.h>
#endif

#ifdef XP_WIN
#include <io.h>
#endif


#include <stdio.h>
#include <cstring>
#include <cstdarg>

#define LF __LINE__,__FILE__
#define MY_LOGFILEC "C:\\MY_LOG.log"
#define MY_LOGFILED "D:\\MY_LOG.log"


static void MYDBG( int line, const char * file, char * fmt, ... )
{
#if !defined (_DEBUG) || !defined( XP_WIN )
    return;
#endif

	char argbuf[1024*5] = {0};
	va_list args;
	va_start( args, fmt );
	vsprintf(argbuf,fmt,args);
	va_end(args);

	char filenopath[260] = {0};
	strcpy(filenopath, file);
	char * filepos = filenopath;
	char * slash = "\\";
	while (strstr(filepos, slash))
	{
		filepos = strstr(filepos, slash);
		filepos++;
	}

	char buf[1024*6] = {0};
	sprintf(buf, "%s(%d):  ", filepos, line); 
	strcat(buf, argbuf);
  strcat(buf, "\n");

  //view the debug message through console,
  //and must run up the browser through the console.
  printf( buf );

#ifdef XP_WIN
	OutputDebugStringA(buf);
	if ( _access(MY_LOGFILEC, 0) == 0 || _access(MY_LOGFILED, 0) == 0 )
        MessageBoxA(NULL, buf, "npsimple", MB_OK);
#endif
}


static void MYDBG( int line, const char * file, wchar_t * fmt, ... )
{	
#if !defined (_DEBUG) || !defined( XP_WIN )
    return;
#endif



#ifdef XP_WIN
	wchar_t argbuf[1024*5] = {0};
	va_list args;
	va_start( args, fmt );
	vswprintf(argbuf,fmt,args);
	va_end(args);

	wchar_t buf[1024*6] = {0};


	char filenopath[260] = {0};
	strcpy(filenopath, file);
	char * filepos = filenopath;
	char * slash = "\\";
	while (strstr(filepos, slash))
	{
		filepos = strstr(filepos, slash);
		filepos++;
	}


	wchar_t wfile[260*2] = {0};
	int nMConvertedLen = MultiByteToWideChar(CP_ACP, 0, file, strlen(file), NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, filepos, strlen(filepos), wfile, nMConvertedLen);

	swprintf(buf, L"%s(%d):  ", wfile, line); 
	wcscat(buf, argbuf);

	OutputDebugStringW(buf);
    if ( _access(MY_LOGFILEC, 0) == 0 || _access(MY_LOGFILED, 0) == 0 )
        MessageBoxW(NULL, buf, L"npsimple", MB_OK);
#endif
}


/*

static void MYDBG( int line, const char * file, char * fmt, ... )
{
	if ( _access(MY_LOGFILEC, 0) == 0 || _access(MY_LOGFILED, 0) == 0 )
	{
		char argbuf[1024*5] = {0};
		va_list args;
		va_start( args, fmt );
		vsprintf(argbuf,fmt,args);
		va_end(args);

		char filenopath[260] = {0};
		strcpy(filenopath, file);
		char * filepos = filenopath;
		char * slash = "\\";
		while (strstr(filepos, slash))
		{
			filepos = strstr(filepos, slash);
			filepos++;
		}

		char buf[1024*6] = {0};
		sprintf(buf, "%s(%d):  ", filepos, line); 
		strcat(buf, argbuf);

		OutputDebugStringA(buf);
		
		char* filename;
		if ( _access(MY_LOGFILEC, 0) == 0 ){
			filename = MY_LOGFILEC;
		}else{
			filename = MY_LOGFILED;
		}

		FILE *fp = NULL;
		fp=fopen(filename,"at");
		if(fp)
		{
			SYSTEMTIME systime;
			GetLocalTime(&systime);
			char timebuf[128] = {0};
			sprintf(timebuf,
				"%02d.%02d-%02d:%02d:%02d",
				systime.wMonth,systime.wDay,
				systime.wHour,systime.wMinute,systime.wSecond);
			
			fprintf(fp, "%s#", timebuf);
			fprintf(fp, "%s", buf);
			fprintf(fp, "%s", "\n");
			fclose(fp);
		}
	}
}


static void MYDBG( int line, const char * file, wchar_t * fmt, ... )
{	
	if ( _access(MY_LOGFILEC, 0) == 0 || _access(MY_LOGFILED, 0) == 0 )
	{
	
		wchar_t argbuf[1024*5] = {0};
		va_list args;
		va_start( args, fmt );
		vswprintf(argbuf,fmt,args);
		va_end(args);

		wchar_t buf[1024*6] = {0};


		char filenopath[260] = {0};
		strcpy(filenopath, file);
		char * filepos = filenopath;
		char * slash = "\\";
		while (strstr(filepos, slash))
		{
			filepos = strstr(filepos, slash);
			filepos++;
		}

		wchar_t wfile[260*2] = {0};
		int nMConvertedLen = MultiByteToWideChar(CP_ACP, 0, file, strlen(file), NULL, 0);
		MultiByteToWideChar(CP_ACP, 0, filepos, strlen(filepos), wfile, nMConvertedLen);

		swprintf(buf, L"%s(%d):  ", wfile, line); 
		wcscat(buf, argbuf);

		OutputDebugStringW(buf);


		//file log	
		char buf2[1024*6] = {0};
		int nConvertedLen = WideCharToMultiByte(CP_ACP, 0, buf, -1, NULL, 0,NULL,NULL);
		WideCharToMultiByte(CP_ACP, 0, buf, -1, buf2, nConvertedLen,NULL,NULL);
	
		char* filename;
		if ( _access(MY_LOGFILEC, 0) == 0 ){
			filename = MY_LOGFILEC;
		}else{
			filename = MY_LOGFILED;
		}

		FILE *fp = NULL;
		fp=fopen(filename,"at");
		if(fp)
		{
			SYSTEMTIME systime;
			GetLocalTime(&systime);
			char timebuf[128] = {0};
			sprintf(timebuf,
				"%02d.%02d-%02d:%02d:%02d",
				systime.wMonth,systime.wDay,
				systime.wHour,systime.wMinute,systime.wSecond);
			
			fprintf(fp, "%s#", timebuf);
			fprintf(fp, "%s", buf2);
			fprintf(fp, "%s", "\n");
			fclose(fp);
		}
	}
}

*/

#endif
