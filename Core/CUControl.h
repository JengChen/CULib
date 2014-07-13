/**  
*  @file	CUControl.h   
*  @brief  
*  @author        
*  @date  
*  @version    
*/
#ifndef __CUCONTROL_H__
#define __CUCONTROL_H__

#pragma once
#include "CUDelegate.h"
namespace CULib{

typedef CControlUI* (CALLBACK* FINDCONTROLPROC)(CControlUI*, LPVOID);

/** �ؼ����� */
class CULIB_API CControlUI
{
public:
	CControlUI();
	virtual ~CControlUI();

public:
	/** �õ������ÿؼ����ƣ�����Ϊ�ؼ���ΨһID */
	virtual CStdString GetName() const;
	virtual void SetName(LPCTSTR pstrName);

	/** �õ��ؼ����� */
	virtual LPCTSTR GetClass() const;

	/** �õ��ؼ�ָ�� */
	virtual LPVOID GetInterface(LPCTSTR pstrName);

	/** �õ��ؼ������ͱ�־ */
	virtual UINT GetControlFlags() const;

	/** �ؼ��Ƿ��Ծ */
	virtual bool Activate();

	/** �õ������û��ƹ����� */
	virtual CPaintManagerUI* GetManager() const;
	virtual void SetManager(CPaintManagerUI* pManager, CControlUI* pParent, bool bInit = true);
	
	/** �õ����ؼ� */
	virtual CControlUI* GetParent() const;

	/**�õ������ÿؼ���ʾ���� */
	virtual CStdString GetText() const;
	virtual void SetText(LPCTSTR pstrText);

	/** �õ������ñ��� */
	DWORD GetBkColor() const;
	void SetBkColor(DWORD dwBackColor);
	DWORD GetBkColor2() const;
	void SetBkColor2(DWORD dwBackColor);
	DWORD GetBkColor3() const;
	void SetBkColor3(DWORD dwBackColor);

	/** �õ������ñ���ͼƬ */ 
	LPCTSTR GetBkImage();
	void SetBkImage(LPCTSTR pStrImage);

	/** �õ������ñߵ���ɫ */
	DWORD GetBorderColor() const;
	void SetBorderColor(DWORD dwBorderColor);

	/** �õ������û�ý���ʱ�ߵ���ɫ */
	DWORD GetFocusBorderColor() const;
	void SetFocusBorderColor(DWORD dwBorderColor);
	bool IsColorHSL() const;
	void SetColorHSL(bool bColorHSL);

	/** �õ������ñߵĿ�� */
	int GetBorderSize() const;
	void SetBorderSize(int nSize);

	/** �õ�������Բ�� */
	SIZE GetBorderRound() const;
	void SetBorderRound(SIZE cxyRound);

	/** ����ͼƬ */
	bool DrawImage(HDC hDC, LPCTSTR pStrImage, LPCTSTR pStrModify = NULL);

	/** �õ������ÿؼ�λ�� */
	virtual const RECT& GetPos() const;
	virtual void SetPos(RECT rc);

	/** �õ��ؼ���Ⱥ͸߶� */
	virtual int GetWidth() const;
	virtual int GetHeight() const;

	/** �õ��ؼ��������������λ�� */
	virtual int GetX() const;
	virtual int GetY() const;

	/** ��ú�������߾�,���ϲ㴰�ڻ��� */
	virtual RECT GetPadding() const;
	virtual void SetPadding(RECT rcPadding); 

	/** ʵ�ʴ�Сλ��ʹ��GetPos��ȡ������õ�����Ԥ��Ĳο�ֵ */
	virtual SIZE GetFixedXY() const;   

	/** ��floatΪtrueʱ��Ч */
	virtual void SetFixedXY(SIZE szXY);  

	/** ʵ�ʴ�Сλ��ʹ��GetPos��ȡ������õ�����Ԥ��Ĳο�ֵ */
	virtual int GetFixedWidth() const;       

	/** Ԥ��Ĳο�ֵ */
	virtual void SetFixedWidth(int cx);  

	/** ʵ�ʴ�Сλ��ʹ��GetPos��ȡ������õ�����Ԥ��Ĳο�ֵ */
	virtual int GetFixedHeight() const;     

	/**  Ԥ��Ĳο�ֵ */
	virtual void SetFixedHeight(int cy);  

	/** ��ȡ�����ô�С������ֵ */
	virtual int GetMinWidth() const;
	virtual void SetMinWidth(int cx);
	virtual int GetMaxWidth() const;
	virtual void SetMaxWidth(int cx);
	virtual int GetMinHeight() const;
	virtual void SetMinHeight(int cy);
	virtual int GetMaxHeight() const;
	virtual void SetMaxHeight(int cy);

	/** �������λ�ñ��� */
	virtual void SetRelativePos(SIZE szMove,SIZE szZoom);

	/** ���ø��ؼ���С */
	virtual void SetRelativeParentSize(SIZE sz);

	/** �õ����λ�ñ��� */
	virtual TRelativePosUI GetRelativePos() const;

	/** �Ƿ�ʹ�����λ�� */
	virtual bool IsRelativePos() const;

