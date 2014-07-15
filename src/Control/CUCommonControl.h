/**  
*  @file	CUCommonControl.h   
*  @brief  
*  @author        
*  @date  
*  @version    
*/
#ifndef __CUCOMMONCONTROLS_H__
#define __CUCOMMONCONTROLS_H__

#pragma once

namespace CULib {

class CULIB_API CPictureBox:public CControlUI
{
public:
	CPictureBox();
	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);
};

/** ��ǩ�ؼ� */
class CULIB_API CLabelUI : public CControlUI
{
public:
	CLabelUI();

	/** ���ؿؼ��� */
	LPCTSTR GetClass() const;

	/** �õ�����ָ�� */
	LPVOID GetInterface(LPCTSTR pstrName);

	/** ��ȡ OR ���� �ı���ʽ */
	void SetTextStyle(UINT uStyle);
	UINT GetTextStyle() const;

	/** ��ȡ OR ���� ����״̬������ɫ */
	void SetTextColor(DWORD dwTextColor);
	DWORD GetTextColor() const;

	/** ��ȡ OR ���� ������״̬������ɫ */
	void SetDisabledTextColor(DWORD dwTextColor);
	DWORD GetDisabledTextColor() const;

	/** ��ȡ OR ���� �ؼ�ʹ�õ�����, ��Ӧ�������б��е���� */
	void SetFont(int index);
	int GetFont() const;
	 /** ��ȡ OR ���� ������߿�֮�������� */
	RECT GetTextPadding() const;
	void SetTextPadding(RECT rc);

	/** ��ȡ OR ���� �Ƿ�ʹ����Ƕhtml��Ǹ�ʽ */
	bool IsShowHtml();
	void SetShowHtml(bool bShowHtml = true);

	/** Ԥ���ؼ���С */
	SIZE EstimateSize(SIZE szAvailable);
	void DoEvent(TEventUI& event);
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	void PaintText(HDC hDC);

protected:
	DWORD m_dwTextColor;
	DWORD m_dwDisabledTextColor;
	int m_iFont;
	UINT m_uTextStyle;
	RECT m_rcTextPadding;
	bool m_bShowHtml;
	TOOLINFO m_ToolTip;
	HWND m_hwndTooltip;
	bool m_bMouseTracking;
};

/////////////////////////////////////////////////////////////////////////////////////
//

class CULIB_API CButtonUI : public CLabelUI
{
public:
	CButtonUI();

	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);
	UINT GetControlFlags() const;

	/** 
	*���� ���ť�ؼ�
	*ʵ�� �ж��Ƿ��Ծ�����Ծ����֪ͨ
	*/
	bool Activate();

	/** ���ð�ť�ؼ��Ƿ���� */
	void SetEnabled(bool bEnable = true);
	void DoEvent(TEventUI& event);

	/** ��ȡ OR ���� ����״̬�°�ť����ͼƬ */
	LPCTSTR GetNormalImage();
	void SetNormalImage(LPCTSTR pStrImage);

	/** ��ȡ OR ���� �������ʱ��ť����ͼƬ */
	LPCTSTR GetHotImage();
	void SetHotImage(LPCTSTR pStrImage);

	/** ��ȡ OR ���� ��ť������ʱ����ͼƬ */
	LPCTSTR GetPushedImage();
	void SetPushedImage(LPCTSTR pStrImage);

	/** ��ȡ OR ���� ��ť��ý���ʱ����ͼƬ */
	LPCTSTR GetFocusedImage();
	void SetFocusedImage(LPCTSTR pStrImage);

	/** ��ȡ OR ���� �ǿ���״̬�°�ť����ͼƬ */
	LPCTSTR GetDisabledImage();
	void SetDisabledImage(LPCTSTR pStrImage);

	/** ����/��ȡ �����ʱ�ı�����ɫ */
	void SetHotTextColor(DWORD dwColor);
	DWORD GetHotTextColor() const;

	/** ����/��ȡ ��ť����ʱ�ı���ɫ */
	void SetPushedTextColor(DWORD dwColor);
	DWORD GetPushedTextColor() const;

	/** ����/��ȡ ��ť��ý���ʱ�ı���ɫ */
	void SetFocusedTextColor(DWORD dwColor);
	DWORD GetFocusedTextColor() const;
	SIZE EstimateSize(SIZE szAvailable);
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	void PaintText(HDC hDC);
	void PaintStatusImage(HDC hDC);

