#pragma once
#include <fstream>
#include <Windows.h>

#include "CULib.h"

using namespace std;

using namespace CULib;

/************************************************************************/
/* ʹ�ø�����Ҫ���� ���� CreateLog(LogFileName) ����һ��LogFile, Ȼ��
	ÿ�ε��� AppendLog(strMsg) ���ļ�����������
                                                                     */
/************************************************************************/

class GELog  
{
public:
	/** ������c_pGELogָ�� */
	void FinalCleanup();

	/** �õ�Ψһ��Logָ�� */
	static GELog * GetSingleton() { return c_pGELog; };

	/** ����־�ļ��м�����Ϣ \n
	 * @param [string]	errFile: �ļ��� һ��Ҫд __FILE__
	 * @return �Ƿ���ӳɹ�
	 */
	bool AppendLog(LPCTSTR pstrFormat, ...);
	void GetSyStime();

	/** �����µ���־�ļ�,ͬʱ��رվɵ���־�ļ� \n
	 * @param [string] strLogFileName : �µ���־�ļ���
	 * @return �Ƿ񴴽��ɹ�
	 */
	bool CreateLog(CStdString strLogFileName);

	
	virtual ~GELog();

private:
	GELog();

protected:
	CStdString m_slog;
	CStdString m_logname;
	CStdString m_buffer;
	CStdString m_time;
	SYSTEMTIME m_date;
	char* m_strdate;
	DWORD m_pos;
	HANDLE hFile;
	bool showtime;
	
	/** ��̬���Աָ��,����GetSingleton*/
	static GELog * c_pGELog;

};