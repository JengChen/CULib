#ifndef __CUACTIVEX_H__
#define __CUACTIVEX_H__

#pragma once

struct IOleObject;

namespace CULib {
/////////////////////////////////////////////////////////////////////////////////////
//

class CActiveXCtrl;

/** ��ȫ�ͷŶ���t */
template< class T >
class CSafeRelease
{
public:
	CSafeRelease(T* p) : m_p(p) { };
	~CSafeRelease() { if( m_p != NULL ) m_p->Release(); };
	T* Detach() { T* t = m_p; m_p = NULL; return t; };
	T* m_p;
};

/////////////////////////////////////////////////////////////////////////////////////
//

/** Ϊ��Ҫ���װ��CActiveXCtrl��CActiveXWnd��Ϊ�ؼ����û�ʹ�� */
class CULIB_API CActiveXUI : public CControlUI, public IMessageFilterUI
{
	friend CActiveXCtrl;
public:
	CActiveXUI();
	virtual ~CActiveXUI();

	/** �õ��ؼ����� */
	LPCTSTR GetClass() const;
	/** �õ��ؼ�ָ�� */
	LPVOID GetInterface(LPCTSTR pstrName);

	/** �õ��������ھ�� */
	HWND GetHostWindow() const;

	/** ��ȡ OR ������ʱ����activeX�ؼ� */
	bool IsDelayCreate() const;
	void SetDelayCreate(bool bDelayCreate = true);

	/** ��clsid�����ؼ� */
	bool CreateControl(const CLSID clsid);
	/** ��activeX�������ؼ� */
	bool CreateControl(LPCTSTR pstrCLSID);
	/** ��ȡ�ؼ��ӿ� */
	HRESULT GetControl(const IID iid, LPVOID* ppRet);
	/** �õ�ActiveX�ؼ�id */
	CLSID GetClisd() const;
	/** �õ��ؼ����� */
	CStdString GetModuleName() const;
	/** ���ÿؼ����� */
	void SetModuleName(LPCTSTR pstrText);

	/** �����Ƿ�ɼ� */
	void SetVisible(bool bVisible = true);
	void SetInternVisible(bool bVisible = true);
	/** ���ÿؼ�λ�� */
	void SetPos(RECT rc);
	/** ����CActiveXCtrl::IViewObject::Draw() ʵ�ֻ��� */
	void DoPaint(HDC hDC, const RECT& rcPaint);

	/** ���ÿؼ����� */
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	/** ��Ϣ���� */
	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

protected:
	/** �ͷſؼ� */
	void ReleaseControl();
	/** �����ؼ� */
	bool DoCreateControl();

protected:
	CLSID m_clsid;
	CStdString m_sModuleName;
	bool m_bCreated;
	bool m_bDelayCreate;
	IOleObject* m_pUnk;
	CActiveXCtrl* m_pControl;
	HWND m_hwndHost;
};

} // namespace DuiLib

#endif