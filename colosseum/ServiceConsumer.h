#ifndef CSERVICE_CONSUMER_H
#define CSERVICE_CONSUMER_H


#include "soapCustomBinding_USCOREIService1Proxy.h"
#include <iostream>
#include <sstream>
/**
	This class is the main class for consuming the service.
	Provide the same methods that the service contains.
*/
class CServiceConsumer
{
protected:
	CustomBinding_USCOREIService1Proxy m_proxy;
	
	/// ostringstream object for receiving the error
	std::ostringstream m_error;

public:
	CServiceConsumer(const char *endpoint);
	~CServiceConsumer();
	int getLimit();
	std::string openSession(int fileId);
	void closeSession(std::string uuid);
	std::string getObject(std::string uuid, std::string entityName, int offset);
	
};

#endif