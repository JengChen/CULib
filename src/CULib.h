/**  
*  @file	  CULib.h 
*  @brief  
*  @author        
*  @date  
*  @version 
* ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
* ��ı�׼�������� DLL �е������ļ��������������϶���� CULIB_EXPORTS
* ���ű���ġ���ʹ�ô� DLL ��
* �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
* CULIB_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
* ������Ϊ�Ǳ������ġ�
*/
#ifdef  CULIB_EXPORTS
#define CULIB_API  __declspec(dllexport)
#else
#define CULIB_API  __declspec(dllimport)
#endif

#include <windows.h>
#include <windowsx.h>
#include <winuser.h>
#include <olectl.h>
#include <tchar.h>
#include <assert.h>
#include <malloc.h>
#include <string>

#define  _CRT_SECURE_NO_WARNING

#include "CUBase.h"
#include "CUManager.h"
#include "CUDelegate.h"
#include "CUControl.h"
#include "CUContainer.h"
#include "CUCommonControl.h"
#include "CUList.h"
#include "CUMenu.h"
#include "CUCombo.h"
#include "CUActiveX.h"
#include "CMarkup.h"
#include "CUDlgBuilder.h"
#include "CURender.h"
#include "UIRichEdit.h"
#include "XUnzip.h"
#include "CULog.h"

#define lengthof(x) (sizeof(x)/sizeof(*x))
#define MAX max
#define MIN min
#define CLAMP(x,a,b) (MIN(b,MAX(a,x)))
