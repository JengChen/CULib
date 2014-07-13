/**  
*  @file    CUlist.h
*  @brief  
*  @author        
*  @date  
*  @version    
*/
#ifndef __CULIST_H__
#define __CULIST_H__

#pragma once
#include <vector>
#include <math.h>

inline double CalculateDelay(double state) {
	return pow(state, 2);
}

namespace CULib {

	class CListHeaderUI;

#define UILIST_MAX_COLUMNS 32

typedef struct tagTListInfoUI
{
	int nColumns;
	RECT rcColumn[UILIST_MAX_COLUMNS];
	int nFont;
	UINT uTextStyle;
	RECT rcTextPadding;
	DWORD dwTextColor;
	DWORD dwBkColor;
	CStdString sBkImage;
	bool bAlternateBk;
	DWORD dwSelectedTextColor;
	DWORD dwSelectedBkColor;
	CStdString sSelectedImage;
	DWORD dwHotTextColor;
	DWORD dwHotBkColor;
	CStdString sHotImage;
	DWORD dwDisabledTextColor;
	DWORD dwDisabledBkColor;
	CStdString sDisabledImage;
	DWORD dwLineColor;
	bool bShowHtml;
	bool bMultiExpandable;
} TListInfoUI;


/////////////////////////////////////////////////////////////////////////////////////
//

class IListCallbackUI
{
public:
	virtual LPCTSTR GetItemText(CControlUI* pList, int iItem, int iSubItem) = 0;
};

class IListOwnerUI
{
public:
	virtual TListInfoUI* GetListInfo() = 0;
	virtual int GetCurSel() const = 0;
	virtual bool SelectItem(int iIndex, bool bTakeFocus = false) = 0;
	virtual void DoEvent(TEventUI& event) = 0;
};

class IListUI : public IListOwnerUI
{
public:
	virtual CListHeaderUI* GetHeader() const = 0;
	virtual CContainerUI* GetList() const = 0;
	virtual IListCallbackUI* GetTextCallback() const = 0;
	virtual void SetTextCallback(IListCallbackUI* pCallback) = 0;
	virtual bool ExpandItem(int iIndex, bool bExpand = true) = 0;
	virtual int GetExpandedItem() const = 0;
};

class IListItemUI
{
public:
	/** �õ������������ */
	virtual int GetIndex() const = 0;
	virtual void SetIndex(int iIndex) = 0;
	/** ��ȡ�������б�ӵ���� */
	virtual IListOwnerUI* GetOwner() = 0;
	virtual void SetOwner(CControlUI* pOwner) = 0;
	/** ��ȡ�����ñ�ѡ�� */
	virtual bool IsSelected() const = 0;
	virtual bool Select(bool bSelect = true) = 0;
	/** ��ȡ�������Ƿ�չ���� */
	virtual bool IsExpanded() const = 0;
	virtual bool Expand(bool bExpand = true) = 0;
	/** ��������ı� */
	virtual void DrawItemText(HDC hDC, const RECT& rcItem) = 0;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class CListBodyUI;
class CListHeaderUI;

class CULIB_API CListUI : public CVerticalLayoutUI, public IListUI
{
public:
	CListUI();

	LPCTSTR GetClass() const;
	UINT GetControlFlags() const;
	LPVOID GetInterface(LPCTSTR pstrName);

	/** ��ȡ�����ù������Ƿ�ѡ�� */
	bool GetScrollSelect();
	void SetScrollSelect(bool bScrollSelect);
	/** �õ���ǰѡ���� */
	int GetCurSel() const;
	/** ���õ�ǰѡ���� �������Ƿ��ý��� */
	bool SelectItem(int iIndex, bool bTakeFocus = false);

	/** �õ��б�ͷָ�� */
	CListHeaderUI* GetHeader() const;  
	/** �õ��б���ָ�� */
	CContainerUI* GetList() const;
	/** �õ��б����� */
	TListInfoUI* GetListInfo();

	/** ����Ż�ȡ�б��� */
	CControlUI* GetItemAt(int iIndex) const;
	/** ���ؼ�ָ���ȡ��� */
	int GetItemIndex(CControlUI* pControl) const;
	/** �����б��� */
	bool SetItemIndex(CControlUI* pControl, int iIndex);
	/** �õ��б����� */
	int GetCount() const;
	/** ����һ���ؼ� */
	bool Add(CControlUI* pControl,CControlUI* pParent=NULL);
	bool AddAt(CControlUI* pControl, int iIndex);
	/** �Ƴ��ؼ� */
	bool Remove(CControlUI* pControl);
	bool RemoveAt(int iIndex);
	void RemoveAll();

