/**  
*  @file   CUDlgBuilder.cpp
*  @brief  ���ļ�����ʵ�ֲ˵��ؼ� 
*  
*		   �ļ���ǰ�벿��Ϊ�۲���ģʽ��ʵ�֣���벿�ֹ����������࣬�ֱ�Ϊ
*	       �˵��ؼ�����CMenuUI���˵�����CMenuWnd���˵�ѡ��CMenuElementUI��
* @author  chencheng
* @data    2013-04-13
*/
#ifndef __UIMENU_H__
#define __UIMENU_H__

#ifdef _MSC_VER
#pragma once
#endif
#include "CULib.h"
#include <map>
#include <vector>

namespace CULib {

template <typename ReturnT, typename ParamT>
class ReceiverImplBase;

/** �۲������� */
template <typename ReturnT, typename ParamT>
class ObserverImplBase
{
public:
	virtual void AddReceiver(ReceiverImplBase<ReturnT, ParamT>* receiver) = 0;
	virtual void RemoveReceiver(ReceiverImplBase<ReturnT, ParamT>* receiver) = 0;
	virtual ReturnT Broadcast(ParamT param) = 0;
	virtual ReturnT RBroadcast(ParamT param) = 0;
	virtual ReturnT Notify(ParamT param) = 0;
};

/** �۲��߻��� */
template <typename ReturnT, typename ParamT>
class ReceiverImplBase
{
public:
	virtual void AddObserver(ObserverImplBase<ReturnT, ParamT>* observer) = 0;
	virtual void RemoveObserver() = 0;
	virtual ReturnT Receive(ParamT param) = 0;
	virtual ReturnT Respond(ParamT param, ObserverImplBase<ReturnT, ParamT>* observer) = 0;
};

template <typename ReturnT, typename ParamT>
class ReceiverImpl;

/** �۲���� */
template <typename ReturnT, typename ParamT>
class ObserverImpl : public ObserverImplBase<ReturnT, ParamT>
{
	template <typename ReturnT, typename ParamT>
	friend class Iterator;
public:
	ObserverImpl()
	{}

	virtual ~ObserverImpl()	{}

	/** ���ӹ۲��� */
	virtual void AddReceiver(ReceiverImplBase<ReturnT, ParamT>* receiver)
	{
		if (receiver == NULL)
			return;

		receivers_.push_back(receiver);
		receiver->AddObserver(this);
	}

	/** �Ƴ����й۲��� */
	virtual void RemoveReceiver(ReceiverImplBase<ReturnT, ParamT>* receiver)
	{
		if (receiver == NULL)
			return;

		ReceiversVector::iterator it = receivers_.begin();
		for (; it != receivers_.end(); ++it)
		{
			if (*it == receiver)
			{
				receivers_.erase(it);
				break;
			}
		}
	}

	/** ��۲��߷���֪ͨ */
	virtual ReturnT Broadcast(ParamT param)
	{
		ReceiversVector::iterator it = receivers_.begin();
		for (; it != receivers_.end(); ++it)
		{
			(*it)->Receive(param);
		}

		return ReturnT();
	}

	/** ������˳����۲��߷���֪ͨ */
	virtual ReturnT RBroadcast(ParamT param)
	{
		ReceiversVector::reverse_iterator it = receivers_.rbegin();
		for (; it != receivers_.rend(); ++it)
		{
			(*it)->Receive(param);
		}

		return ReturnT();
	}

	/** ��۲��߷���֪ͨ������������Ϊ�������� */
	virtual ReturnT Notify(ParamT param)
	{
		ReceiversVector::iterator it = receivers_.begin();
		for (; it != receivers_.end(); ++it)
		{
			(*it)->Respond(param, this);
		}

		return ReturnT();
	}

	/** �۲����ĵ����� */
	template <typename ReturnT, typename ParamT>
	class Iterator
	{
		ObserverImpl<ReturnT, ParamT> & _tbl;
		int index;
		ReceiverImplBase<ReturnT, ParamT>* ptr;
	public:
		Iterator( ObserverImpl & table )
			: _tbl( table ), index(0), ptr(NULL)
		{}

		Iterator( const Iterator & v )
			: _tbl( v._tbl ), index(v.index), ptr(v.ptr)
		{}

		ReceiverImplBase<ReturnT, ParamT>* next()
		{
			if ( index >= _tbl.receivers_.size() )
				return NULL;

			for ( ; index < _tbl.receivers_.size(); )
			{
				ptr = _tbl.receivers_[ index++ ];
				if ( ptr )
					return ptr;
			}
			return NULL;
		}
	};

protected:
	typedef std::vector<ReceiverImplBase<ReturnT, ParamT>*> ReceiversVector;
	ReceiversVector receivers_;
};

/** �۲��� */
template <typename ReturnT, typename ParamT>
class ReceiverImpl : public ReceiverImplBase<ReturnT, ParamT>
{
public:
	ReceiverImpl()
	{}

