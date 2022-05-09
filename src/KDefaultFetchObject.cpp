#include "KDefaultFetchObject.h"
#include "KStaticFetchObject.h"
#include "KHttpRequest.h"
#include "KDirectoryFetchObject.h"
#include "HttpFiber.h"
#include "KSubVirtualHost.h"
#include "KVirtualHost.h"

KGL_RESULT KDefaultFetchObject::Open(KHttpRequest* rq, kgl_input_stream* in, kgl_output_stream* out)
{
	if (rq->file->isDirectory()) {
		if (!rq->file->isPrevDirectory()) {
			//url���治����/��β,�ض�����
			if (rq->sink->data.meth == METH_GET) {
				KPrevDirectoryFetchObject fo;
				return fo.Open(rq, in, out);
			} else {
				return out->f->write_message(out, rq, KGL_MSG_ERROR, "method not allowed", STATUS_METH_NOT_ALLOWED);
			}
		}
		auto svh = rq->get_virtual_host();
		if (!svh->vh->browse) {
			//����������
			return out->f->write_message(out, rq, KGL_MSG_ERROR, "You don't have permission to browse.", STATUS_FORBIDEN);
		}
		KDirectoryFetchObject fo;
		return fo.Open(rq, in, out);
	}
	KStaticFetchObject fo;
	return fo.Open(rq, in, out);
}
