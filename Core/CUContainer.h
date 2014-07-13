/**  
*  @file	CUContainer.h   
*  @brief  
*  @author        
*  @date  
*  @version    
*/
#ifndef __CUCONTAINER_H__
#define __CUCONTAINER_H__

namespace CULib{

class IContainerUI
{
public:
	virtual CControlUI* GetItemAt(int iIndex) const = 0;
	virtual int GetItemIndex(CControlUI* pControl) const  = 0;
	virtual bool SetItemIndex(CControlUI* pControl, int iIndex)  = 0;
	virtual int GetCount() const = 0;
	virtual bool Add(CControlUI* pControl,CControlUI* pParent=NULL) = 0;
	virtual bool AddAt(CControlUI* pControl, int iIndex)  = 0;
	virtual bool Remove(CControlUI* pControl) = 0;
	virtual bool RemoveAt(int iIndex)  = 0;
	virtual void RemoveAll() = 0;
};

class CScrollBarUI;

class CULIB_API CContainerUI : public CControlUI, public IContainerUI
{
public:

	CContainerUI();
	virtual ~CContainerUI();

public:
	/** �õ��ؼ�����*/
	LPCTSTR GetClass() const;
	/** �õ��ؼ�ָ�� */
	LPVOID GetInterface(LPCTSTR pstrName);

	/** �õ������пؼ��� */
	CControlUI* GetItemAt(int iIndex) const;
	/** ����Ż�ȡ�����������пؼ��� */
	int GetItemIndex(CControlUI* pControl) const;
	bool SetItemIndex(CControlUI* pControl, int iIndex);
	/** ��ȡ�����ؼ����� */
	int GetCount() const;
	/** ����һ���ؼ��������� */
	bool Add(CControlUI* pControl,CControlUI* pParent=NULL);
	bool AddAt(CControlUI* pControl, int iIndex);
	/** ɾ�������пؼ��� */
	bool Remove(CControlUI* pControl);
	/** ɾ��ָ����ŵ������ؼ��� */
	bool RemoveAt(int iIndex);
	void RemoveAll();

	void DoEvent(TEventUI& event);
	/** ���������Ƿ�ɼ� */
	void SetVisible(bool bVisible = true);
	void SetInternVisible(bool bVisible = true);
	/** �����Ƿ�������¼� */
	void SetMouseEnabled(bool bEnable = true);

	/** ��ȡ OR �����ڱ߾࣬�൱�����ÿͻ��� */
	virtual RECT GetInset() const;
	virtual void SetInset(RECT rcInset); 
	/** ��ȡ�������ӿؼ���� */
	virtual int GetChildPadding() const;
	virtual void SetChildPadding(int iPadding);
	/** ��ȡ OR ���������ڿؼ����Ƿ��Զ��ݻ� */
	virtual bool IsAutoDestroy() const;
	virtual void SetAutoDestroy(bool bAuto);
	/** ��ȡ OR �������������Ƿ��ӳٴݻ� */
	virtual bool IsDelayedDestroy() const;
	virtual void SetDelayedDestroy(bool bDelayed);
	/** ��ȡ OR ���������пؼ��Ƿ���Ӧ����¼� */
	virtual bool IsMouseChildEnabled() const;
	virtual void SetMouseChildEnabled(bool bEnable = true);
	
	/** ������������һ����ѡ�� */
	virtual int FindSelectable(int iIndex, bool bForward = true) const;

	void SetPos(RECT rc);
	void DoPaint(HDC hDC, const RECT& rcPaint);

	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	void SetManager(CPaintManagerUI* pManager, CControlUI* pParent, bool bInit = true);
	CControlUI* FindControl(FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags);

	/** ��ȡ�����ù�����λ�� */
	virtual SIZE GetScrollPos() const;
	virtual void SetScrollPos(SIZE szPos);
	/** ��ȡ��������Χ */
	virtual SIZE GetScrollRange() const;
	/** ��ͬ������ݹ����� */
	virtual void LineUp();
	virtual void LineDown();
	virtual void PageUp();
	virtual void PageDown();
	virtual void HomeUp();
	virtual void EndDown();
	virtual void LineLeft();
	virtual void LineRight();
	virtual void PageLeft();
	virtual void PageRight();
	virtual void HomeLeft();
	virtual void EndRight();
	/** ���������� */
	virtual void EnableScrollBar(bool bEnableVertical = true, bool bEnableHorizontal = false);
	/** �õ�����ͺ�������� */
	virtual CScrollBarUI* GetVerticalScrollBar() const;
	virtual CScrollBarUI* GetHorizontalScrollBar() const;

protected:
	/** ��������λ�� */
	virtual void SetFloatPos(int iIndex);
	/** ��������� */
	virtual void ProcessScrollBar(RECT rc, int cxRequired, int cyRequired);

protected:
	/** �����еĿռ��� */
	CStdPtrArray m_items;
	/** �����ڱ߾� �ͻ��� */
	RECT m_rcInset;
	/** �ؼ����� */
	int m_iChildPadding;
	/** �Զ��ݻ��ӿؼ� */
	bool m_bAutoDestroy;
	bool m_bDelayedDestroy;
	/** ������ */
	bool m_bMouseChildEnabled;
	/** �Ƿ������ */
	bool m_bScrollProcess; 
	/** �������������� */
	CScrollBarUI* m_pVerticalScrollBar;
	CScrollBarUI* m_pHorizontalScrollBar;