	/** ȷ����ʾ��iIndex�� */
	void EnsureVisible(int iIndex);
	/** ���� */
	void Scroll(int dx, int dy);

	/** ��ȡ�������ӿؼ���� */
	int GetChildPadding() const;
	void SetChildPadding(int iPadding);

	/** �������� */
	void SetItemFont(int index);
	/** �����ı����� */
	void SetItemTextStyle(UINT uStyle);
	/** �����ı���� */
	void SetItemTextPadding(RECT rc);
	/** �����ı�ɫ ����ɫ ����ͼ */
	void SetItemTextColor(DWORD dwTextColor);
	void SetItemBkColor(DWORD dwBkColor);
	void SetItemBkImage(LPCTSTR pStrImage);

	/** ���ñ��ñ������� */
	void SetAlternateBk(bool bAlternateBk);
	/** ����ѡ�����ı�ɫ ����ɫ ����ͼ*/
	void SetSelectedItemTextColor(DWORD dwTextColor);
	void SetSelectedItemBkColor(DWORD dwBkColor);
	void SetSelectedItemImage(LPCTSTR pStrImage); 

	/** ���û�Ծ���ı�ɫ ����ɫ ����ͼ*/
	void SetHotItemTextColor(DWORD dwTextColor);
	void SetHotItemBkColor(DWORD dwBkColor);
	void SetHotItemImage(LPCTSTR pStrImage);

	/** ���÷ǿ������ı�ɫ ����ɫ ����ͼ */
	void SetDisabledItemTextColor(DWORD dwTextColor);
	void SetDisabledItemBkColor(DWORD dwBkColor);
	void SetDisabledItemImage(LPCTSTR pStrImage);

	/** ���úͻ�ȡ��߿�ɫ */
	void SetItemLineColor(DWORD dwLineColor);
	DWORD GetItemLineColor() const;

	/** ��ȡ���������Ƿ�ʹ����Ƕhtml��ʶ */
	bool IsItemShowHtml();
	void SetItemShowHtml(bool bShowHtml = true);
	/** ��ȡ�ı���� */
	RECT GetItemTextPadding() const;
	/** ��ȡ�ı���ɫ ����ɫ ����ͼ */
	DWORD GetItemTextColor() const;
	DWORD GetItemBkColor() const;
	LPCTSTR GetItemBkImage() const;

	/** ��ȡ���ñ������� */
	bool IsAlternateBk() const;
	/** ��ȡѡ�����ı�ɫ ����ɫ ����ͼ */
	DWORD GetSelectedItemTextColor() const;
	DWORD GetSelectedItemBkColor() const;
	LPCTSTR GetSelectedItemImage() const;

	/** ��ȡ����״̬���ı�ɫ ����ɫ ����ͼ */
	DWORD GetHotItemTextColor() const;
	DWORD GetHotItemBkColor() const;
	LPCTSTR GetHotItemImage() const;

	/** ��ȡ�ǿ������ı�ɫ ����ɫ ����ͼ */
	DWORD GetDisabledItemTextColor() const;
	DWORD GetDisabledItemBkColor() const;
	LPCTSTR GetDisabledItemImage() const;

	/** ���ö���չ������ */
	void SetMultiExpanding(bool bMultiExpandable); 
	/** ��ȡչ������� */
	int GetExpandedItem() const;
	/** չ���� */
	bool ExpandItem(int iIndex, bool bExpand = true);

	void SetPos(RECT rc);
	void DoEvent(TEventUI& event);
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	/** ��ȡ�������ı��ص� */
	IListCallbackUI* GetTextCallback() const;
	void SetTextCallback(IListCallbackUI* pCallback);

