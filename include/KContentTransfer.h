#ifndef KCONTENTTRANSFER_H
#define KCONTENTTRANSFER_H
#include "KHttpStream.h"
#include "KHttpRequest.h"

/*
���ݱ任
*/
class KContentTransfer : public KHttpStream
{
public:
	KContentTransfer(KWriteStream *st, bool autoDelete) : KHttpStream(st, autoDelete)
	{

	}
	StreamState write_all(KHttpRequest *rq,const char *str,int len);
};
#endif
