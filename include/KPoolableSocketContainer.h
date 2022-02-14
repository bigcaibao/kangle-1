/*
 * KPoolableStreamContainer.h
 *
 *  Created on: 2010-8-18
 *      Author: keengo
 */

#ifndef KPOOLABLESTREAMCONTAINER_H_
#define KPOOLABLESTREAMCONTAINER_H_
#include <list>
#include "global.h"
#include "KUpstream.h"
#include "KStringBuf.h"
#include "KMutex.h"
#include "KCountable.h"
#include "time_utils.h"
#include "KHttpEnv.h"
void SafeDestroyUpstream(KUpstream *st);
/*
 * ���ӳ�������
 */
class KPoolableSocketContainerImp {
public:
	KPoolableSocketContainerImp();
	~KPoolableSocketContainerImp();
	void refresh(bool clean);
	void refreshList(kgl_list *l, bool clean);
	kgl_list *GetList()
	{
		return &head;
	}	
	unsigned size;
protected:
	kgl_list head;
};
class KPoolableSocketContainer: public KCountableEx {
public:
	KPoolableSocketContainer();
	virtual ~KPoolableSocketContainer();
	KUpstream *GetPoolSocket(KHttpRequest *rq);
	/*
	��������
	close,�Ƿ�ر�
	lifeTime ����ʱ��
	*/
	virtual void gcSocket(KUpstream *st,int lifeTime, time_t base_time);
	void bind(KUpstream *st);
	void unbind(KUpstream *st);
	int getLifeTime() {
		return lifeTime;
	}
	kgl_refs_string *GetParam();
	void SetParam(const char *param);
	/*
	 * �������ӳ�ʱʱ��
	 */
	void setLifeTime(int lifeTime);
	/*
	 * ����ˢ��ɾ����������
	 */
	virtual void refresh(time_t nowTime);
	/*
	 * �����������
	 */
	void clean();
	/*
	 * �õ�������
	 */
	unsigned getSize() {
		unsigned size = 0;
		lock.Lock();
		if (imp) {
			size = imp->size;
		}
		lock.Unlock();
		return size;
	}
	//isBad,isGood���ڼ���������
	virtual void isBad(KUpstream *st,BadStage stage)
	{
	}
	virtual void isGood(KUpstream *st)
	{
	}

#ifdef HTTP_PROXY
	virtual void addHeader(KHttpRequest *rq,KHttpEnv *s)
	{
	}
#endif
protected:
	/*
	 * �����������������
	 */
	void PutPoolSocket(KUpstream *st);
	kgl_refs_string *param;
	int lifeTime;	
	KMutex lock;
private:
	KUpstream *internalGetPoolSocket(KHttpRequest *rq);
	time_t getHttp2ExpireTime()
	{
		int lifeTime = this->lifeTime;
		if (lifeTime <= 10) {
			//http2����10������ʱ��
			lifeTime = 10;
		}
		return kgl_current_sec + lifeTime;
	}
	KPoolableSocketContainerImp *imp;
};
#endif /* KPOOLABLESTREAMCONTAINER_H_ */
