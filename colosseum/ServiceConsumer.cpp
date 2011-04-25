#include "stdafx.h"
#include "ServiceConsumer.h"

CServiceConsumer::CServiceConsumer(const char* _endpoint)
{
	m_proxy.soap_endpoint = _endpoint;
}

CServiceConsumer::~CServiceConsumer()
{
	m_proxy.destroy();
}


std::string CServiceConsumer::openSession(int fileId)
{
	_ns1__OpenSession param;
	param.fileId = &fileId;
	_ns1__OpenSessionResponse response;
	if(m_proxy.OpenSession(&param, &response) == SOAP_OK)
		return *(response.OpenSessionResult);
	else  {
		m_proxy.soap_stream_fault(m_error);
		throw std::exception(m_error.str().c_str());
	}
}

int CServiceConsumer::getLimit()
{
	_ns1__getLimit  param;
	_ns1__getLimitResponse response;
	
	if( m_proxy.getLimit(&param, &response) == SOAP_OK )
		return *(response.getLimitResult);
	else  {
		m_proxy.soap_stream_fault(m_error);
		throw std::exception(m_error.str().c_str());
	}
}

void CServiceConsumer::closeSession(std::string uuid)
{
	_ns1__CloseSession param;
	_ns1__CloseSessionResponse response;
	param.uuid = &uuid;
	if(m_proxy.CloseSession(&param, &response) == SOAP_OK)
		return;
	else {
		m_proxy.soap_stream_fault(m_error);
		throw std::exception(m_error.str().c_str());
	}
}

std::string CServiceConsumer::getObject(std::string uuid, std::string entityName, int offset)
{
	_ns1__getObject param;
	_ns1__getObjectResponse response;
	param.uuid = &uuid;
	param.entityName = &entityName;
	param.offset = &offset;

	if(m_proxy.getObject(&param, &response) == SOAP_OK)
		return *(response.getObjectResult);
	else {
		m_proxy.soap_stream_fault(m_error);
		throw std::exception(m_error.str().c_str());
	}
}

int	CServiceConsumer::LinesCount(std::string uuid)
{
	_ns1__LinesCount param;
	_ns1__LinesCountResponse response;
	param.uuid = &uuid;
	
	if( m_proxy.LinesCount(&param, &response) == SOAP_OK )
		return *(response.LinesCountResult);
	else {
		m_proxy.soap_stream_fault(m_error);
		throw std::exception(m_error.str().c_str());
	}
}