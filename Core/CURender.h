/**  
*  @file	  CURender.h  
*  @brief  
*  @author        
*  @date  
*  @version    
*/
#ifndef __CURENDER_H__
#define __CURENDER_H__

#pragma once

namespace CULib {

/** ��Ⱦ������ƣ�������dc�ϻ��Ƶ����򣬷�ֹ�ӿؼ����Ƶ����ؼ��� */
class CULIB_API CRenderClip
{
public:
	~CRenderClip();
	RECT rcItem;
	HDC hDC;
	HRGN hRgn;
	HRGN hOldRgn;
	
	/** ����һ���������� */
	static void GenerateClip(HDC hDC, RECT rc, CRenderClip& clip);
	/** ����һ��Բ�Ǽ������� **/
	static void GenerateRoundClip(HDC hDC, RECT rc, RECT rcItem, int width, int height, CRenderClip& clip);
	/** ʹ��������Ծ������Ϊ������ */
	static void UseOldClipBegin(HDC hDC, CRenderClip& clip);
	/** ʹ�õ�ǰ�ؼ���Ч������Ϊ������ */
	static void UseOldClipEnd(HDC hDC, CRenderClip& clip);
};

/** ��Ⱦ���� */
class CULIB_API CRenderEngine
{
public:
	static DWORD AdjustColor(DWORD dwColor, short H, short S, short L);
	/** ����ͼ�� */
	static TImageInfo* LoadImage(STRINGorID bitmap, LPCTSTR type = NULL, DWORD mask = 0);
	static void FreeImage(const TImageInfo* bitmap);
	/** ����ͼ�� */
	static void DrawImage(HDC hDC, HBITMAP hBitmap, const RECT& rc, const RECT& rcPaint, \
		const RECT& rcBmpPart, const RECT& rcCorners, bool alphaChannel, BYTE uFade = 255, 
		bool hole = false, bool xtiled = false, bool ytiled = false);
	/** ����ʶ�ַ�������ͼ�� */
	static bool DrawImageString(HDC hDC, CPaintManagerUI* pManager, const RECT& rcItem, const RECT& rcPaint, 
		LPCTSTR pStrImage, LPCTSTR pStrModify = NULL);
	static void DrawColor(HDC hDC, const RECT& rc, DWORD color);
	/** ���ƽ��� */
	static void DrawGradient(HDC hDC, const RECT& rc, DWORD dwFirst, DWORD dwSecond, bool bVertical, int nSteps);

	/** ���º����е���ɫ����alphaֵ��Ч */
	/** ����ֱ�� */
	static void DrawLine(HDC hDC, const RECT& rc, int nSize, DWORD dwPenColor);
	/** ���ƾ��� */
	static void DrawRect(HDC hDC, const RECT& rc, int nSize, DWORD dwPenColor);
	/** ����Բ�Ǿ��� */
	static void DrawRoundRect(HDC hDC, const RECT& rc, int width, int height, int nSize, DWORD dwPenColor);
	/** �������� */
	static void DrawText(HDC hDC, CPaintManagerUI* pManager, RECT& rc, LPCTSTR pstrText, \
		DWORD dwTextColor, int iFont, UINT uStyle);
	/** ���� "mini-html" ��ʶ�ַ��� */
	static void DrawHtmlText(HDC hDC, CPaintManagerUI* pManager, RECT& rc, LPCTSTR pstrText, 
		DWORD dwTextColor, RECT* pLinks, CStdString* sLinks, int& nLinkRects, UINT uStyle);
	/** ����һ��BMPλͼ */
	static HBITMAP GenerateBitmap(CPaintManagerUI* pManager, CControlUI* pControl, RECT rc);
};

} // namespace DuiLib

#endif // __UIRENDER_H__