protected:
	UINT m_uButtonState;

	DWORD m_dwHotTextColor;
	DWORD m_dwPushedTextColor;
	DWORD m_dwFocusedTextColor;

	CStdString m_sNormalImage;
	CStdString m_sHotImage;
	CStdString m_sPushedImage;
	CStdString m_sFocusedImage;
	CStdString m_sDisabledImage;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class CULIB_API COptionUI : public CButtonUI
{
public:
	COptionUI();
	~COptionUI();

	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);

	void SetManager(CPaintManagerUI* pManager, CControlUI* pParent, bool bInit = true);

	bool Activate();
	void SetEnabled(bool bEnable = true);

	/** ��ȡ OR ���� ѡ��״̬����ͼƬ */
	LPCTSTR GetSelectedImage();
	void SetSelectedImage(LPCTSTR pStrImage);

	/** ��ȡ OR ����ѡ���ı���ɫ */
	void SetSelectedTextColor(DWORD dwTextColor);
	DWORD GetSelectedTextColor();

	/** ��ȡ OR ���� ǰ��ͼƬ */
	LPCTSTR GetForeImage();
	void SetForeImage(LPCTSTR pStrImage);

	/** ��ȡ OR ���� ѡ�������� */
	LPCTSTR GetGroup() const;
	void SetGroup(LPCTSTR pStrGroupName = NULL);

	/** ��ȡ OR ���� ѡ���Ƿ���ѡ��״̬ */
	bool IsSelected() const;
	void Selected(bool bSelected);

	SIZE EstimateSize(SIZE szAvailable);
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	void PaintStatusImage(HDC hDC);
	void PaintText(HDC hDC);

