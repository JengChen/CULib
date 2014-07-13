/**  
*  @file   CUDlgBuilder.cpp
*  @brief  ���ļ��еĺ���ͨ�����ý��������xml�������ɿؼ� 
*  
*		   LoadFromFile��������LoadFromMem���������ߵ���һϵ��zip�������н�ѹ��
*		   ǰ�ߵ�Create�����ǰ�װ��������������ں�ߵ�Create�����У����е�����
*		   �Ƕ�ͨ��Ԫ�صĽ���������ؼ��Ľ�����parse�����С�
* @author  chencheng
* @data    2013-04-05
*/

#ifndef __CUDLGBUILDER_H__
#define __CUDLGBUILDER_H__

#pragma once

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
	/**  ��Դdll */
	LPCTSTR m_pstrtype;     

	TCHAR m_szErrorMsg[100];
	TCHAR m_szErrorXML[50];
};

} 
#endif

