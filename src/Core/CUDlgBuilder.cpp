/**  
*  @file   CUDlgBuilder.cpp
*  @brief  ���ļ��еĺ���ͨ�����ý��������xml�������ɿؼ� 
*  
*		   LoadFromFile��������LoadFromMem���������ߵ���һϵ��zip�������н�ѹ��
*		   ǰ�ߵ�Create�����ǰ�װ��������������ں�ߵ�Create�����У����е�����
*		   �Ƕ�ͨ��Ԫ�صĽ���������ؼ��Ľ�����parse�����С�
*/
#include "CULib.h"

#ifdef MARK_UP

namespace CULib {

	CDialogBuilder::CDialogBuilder() : m_pCallback(NULL), m_pstrtype(NULL)
	{

	}

	CControlUI* CDialogBuilder::Create(STRINGorID xml, IDialogBuilderCallback* pCallback, 
		CPaintManagerUI* pManager, CControlUI* pParent, LPCTSTR type)
	{
		if( HIWORD(xml.m_lpstr) != NULL ) {
			if( *(xml.m_lpstr) == _T('<') ) {
				if( !m_xml.Load(xml.m_lpstr) ) return NULL;
			}
			else {
				if( !m_xml.LoadFromFile(xml.m_lpstr) ) return NULL;
			}
		}
		else {
			HRSRC hResource = ::FindResource(CPaintManagerUI::GetResourceDll(), xml.m_lpstr, type);
			if( hResource == NULL ) return NULL;
			HGLOBAL hGlobal = ::LoadResource(CPaintManagerUI::GetResourceDll(), hResource);
			if( hGlobal == NULL ) {
#ifndef _WIN32_WCE
				FreeResource(hResource);
#endif
				return NULL;
			}

			m_pCallback = pCallback;
			if( !m_xml.LoadFromMem((BYTE*)::LockResource(hGlobal), ::SizeofResource(CPaintManagerUI::GetResourceDll(), hResource) )) return NULL;
#ifndef _WIN32_WCE
			::FreeResource(hResource);
#endif
			m_pstrtype = type;
		}

		return Create(pCallback, pManager, pParent);
	}

