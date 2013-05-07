/**  
*  @file      CUManager.h
*  @brief  
*  @author        
*  @date  
*  @version    
*/
#ifndef __UIMANAGER_H__
#define __UIMANAGER_H__

#include <commctrl.h>
#pragma once

namespace CULib {

class CControlUI;

typedef enum EVENTTYPE_UI
{
	UIEVENT__FIRST = 1,
	UIEVENT__KEYBEGIN,
	UIEVENT_KEYDOWN,
	UIEVENT_KEYUP,
	UIEVENT_CHAR,
	UIEVENT_SYSKEY,
	UIEVENT__KEYEND,
	UIEVENT__MOUSEBEGIN,
	UIEVENT_MOUSEMOVE,
	UIEVENT_MOUSELEAVE,
	UIEVENT_MOUSEENTER,
	UIEVENT_MOUSEHOVER,
	UIEVENT_BUTTONDOWN,
	UIEVENT_BUTTONUP,
	UIEVENT_RBUTTONDOWN,
	UIEVENT_DBLCLICK,
	UIEVENT_CONTEXTMENU,
	UIEVENT_SCROLLWHEEL,
	UIEVENT__MOUSEEND,
	UIEVENT_KILLFOCUS,
	UIEVENT_SETFOCUS,
	UIEVENT_WINDOWSIZE,
	UIEVENT_SETCURSOR,
	UIEVENT_TIMER,
	UIEVENT_NOTIFY,
	UIEVENT_COMMAND,
	UIEVENT__LAST,
};

/** CControlUI::GetControlFlags()�����ı�־ */
#define UIFLAG_TABSTOP       0x00000001
#define UIFLAG_SETCURSOR     0x00000002
#define UIFLAG_WANTRETURN    0x00000004

/** FindControl()�����ı�־ */
#define UIFIND_ALL           0x00000000
#define UIFIND_VISIBLE       0x00000001
#define UIFIND_ENABLED       0x00000002
#define UIFIND_HITTEST       0x00000004
#define UIFIND_TOP_FIRST     0x00000008
#define UIFIND_ME_FIRST      0x80000000

/** CDialogLayout stretching �ı�־ */
#define UISTRETCH_NEWGROUP   0x00000001
#define UISTRETCH_NEWLINE    0x00000002
#define UISTRETCH_MOVE_X     0x00000004
#define UISTRETCH_MOVE_Y     0x00000008
#define UISTRETCH_SIZE_X     0x00000010
#define UISTRETCH_SIZE_Y     0x00000020

/** ���ƻ滭�ı�־ */
#define UISTATE_FOCUSED      0x00000001
#define UISTATE_SELECTED     0x00000002
#define UISTATE_DISABLED     0x00000004
#define UISTATE_HOT          0x00000008
#define UISTATE_PUSHED       0x00000010
#define UISTATE_READONLY     0x00000020
#define UISTATE_CAPTURED     0x00000040

/** ��ʱ��ID */
#define MOUSEMOVE_TIMERID	0x00000001

/** ������Ϣ�ṹ�� */
typedef struct tagTFontInfo
{
	HFONT hFont;
	CStdString sFontName;
	int iSize;
	bool bBold;
	bool bUnderline;
	bool bItalic;
	TEXTMETRIC tm;
} TFontInfo;

/** ͼƬ��Ϣ�ṹ�� */
typedef struct tagTImageInfo
{
	HBITMAP hBitmap;
	int nX;
	int nY;
	bool alphaChannel;
	CStdString sResType;
	DWORD dwMask;
} TImageInfo;

/** ϵͳ�¼��Ľṹ�� */
typedef struct tagTEventUI
{
	int Type;
	CControlUI* pSender;
	DWORD dwTimestamp;
	POINT ptMouse;
	TCHAR chKey;
	WORD wKeyState;
	WPARAM wParam;
	LPARAM lParam;
} TEventUI;

/** ����Ӧ�õ�֪ͨ�ṹ�� */
typedef struct tagTNotifyUI 
{
	CStdString sType;
	CControlUI* pSender;
	DWORD dwTimestamp;
	POINT ptMouse;
	WPARAM wParam;
	LPARAM lParam;
} TNotifyUI;

/**  ���ؼ����λ�õĽṹ�� */
typedef struct tagTRelativePosUI
{
	bool bRelative;
	SIZE szParent;
	int nMoveXPercent;
	int nMoveYPercent;
	int nZoomXPercent;
	int nZoomYPercent;
}TRelativePosUI;

/** ֪ͨ�ӿ� */
class INotifyUI
{
public:
	virtual void Notify(TNotifyUI& msg) = 0;
};

/** ��Ϣ�������ӿ� */
class IMessageFilterUI
{
public:
	virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled) = 0;
};