protected:
	bool m_bSelected;
	CStdString m_sGroupName;

	DWORD m_dwSelectedTextColor;

	CStdString m_sSelectedImage;
	CStdString m_sForeImage;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class CULIB_API CTextUI : public CLabelUI
{
public:
	CTextUI();
	~CTextUI();

	LPCTSTR GetClass() const;
	UINT GetControlFlags() const;
	LPVOID GetInterface(LPCTSTR pstrName);

	/** �õ���ǰ�ؼ���ָ����ŵĳ��ı������� */
	CStdString* GetLinkContent(int iIndex);

	void DoEvent(TEventUI& event);
	SIZE EstimateSize(SIZE szAvailable);

	void PaintText(HDC hDC);

protected:
	enum { MAX_LINK = 8 };

	/** ���ı����� */
	int m_nLinks;

	/** ���ı����� */
	RECT m_rcLinks[MAX_LINK];

	/** ���ı��������� */
	CStdString m_sLinks[MAX_LINK];
	int m_nHoverLink;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class CULIB_API CProgressUI : public CLabelUI
{
public:
	CProgressUI();

	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);

	/** ��ȡ OR ���� ���������� */
	bool IsHorizontal();
	void SetHorizontal(bool bHorizontal = true);

	/** ��ȡ OR ���� ��Сֵ */
	int GetMinValue() const;
	void SetMinValue(int nMin);

	/** ��ȡ OR ���� ���ֵ */
	int GetMaxValue() const;
	void SetMaxValue(int nMax);

	/** ��ȡ OR ���� ��ǰֵ */
	int GetValue() const;
	void SetValue(int nValue);

	/** ��ȡ OR ���� ǰ��ͼ */
	LPCTSTR GetForeImage() const;
	void SetForeImage(LPCTSTR pStrImage);

	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	void PaintStatusImage(HDC hDC);

protected:
	/** �������ؼ����� */
	bool m_bHorizontal;
	int m_nMax;
	int m_nMin;
	int m_nValue;

	CStdString m_sForeImage;
	CStdString m_sForeImageModify;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class CULIB_API CSliderUI : public CProgressUI
{
public:
	CSliderUI();

	LPCTSTR GetClass() const;
	UINT GetControlFlags() const;
	LPVOID GetInterface(LPCTSTR pstrName);

	/** ���û���ؼ��Ƿ���� */
	void SetEnabled(bool bEnable = true);

	/** ��ȡ OR ���û��鲽�� */
	int GetChangeStep();
	void SetChangeStep(int step);

	/** ��ȡ OR ���û����С */
	void SetThumbSize(SIZE szXY);
	RECT GetThumbRect() const;

	/** ��ȡ OR ���û���ͼ */
	LPCTSTR GetThumbImage() const;
	void SetThumbImage(LPCTSTR pStrImage);
	
	/** ��ȡ OR �����������״̬����ͼ */
	LPCTSTR GetThumbHotImage() const;
	void SetThumbHotImage(LPCTSTR pStrImage);

	/** ��ȡ OR ���û��鰴��״̬����ͼ */
	LPCTSTR GetThumbPushedImage() const;
	void SetThumbPushedImage(LPCTSTR pStrImage);

	void DoEvent(TEventUI& event);
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	void PaintStatusImage(HDC hDC);

protected:
	SIZE m_szThumb;
	
	/** �ؼ�״̬ */
	UINT m_uButtonState;

	/** ���� */
	int m_nStep;

	/** ����״̬�����ͼ */
	CStdString m_sThumbImage;

	/** �������״̬����ͼ */
	CStdString m_sThumbHotImage;

	/** ����״̬����ͼ */
	CStdString m_sThumbPushedImage;

	CStdString m_sImageModify;
};

/////////////////////////////////////////////////////////////////////////////////////
//

class CEditWnd;

class CULIB_API CEditUI : public CLabelUI
{
	friend CEditWnd;
public:
	CEditUI();

	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);
	
	/** �õ��ؼ������ͱ�־ */
	UINT GetControlFlags() const;

	/** ���ñ༭��ؼ��Ƿ���� */
	void SetEnabled(bool bEnable = true);

	/** �����ı� */
	void SetText(LPCTSTR pstrText);

	/** ���������ı��������� */
	void SetMaxChar(UINT uMax);

	/** ��ȡ��������ı����� */
	UINT GetMaxChar();

	/** ���úͻ�ȡֻ��ģʽ */
	void SetReadOnly(bool bReadOnly);
	bool IsReadOnly() const;

	/** ��ȡ����������༭��ģʽ */
	void SetPasswordMode(bool bPasswordMode);
	bool IsPasswordMode() const;

	/** ���úͻ�ȡ����ģʽ��ʾ�ַ� */
	void SetPasswordChar(TCHAR cPasswordChar);
	TCHAR GetPasswordChar() const;

	/** ��ȡ OR ��������״̬ͼ */
	LPCTSTR GetNormalImage();
	void SetNormalImage(LPCTSTR pStrImage);

	/** ��ȡ OR ��������״̬ͼ */
	LPCTSTR GetHotImage();
	void SetHotImage(LPCTSTR pStrImage);

	/** ��ȡ OR ���û�ý���״̬ͼ */
	LPCTSTR GetFocusedImage();
	void SetFocusedImage(LPCTSTR pStrImage);

	/** ��ȡ OR ���÷ǿ���״̬ͼ */
	LPCTSTR GetDisabledImage();
	void SetDisabledImage(LPCTSTR pStrImage);

	/** ��ȡ OR ����ԭ���༭�򱳾�ɫ */
	void SetNativeEditBkColor(DWORD dwBkColor);
	DWORD GetNativeEditBkColor() const;

	/** �õ��༭��λ�� */
	void SetPos(RECT rc);

	/** ���ÿɼ�״̬ */
	void SetVisible(bool bVisible = true);
	void SetInternVisible(bool bVisible = true);
	SIZE EstimateSize(SIZE szAvailable);
	void DoEvent(TEventUI& event);
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	void PaintStatusImage(HDC hDC);
	void PaintText(HDC hDC);

protected:
	/** ԭ���༭�򴰿� */
	CEditWnd* m_pWindow;

	/** �ı��������� */
	UINT m_uMaxChar;

	/** ֻ����ʽ */
	bool m_bReadOnly;

	/** ��ʾ����ģʽ */
	bool m_bPasswordMode;

	/** ����ģʽ��ʾ���ַ� */
	TCHAR m_cPasswordChar;

	/** �༭��״̬ */
	UINT m_uButtonState;

	/** ��ͬ״̬�ı���ͼ */
	CStdString m_sNormalImage;
	CStdString m_sHotImage;
	CStdString m_sFocusedImage;
	CStdString m_sDisabledImage;

	/** �༭�򱳾�ɫ */
	DWORD m_dwEditbkColor;
};