	CControlUI* CDialogBuilder::Create(IDialogBuilderCallback* pCallback, CPaintManagerUI* pManager, CControlUI* pParent)
	{
		m_pCallback = pCallback;
		CMarkupNode root = m_xml.GetRoot();
		if( !root.IsValid() ) return NULL;

		if( pManager ) {
			LPCTSTR pstrClass = NULL;
			int nAttributes = 0;
			LPCTSTR pstrName = NULL;
			LPCTSTR pstrValue = NULL;
			LPTSTR pstr = NULL;
			for( CMarkupNode node = root.GetChild() ; node.IsValid(); node = node.GetSibling() ) {
				pstrClass = node.GetName();
				if( _tcscmp(pstrClass, _T("Image")) == 0 ) {
					nAttributes = node.GetAttributeCount();
					LPCTSTR pImageName = NULL;
					LPCTSTR pImageResType = NULL;
					DWORD mask = 0;
					for( int i = 0; i < nAttributes; i++ ) {
						pstrName = node.GetAttributeName(i);
						pstrValue = node.GetAttributeValue(i);
						if( _tcscmp(pstrName, _T("name")) == 0 ) {
							pImageName = pstrValue;
						}
						else if( _tcscmp(pstrName, _T("restype")) == 0 ) {
							pImageResType = pstrValue;
						}
						else if( _tcscmp(pstrName, _T("mask")) == 0 ) {
							if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
							mask = _tcstoul(pstrValue, &pstr, 16);
						}
					}
					if( pImageName ) pManager->AddImage(pImageName, pImageResType, mask);
				}
				else if( _tcscmp(pstrClass, _T("Font")) == 0 ) {
					nAttributes = node.GetAttributeCount();
					LPCTSTR pFontName = NULL;
					int size = 12;
					bool bold = false;
					bool underline = false;
					bool italic = false;
					bool defaultfont = false;
					for( int i = 0; i < nAttributes; i++ ) {
						pstrName = node.GetAttributeName(i);
						pstrValue = node.GetAttributeValue(i);
						if( _tcscmp(pstrName, _T("name")) == 0 ) {
							pFontName = pstrValue;
						}
						else if( _tcscmp(pstrName, _T("size")) == 0 ) {
							size = _tcstol(pstrValue, &pstr, 10);
						}
						else if( _tcscmp(pstrName, _T("bold")) == 0 ) {
							bold = (_tcscmp(pstrValue, _T("true")) == 0);
						}
						else if( _tcscmp(pstrName, _T("underline")) == 0 ) {
							underline = (_tcscmp(pstrValue, _T("true")) == 0);
						}
						else if( _tcscmp(pstrName, _T("italic")) == 0 ) {
							italic = (_tcscmp(pstrValue, _T("true")) == 0);
						}
						else if( _tcscmp(pstrName, _T("default")) == 0 ) {
							defaultfont = (_tcscmp(pstrValue, _T("true")) == 0);
						}
					}
					if( pFontName ) {
						pManager->AddFont(pFontName, size, bold, underline, italic);
						if( defaultfont ) pManager->SetDefaultFont(pFontName, size, bold, underline, italic);
					}
				}
				else if( _tcscmp(pstrClass, _T("Default")) == 0 ) {
					nAttributes = node.GetAttributeCount();
					LPCTSTR pControlName = NULL;
					LPCTSTR pControlValue = NULL;
					for( int i = 0; i < nAttributes; i++ ) {
						pstrName = node.GetAttributeName(i);
						pstrValue = node.GetAttributeValue(i);
						if( _tcscmp(pstrName, _T("name")) == 0 ) {
							pControlName = pstrValue;
						}
						else if( _tcscmp(pstrName, _T("value")) == 0 ) {
							pControlValue = pstrValue;
						}
					}
					if( pControlName ) {
						pManager->AddDefaultAttributeList(pControlName, pControlValue);
					}
				}
			}

			pstrClass = root.GetName();
			if( _tcscmp(pstrClass, _T("Window")) == 0 ) {
				if( pManager->GetPaintWindow() ) {
					int nAttributes = root.GetAttributeCount();
					for( int i = 0; i < nAttributes; i++ ) {
						pstrName = root.GetAttributeName(i);
						pstrValue = root.GetAttributeValue(i);
						if( _tcscmp(pstrName, _T("size")) == 0 ) {
							LPTSTR pstr = NULL;
							int cx = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);    
							int cy = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr); 
							pManager->SetInitSize(cx, cy);
						} 
						else if( _tcscmp(pstrName, _T("sizebox")) == 0 ) {
							RECT rcSizeBox = { 0 };
							LPTSTR pstr = NULL;
							rcSizeBox.left = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);    
							rcSizeBox.top = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);    
							rcSizeBox.right = _tcstol(pstr + 1, &pstr, 10);  ASSERT(pstr);    
							rcSizeBox.bottom = _tcstol(pstr + 1, &pstr, 10); ASSERT(pstr);    
							pManager->SetSizeBox(rcSizeBox);
						}
						else if( _tcscmp(pstrName, _T("caption")) == 0 ) {
							RECT rcCaption = { 0 };
							LPTSTR pstr = NULL;
							rcCaption.left = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);    
							rcCaption.top = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);    
							rcCaption.right = _tcstol(pstr + 1, &pstr, 10);  ASSERT(pstr);    
							rcCaption.bottom = _tcstol(pstr + 1, &pstr, 10); ASSERT(pstr);    
							pManager->SetCaptionRect(rcCaption);
						}
						else if( _tcscmp(pstrName, _T("roundcorner")) == 0 ) {
							LPTSTR pstr = NULL;
							int cx = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);    
							int cy = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr); 
							pManager->SetRoundCorner(cx, cy);
						} 
						else if( _tcscmp(pstrName, _T("mininfo")) == 0 ) {
							LPTSTR pstr = NULL;
							int cx = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);    
							int cy = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr); 
							pManager->SetMinInfo(cx, cy);
						}
						else if( _tcscmp(pstrName, _T("maxinfo")) == 0 ) {
							LPTSTR pstr = NULL;
							int cx = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);    
							int cy = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr); 
							pManager->SetMaxInfo(cx, cy);
						}
						else if( _tcscmp(pstrName, _T("showdirty")) == 0 ) {
							pManager->SetShowUpdateRect(_tcscmp(pstrValue, _T("true")) == 0);
						} 
						else if( _tcscmp(pstrName, _T("alpha")) == 0 ) {
							pManager->SetTransparent(_ttoi(pstrValue));
						} 
						else if( _tcscmp(pstrName, _T("bktrans")) == 0 ) {
							pManager->SetBackgroundTransparent(_tcscmp(pstrValue, _T("true")) == 0);
						} 
						else if( _tcscmp(pstrName, _T("disabledfontcolor")) == 0 ) {
							if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
							LPTSTR pstr = NULL;
							DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
							pManager->SetDefaultDisabledColor(clrColor);
						} 
						else if( _tcscmp(pstrName, _T("defaultfontcolor")) == 0 ) {
							if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
							LPTSTR pstr = NULL;
							DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
							pManager->SetDefaultFontColor(clrColor);
						}
						else if( _tcscmp(pstrName, _T("linkfontcolor")) == 0 ) {
							if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
							LPTSTR pstr = NULL;
							DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
							pManager->SetDefaultLinkFontColor(clrColor);
						} 
						else if( _tcscmp(pstrName, _T("linkhoverfontcolor")) == 0 ) {
							if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
							LPTSTR pstr = NULL;
							DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
							pManager->SetDefaultLinkHoverFontColor(clrColor);
						} 
						else if( _tcscmp(pstrName, _T("selectedcolor")) == 0 ) {
							if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
							LPTSTR pstr = NULL;
							DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
							pManager->SetDefaultSelectedBkColor(clrColor);
						} 
					}
				}
			}
		}
		return _Parse(&root, pParent, pManager);
	}

	CMarkup* CDialogBuilder::GetMarkup()
	{
		return &m_xml;
	}

	void CDialogBuilder::GetLastErrorMessage(LPTSTR pstrMessage, SIZE_T cchMax) const
	{
		return m_xml.GetLastErrorMessage(pstrMessage, cchMax);
	}

	void CDialogBuilder::GetLastErrorLocation(LPTSTR pstrSource, SIZE_T cchMax) const
	{
		return m_xml.GetLastErrorLocation(pstrSource, cchMax);
	}

	CControlUI* CDialogBuilder::_Parse(CMarkupNode* pRoot, CControlUI* pParent, CPaintManagerUI* pManager)
	{
		IContainerUI* pContainer = NULL;
		CControlUI* pReturn = NULL;
		for( CMarkupNode node = pRoot->GetChild() ; node.IsValid(); node = node.GetSibling() ) {
			LPCTSTR pstrClass = node.GetName();
			if( _tcscmp(pstrClass, _T("Image")) == 0 || _tcscmp(pstrClass, _T("Font")) == 0 \
				|| _tcscmp(pstrClass, _T("Default")) == 0 ) continue;

			CControlUI* pControl = NULL;
			if( _tcscmp(pstrClass, _T("Include")) == 0 ) {
				if( !node.HasAttributes() ) continue;
				int count = 1;
				LPTSTR pstr = NULL;
				TCHAR szValue[500] = { 0 };
				SIZE_T cchLen = lengthof(szValue) - 1;
				if ( node.GetAttributeValue(_T("count"), szValue, cchLen) )
					count = _tcstol(szValue, &pstr, 10);
				cchLen = lengthof(szValue) - 1;
				if ( !node.GetAttributeValue(_T("source"), szValue, cchLen) ) continue;
				for ( int i = 0; i < count; i++ ) {
					CDialogBuilder builder;
					if( m_pstrtype != NULL ) { // ʹ����Դdll������Դ�ж�ȡ
						WORD id = (WORD)_tcstol(szValue, &pstr, 10); 
						pControl = builder.Create((UINT)id, m_pCallback, pManager, pParent, m_pstrtype);
					}
					else {
						pControl = builder.Create((LPCTSTR)szValue,  m_pCallback, pManager, pParent,(UINT)0);
					}
				}
				continue;
			}
			else {
				SIZE_T cchLen = _tcslen(pstrClass);
				switch( cchLen ) {
			case 4:
				if( _tcscmp(pstrClass, _T("Edit")) == 0 )                   pControl = new CEditUI;
				else if( _tcscmp(pstrClass, _T("List")) == 0 )              pControl = new CListUI;
				else if( _tcscmp(pstrClass, _T("Text")) == 0 )              pControl = new CTextUI;
				break;
			case 5:
				if( _tcscmp(pstrClass, _T("Combo")) == 0 )                  pControl = new CComboUI;
				else if( _tcscmp(pstrClass, _T("Label")) == 0 )             pControl = new CLabelUI;
				break;
			case 6:
				if( _tcscmp(pstrClass, _T("Button")) == 0 )                 pControl = new CButtonUI;
				else if( _tcscmp(pstrClass, _T("Option")) == 0 )            pControl = new COptionUI;
				else if( _tcscmp(pstrClass, _T("Slider")) == 0 )            pControl = new CSliderUI;
				break;
			case 7:
				if( _tcscmp(pstrClass, _T("Control")) == 0 )                pControl = new CControlUI;
#ifndef _WIN32_WCE
				else if( _tcscmp(pstrClass, _T("ActiveX")) == 0 )           pControl = new CActiveXUI;
#endif
				break;
			case 8:
				if( _tcscmp(pstrClass, _T("Progress")) == 0 )               pControl = new CProgressUI;
//				else if( _tcscmp(pstrClass, _T("TreeView")) == 0 )          pControl = new CTreeViewUI;
				else if(  _tcscmp(pstrClass, _T("RichEdit")) == 0 )         pControl = new CRichEditUI;
				break;
			case 9:
				if( _tcscmp(pstrClass, _T("Container")) == 0 )              pControl = new CContainerUI;
				else if( _tcscmp(pstrClass, _T("TabLayout")) == 0 )         pControl = new CTabLayoutUI;
				else if( _tcscmp(pstrClass, _T("ScrollBar")) == 0 )         pControl = new CScrollBarUI; 
				break;
			case 10:
				if( _tcscmp(pstrClass, _T("ListHeader")) == 0 )             pControl = new CListHeaderUI;
				else if( _tcscmp(pstrClass, _T("TileLayout")) == 0 )        pControl = new CTileLayoutUI;
				break;
			case 14:
				if( _tcscmp(pstrClass, _T("VerticalLayout")) == 0 )         pControl = new CVerticalLayoutUI;
				else if( _tcscmp(pstrClass, _T("ListHeaderItem")) == 0 )    pControl = new CListHeaderItemUI;
				break;
			case 15:
				if( _tcscmp(pstrClass, _T("ListTextElement")) == 0 )        pControl = new CListTextElementUI;
				break;
			case 16:
				if( _tcscmp(pstrClass, _T("HorizontalLayout")) == 0 )       pControl = new CHorizontalLayoutUI;
				else if( _tcscmp(pstrClass, _T("ListLabelElement")) == 0 )  pControl = new CListLabelElementUI;
				break;
			case 20:
				if( _tcscmp(pstrClass, _T("ListContainerElement")) == 0 )   pControl = new CListContainerElementUI;
				break;
				}
				// User-supplied control factory
				if( pControl == NULL ) {
					CStdPtrArray* pPlugins = CPaintManagerUI::GetPlugins();
					LPCREATECONTROL lpCreateControl = NULL;
					for( int i = 0; i < pPlugins->GetSize(); ++i ) {
						lpCreateControl = (LPCREATECONTROL)pPlugins->GetAt(i);
						if( lpCreateControl != NULL ) {
							pControl = lpCreateControl(pstrClass);
							if( pControl != NULL ) break;
						}
					}
				}
				if( pControl == NULL && m_pCallback != NULL ) {
					pControl = m_pCallback->CreateControl(pstrClass);
				}
			}

			ASSERT(pControl);
			if( pControl == NULL ) continue;

			// Add children
			if( node.HasChildren() ) {
				_Parse(&node, pControl, pManager);
			}
			// Attach to parent
			// ��ΪĳЩ���Ժ͸�������أ�����selected��������Add��������
			if( pParent != NULL ) {
				if( pContainer == NULL ) pContainer = static_cast<IContainerUI*>(pParent->GetInterface(_T("IContainer")));
				ASSERT(pContainer);
				if( pContainer == NULL ) return NULL;
				if( !pContainer->Add(pControl) ) {
					delete pControl;
					continue;
				}
			}
			// Init default attributes
			if( pManager ) {
				pControl->SetManager(pManager, NULL, false);
				LPCTSTR pDefaultAttributes = pManager->GetDefaultAttributeList(pstrClass);
				if( pDefaultAttributes ) {
					pControl->ApplyAttributeList(pDefaultAttributes);
				}
			}
			// Process attributes
			if( node.HasAttributes() ) {
				TCHAR szValue[500] = { 0 };
				SIZE_T cchLen = lengthof(szValue) - 1;
				// Set ordinary attributes
				int nAttributes = node.GetAttributeCount();
				for( int i = 0; i < nAttributes; i++ ) {
					pControl->SetAttribute(node.GetAttributeName(i), node.GetAttributeValue(i));
				}
			}
			if( pManager ) {
				pControl->SetManager(NULL, NULL, false);
			}
			// Return first item
			if( pReturn == NULL ) pReturn = pControl;
		}
		return pReturn;
	}

} // namespace DuiLib

