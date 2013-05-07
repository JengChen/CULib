/**  
*  @file	 CUDelegate.h   
*  @brief  
*  @author        
*  @date  
*  @version    
*/
#ifndef __CUDELEGATE_H__
#define __CUDELEGATE_H__

#pragma once
namespace CULib{

/** ί��ģʽ�е������ */ 
class CULIB_API CDelegateBase	 
{
public:
	/** ���캯����pObjectΪί���ߵĶ��� pFnΪִ�з��� */
	CDelegateBase(void* pObject, void* pFn);
	CDelegateBase(const CDelegateBase& rhs);

	virtual ~CDelegateBase();

	/** �Ƚ�����ί����, true һ�� false��ͬ */
	bool Equals(const CDelegateBase& rhs) const;

	/** ��Ӧί�н��д��� eventΪ��Ӧ���¼� */
	bool operator() (void* param);

	/** ����һ��ί���� */
	virtual CDelegateBase* Copy() = 0;

protected:
	/** �õ�ִ�з��� */
	void* GetFn();

	/** �õ�ί���߶��� */
	void* GetObject();

	/** ����ִ�з��� */
	virtual bool Invoke(void* param) = 0;

private:
	void* m_pObject;
	void* m_pFn;
};

/** ��̬ί�У�ί����Ϊ�գ�����ִ�й��� */
class CDelegateStatic: public CDelegateBase
{
	typedef bool (*Fn)(void*);
public:
	CDelegateStatic(Fn pFn) : CDelegateBase(NULL, pFn) { } 
	CDelegateStatic(const CDelegateStatic& rhs) : CDelegateBase(rhs) { } 
	virtual CDelegateBase* Copy() { return new CDelegateStatic(*this); }

protected:
	virtual bool Invoke(void* param)
	{
		Fn pFn = (Fn)GetFn();
		return (*pFn)(param); 
	}
};

template <class O, class T>
class CDelegate : public CDelegateBase
{
	typedef bool (T::* Fn)(void*);
public:
	CDelegate(O* pObj, Fn pFn) : CDelegateBase(pObj, &pFn), m_pFn(pFn) { }
	CDelegate(const CDelegate& rhs) : CDelegateBase(rhs) { m_pFn = rhs.m_pFn; } 
	virtual CDelegateBase* Copy() { return new CDelegate(*this); }

protected:
	virtual bool Invoke(void* param)
	{
		O* pObject = (O*) GetObject();
		return (pObject->*m_pFn)(param); 
	}  

private:
	Fn m_pFn;
};

/** ����ί�� */
template <class O, class T>
CDelegate<O, T> MakeDelegate(O* pObject, bool (T::* pFn)(void*))
{
	return CDelegate<O, T>(pObject, pFn);
}
inline CDelegateStatic MakeDelegate(bool (*pFn)(void*))
{
	return CDelegateStatic(pFn); 
}

/** �¼�Դ */
class CULIB_API CEventSource
{
	typedef bool (*FnType)(void*);
public:
	~CEventSource();
	operator bool();

	/** ����һ��ί���� */
	void operator+= (CDelegateBase& d);
	void operator+= (FnType pFn);

	/** ɾ��һ��ί���� */
	void operator-= (CDelegateBase& d);
	void operator-= (FnType pFn);

	/** ��Ӧ�¼����д��� */
	bool operator() (void* param);

protected:
	CStdPtrArray m_aDelegates;
};

}
#endif