/////////////////////////////////////////////////////////////////////////////////////
//

/** �������ؼ� */
class CULIB_API CScrollBarUI : public CControlUI
{
public:
	CScrollBarUI();

	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);

	/** �õ������ù�����ӵ���� */
	CContainerUI* GetOwner() const;
	void SetOwner(CContainerUI* pOwner);

	void SetVisible(bool bVisible = true);
	
	/** ���ù������Ƿ���� */
	void SetEnabled(bool bEnable = true);
	void SetFocus();

	/** ��ȡ�����ù��������� */
	bool IsHorizontal();
	void SetHorizontal(bool bHorizontal = true);

	/** �õ������ù�������Χ */ 
	int GetScrollRange() const;
	void SetScrollRange(int nRange);

	/** �õ������ù�����λ�� */
	int GetScrollPos() const;
	void SetScrollPos(int nPos);

	/** �õ������ò�����С */
	int GetLineSize() const;
	void SetLineSize(int nSize);

	/** ��ȡ OR ���� �ϻ���λ�õİ�ť��ʾ״̬ */
	bool GetShowButton1();
	void SetShowButton1(bool bShow);

	/** ��ȡ OR ���� �ϻ���λ�õ�����״̬ͼ */
	LPCTSTR GetButton1NormalImage();
	void SetButton1NormalImage(LPCTSTR pStrImage);

	/** ��ȡ OR ���� �ϻ���λ�õ�����״̬ͼ */
	LPCTSTR GetButton1HotImage();
	void SetButton1HotImage(LPCTSTR pStrImage);

	/** ��ȡ OR ���� �ϻ���λ�õİ���״̬ͼ  */
	LPCTSTR GetButton1PushedImage();
	void SetButton1PushedImage(LPCTSTR pStrImage);

	/** ��ȡ OR ���� �ϻ���λ�õķǿ���״̬ͼ */
	LPCTSTR GetButton1DisabledImage();
	void SetButton1DisabledImage(LPCTSTR pStrImage);

	/** ��ȡ OR ���� �»���λ�õİ�ť��ʾ״̬ */
	bool GetShowButton2();
	void SetShowButton2(bool bShow);

	/** ��ȡ OR ���� �»���λ�õ�����״̬ͼ */
	LPCTSTR GetButton2NormalImage();
	void SetButton2NormalImage(LPCTSTR pStrImage);

	/** ��ȡ OR ���� �»���λ�õ�����״̬ͼ */
	LPCTSTR GetButton2HotImage();
	void SetButton2HotImage(LPCTSTR pStrImage);

	/** ��ȡ OR ���� �»���λ�õİ���״̬ͼ  */
	LPCTSTR GetButton2PushedImage();
	void SetButton2PushedImage(LPCTSTR pStrImage);

	/** ��ȡ OR ���� �»���λ�õķǿ���״̬ͼ */
	LPCTSTR GetButton2DisabledImage();
	void SetButton2DisabledImage(LPCTSTR pStrImage);

	/** ��ȡ OR ���� ������ ����״̬ͼ */
	LPCTSTR GetThumbNormalImage();
	void SetThumbNormalImage(LPCTSTR pStrImage);

	/** ��ȡ OR ���� ������ ����״̬ͼ */
	LPCTSTR GetThumbHotImage();
	void SetThumbHotImage(LPCTSTR pStrImage);

	/** ��ȡ OR ���� ������ ����״̬ͼ */
	LPCTSTR GetThumbPushedImage();
	void SetThumbPushedImage(LPCTSTR pStrImage);

	/** ��ȡ OR ���� ������ �ǿ���״̬ͼ */
	LPCTSTR GetThumbDisabledImage();
	void SetThumbDisabledImage(LPCTSTR pStrImage);

	/** ��ȡ OR ���� �����켣 ����״̬ͼ */
	LPCTSTR GetRailNormalImage();
	void SetRailNormalImage(LPCTSTR pStrImage);

	/** ��ȡ OR ���� �����켣 ����״̬ͼ */
	LPCTSTR GetRailHotImage();
	void SetRailHotImage(LPCTSTR pStrImage);

	/** ��ȡ OR ���� �����켣 ����״̬ͼ */
	LPCTSTR GetRailPushedImage();
	void SetRailPushedImage(LPCTSTR pStrImage);

	/** ��ȡ OR ���� �����켣 �ǿ���״̬ͼ */
	LPCTSTR GetRailDisabledImage();
	void SetRailDisabledImage(LPCTSTR pStrImage);

	/** ��ȡ OR ���� ������ ����ͼ */
	LPCTSTR GetBkNormalImage();
	void SetBkNormalImage(LPCTSTR pStrImage);

	/** ��ȡ OR ���� ������ ����״̬ͼ */
	LPCTSTR GetBkHotImage();
	void SetBkHotImage(LPCTSTR pStrImage);

	/** ��ȡ OR ���� ������ ����״̬ͼ */
	LPCTSTR GetBkPushedImage();
	void SetBkPushedImage(LPCTSTR pStrImage);

	/** ��ȡ OR ���� ������ �ǿ���״̬ͼ */
	LPCTSTR GetBkDisabledImage();
	void SetBkDisabledImage(LPCTSTR pStrImage);

	void SetPos(RECT rc);
	void DoEvent(TEventUI& event);
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	void DoPaint(HDC hDC, const RECT& rcPaint);

	void PaintBk(HDC hDC);

	/** �����ϻ�����İ�ť */
	void PaintButton1(HDC hDC);
	/** �����»���λ�õİ�ť */
	void PaintButton2(HDC hDC);

	/** ���ƹ����� */
	void PaintThumb(HDC hDC);
	/** ���ƹ����켣 */
	void PaintRail(HDC hDC);

