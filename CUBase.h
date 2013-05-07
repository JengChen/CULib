/**  
*  @file  CUBase.h  
*  @brief  
*  @author        
*  @date  
*  @version  
*   
*/
#ifndef __CUBASE_H_
#define __CUBASE_H_

#pragma once

#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))

namespace CULib{

#define WC_EDIT                L"Edit"

/** ��ʾ���������ļ������Լ�expr������ */
#ifndef ASSERT
#define ASSERT(expr)  _ASSERTE(expr)
#endif

#ifdef _DEBUG
#ifndef TRACE
#define TRACE __Trace
#endif
#define TRACEMSG __TraceMsg
#else
#ifndef TRACE
#define TRACE
#endif
#define TRACEMSG _T("")
#endif

/** ��windows��Ϣת�������Ӧ�ĺ��� */
void CULIB_API __Trace(LPCTSTR pstrFormat, ...);
LPCTSTR CULIB_API __TraceMsg(UINT uMsg);

/** ����ͳһ������ԴID���ַ��� */
class  STRINGorID
{
public:
	STRINGorID(LPCTSTR lpString) : m_lpstr(lpString)
	{ }
	STRINGorID(UINT nID) : m_lpstr(MAKEINTRESOURCE(nID))
	{ }
	LPCTSTR m_lpstr;
};

/** �����ĳ��� */
class CULIB_API CPoint : public tagPOINT
{
public:
	CPoint();
	CPoint(const POINT& src);
	CPoint(int x, int y);
	CPoint(LPARAM lParam);
};

/** �����С�ĳ��� */
class CULIB_API CSize : public tagSIZE
{
public:
	CSize();
	CSize(const SIZE& src);
	CSize(const RECT rc);
	CSize(int cx, int cy);
};

/** ������״�ĳ��� */
class CULIB_API CRect : public tagRECT
{
public:
	CRect();
	CRect(const RECT& src);
	CRect(int iLeft, int iTop, int iRight, int iBottom);

	int GetWidth() const;
	int GetHeight() const;
	void Empty();
	bool IsNull() const;
	void Join(const RECT& rc);
	void ResetOffset();
	void Normalize();
	void Offset(int cx, int cy);
	void Inflate(int cx, int cy);
	void Deflate(int cx, int cy);
	void Union(CRect& rc);
};

/**  ָ������ */
class CULIB_API CStdPtrArray
{
public:
	CStdPtrArray(int iPreallocSize = 0);
	CStdPtrArray(const CStdPtrArray& src);
	~CStdPtrArray();

	void Empty();
	void Resize(int iSize);
	bool IsEmpty() const;
	int Find(LPVOID iIndex) const;
	bool Add(LPVOID pData);
	bool SetAt(int iIndex, LPVOID pData);
	bool InsertAt(int iIndex, LPVOID pData);
	bool Remove(int iIndex);
	int GetSize() const;
	LPVOID* GetData();

	LPVOID GetAt(int iIndex) const;
	LPVOID operator[] (int nIndex) const;

protected:
	LPVOID* m_ppVoid;
	int m_nCount;
	int m_nAllocated;
};

/**  ֵ���� */
class CULIB_API CStdValArray
{
public:
	CStdValArray(int iElementSize, int iPreallocSize = 0);
	~CStdValArray();

	void Empty();
	bool IsEmpty() const;
	bool Add(LPCVOID pData);
	bool Remove(int iIndex);
	int GetSize() const;
	LPVOID GetData();

	LPVOID GetAt(int iIndex) const;
	LPVOID operator[] (int nIndex) const;

protected:
	LPBYTE m_pVoid;
	int m_iElementSize;
	int m_nCount;
	int m_nAllocated;
};

/** �ַ�����װ */
class CULIB_API CStdString
{
public:
	enum { MAX_LOCAL_STRING_LEN = 63 };

	CStdString();
	CStdString(const TCHAR ch);
	CStdString(const CStdString& src);
	CStdString(LPCTSTR lpsz, int nLen = -1);
	~CStdString();

	void Empty();

	/** �õ��ַ����ĳ��� */
	int GetLength() const;
	/** �ж��ַ����Ƿ�Ϊ�� */
	bool IsEmpty() const;
	/** ��ȡ����������λ�õ��ַ� */
	TCHAR GetAt(int nIndex) const;
	void SetAt(int nIndex, TCHAR ch);
	void Append(LPCTSTR pstr);

