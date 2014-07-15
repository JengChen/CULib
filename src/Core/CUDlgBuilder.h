
#ifndef __CUDLGBUILDER_H__
#define __CUDLGBUILDER_H__

#pragma once
#ifdef MARK_UP

namespace CULib{

	/** ����UIʱ�ص��� ���ڴ����û��Զ���Ŀؼ� */
	class IDialogBuilderCallback
	{
	public:
		/** �����û��Զ���ؼ� */
		virtual CControlUI* CreateControl(LPCTSTR pstrClass) = 0;
	};


	/** UI������, ���ڹ���UI */
	class CULIB_API CDialogBuilder
	{
	public:
		CDialogBuilder();
		/** ����UI */
		CControlUI* Create(STRINGorID xml, IDialogBuilderCallback* pCallback = NULL,
			CPaintManagerUI* pManager = NULL, CControlUI* pParent = NULL, LPCTSTR type = NULL);
		CControlUI* Create(IDialogBuilderCallback* pCallback = NULL, CPaintManagerUI* pManager = NULL,
			CControlUI* pParent = NULL);

		CMarkup* GetMarkup();

		void GetLastErrorMessage(LPTSTR pstrMessage, SIZE_T cchMax) const;
		void GetLastErrorLocation(LPTSTR pstrSource, SIZE_T cchMax) const;
	private:
		CControlUI* _Parse(CMarkupNode* parent, CControlUI* pParent = NULL, CPaintManagerUI* pManager = NULL);

		CMarkup m_xml;
		IDialogBuilderCallback* m_pCallback;
		LPCTSTR m_pstrtype;
	};

} // namespace DuiLib
#else


#include "Markup.h"
namespace CULib {

enum
{
	XMLFILE_ENCODING_UTF8 = 0,
	XMLFILE_ENCODING_UNICODE = 1,
	XMLFILE_ENCODING_ASNI = 2,
};

/** ����UIʱ�ص��� ���ڴ����û��Զ���Ŀؼ� */
class IDialogBuilderCallback
{
public:
	/** �����û��Զ���ؼ� */
	virtual CControlUI* CreateControl(LPCTSTR pstrClass) = 0;
};

/** UI������, ���ڹ���UI */
class CULIB_API CDialogBuilder
{
public:
	CDialogBuilder();
	/** ����UI */
	CControlUI* Create(STRINGorID xml, IDialogBuilderCallback* pCallback=NULL, 
		CPaintManagerUI* pManager=NULL, CControlUI* pParent=NULL, LPCTSTR type = NULL);
	bool _Failed(LPCTSTR pstrError, LPCTSTR pstrLocation=NULL);
	bool LoadFromFile(LPCTSTR pstrFilename, int encoding=XMLFILE_ENCODING_UNICODE);
	bool LoadFromMem(LPCTSTR pstrFilename, int encoding=XMLFILE_ENCODING_UNICODE);
	CControlUI* Create(IDialogBuilderCallback* pCallback, CPaintManagerUI* pManager, CControlUI* pParent);
	CControlUI* parse(CControlUI* pParent,CPaintManagerUI* pManager);
private:
	CMarkup m_xml;
	IDialogBuilderCallback* m_pCallback;
	LPCTSTR m_pstrtype;      //��Դdll

	TCHAR m_szErrorMsg[100];
	TCHAR m_szErrorXML[50];
};

} 
#endif
#endif 