	/** ��ȡ������λ�� */
	SIZE GetScrollPos() const;
	/** ��ȡ�����ù�����λ�� */
	SIZE GetScrollRange() const;
	void SetScrollPos(SIZE szPos);
	/** �����������ݹ����� */
	void LineUp();
	void LineDown();
	void PageUp();
	void PageDown();
	void HomeUp();
	void EndDown();
	void LineLeft();
	void LineRight();
	void PageLeft();
	void PageRight();
	void HomeLeft();
	void EndRight();
	/** �����Ƿ�ʹ�ù����� */
	void EnableScrollBar(bool bEnableVertical = true, bool bEnableHorizontal = false);
	/** ��ȡ�������������� */
	virtual CScrollBarUI* GetVerticalScrollBar() const;
	virtual CScrollBarUI* GetHorizontalScrollBar() const;

protected:
	/** ��������ѡ�� */
	bool m_bScrollSelect;
	/** ��ǰѡ���� */
	int m_iCurSel;
	/** չ���� */
	int m_iExpandedItem;
	/** �ص� */
	IListCallbackUI* m_pCallback;
	/** ����ָ�� */
	CListBodyUI* m_pList;
	/** ��ͷ */
	CListHeaderUI* m_pHeader;
	/** ������ */
	TListInfoUI m_ListInfo;
};

/////////////////////////////////////////////////////////////////////////////////////
//

class CULIB_API CListBodyUI : public CVerticalLayoutUI
{
public:
	CListBodyUI(CListUI* pOwner);

	/** ���ù�����λ�� */
	void SetScrollPos(SIZE szPos);
	void SetPos(RECT rc);
	void DoEvent(TEventUI& event);

protected:
	/** ӵ����ָ�� */
	CListUI* m_pOwner;
};

/////////////////////////////////////////////////////////////////////////////////////
//

class CULIB_API CListHeaderUI : public CHorizontalLayoutUI
{
public:
	CListHeaderUI();

	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);

	/** �����С*/
	SIZE EstimateSize(SIZE szAvailable);
};


/////////////////////////////////////////////////////////////////////////////////////
//

class CULIB_API CListHeaderItemUI : public CControlUI
{
public:
	CListHeaderItemUI();

	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);
	UINT GetControlFlags() const;

	void SetEnabled(bool bEnable = true);

	/** ��ȡ�������Ƿ�֧����ק */
	bool IsDragable() const;
	void SetDragable(bool bDragable);
	/** ��ȡ�����÷ָ������ */
	DWORD GetSepWidth() const;
	void SetSepWidth(int iWidth);
	/** ��ȡ�������ı����� */
	DWORD GetTextStyle() const;
	void SetTextStyle(UINT uStyle);
	/** ��ȡ�������ı���ɫ */
	DWORD GetTextColor() const;
	void SetTextColor(DWORD dwTextColor);
	/** ���úͻ�ȡ�ı���� */
	void SetTextPadding(RECT rc);
	RECT GetTextPadding() const;
	/** �������� */
	void SetFont(int index);
	/** ��ȡ�������Ƿ�ʹ����Ƕhtml��� */
	bool IsShowHtml();
	void SetShowHtml(bool bShowHtml = true);
	/** ��ȡ����������״̬ͼ */
	LPCTSTR GetNormalImage() const;
	void SetNormalImage(LPCTSTR pStrImage);
	/** ��ȡ�����ü���״̬ͼ  */
	LPCTSTR GetHotImage() const;
	void SetHotImage(LPCTSTR pStrImage);
	/** ��ȡ�����ð���״̬ͼ */
	LPCTSTR GetPushedImage() const;
	void SetPushedImage(LPCTSTR pStrImage);
	/** ��ȡ�����ý���״̬ͼ */
	LPCTSTR GetFocusedImage() const;
	void SetFocusedImage(LPCTSTR pStrImage);
	/** ��ȡ�����÷ָ�������ͼ */
	LPCTSTR GetSepImage() const;
	void SetSepImage(LPCTSTR pStrImage);

	void DoEvent(TEventUI& event);
	SIZE EstimateSize(SIZE szAvailable);
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	/** ��ȡ��� */
	RECT GetThumbRect() const;

	void PaintText(HDC hDC);
	void PaintStatusImage(HDC hDC);

protected:
	/** ���λ�� */
	POINT ptLastMouse;
	/** ����ק���� */
	bool m_bDragable;
	/** �ؼ�״̬ */
	UINT m_uButtonState;
	/** �ָ������ */
	int m_iSepWidth;
	/** �ı���ɫ */
	DWORD m_dwTextColor;
	/** ���� */
	int m_iFont;
	/** �ı����� */
	UINT m_uTextStyle;
	/** �Ƿ�ʹ����Ƕhtml */
	bool m_bShowHtml;
	/** �ı���� */
	RECT m_rcTextPadding;