protected:

	enum { 
		/** ������Ĭ�ϴ�С */
		DEFAULT_SCROLLBAR_SIZE = 16,
		/** Ĭ�ϼ�ʱ��id */
		DEFAULT_TIMERID = 10,
	};
	/** ���������ݷ��� */
	bool m_bHorizontal;
	/** ��Χ */
	int m_nRange;
	/** ������λ�� */
	int m_nScrollPos;
	/** ���� */
	int m_nLineSize;
	/** ������ӵ���� */
	CContainerUI* m_pOwner;
	/** ���λ�� */
	POINT ptLastMouse;
	/** ������λ�� */
	int m_nLastScrollPos;
	/** ������ƫ���� δʹ�� */
	int m_nLastScrollOffset;
	int m_nScrollRepeatDelay;

	/** ����״̬��ͼ�� */
	CStdString m_sBkNormalImage;
	CStdString m_sBkHotImage;
	CStdString m_sBkPushedImage;
	CStdString m_sBkDisabledImage;

	bool m_bShowButton1;
	RECT m_rcButton1;
	UINT m_uButton1State;
	CStdString m_sButton1NormalImage;
	CStdString m_sButton1HotImage;
	CStdString m_sButton1PushedImage;
	CStdString m_sButton1DisabledImage;

	bool m_bShowButton2;
	RECT m_rcButton2;
	UINT m_uButton2State;
	CStdString m_sButton2NormalImage;
	CStdString m_sButton2HotImage;
	CStdString m_sButton2PushedImage;
	CStdString m_sButton2DisabledImage;

	RECT m_rcThumb;
	UINT m_uThumbState;
	CStdString m_sThumbNormalImage;
	CStdString m_sThumbHotImage;
	CStdString m_sThumbPushedImage;
	CStdString m_sThumbDisabledImage;

	CStdString m_sRailNormalImage;
	CStdString m_sRailHotImage;
	CStdString m_sRailPushedImage;
	CStdString m_sRailDisabledImage;

	CStdString m_sImageModify;
};

} 

#endif 