typedef CControlUI* (*LPCREATECONTROL)(LPCTSTR pstrType);

class CULIB_API CPaintManagerUI
{
public:
	CPaintManagerUI();
	~CPaintManagerUI();

public:

	/** ��ʼ�� */
	void Init(HWND hWnd);

	/** ���ý�����±�־λ */
	void NeedUpdate();

	/** InvalidateRect API�ķ�װ */
	void Invalidate(RECT& rcItem);

	/** �õ��豸��� */
	HDC GetPaintDC() const;

	/** �õ����ھ�� */
	HWND GetPaintWindow() const;

	/** �õ����λ�� */
	POINT GetMousePos() const;

	/** �õ��ͻ��������С */
	SIZE GetClientSize() const;

	/** ���úͻ�ȡ���ڳ�ʼ��ʱ��С */
	SIZE GetInitSize();
	void SetInitSize(int cx, int cy);

	/** ��ȡ�����ô��ڱ߿��С */
	RECT& GetSizeBox();
	void SetSizeBox(RECT& rcSizeBox);

	/** ���úͻ�ȡ��������С */
	RECT& GetCaptionRect();
	void SetCaptionRect(RECT& rcCaption);
	
	/** ���úͻ�ȡ����Բ�Ǵ�С */
	SIZE GetRoundCorner() const;
	void SetRoundCorner(int cx, int cy);

	/** ���úͻ�ô�����С��С */
	SIZE GetMinInfo() const;
	void SetMinInfo(int cx, int cy);

	/** ���úͻ�ȡ��������С */
	SIZE GetMaxInfo() const;
	void SetMaxInfo(int cx, int cy);

	/** ���ô���͸���� */
	void SetTransparent(int nOpacity);

	/** ���ñ�����͸���� */
	void SetBackgroundTransparent(bool bTrans);

	/** ���úͻ�ȡ���ڸ�����Ϣ */
	bool IsShowUpdateRect() const;
	void SetShowUpdateRect(bool show);

	/** ���úͻ�ȡ����ʵ����� */
	static HINSTANCE GetInstance();
    static void SetInstance(HINSTANCE hInst);
	
	/** ����ʵ��·�� */
	static CStdString GetInstancePath();
	
	/** ���úͻ�ȡ��ԴDLL */
	static void SetResourceDll(HINSTANCE hInst);
	static HINSTANCE GetResourceDll();

	/** ���úͻ�ȡ��Դ·�� */
	static void SetResourcePath(LPCTSTR pStrPath);
	static const CStdString& GetResourcePath();

	/** ���úͻ�ȡ��Դ���� */
	static void SetResourceZip(LPVOID pVoid, unsigned int len);
	static void SetResourceZip(LPCTSTR pstrZip, bool bCachedResourceZip = false);
	static const CStdString& GetResourceZip();

	/** ��Դ�Ƿ񻺴� */
	static bool IsCachedResourceZip();

	/** �õ���Դ��� */
	static HANDLE GetResourceZipHandle();


	static void GetHSL(short* H, short* S, short* L);
	static void SetHSL(bool bUseHSL, short H, short S, short L); // H:0~360, S:0~200, L:0~200 

	/** ���¼���Ƥ�� */
	static void ReloadSkin();

	/** ���غͻ�ȡ��� */
	static bool LoadPlugin(LPCTSTR pstrModuleName);
	static CStdPtrArray* GetPlugins();
	
	/** ���úͻ�ȡ����Դ����ָ�� */
	bool UseParentResource(CPaintManagerUI* pm);
	CPaintManagerUI* GetParentResource() const;

	/** ���úͻ�ȡ�ǿ���״̬������ɫֵ */
	DWORD GetDefaultDisabledColor() const;
	void SetDefaultDisabledColor(DWORD dwColor);
	
	/** ���úͻ�ȡĬ��������ɫֵ */
	DWORD GetDefaultFontColor() const;
	void SetDefaultFontColor(DWORD dwColor);

	/** ���úͻ�ȡ������������ɫֵ */
	DWORD GetDefaultLinkFontColor() const;
	void SetDefaultLinkFontColor(DWORD dwColor);

	/** ���úͻ�ȡͣ����������ʱ��������ɫ */
	DWORD GetDefaultLinkHoverFontColor() const;
	void SetDefaultLinkHoverFontColor(DWORD dwColor);

	/** ���úͻ�ȡѡ�к󱳾���ɫ */
	DWORD GetDefaultSelectedBkColor() const;
	void SetDefaultSelectedBkColor(DWORD dwColor);