	/** ָ��ǰ������ǰһ���ͺ�һ������ */
	CContainerUI* m_prevContainer;
	CContainerUI* m_nextContainer;
	
};

/** ���򲼾ֵ������ؼ� */
class CULIB_API CVerticalLayoutUI : public CContainerUI
{
public:
	CVerticalLayoutUI();

	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);
	UINT GetControlFlags() const;

	/** ���úͻ�ȡ�ָ����߶� */
	void SetSepHeight(int iHeight);
	int GetSepHeight() const;
	/** ���úͻ�ȡˢ��ģʽ,����ˢ�»���ʱˢ�� */
	void SetSepImmMode(bool bImmediately);
	bool IsSepImmMode() const;
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	void DoEvent(TEventUI& event);

	void SetPos(RECT rc);
	void DoPostPaint(HDC hDC, const RECT& rcPaint);
	/** ��ȡ��ˢ�µ����� */
	RECT GetThumbRect(bool bUseNew = false) const;

protected:
	/** �ָ����߶� */
	int m_iSepHeight;
	/** �����ؼ�״̬ */
	UINT m_uButtonState;
	/** ���λ�� */
	POINT ptLastMouse;
	/** ˢ������ */
	RECT m_rcNewPos;
	/** ����ˢ��ģʽ */
	bool m_bImmMode;
};

class CULIB_API CHorizontalLayoutUI : public CContainerUI
{
public:
	CHorizontalLayoutUI();

	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);
	UINT GetControlFlags() const;
	/** ��ȡ OR ���÷ָ������ */
	void SetSepWidth(int iWidth);
	int GetSepWidth() const;
	/** ��ȡ OR ����ˢ��ģʽ */
	void SetSepImmMode(bool bImmediately);
	bool IsSepImmMode() const;
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	void DoEvent(TEventUI& event);

	void SetPos(RECT rc);
	void DoPostPaint(HDC hDC, const RECT& rcPaint);

	/** ��ȡˢ������ */
	RECT GetThumbRect(bool bUseNew = false) const;

protected:
	/** �ָ������*/
	int m_iSepWidth;
	/** �ؼ�״̬ */
	UINT m_uButtonState;
	/** ���λ�� */
	POINT ptLastMouse;
	/** ����λ�� */
	RECT m_rcNewPos;
	/** ����ˢ��ģʽ */
	bool m_bImmMode;
};
/////////////////////////////////////////////////////////////////////////////////////
//
class CULIB_API CDialogLayoutUI : public CContainerUI
{
public:
	CDialogLayoutUI();

	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);

	/** ��������ģʽ */
	void SetStretchMode(CControlUI* pControl, UINT uMode);

	void SetPos(RECT rc);
	SIZE EstimateSize(SIZE szAvailable);
	/** ���¼������� */
	RECT RecalcArea();   

protected:  
	/** ����ģʽ�ṹ */
	typedef struct 
	{
		CControlUI* pControl;
		UINT uMode;
		RECT rcItem;
	} STRETCHMODE;

	/** ����ģʽ�б� */
	CStdValArray m_aModes;
};

/////////////////////////////////////////////////////////////////////////////////////
//

class CULIB_API CTileLayoutUI : public CContainerUI
{
public:
	CTileLayoutUI();

	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);

	/** �����������������ڿؼ���λ�� */
	void SetPos(RECT rc);

	/** ��ȡ OR �����ӿؼ���С */
	SIZE GetItemSize() const;
	void SetItemSize(SIZE szItem);
	/** ��ȡ OR ���� �������� */
	int GetColumns() const;
	void SetColumns(int nCols);

	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

protected:
	SIZE m_szItem;
	int m_nColumns;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class CULIB_API CTabLayoutUI : public CContainerUI
{
public:
	CTabLayoutUI();

	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);

	/** ����������ӿؼ����������ѡ����������Ϊ�ǿɼ� */
	bool Add(CControlUI* pControl,CControlUI* pParent=NULL);
	bool AddAt(CControlUI* pControl, int iIndex);
	/** �Ƴ��ؼ� */
	bool Remove(CControlUI* pControl);
	void RemoveAll();
	/** �õ���ǰѡ�еĿؼ� */
	int GetCurSel() const;
	/** ���ÿؼ���Ϊѡ���� */
	bool SelectItem(int iIndex);

	/** ������������ؼ�λ�� */
	void SetPos(RECT rc);

	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

protected:
	int m_iCurSel;
};

}

#endif