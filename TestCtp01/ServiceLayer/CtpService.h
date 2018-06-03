#ifndef _CTP_SERVICE_H_
#define _CTP_SERVICE_H_

#include "iservice.h"
class CtpService :
	public IService
{
public:
	CtpService(void);
	virtual ~CtpService(void);
};

#endif