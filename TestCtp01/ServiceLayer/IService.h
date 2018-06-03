#ifndef _ISERVICE_H_
#define _ISERVICE_H_
#endif
#include <string>
using namespace std;

class IService
{
public:
	virtual bool login(string username, string password, BrokerServer bs);
	IService(void);
	virtual ~IService(void);
};

#endif // _ISERVICE_H_