#else

namespace CULib {

CDialogBuilder::CDialogBuilder() : m_pCallback(NULL)//, m_pstrtype(NULL)
{

}


/**
* @brief �˺�������Ӧ�ò����
* 
* @param STRINGorID xml	��������xml�ļ���
* @param IDialogBuilderCallback * pCallback	�û��Զ���ؼ�����
* @param CPaintManagerUI * pManager	ȫ�ֻ�ͼ����Ϣ�������
* @param CControlUI * pParent	�����������ڵ�ĸ��ڵ㣬һ��ΪNULL
* @return �������пؼ��ĸ��ڵ�
* @retval CControlUI*
* SetDocΪCMarkup�⺯���������ַ������õ��˺���
* LoadFromFile��������ѹ���ļ�
* Create�������ɿؼ�
*/
CControlUI* CDialogBuilder::Create( STRINGorID xml, IDialogBuilderCallback* pCallback, CPaintManagerUI* pManager,CControlUI* pParent , LPCTSTR type)
{
	if( HIWORD(xml.m_lpstr) != NULL ) 
	{
		if( *(xml.m_lpstr) == _T('<') )
		{
			if( !m_xml.SetDoc(xml.m_lpstr) )
				return NULL;
		}
		else
		{
			if(!LoadFromFile(xml.m_lpstr))
				return NULL;
		}
	}
	else
	{
		HRSRC hResource = ::FindResource(CPaintManagerUI::GetResourceDll(), xml.m_lpstr, type);
		if( hResource == NULL ) return NULL;
		HGLOBAL hGlobal = ::LoadResource(CPaintManagerUI::GetResourceDll(), hResource);
		if( hGlobal == NULL ) {
			FreeLibrary((HMODULE)hResource);
			return NULL;
		}		
		m_pCallback = pCallback;
		int dwSize=::SizeofResource(CPaintManagerUI::GetResourceDll(), hResource);
		char* pByte=(char*)LockResource(hGlobal);
		wchar_t* pChart = new wchar_t[ dwSize ];
		MultiByteToWideChar(CP_UTF8,0,pByte,dwSize,pChart,dwSize);
		if(!m_xml.SetDoc(pChart))
			return NULL;
		FreeLibrary((HMODULE)hResource);
		m_pstrtype = type;
	}

	return Create(pCallback, pManager, NULL);
}


/**
* @brief	����LoadFromMem��ѹ��
* 
* @param    LPCTSTR pstrFilename	���������ļ���
* @param    int encoding	���뷽ʽ��һ��ΪUTF-8
* @return	�ɹ�����true��ʧ�ܷ���false
* @retval   bool
*/
bool CDialogBuilder::LoadFromFile( LPCTSTR pstrFilename, int encoding )
{
	CStdString sFile = CPaintManagerUI::GetResourcePath();
	if( CPaintManagerUI::GetResourceZip().IsEmpty() )
	{
		sFile += pstrFilename;
		MCD_CSTR mcdFile(sFile);
		return m_xml.Load(mcdFile);
	}
	else if( !LoadFromMem(pstrFilename,encoding) )
		return NULL;
	return true;
}

/**
* @brief	��ɽ�ѹ������
* 
* @param    LPCTSTR pstrFilename	����������ļ���
* @param    int encoding	���뷽ʽ
* @return	�ɹ�����true��ʧ�ܷ���false
* @retval   bool
*			GetResourcePath�����õ�ѹ���ļ�·����GetResourceZip�����õ�ѹ���ļ���
*			Openzip��FindZipItem��UnzipItem�ǽ�ѹ���ĺ���
*			��ѹ��֮��xml�ļ��������ڴ��У�����Cmarkup��SetDoc�������н���
*/
bool CDialogBuilder::LoadFromMem( LPCTSTR pstrFilename, int encoding )
{
	CStdString sFile = CPaintManagerUI::GetResourcePath();
	sFile += CPaintManagerUI::GetResourceZip();
	HZIP hz = NULL;
	if( CPaintManagerUI::IsCachedResourceZip() ) 
		hz = (HZIP)CPaintManagerUI::GetResourceZipHandle();
	else
		hz = OpenZip((void*)sFile.GetData(), 0, 2);
	if( hz == NULL ) 
		return _Failed(_T("Error opening zip file"));
	ZIPENTRYW ze; 
	int i; 
	if( FindZipItem(hz, pstrFilename, true, &i, &ze) != 0 )
		return _Failed(_T("Could not find ziped file"));
	DWORD dwSize = ze.unc_size;
	if( dwSize == 0 ) 
		return _Failed(_T("File is empty"));
	if ( dwSize > 4096*1024 ) 
		return _Failed(_T("File too large"));
	wchar_t* pChart = new wchar_t[ dwSize ];
	char* pByte = new char[ dwSize ];
	int res = UnzipItem(hz, i, (void*)pByte, dwSize, 3);
	if( res != 0x00000000 && res != 0x00000600) {
		delete[] pByte;
		delete[] pChart;
	if( !CPaintManagerUI::IsCachedResourceZip() ) 
		CloseZip(hz);
	return _Failed(_T("Could not unzip file"));
	}
	MultiByteToWideChar(CP_UTF8,0,pByte,dwSize,pChart,dwSize);
	if( !CPaintManagerUI::IsCachedResourceZip() )
		CloseZip(hz);
	bool ret=m_xml.SetDoc(pChart);
	delete[] pChart;
	return ret;
}

bool CDialogBuilder::_Failed(LPCTSTR pstrError, LPCTSTR pstrLocation)
{
	// Register last error
	TRACE(_T("XML Error: %s"), pstrError);
	if( pstrLocation != NULL ) TRACE(pstrLocation);
	_tcsncpy(m_szErrorMsg, pstrError, (sizeof(m_szErrorMsg) / sizeof(m_szErrorMsg[0])) - 1);
	_tcsncpy(m_szErrorXML, pstrLocation != NULL ? pstrLocation : _T(""), lengthof(m_szErrorXML) - 1);
	return false; // Always return 'false'
}

/**
* @brief	�˺�����ʼxmlԪ����ؼ�����İ�
* 
* @param    IDialogBuilderCallback * pCallback	�û��Զ���ؼ�����
* @param    CPaintManagerUI * pManager	ȫ�ֻ�ͼ����Ϣ�������
* @param    CControlUI * pParent	�����������ڵ�ĸ��ڵ�
* @return	�������пؼ��ĸ��ڵ�
* @retval   CControlUI*
*			image��font��default��ͨ��Ԫ�أ�window������Ҳ�ڴβ���
*			parse�������������ؼ�������
*/
CControlUI* CDialogBuilder::Create( IDialogBuilderCallback* pCallback, CPaintManagerUI* pManager, CControlUI* pParent )
{
	if (!m_xml.IsWellFormed()||!(m_xml.FindElem()||m_xml.FindChildElem()))
		return NULL;
	m_pCallback = pCallback;
	if( pManager ) 
	{
		LPCTSTR pstrClass = NULL;
		int nAttributes = 0;
		LPCTSTR pstrName = NULL;
		LPCTSTR pstrValue = NULL;
		MCD_STR pName;
		MCD_STR pValue;
		MCD_STR pClass;
		LPTSTR pstr = NULL;
		while(m_xml.FindChildElem())
		{
			m_xml.IntoElem();
			pClass=m_xml.GetTagName();
			pstrClass=pClass.c_str();
			if( _tcscmp(pstrClass, _T("Image")) == 0 )
			{
				LPCTSTR pImageName = NULL;
				LPCTSTR pImageResType = NULL;
				DWORD mask = 0;
				for(int n=0;;n++)
				{
					if(!m_xml.GetNthAttrib(n,pName,pValue))
						break;	
					pstrName=pName.c_str();
					pstrValue=pValue.c_str();
					if( _tcscmp(pstrName, _T("name")) == 0 ) {
						pImageName = pstrValue;
					}
					else if( _tcscmp(pstrName, _T("restype")) == 0 ) {
						pImageResType = pstrValue;
					}
					else if( _tcscmp(pstrName, _T("mask")) == 0 ) {
						if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
						mask = _tcstoul(pstrValue, &pstr, 16);
					}
				}
				if( pImageName ) pManager->AddImage(pImageName, pImageResType, mask);
			}
			else if( _tcscmp(pstrClass, _T("Font")) == 0 )
			{
				LPCTSTR pFontName = NULL;
				int size = 12;
				bool bold = false;
				bool underline = false;
				bool italic = false;
				bool defaultfont = false;
				for(int n=0;;n++)
				{
					if(!m_xml.GetNthAttrib(n,pName,pValue))
						break;	
					pstrName=pName.c_str();
					pstrValue=pValue.c_str();
					if( _tcscmp(pstrName, _T("name")) == 0 ) 
					{
						pFontName = pstrValue;
					}
					else if( _tcscmp(pstrName, _T("size")) == 0 ) 
					{
						size = _tcstol(pstrValue, &pstr, 10);
					}
					else if( _tcscmp(pstrName, _T("bold")) == 0 )
					{
						bold = (_tcscmp(pstrValue, _T("true")) == 0);
					}
					else if( _tcscmp(pstrName, _T("underline")) == 0 )
					{
						underline = (_tcscmp(pstrValue, _T("true")) == 0);
					}
					else if( _tcscmp(pstrName, _T("italic")) == 0 ) 
					{
						italic = (_tcscmp(pstrValue, _T("true")) == 0);
					}
					else if( _tcscmp(pstrName, _T("default")) == 0 )
					{
						defaultfont = (_tcscmp(pstrValue, _T("true")) == 0);
					}
				}
			if( pFontName ) 
			{
				pManager->AddFont(pFontName, size, bold, underline, italic);
				if( defaultfont ) pManager->SetDefaultFont(pFontName, size, bold, underline, italic);
			}
		}
		else if( _tcscmp(pstrClass, _T("Default")) == 0 ) 
		{
//			LPCTSTR pControlName = NULL;
//			LPCTSTR pControlValue = NULL;
			MCD_STR pControlName ;
			MCD_STR pControlValue ;
			for(int n=0;;n++)
			{
				if(!m_xml.GetNthAttrib(n,pName,pValue))
					break;	
				pstrName=pName.c_str();
				pstrValue=pValue.c_str();
				if( _tcscmp(pstrName, _T ("name")) == 0)
				{
					pControlName = pValue;
				}
				else if( _tcscmp(pstrName, _T("value"))==0 ) 
				{
					pControlValue = pValue;
				}
			}
			if( !pControlName.empty() )
			{
				pManager->AddDefaultAttributeList(pControlName.c_str(), pControlValue.c_str());
			}
		}
		m_xml.OutOfElem();
	}
	m_xml.ResetPos();
	m_xml.FindElem(_T("Window"));
	pClass = m_xml.GetTagName();
	pstrClass=pClass.c_str();
	if( _tcscmp(pstrClass, _T("Window")) == 0)
	{
		if( pManager->GetPaintWindow() ) 
		{
			for(int n=0;;n++)
			{
				if(!m_xml.GetNthAttrib(n,pName,pValue))
					break;	
				pstrName=pName.c_str();
				pstrValue=pValue.c_str();
				if( _tcscmp(pstrName, _T("size")) == 0 )
				{
					LPTSTR pstr = NULL;
					int cx = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);    
					int cy = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr); 
					pManager->SetInitSize(cx, cy);
				} 
				else if( _tcscmp(pstrName, _T("sizebox")) == 0 ) 
				{
					RECT rcSizeBox = { 0 };
					LPTSTR pstr = NULL;
					rcSizeBox.left = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);    
					rcSizeBox.top = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);    
					rcSizeBox.right = _tcstol(pstr + 1, &pstr, 10);  ASSERT(pstr);    
					rcSizeBox.bottom = _tcstol(pstr + 1, &pstr, 10); ASSERT(pstr);    
					pManager->SetSizeBox(rcSizeBox);
				}
				else if( _tcscmp(pstrName, _T("caption")) == 0 )
				{
					RECT rcCaption = { 0 };
					LPTSTR pstr = NULL;
					rcCaption.left = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);    
					rcCaption.top = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);    
					rcCaption.right = _tcstol(pstr + 1, &pstr, 10);  ASSERT(pstr);    
					rcCaption.bottom = _tcstol(pstr + 1, &pstr, 10); ASSERT(pstr);    
					pManager->SetCaptionRect(rcCaption);
				}
				else if( _tcscmp(pstrName, _T("roundcorner")) == 0 )
				{
					LPTSTR pstr = NULL;
					int cx = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);    
					int cy = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr); 
					pManager->SetRoundCorner(cx, cy);
				} 
				else if( _tcscmp(pstrName, _T("mininfo")) == 0 ) 
				{
					LPTSTR pstr = NULL;
					int cx = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);    
					int cy = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr); 
					pManager->SetMinInfo(cx, cy);
				}
				else if( _tcscmp(pstrName, _T("maxinfo")) == 0 )
				{
					LPTSTR pstr = NULL;
					int cx = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);    
					int cy = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr); 
					pManager->SetMaxInfo(cx, cy);
				}
				else if( _tcscmp(pstrName, _T("showdirty")) == 0 )
				{
					pManager->SetShowUpdateRect(_tcscmp(pstrValue, _T("true")) == 0);
				} 
				else if( _tcscmp(pstrName, _T("alpha")) == 0 )
				{
					pManager->SetTransparent(_ttoi(pstrValue));
				} 
				else if( _tcscmp(pstrName, _T("bktrans")) == 0 )
				{
					pManager->SetBackgroundTransparent(_tcscmp(pstrValue, _T("true")) == 0);
				} 
				else if( _tcscmp(pstrName, _T("disabledfontcolor")) == 0 )
				{
					if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
					LPTSTR pstr = NULL;
					DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
					pManager->SetDefaultDisabledColor(clrColor);
				} 
				else if( _tcscmp(pstrName, _T("defaultfontcolor")) == 0 )
				{
					if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
					LPTSTR pstr = NULL;
					DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
					pManager->SetDefaultFontColor(clrColor);
				}
				else if( _tcscmp(pstrName, _T("linkfontcolor")) == 0 ) 
				{
					if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
					LPTSTR pstr = NULL;
					DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
					pManager->SetDefaultLinkFontColor(clrColor);
				} 
				else if( _tcscmp(pstrName, _T("linkhoverfontcolor")) == 0 ) 
				{
					if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
					LPTSTR pstr = NULL;
					DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
					pManager->SetDefaultLinkHoverFontColor(clrColor);
				} 
				else if( _tcscmp(pstrName, _T("selectedcolor")) == 0 ) 
				{
					if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
					LPTSTR pstr = NULL;
					DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
					pManager->SetDefaultSelectedBkColor(clrColor);
				} 
			}
		}
	}
	}
	m_xml.ResetPos();
