/**  
*  @file    CUCombo.h
*  @brief  
*  @author        
*  @date  
*  @version    
*/
#ifndef __CUCOMBO_H__
#define __CUCOMBO_H__

#pragma once

namespace CULib {
//////////////////////////////////////////////////////////////////////////

class CComboWnd;

/** ��Ͽؼ� */
class CULIB_API CComboUI : public CContainerUI, public IListOwnerUI
{
	friend CComboWnd;
public:
	CComboUI();

	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);

	void DoInit();
	/** ����tab�л�ͣ������ */
	UINT GetControlFlags() const;
	/** �õ��ı� */
	CStdString GetText() const;
	void SetEnabled(bool bEnable = true);

	/** ��ȡ�����������������б��ַ��� */
	CStdString GetDropBoxAttributeList();
	void SetDropBoxAttributeList(LPCTSTR pstrList);
	
	/** �õ��������������С */
	SIZE GetDropBoxSize() const;
	void SetDropBoxSize(SIZE szDropBox);

	/** ��ȡ��ǰѡ���� */
	int GetCurSel() const;  
	/** ���õ�ǰѡ���� */
	bool SelectItem(int iIndex, bool bTakeFocus = false);
	/** ����Ŀؼ�ָ���ȡ����� */
	bool SetItemIndex(CControlUI* pControl, int iIndex);

	/** ����һ�� */
	bool Add(CControlUI* pControl,CControlUI* pParent=NULL);
	/** ����һ��б�ָ��λ�� */
	bool AddAt(CControlUI* pControl, int iIndex);
	/** ����ؼ���ָ���Ƴ�һ�� */
	bool Remove(CControlUI* pControl);
	/** �Ƴ�ָ����ŵ�һ�� */
	bool RemoveAt(int iIndex);
	/** �Ƴ������� */
	void RemoveAll();

	/** ���ÿؼ���Ծ */
	bool Activate();

	/** ��ȡ�������ı���ؼ���Ե�ļ�� */
	RECT GetTextPadding() const;
	void SetTextPadding(RECT rc);

	/** ��ȡ����������״̬ͼ */
	LPCTSTR GetNormalImage() const;
	void SetNormalImage(LPCTSTR pStrImage);

	/** ��ȡ�����û�Ծ״̬ͼ */
	LPCTSTR GetHotImage() const;
	void SetHotImage(LPCTSTR pStrImage);

	/** ��ȡ�����ð���״̬ͼ */
	LPCTSTR GetPushedImage() const;
	void SetPushedImage(LPCTSTR pStrImage);

	/** ��ȡ�����ý���״̬ͼ */
	LPCTSTR GetFocusedImage() const;
	void SetFocusedImage(LPCTSTR pStrImage);

	/** ��ȡ�����÷ǿ���״̬ͼ */
	LPCTSTR GetDisabledImage() const;
	void SetDisabledImage(LPCTSTR pStrImage);

	/** ��ȡ�б���Ϣ */
	TListInfoUI* GetListInfo();
	/** ���������� */
	void SetItemFont(int index);
	/** �����������С */
	void SetItemTextStyle(UINT uStyle);
	/** ��ȡ���������ı���� */
	RECT GetItemTextPadding() const;
	void SetItemTextPadding(RECT rc);
	/** �õ���������Ŀ�ı�ɫ */
	DWORD GetItemTextColor() const;
	void SetItemTextColor(DWORD dwTextColor);
	/** ��ȡ���������ɫ */
	DWORD GetItemBkColor() const;
	void SetItemBkColor(DWORD dwBkColor);
	/** ��ȡ��������ͼ */
	LPCTSTR GetItemBkImage() const;
	void SetItemBkImage(LPCTSTR pStrImage);
	bool IsAlternateBk() const;
	void SetAlternateBk(bool bAlternateBk);
	
	/** �õ�������ѡ��״̬�ı�ɫ */
	DWORD GetSelectedItemTextColor() const;
	void SetSelectedItemTextColor(DWORD dwTextColor);
	/** �õ���������ѡ��״̬����ͼ */
	DWORD GetSelectedItemBkColor() const;
	void SetSelectedItemBkColor(DWORD dwBkColor);
	/** �õ���������ѡ��״̬����ͼ */
	LPCTSTR GetSelectedItemImage() const;
	void SetSelectedItemImage(LPCTSTR pStrImage);
	/** �õ����������Ծ״̬�ı�ɫ */
	DWORD GetHotItemTextColor() const;
	void SetHotItemTextColor(DWORD dwTextColor);
	/** �õ����������Ծ״̬����ɫ */
	DWORD GetHotItemBkColor() const;
	void SetHotItemBkColor(DWORD dwBkColor);
	/** �������Ծ״̬ͼ */
	LPCTSTR GetHotItemImage() const;
	void SetHotItemImage(LPCTSTR pStrImage);
	/** �õ������÷ǿ������ı�ɫ */
	DWORD GetDisabledItemTextColor() const;
	void SetDisabledItemTextColor(DWORD dwTextColor);
	/** �õ���������ǿ���״̬����ɫ */
	DWORD GetDisabledItemBkColor() const;
	void SetDisabledItemBkColor(DWORD dwBkColor);
	/** ��ȡ��������ǿ���״̬ͼ */
	LPCTSTR GetDisabledItemImage() const;
	void SetDisabledItemImage(LPCTSTR pStrImage);
	/** ��ȡ��������߿�ɫ */
	DWORD GetItemLineColor() const;
	void SetItemLineColor(DWORD dwLineColor);
	/** ��ȡ���������Ƿ�ʹ����Ƕhtml��ʶ���� */
	bool IsItemShowHtml();
	void SetItemShowHtml(bool bShowHtml = true);

	SIZE EstimateSize(SIZE szAvailable);
	void SetPos(RECT rc);
	void DoEvent(TEventUI& event);
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	void DoPaint(HDC hDC, const RECT& rcPaint);
	void PaintText(HDC hDC);
	void PaintStatusImage(HDC hDC);

protected:
	/** �����򴰿� */
	CComboWnd* m_pWindow;
	/** ��ǰѡ���� */
	int m_iCurSel;
	/** �ı���ؼ���Ե��� */
	RECT m_rcTextPadding;
	/** ���������� */
	CStdString m_sDropBoxAttributes;
	/** ���������С */
	SIZE m_szDropBox;
	/** �ؼ�״̬ */
	UINT m_uButtonState;

	/** ����״̬ͼ */
	CStdString m_sNormalImage;
	CStdString m_sHotImage;
	CStdString m_sPushedImage;
	CStdString m_sFocusedImage;
	CStdString m_sDisabledImage;

	/** ����������б� */
	TListInfoUI m_ListInfo;
};

} // namespace DuiLib

#endif // __UICOMBO_H__