	/** ����״̬ͼ */
	CStdString m_sNormalImage;
	CStdString m_sHotImage;
	CStdString m_sPushedImage;
	CStdString m_sFocusedImage;
	/** �ָ�������ͼ */
	CStdString m_sSepImage;
	CStdString m_sSepImageModify;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class CULIB_API CListElementUI : public CControlUI, public IListItemUI
{
public:
	CListElementUI();

	LPCTSTR GetClass() const;
	/** ��ȡ�ؼ���־ */
	UINT GetControlFlags() const;
	LPVOID GetInterface(LPCTSTR pstrName);

	void SetEnabled(bool bEnable = true);

	/** �õ��������б�Ԫ����� */
	int GetIndex() const;
	void SetIndex(int iIndex);

	/** ��ȡ�������б�Ԫ��ӵ���� */
	IListOwnerUI* GetOwner();
	void SetOwner(CControlUI* pOwner);
	/** �����б�Ԫ�ؿɼ��� */
	void SetVisible(bool bVisible = true);

	/** ��ȡ�����ñ�ѡ�� */
	bool IsSelected() const;
	bool Select(bool bSelect = true);
	bool IsExpanded() const;
	bool Expand(bool bExpand = true);

	/** ʹ����ʧЧ,ֱ��CControl::Invalidate�ᵼ�¹�����ˢ�£���д����ˢ������ */
	void Invalidate(); 
	/** �����б�Ԫ��״̬ */
	bool Activate();

	void DoEvent(TEventUI& event);
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	/** �����б�Ԫ�ر���ɫ */
	void DrawItemBk(HDC hDC, const RECT& rcItem);

protected:
	/** �б�Ԫ�����к� */
	int m_iIndex;
	/** �Ƿ�ѡ�� */
	bool m_bSelected;
	/** �б�Ԫ��״̬ */
	UINT m_uButtonState;
	/** �б�Ԫ��ӵ���� */
	IListOwnerUI* m_pOwner;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class CULIB_API CListLabelElementUI : public CListElementUI
{
public:
	CListLabelElementUI();

	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);

	void DoEvent(TEventUI& event);
	SIZE EstimateSize(SIZE szAvailable);
	void DoPaint(HDC hDC, const RECT& rcPaint);
	/** �����б����ı� */
	void DrawItemText(HDC hDC, const RECT& rcItem);
};


/////////////////////////////////////////////////////////////////////////////////////
//

class CULIB_API CListTextElementUI : public CListLabelElementUI
{
public:
	CListTextElementUI();
	~CListTextElementUI();

	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);
	UINT GetControlFlags() const;

	/** �õ��������ı� */
	LPCTSTR GetText(int iIndex) const;
	void SetText(int iIndex, LPCTSTR pstrText);

	/** ����ӵ���� */
	void SetOwner(CControlUI* pOwner);
	/** �õ����������� */
	CStdString* GetLinkContent(int iIndex);

	void DoEvent(TEventUI& event);
	SIZE EstimateSize(SIZE szAvailable);
	/** �����ı� */
	void DrawItemText(HDC hDC, const RECT& rcItem);

protected:
	/** ��������� */
	enum { MAX_LINK = 8 };
	/** ��ǰ��������Ŀ */
	int m_nLinks;
	/** �����ı����� */
	RECT m_rcLinks[MAX_LINK];
	/** �����ı����� */
	CStdString m_sLinks[MAX_LINK];
	int m_nHoverLink;
	/** ӵ���� */
	IListUI* m_pOwner;
	/** ������ı� */
	CStdPtrArray m_aTexts;
};

/////////////////////////////////////////////////////////////////////////////////////
//

class CULIB_API CListContainerElementUI : public CContainerUI, public IListItemUI
{
public:
	CListContainerElementUI();

	LPCTSTR GetClass() const;
	UINT GetControlFlags() const;
	LPVOID GetInterface(LPCTSTR pstrName);

	int GetIndex() const;
	void SetIndex(int iIndex);

	IListOwnerUI* GetOwner();
	void SetOwner(CControlUI* pOwner);
	void SetVisible(bool bVisible = true);
	/** �����Ƿ���� */
	void SetEnabled(bool bEnable = true);

	/** ��ȡ�������Ƿ�ѡ�� */
	bool IsSelected() const;
	bool Select(bool bSelect = true);

	/** ��ȡ�������Ƿ�չ�� */
	bool IsExpanded() const;
	bool Expand(bool bExpand = true);