//	m_xml.FindElem(_T("Window"));
	m_xml.FindElem();
	m_xml.IntoElem();
	return parse(pParent, pManager);
}

/**
* @brief	�������ÿؼ������ֵȶ���
* 
* @param    CControlUI * pParent	���ؼ�
* @param    CPaintManagerUI * pManager	��ͼ����Ϣ����
* @return	�������ɵĿؼ�����
* @retval   CControlUI*
*			parse��һ���ݹ麯����FindElem����������һ��Ԫ�أ�û���򷵻�falseѭ������
*			GetTagName�����õ�Ԫ�����ƣ���switch��ƥ���ַ���������ؼ�����
*			����Ե�ǰ�ؼ�Ϊ���ؼ��ݹ����parse���Ե�ǰ�ؼ�������������
*/
CControlUI* CDialogBuilder::parse(CControlUI* pParent,CPaintManagerUI* pManager)
{
	IContainerUI* pContainer = NULL;
	CDialogLayoutUI* pDialogLayout = NULL;
	CControlUI* pReturn = NULL;
	m_xml.ResetMainPos ();
	while(m_xml.FindElem())
	{
		MCD_STR pClass = m_xml.GetTagName();
		LPCTSTR pstrClass=pClass.c_str();
		if( _tcscmp(pstrClass, _T("Image")) == 0 || _tcscmp(pstrClass, _T("Font")) == 0 \
			|| _tcscmp(pstrClass, _T("Default")) == 0 ) 
			continue;
		CControlUI* pControl = NULL;
		///����xml��include����
		if( _tcscmp(pstrClass, _T("Include")) == 0 ) 
		{
			MCD_STR pName;
			MCD_STR pValue;
			LPCTSTR pstrName;
			LPCTSTR pstrValue;
			for(int n=0;;n++)
			{
				if(!m_xml.GetNthAttrib(n,pName,pValue))
					break;	
		        pstrName=pName.c_str();
				pstrValue=pValue.c_str();
				if(_tcscmp(pstrName, _T("source")) == 0)
				{
				    CDialogBuilder builder;
				    pControl = builder.Create(pstrValue, m_pCallback, pManager, pParent);
				}
			}
			
			continue;
		}
		SIZE_T cchLen = _tcslen(pstrClass);
		switch( cchLen ) 
		{
			case 4:
				if( _tcscmp(pstrClass, _T("Edit")) == 0 )                   pControl = new CEditUI;
				else if( _tcscmp(pstrClass, _T("List")) == 0 )              pControl = new CListUI;
				else if( _tcscmp(pstrClass, _T("Text")) == 0 )              pControl = new CTextUI;
				break;
			case 5:
				if( _tcscmp(pstrClass, _T("Combo")) == 0 )                  pControl = new CComboUI;
				else if( _tcscmp(pstrClass, _T("Label")) == 0 )             pControl = new CLabelUI;
				break;
			case 6:
				if( _tcscmp(pstrClass, _T("Button")) == 0 )                 pControl = new CButtonUI;
				else if( _tcscmp(pstrClass, _T("Option")) == 0 )            pControl = new COptionUI;
				else if( _tcscmp(pstrClass, _T("Slider")) == 0 )            pControl = new CSliderUI;
				break;
			case 7:
				if( _tcscmp(pstrClass, _T("Control")) == 0 )                pControl = new CControlUI;
				else if( _tcscmp(pstrClass, _T("ActiveX")) == 0 )           pControl = new CActiveXUI;
				break;
			case 8:
				if( _tcscmp(pstrClass, _T("Progress")) == 0 )               pControl = new CProgressUI;
				else if (_tcscmp(pstrClass, _T("RichEdit")) == 0)			pControl = new CRichEditUI;
				break;
			case 9:
				if( _tcscmp(pstrClass, _T("Container")) == 0 )              pControl = new CContainerUI;
				else if( _tcscmp(pstrClass, _T("TabLayout")) == 0 )         pControl = new CTabLayoutUI;
				else if( _tcscmp(pstrClass, _T("ScrollBar")) == 0 )         pControl = new CScrollBarUI; 
				break;
			case 10:
				if( _tcscmp(pstrClass, _T("ListHeader")) == 0 )             pControl = new CListHeaderUI;
				else if( _tcscmp(pstrClass, _T("TileLayout")) == 0 )        pControl = new CTileLayoutUI;
				else if(_tcscmp(pstrClass, _T("PictureBox")) == 0  )		pControl = new CPictureBox;
				break;
			case 12:
				if( _tcscmp(pstrClass, _T("DialogLayout")) == 0 )           pControl = new CDialogLayoutUI;
				break;
			case 14:
				if( _tcscmp(pstrClass, _T("VerticalLayout")) == 0 )         pControl = new CVerticalLayoutUI;
				else if( _tcscmp(pstrClass, _T("ListHeaderItem")) == 0 )    pControl = new CListHeaderItemUI;
				break;
			case 15:
				if( _tcscmp(pstrClass, _T("ListTextElement")) == 0 )        pControl = new CListTextElementUI;
				break;
			case 16:
				if( _tcscmp(pstrClass, _T("HorizontalLayout")) == 0 )       pControl = new CHorizontalLayoutUI;
				else if( _tcscmp(pstrClass, _T("ListLabelElement")) == 0 )  pControl = new CListLabelElementUI;
				break;
			case 20:
				if( _tcscmp(pstrClass, _T("ListContainerElement")) == 0 )   pControl = new CListContainerElementUI;
				break;
		}
		/**
		 *���pControlΪ����˵����ǰ�ؼ����ڿ���û�ҵ�����ǰ�ؼ�Ϊ�û��Զ���ؼ�
		 *�����ڲ�����ң��Ҳ�������m_pCallback�ص���������
		 */
		if( pControl == NULL ) 
		{
			CStdPtrArray* pPlugins = CPaintManagerUI::GetPlugins();
			LPCREATECONTROL lpCreateControl = NULL;
			for( int i = 0; i < pPlugins->GetSize(); ++i ) 
			{
				lpCreateControl = (LPCREATECONTROL)pPlugins->GetAt(i);
				if( lpCreateControl != NULL ) 
				{
					pControl = lpCreateControl(pstrClass);
					if( pControl != NULL ) break;
				}
			}
		}
		if( pControl == NULL && m_pCallback != NULL )
		{
			pControl = m_pCallback->CreateControl(pstrClass);
		}
		ASSERT(pControl);
		if( pControl == NULL ) continue;
		/** 
		 *�Ե�ǰ�ؼ����ӿؼ���������
		 */
		while(m_xml .FindChildElem())
		{
			m_xml.IntoElem ();
			parse(pControl,pManager);
			m_xml.OutOfElem ();
		}
		if( pParent != NULL ) 
		{
			if( pContainer == NULL ) 
				pContainer = static_cast<IContainerUI*>(pParent->GetInterface(_T("IContainer")));
			ASSERT(pContainer);
			if( pContainer == NULL )
				return NULL;
			if( !pContainer->Add(pControl) ) 
			{
				delete pControl;
				continue;
			}
		}
		if( pManager ) 
		{
			pControl->SetManager(pManager, NULL, false);
			LPCTSTR pDefaultAttributes = pManager->GetDefaultAttributeList(pstrClass);
			if( pDefaultAttributes )
			{
				 /** ��ͨ������Ӧ�õ���ǰ�ؼ� */
				pControl->ApplyAttributeList(pDefaultAttributes);
			}
		}
		LPCTSTR pstrName = NULL;
		LPCTSTR pstrValue = NULL;
		MCD_STR pName;
		MCD_STR pValue;
		 /** �Կؼ������������� */
		for(int n=0;;n++)
		{
			if(!m_xml.GetNthAttrib(n,pName,pValue))
			break;
			pstrName=pName.c_str();
			pstrValue=pValue.c_str();
			// Set ordinary attributes
			pControl->SetAttribute(pstrName, pstrValue);
			
			if (_tcscmp(pstrName, _T("stretch")) == 0 )
			{
				if( pParent == NULL ) continue;

				if( pDialogLayout == NULL ) pDialogLayout = static_cast<CDialogLayoutUI*>(pParent->GetInterface(_T("DialogLayout")));
				ASSERT(pDialogLayout);
				if( pDialogLayout == NULL ) continue;

				UINT uMode = 0;
				if( _tcsstr(pstrValue, _T("move_x")) != NULL ) uMode |= UISTRETCH_MOVE_X;
				if( _tcsstr(pstrValue, _T("move_y")) != NULL ) uMode |= UISTRETCH_MOVE_Y;
				if( _tcsstr(pstrValue, _T("move_xy")) != NULL ) uMode |= UISTRETCH_MOVE_X | UISTRETCH_MOVE_Y;
				if( _tcsstr(pstrValue, _T("size_x")) != NULL ) uMode |= UISTRETCH_SIZE_X;
				if( _tcsstr(pstrValue, _T("size_y")) != NULL ) uMode |= UISTRETCH_SIZE_Y;
				if( _tcsstr(pstrValue, _T("size_xy")) != NULL ) uMode |= UISTRETCH_SIZE_X | UISTRETCH_SIZE_Y;
				if( _tcsstr(pstrValue, _T("group")) != NULL ) uMode |= UISTRETCH_NEWGROUP;
				if( _tcsstr(pstrValue, _T("line")) != NULL ) uMode |= UISTRETCH_NEWLINE;
				pDialogLayout->SetStretchMode(pControl, uMode);
			}
		}
		if( pManager ) 
		{
			pControl->SetManager(NULL, NULL, false);
		}
		if( pReturn == NULL ) pReturn = pControl;
	}
	return pReturn;
}

} // namespace CULib
#endif
