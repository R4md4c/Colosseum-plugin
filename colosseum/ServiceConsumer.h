#ifndef CSERVICE_CONSUMER_H
#define CSERVICE_CONSUMER_H


#include "soapCustomBinding_USCOREIService1Proxy.h"
#include <iostream>
#include <sstream>
/**
	This class is the main class for consuming the service.
	Provide the same methods that the service provides.
*/
class CServiceConsumer
{
protected:
	CustomBinding_USCOREIService1Proxy m_proxy;
	
	std::string m_endpointString;
	/// ostringstream object for receiving the error
	std::ostringstream m_error;

public:
	CServiceConsumer(const char *endpoint);
	CServiceConsumer();
	~CServiceConsumer();

	std::string		getEndpointString() {
		return m_endpointString;
	}

	void			setEndpointString(const std::string& _endpoint) {
		m_endpointString = _endpoint;
		m_proxy.soap_endpoint = m_endpointString.c_str();
	}
	int				getLimit();
	std::string		openSession(int fileId);
	void			closeSession(std::string uuid);
	std::string		getObject(std::string uuid, std::string entityName, int offset);
	int				LinesCount(std::string uuid);
	CustomBinding_USCOREIService1Proxy& getProxy();
	
};

#endif