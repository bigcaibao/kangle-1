#ifndef KSYNCFETCHOBJECT_H
#define KSYNCFETCHOBJECT_H
#include "KFetchObject.h"
/**
* ͬ��������չ������Ҫ��ͬ�����õ���չ���Ӹ���̳�
*/
#if 0
class KSyncFetchObject : public KFetchObject
{
public:
#ifdef ENABLE_REQUEST_QUEUE
	virtual bool needQueue()
	{
		return true;
	}
#endif
};
#endif
#endif