	/** ���䲢�洢�ַ��� */
	void Assign(LPCTSTR pstr, int nLength = -1);
	LPCTSTR GetData();

	operator LPCTSTR() const;

	TCHAR operator[] (int nIndex) const;
	const CStdString& operator=(const CStdString& src);
	const CStdString& operator=(const TCHAR ch);
	const CStdString& operator=(LPCTSTR );

	const CStdString& CStdString::operator=(LPCSTR lpStr);
	const CStdString& CStdString::operator+=(LPCSTR lpStr);

	CStdString operator+(const CStdString& src) const;
	CStdString operator+(LPCTSTR pstr) const;
	const CStdString& operator+=(const CStdString& src);
	const CStdString& operator+=(LPCTSTR pstr);
	const CStdString& operator+=(const TCHAR ch);

	bool operator == (LPCTSTR str) const;
	bool operator != (LPCTSTR str) const;
	bool operator <= (LPCTSTR str) const;
	bool operator <  (LPCTSTR str) const;
	bool operator >= (LPCTSTR str) const;
	bool operator >  (LPCTSTR str) const;

	int Compare(LPCTSTR pstr) const;
	int CompareNoCase(LPCTSTR pstr) const;

	void MakeUpper();
	void MakeLower();

	CStdString Left(int nLength) const;
	CStdString Mid(int iPos, int nLength = -1) const;
	CStdString Right(int nLength) const;

	int Find(TCHAR ch, int iPos = 0) const;
	int Find(LPCTSTR pstr, int iPos = 0) const;
	int ReverseFind(TCHAR ch) const;
	int Replace(LPCTSTR pstrFrom, LPCTSTR pstrTo);

	int __cdecl Format(LPCTSTR pstrFormat, ...);
	int __cdecl SmallFormat(LPCTSTR pstrFormat, ...);

protected:
	LPTSTR m_pstr;
	TCHAR m_szBuffer[MAX_LOCAL_STRING_LEN + 1];
};


struct TITEM
{
	CStdString Key;
	LPVOID Data;
	struct TITEM* pNext;
};

/** �ַ���-ָ��map */
class CULIB_API CStdStringPtrMap
{
public:
	CStdStringPtrMap(int nSize = 83);
	~CStdStringPtrMap();

	void Resize(int nSize = 83);
	LPVOID Find(LPCTSTR key) const;
	bool Insert(LPCTSTR key, LPVOID pData);
	LPVOID Set(LPCTSTR key, LPVOID pData);
	bool Remove(LPCTSTR key);
	int GetSize() const;
	LPCTSTR GetAt(int iIndex) const;
	LPCTSTR operator[] (int nIndex) const;
protected:
	TITEM** m_aT;
	int m_nBuckets;
};

/** ���ڵķ�װ�� */
class CULIB_API CWindowWnd
{
public:
	CWindowWnd();

	HWND GetHWND() const;
	operator HWND() const;

	/** RegisterClass�ķ�װ */
	bool RegisterWindowClass();

	/** ���໯���� */
	bool RegisterSuperclass();

	HWND Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, const RECT rc, HMENU hMenu = NULL);
	HWND Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT, HMENU hMenu = NULL);
	HWND Subclass(HWND hWnd);
	void Unsubclass();
	void ShowWindow(bool bShow = true, bool bTakeFocus = true);
	UINT ShowModal();
	void Close(UINT nRet = IDOK);
	void CenterWindow();
	void SetIcon(UINT nRes);

	LRESULT SendMessage(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L);
	LRESULT PostMessage(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L);
	void ResizeClient(int cx = -1, int cy = -1);

protected:
	virtual LPCTSTR GetWindowClassName() const = 0;
	virtual LPCTSTR GetSuperClassName() const;
	virtual UINT GetClassStyle() const;

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual void OnFinalMessage(HWND hWnd);

	static LRESULT CALLBACK __WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK __ControlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	HWND m_hWnd;
	WNDPROC m_OldWndProc;
	bool m_bSubclassed;
};

/** 
 *@brief	ɳ©�����
 *���캯�������������״Ϊɳ©
 *���������л�ԭ�����״
 */
class CULIB_API CWaitCursor
{
public:
	CWaitCursor();
	~CWaitCursor();

protected:
	HCURSOR m_hOrigCursor;
};

}

#endif