	/**  ֱ��CControl::Invalidate�ᵼ�¹�����ˢ�£���д����ˢ������ */
	void Invalidate(); 
	bool Activate();

	void DoEvent(TEventUI& event);
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	void DoPaint(HDC hDC, const RECT& rcPaint);

	void DrawItemText(HDC hDC, const RECT& rcItem);    
	void DrawItemBk(HDC hDC, const RECT& rcItem);

protected:
	int m_iIndex;
	bool m_bSelected;
	UINT m_uButtonState;
	IListOwnerUI* m_pOwner;
};


class CTreeViewUI;
class CTreeItemUI;

struct NodeData
{
	int _level;			//�ڵ�ĵȼ�
	bool _child_visible;//���ӽڵ�ɼ���
	CStdString _text;	//treeitem�ϵ�html����
	CStdString _tree1;   //���ڵ�ͼƬ1
	CStdString _tree2;   //���ڵ�ͼƬ2
};


class CULIB_API CTreeItemUI:public CListLabelElementUI,IContainerUI//�����ʾtreeview�ؼ���Ԫ��
{
public:
	void DoEvent(TEventUI& event);
public:
	CTreeItemUI();
	CTreeItemUI(NodeData t);
	CTreeItemUI(NodeData t, CTreeItemUI* parent);
	~CTreeItemUI();
	NodeData& data() { return _data; }	
	int num_children() const { return _children.size(); }//���ӽڵ���Ŀ
	CTreeItemUI* child(int i)	{ return _children[i]; }	 //�������ӽڵ�
	CTreeItemUI* parent() { return ( _parent);	}
	bool has_children() const {	return num_children() > 0; }//�Ƿ�ӵ�к��ӽڵ�
	void add_child(CTreeItemUI* child);					 //��Ӻ��ӽڵ�
	void remove_child(CTreeItemUI* child);					 //�Ƴ����ӽڵ�
	CTreeItemUI* get_last_child();							//�������һ������

//////////////////////////////////////////////////////////////
	LPVOID GetInterface(LPCTSTR pstrName);
	CControlUI* GetItemAt(int iIndex) const;
	int GetItemIndex(CControlUI* pControl) const;
	bool SetItemIndex(CControlUI* pControl, int iIndex);
	int GetCount() const;
	bool Add(CControlUI* pControl,CControlUI* pParent=NULL);
	bool AddAt(CControlUI* pControl, int iIndex);
	bool Remove(CControlUI* pControl);
	bool RemoveAt(int iIndex);
	void RemoveAll();
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	void SetHtmlText(LPCTSTR pstrHtml);
private:
	void set_parent(CTreeItemUI* parent) { _parent = parent; }//���ø��ڵ�
public:
	CTreeViewUI* m_root;				//��CTreeViewUI��Ψһ�ģ�
	typedef std::vector <CTreeItemUI*>	Children;
	Children	_children;		//�߼��ӽڵ�
	CTreeItemUI*		_parent;	//�߼����ڵ�
	NodeData    _data;			//�ڵ�������Ϣ
};

class CULIB_API CTreeViewUI : public CListUI
{
public:
	enum { SCROLL_TIMERID = 10 };

	CTreeViewUI();
	~CTreeViewUI() { if(_root) delete _root; }

	bool Add(CControlUI* pControl,CControlUI* pParent=NULL);//���Ԫ��


	bool AddAt(CControlUI* pControl, int iIndex);//���Ԫ�ص�ָ������

	bool Remove(CControlUI* pControl);//�Ƴ�Ԫ��

	bool RemoveAt(int iIndex);//�Ƴ�ָ��Ԫ��

	void RemoveAll();//�Ƴ�����Ԫ��

	void DoEvent(TEventUI& event);//ʱ����Ӧ

	CTreeItemUI* GetRoot() { return _root; }

	CTreeItemUI* AddNode(CControlUI* node,CTreeItemUI* parent = NULL);//����߼��ڵ�

	void RemoveNode(CTreeItemUI* node);//�Ƴ��߼��ڵ�

	void SetChildVisible(CTreeItemUI* node, bool visible);//���ú��ӽڵ�ɼ���

	SIZE GetExpanderSizeX(CTreeItemUI* node) const;//���ƴ�С

private:
	CTreeItemUI* _root;

	LONG m_dwDelayDeltaY;
	DWORD m_dwDelayNum;
	DWORD m_dwDelayLeft;
};

} 

#endif // __UILIST_H__