	/** ���úͻ�ȡĬ������ */
	TFontInfo* GetDefaultFontInfo();
	void SetDefaultFont(LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic);
	
	/** �õ������б��������� */
	DWORD GetCustomFontCount() const;

	/** ����һ�����嵽�����б��� */
	HFONT AddFont(LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic);
	
	/** ����һ�����嵽�����б��ָ��λ�� */
	HFONT AddFontAt(int index, LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic);
	
	/** ������ŵõ������б��е����� */
	HFONT GetFont(int index);

	/** ���������Եõ������б��е����� */
	HFONT GetFont(LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic);
	
	/** ��������������б��е�һ�� */
	bool FindFont(HFONT hFont);

	/** �����Բ��������б��е�һ�� */
	bool FindFont(LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic);
	
	/** �õ�������� */
	int GetFontIndex(HFONT hFont);
	int GetFontIndex(LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic);
	
	/** ������Ƴ������б��е�ָ���� */
	bool RemoveFont(HFONT hFont);

	/** ������Ƴ������б��е�ָ���� */
	bool RemoveFontAt(int index);

	/** �Ƴ������б��е������� */
	void RemoveAllFonts();

	/** ����ŵõ������б���������� */
	TFontInfo* GetFontInfo(int index);

	/** ������õ������б���������� */
	TFontInfo* GetFontInfo(HFONT hFont);

	/** ��ȡͼƬ�� ����б��в������δ����ϲ���ƹ������л�ȡ */
	const TImageInfo* GetImage(LPCTSTR bitmap);

	/** ��ȡͼƬ�� �������������ͼƬ�б������һ�� */
	const TImageInfo* GetImageEx(LPCTSTR bitmap, LPCTSTR type = NULL, DWORD mask = 0);

	/** ���ͼƬ��hash�� */
	const TImageInfo* AddImage(LPCTSTR bitmap, LPCTSTR type = NULL, DWORD mask = 0);
	const TImageInfo* AddImage(LPCTSTR bitmap, HBITMAP hBitmap, int iWidth, int iHeight, bool bAlpha);
	
	/** �Ƴ�ͼƬ */
	bool RemoveImage(LPCTSTR bitmap);

	/** �Ƴ�ͼƬ�б��������� */
	void RemoveAllImages();

	/** ���¼�������ͼƬ */
	void ReloadAllImages();

	/** ����ͻ�ȡĬ�������б� */
	void AddDefaultAttributeList(LPCTSTR pStrControlName, LPCTSTR pStrControlAttrList);
	LPCTSTR GetDefaultAttributeList(LPCTSTR pStrControlName) const;
	
	/** ��Ĭ�������б����Ƴ��� */
	bool RemoveDefaultAttributeList(LPCTSTR pStrControlName);

	/** ��ȡĬ�������б��е��� */
	const CStdStringPtrMap& GetDefaultAttribultes() const;

	/** �Ƴ�Ĭ�������б��������� */
	void RemoveAllDefaultAttributeList();

	/** ���ؼ������ӵ���ǰ���ƹ����� */
	bool AttachDialog(CControlUI* pControl);

	/** ��ʼ���ؼ� �ѿؼ����Ƽ��뵽���ƹ����ߵĿؼ���map�� */
	bool InitControls(CControlUI* pControl, CControlUI* pParent = NULL);
	
	/** ���á�ɾ���ؼ� */
	void ReapObjects(CControlUI* pControl);

	/** ��ӿؼ������� */
	bool AddOptionGroup(LPCTSTR pStrGroupName, CControlUI* pControl);

	/** ͨ�����Ƶõ�ѡ���� */
	CStdPtrArray* GetOptionGroup(LPCTSTR pStrGroupName);

	/** �Ƴ����пؼ� �������û�пؼ����Ƴ��� */
	void RemoveOptionGroup(LPCTSTR pStrGroupName, CControlUI* pControl);

	/** �Ƴ�����ѡ���� */
	void RemoveAllOptionGroups();

	/** �õ��ؼ����� */
	CControlUI* GetFocus() const;

	/** �ؼ���ý��� */
	void SetFocus(CControlUI* pControl);
	void SetFocusNeeded(CControlUI* pControl);

	
	bool SetNextTabControl(bool bForward = true);
	bool SetLeftControl();//������ؼ�
	bool SetRightControl();//
	bool SetUpControl();
	bool SetDownControl();


	/** ���ú������ʱ�� */
	bool SetTimer(CControlUI* pControl, UINT nTimerID, UINT uElapse);
	bool KillTimer(CControlUI* pControl, UINT nTimerID);
	void KillTimer(CControlUI* pControl);
	void RemoveAllTimers();