	/** �����ʾ */
	virtual CStdString GetToolTip() const;
	virtual void SetToolTip(LPCTSTR pstrText);

	/** ��ݼ� */
	virtual TCHAR GetShortcut() const;
	virtual void SetShortcut(TCHAR ch);

	/** �˵� */
	virtual bool IsContextMenuUsed() const;
	virtual void SetContextMenuUsed(bool bMenuUsed);

	/** �û����� */
	virtual const CStdString& GetUserData(); 
	virtual void SetUserData(LPCTSTR pstrText); 
	virtual UINT_PTR GetTag() const; 
	virtual void SetTag(UINT_PTR pTag); 

	/** һЩ��Ҫ������ */
	/** ��ȡ OR ���� �ؼ��Ƿ�ɼ� */
	virtual bool IsVisible() const;
	virtual void SetVisible(bool bVisible = true);
	virtual void SetInternVisible(bool bVisible = true); // �����ڲ����ã���ЩUIӵ�д��ھ������Ҫ��д�˺���
	
	/** ��ȡ OR ���� �ؼ����� */
	virtual bool IsEnabled() const;
	virtual void SetEnabled(bool bEnable = true);

	/** ��ȡ OR ���� �Ƿ�������¼� */
	virtual bool IsMouseEnabled() const;
	virtual void SetMouseEnabled(bool bEnable = true);
	virtual bool IsKeyboardEnabled() const;
	virtual void SetKeyboardEnabled(bool bEnable = true);
	virtual bool IsFocused() const;
	virtual void SetFocus();
	virtual bool IsFloat() const;
	virtual void SetFloat(bool bFloat = true);

	//�������
	virtual bool IsLeft()const;
	virtual bool IsRight()const;
	virtual bool IsUp()const;
	virtual bool IsDown()const;

	/** ���ҿؼ� */
	virtual CControlUI* FindControl(FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags);

	/** ������Ч */
	void Invalidate();

	/** ��ȡ OR ���� �����״̬ */
	bool IsUpdateNeeded() const;
	void NeedUpdate();
	void NeedParentUpdate();
	DWORD GetAdjustColor(DWORD dwColor);

	/** ��ʼ���ؼ��¼���Ӧ, ��SetManager()�б����� */
	virtual void Init();
	virtual void DoInit();

	/** �¼���Ӧ���� */
	virtual void Event(TEventUI& event);
	virtual void DoEvent(TEventUI& event);

	/** ��������, ���ݽ���������ƶ������ĵ���������״̬��Ա������ֵ */
	virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	CControlUI* ApplyAttributeList(LPCTSTR pstrList);

	/** Ԥ���ؼ���С */
	virtual SIZE EstimateSize(SIZE szAvailable);

	/** 
	*�ؼ�����
	*����ѭ�򣺱�����ɫ->����ͼ->״̬ͼ->�ı�->�߿�
	*/
	virtual void DoPaint(HDC hDC, const RECT& rcPaint);

	/** ���Ʊ���ɫ */
	virtual void PaintBkColor(HDC hDC);

	/** ���Ʊ���ͼƬ */
	virtual void PaintBkImage(HDC hDC);

	/** ����״̬���Ʊ���ͼƬ */
	virtual void PaintStatusImage(HDC hDC);

	/** �������� */
	virtual void PaintText(HDC hDC);

	/** ���Ʊ߿� */
	virtual void PaintBorder(HDC hDC);

	/** ��ʱ���� */
	virtual void DoPostPaint(HDC hDC, const RECT& rcPaint);

public:
	CEventSource OnInit;
	CEventSource OnDestroy;
	CEventSource OnSize;
	CEventSource OnEvent;
	CEventSource OnNotify;

protected:
	CPaintManagerUI* m_pManager;
	CControlUI* m_pParent;
	CStdString m_sName;
	bool m_bUpdateNeeded;
	bool m_bMenuUsed;
	RECT m_rcItem;
	RECT m_rcPadding;
	SIZE m_cXY;
	SIZE m_cxyFixed;
	SIZE m_cxyMin;
	SIZE m_cxyMax;
	bool m_bVisible;
	bool m_bInternVisible;
	bool m_bEnabled;
	bool m_bMouseEnabled;
	bool m_bKeyboardEnabled ;
	bool m_bFocused;
	bool m_bFloat;
	bool m_bSetPos; // ��ֹSetPosѭ������
	TRelativePosUI m_tRelativePos;

	CStdString m_sText;
	CStdString m_sToolTip;
	TOOLINFO m_ToolTip;
	HWND m_hwndTooltip;
	bool m_bMouseTracking;
	TCHAR m_chShortcut;
	CStdString m_sUserData;
	UINT_PTR m_pTag;

	DWORD m_dwBackColor;
	DWORD m_dwBackColor2;
	DWORD m_dwBackColor3;
	CStdString m_sBkImage;
	DWORD m_dwBorderColor;
	DWORD m_dwFocusBorderColor;
	bool m_bColorHSL;
	int m_nBorderSize;
	SIZE m_cxyBorderRound;
	RECT m_rcPaint;
};

}

#endif