	virtual ~ReceiverImpl()	{}

	/** ���ӹ۲���� */
	virtual void AddObserver(ObserverImplBase<ReturnT, ParamT>* observer)
	{
		observers_.push_back(observer);
	}

	/** �Ƴ��۲���� */
	virtual void RemoveObserver()
	{
		ObserversVector::iterator it = observers_.begin();
		for (; it != observers_.end(); ++it)
		{
			(*it)->RemoveReceiver(this);
		}
	}

	/** ��Ӧ֪ͨ */
	virtual ReturnT Receive(ParamT param)
	{
		return ReturnT();
	}

	virtual ReturnT Respond(ParamT param, ObserverImplBase<ReturnT, ParamT>* observer)
	{
		return ReturnT();
	}

protected:
	typedef std::vector<ObserverImplBase<ReturnT, ParamT>*> ObserversVector;
	/** �۲�������� */
	ObserversVector observers_;
};


/////////////////////////////////////////////////////////////////////////////////////
//
struct ContextMenuParam
{
	// 1: remove all
	// 2: remove the sub menu
	WPARAM wParam;
	HWND hWnd;
};

enum MenuAlignment
{
	eMenuAlignment_Left = 1 << 1,
	eMenuAlignment_Top = 1 << 2,
	eMenuAlignment_Right = 1 << 3,
	eMenuAlignment_Bottom = 1 << 4,
};

typedef class ObserverImpl<BOOL, ContextMenuParam> ContextMenuObserver;
typedef class ReceiverImpl<BOOL, ContextMenuParam> ContextMenuReceiver;


extern ContextMenuObserver s_context_menu_observer;


extern const TCHAR* const kMenuUIClassName;// = _T("MenuUI");
extern const TCHAR* const kMenuUIInterfaceName;// = _T("Menu");

class CListUI;
/** �˵��ؼ� */
class CULIB_API CMenuUI : public CListUI
{
public:
	CMenuUI();
	~CMenuUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);

	virtual void DoEvent(TEventUI& event);

	/** ��˵������Ӳ˵��� */
    virtual bool Add(CControlUI* pControl,CControlUI* pParent=NULL);
	/** ��ָ��λ����˵������Ӳ˵��� */
    virtual bool AddAt(CControlUI* pControl, int iIndex);

	/** �õ��˵���λ�� */
    virtual int GetItemIndex(CControlUI* pControl) const;
	/** ���ò˵���λ�� */
    virtual bool SetItemIndex(CControlUI* pControl, int iIndex);
	/** �Ƴ��˵��� */
    virtual bool Remove(CControlUI* pControl);

	SIZE EstimateSize(SIZE szAvailable);

	/** �������� */
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
};

/////////////////////////////////////////////////////////////////////////////////////
//

// MenuElementUI
extern const TCHAR* const kMenuElementUIClassName;// = _T("MenuElementUI");
extern const TCHAR* const kMenuElementUIInterfaceName;// = _T("MenuElement);

class CMenuElementUI;
/**
 *  �˵�������popup���͵ĵ������ڣ�����˵�����ʾ���˵����ǲ˵�����
 *  ���ӿؼ����˵�����Ҳ�ǹ۲���ģʽ�еĹ۲���
 */
class  CULIB_API CMenuWnd : public CWindowWnd, public ContextMenuReceiver
{
public:
	CMenuWnd(HWND hParent = NULL);
    void Init(CControlUI* pOwner, STRINGorID xml, LPCTSTR pSkinType, POINT point);
    LPCTSTR GetWindowClassName() const;
    void OnFinalMessage(HWND hWnd);

    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnCreate(UINT uMag, WPARAM wParam, LPARAM lParam,BOOL& bHandled);
	LRESULT OnKillFocus(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL& bHandled);
	LRESULT OnKeyDown(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL& bHandled);
	LRESULT OnClose(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL& bHandled);

	BOOL Receive(ContextMenuParam param);

public:
	HWND m_hParent;
	POINT m_BasedPoint;
	STRINGorID m_xml;
	CStdString m_sType;
    CPaintManagerUI m_pm;
    CMenuElementUI* m_pOwner;
	CControlUI* m_pControl;
    CMenuUI* m_pLayout;
};

class CListContainerElementUI;
/** �˵��� */
class CULIB_API CMenuElementUI : public CListContainerElementUI
{
	friend CMenuWnd;
public:
    CMenuElementUI();
	~CMenuElementUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);

	/** �������� */
    void DoPaint(HDC hDC, const RECT& rcPaint);
    /** �����ı� */
	void DrawItemText(HDC hDC, const RECT& rcItem);

	SIZE EstimateSize(SIZE szAvailable);

	/** �˵����������Ӧ���� */
	bool Activate();

	void DoEvent(TEventUI& event);

	CMenuWnd* GetMenuWnd();

	void CreateMenuWnd();

protected:
	CMenuWnd* m_pWindow;
};

} 

#endif // 