	/** ������ͷ���ꡢ����Ƿ񱻲��� */
	void SetCapture();
	void ReleaseCapture();
	bool IsCaptured();

	/** �����Ƴ�һ��Listener */
	bool AddNotifier(INotifyUI* pControl);
	bool RemoveNotifier(INotifyUI* pControl);

	/** ����һ��֪ͨ */
	void SendNotify(TNotifyUI& Msg, bool bAsync = false);
	void SendNotify(CControlUI* pControl, LPCTSTR pstrMessage, WPARAM wParam = 0, LPARAM lParam = 0, bool bAsync = false);

	/** ������Ƴ�һ��Ԥ����Message Filter */
	bool AddPreMessageFilter(IMessageFilterUI* pFilter);
	bool RemovePreMessageFilter(IMessageFilterUI* pFilter);

	/** ������Ƴ�һ��Message Filter */
	bool AddMessageFilter(IMessageFilterUI* pFilter);
	bool RemoveMessageFilter(IMessageFilterUI* pFilter);

	/** �õ�PostPaint�ؼ����� */
	int GetPostPaintCount() const;

	/** ������Ƴ�һ��PostPaint�ؼ� */
	bool AddPostPaint(CControlUI* pControl);
	bool RemovePostPaint(CControlUI* pControl);

	/** ���ÿؼ���ָ��������λ�� */
	bool SetPostPaintIndex(CControlUI* pControl, int iIndex);

	/** ����ؼ����ӳٴ����б��� */
	void AddDelayedCleanup(CControlUI* pControl);

	/** �õ����ؼ� */
	CControlUI* GetRoot() const;

	/** ���ø��ڵ�ؼ��ĺ���, ��λ��ƥ��ؼ� */
	CControlUI* FindControl(POINT pt) const;

	/** �ڿؼ���map�а�����ƥ��ؼ� */
	CControlUI* FindControl(LPCTSTR pstrName) const;

	/** FindControl(CControlUI*, POINT) ���ø��ؼ��ĺ���, ���ҿؼ� */
	CControlUI* FindSubControlByPoint(CControlUI* pParent, POINT pt) const;
	CControlUI* FindSubControlByName(CControlUI* pParent, LPCTSTR pstrName) const;
	CControlUI* FindSubControlByClass(CControlUI* pParent, LPCTSTR pstrClass, int iIndex = 0);
	CStdPtrArray* FindSubControlsByClass(CControlUI* pParent, LPCTSTR pstrClass);
	CStdPtrArray* GetSubControlsByClass();

	/** ��Ϣѭ�� */
	static void MessageLoop();
	static bool TranslateMessage(const LPMSG pMsg);
	static void Term();

	/** ��Ϣ�������ϢԤ���� */
	bool MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes);
	bool PreMessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes);

private:
	static CControlUI* CALLBACK __FindControlFromNameHash(CControlUI* pThis, LPVOID pData);
	static CControlUI* CALLBACK __FindControlFromCount(CControlUI* pThis, LPVOID pData);
	static CControlUI* CALLBACK __FindControlFromPoint(CControlUI* pThis, LPVOID pData);
	static CControlUI* CALLBACK __FindControlFromTab(CControlUI* pThis, LPVOID pData);
	static CControlUI* CALLBACK __FindControlFromShortcut(CControlUI* pThis, LPVOID pData);
	static CControlUI* CALLBACK __FindControlFromUpdate(CControlUI* pThis, LPVOID pData);
	static CControlUI* CALLBACK __FindControlFromName(CControlUI* pThis, LPVOID pData);
	static CControlUI* CALLBACK __FindControlFromClass(CControlUI* pThis, LPVOID pData);
	static CControlUI* CALLBACK __FindControlsFromClass(CControlUI* pThis, LPVOID pData);
	static CControlUI* CALLBACK __FindControlsFromLeft(CControlUI* pThis, LPVOID pData);//������
	static CControlUI* CALLBACK __FindControlsFromRight(CControlUI* pThis, LPVOID pData);//������
	static CControlUI* CALLBACK __FindControlsFromUp(CControlUI* pThis, LPVOID pData);//������
	static CControlUI* CALLBACK __FindControlsFromDown(CControlUI* pThis, LPVOID pData);//������

private:
	/** ���ƴ��ھ�� */
	HWND m_hWndPaint;
	/** ����DC */
	HDC m_hDcPaint;
	/** ��Ļ�����ڴ�DC */
	HDC m_hDcOffscreen;
	/** ����DC */
	HDC m_hDcBackground;
	/** ��ĻDIB */
	HBITMAP m_hbmpOffscreen;
	/** ����DIB */
	HBITMAP m_hbmpBackground;
	/** �Ƿ���� */
	bool m_bShowUpdateRect;

	/** ���ؼ�ָ�� */
	CControlUI* m_pRoot;
	/** ��ý���ؼ�ָ�� */
	CControlUI* m_pFocus;
	/** ���ͣ���ؼ�ָ�� */
	CControlUI* m_pEventHover;
	/** ����¼��ؼ�ָ�� */
	CControlUI* m_pEventClick;
	/** ��Ӧ�����¼��ؼ�ָ�� */
	CControlUI* m_pEventKey;
	/** ���λ�� */
	POINT m_ptLastMousePos;
	POINT m_ptLastScreenMouse;
	/** ������С���� */
	SIZE m_szMinWindow;
	/** ����������� */
	SIZE m_szMaxWindow;
	/** ��ʼ�����ڴ�С */
	SIZE m_szInitWindowSize;
	/** �����ڱ߾� */
	RECT m_rcSizeBox;
	/** Բ�Ǵ�С */
	SIZE m_szRoundCorner;
	/** �����С */
	RECT m_rcCaption;
	/** �������� */
	RECT m_swPosition;
	/** ��ʱ��ID */
	UINT m_uTimerID;
	/** �Ƿ�Ϊ��һ�� */
	bool m_bFirstLayout;
	/** �Ƿ���Ҫ���� */
	bool m_bUpdateNeeded;
	/** �Ƿ���Ҫ���� */
	bool m_bFocusNeeded;
	/** �Ƿ����m_hDcOffscreen */
	bool m_bOffscreenPaint;
	/** �����Ƿ�͸�� */
	bool m_bAlphaBackground;
	/** �Ƿ�׷����� */
	bool m_bMouseTracking;
	/** �Ƿ񲶻���� */
	bool m_bMouseCapture;
	/** �����ק���ڱ�־ */
	bool m_bMoveFlag;
	
	
	/** ��ʱ���б� */
	CStdPtrArray m_aTimers;
	/** Ԥ������Ϣ�б� */
	CStdPtrArray m_aPreMessageFilters;
	/** ��Ϣ�����б� */
	CStdPtrArray m_aMessageFilters;
	/** PostPaint�ؼ��б� */
	CStdPtrArray m_aPostPaintControls;
	/** �ӳ��ͷſؼ��б� */
	CStdPtrArray m_aDelayedCleanup;
	/** ��Ϣ�첽���� */
	CStdPtrArray m_aAsyncNotify;
	CStdPtrArray m_aFoundControls;
	/** �ؼ�����ϣ�б� */
	CStdStringPtrMap m_mNameHash;
	/** ѡ�����б� */
	CStdStringPtrMap m_mOptionGroup;
	
	/** ��ǰ���ƹ����ߵ���һ����ƹ��� */
	CPaintManagerUI* m_pParentResourcePM;
	/** Ĭ�Ϸǿ���״̬������ɫ */
	DWORD m_dwDefaultDisabledColor;
	/** Ĭ��������ɫ */
	DWORD m_dwDefaultFontColor;
	/** Ĭ��������ɫ */
	DWORD m_dwDefaultLinkFontColor;
	/** Ĭ�����Ư��ʱ������ɫ */
	DWORD m_dwDefaultLinkHoverFontColor;
	/** Ĭ�ϱ�ѡ��󱳾���ɫ */
	DWORD m_dwDefaultSelectedBkColor;
	/** Ĭ��������Ϣ */
	TFontInfo m_DefaultFontInfo;
	/** �����б� */
	CStdPtrArray m_aCustomFonts;

	/** ͼƬ��Դ����ϣ�� */
	CStdStringPtrMap m_mImageHash;
	/** Ĭ�����Թ�ϣ�� */
	CStdStringPtrMap m_DefaultAttrHash;
	
	/** Ӧ�ó������ʵ����� */
	static HINSTANCE m_hInstance;
	/** ��Դ����ʵ����� */
	static HINSTANCE m_hResourceInstance;
	/** ��Դ·�� */
	static CStdString m_pStrResourcePath;
	/** zip����Դ���� */
	static CStdString m_pStrResourceZip;
	static bool m_bCachedResourceZip;
	static HANDLE m_hResourceZip;
	static short m_H;
	static short m_S;
	static short m_L;
	/** Ԥ������Ϣ���� */
	static CStdPtrArray m_aPreMessages;
	static CStdPtrArray m_aPlugins;
	/** Listener �б� */
	static CStdPtrArray m_aNotifiers;
};

}
#endif