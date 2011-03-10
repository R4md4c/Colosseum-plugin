/* soapCustomBinding_USCOREIService1Proxy.h
   Generated by gSOAP 2.7.16 from colosseumService.h
   Copyright(C) 2000-2010, Robert van Engelen, Genivia Inc. All Rights Reserved.
   This part of the software is released under one of the following licenses:
   GPL, the gSOAP public license, or Genivia's license for commercial use.
*/

#ifndef soapCustomBinding_USCOREIService1Proxy_H
#define soapCustomBinding_USCOREIService1Proxy_H
#include "soapH.h"

class SOAP_CMAC CustomBinding_USCOREIService1Proxy : public soap
{ public:
	/// Endpoint URL of service 'CustomBinding_USCOREIService1Proxy' (change as needed)
	const char *soap_endpoint;
	/// Constructor
	CustomBinding_USCOREIService1Proxy();
	/// Constructor with copy of another engine state
	CustomBinding_USCOREIService1Proxy(const struct soap&);
	/// Constructor with engine input+output mode control
	CustomBinding_USCOREIService1Proxy(soap_mode iomode);
	/// Constructor with engine input and output mode control
	CustomBinding_USCOREIService1Proxy(soap_mode imode, soap_mode omode);
	/// Destructor frees deserialized data
	virtual	~CustomBinding_USCOREIService1Proxy();
	/// Initializer used by constructors
	virtual	void CustomBinding_USCOREIService1Proxy_init(soap_mode imode, soap_mode omode);
	/// Delete all deserialized data (uses soap_destroy and soap_end)
	virtual	void destroy();
	/// Disables and removes SOAP Header from message
	virtual	void soap_noheader();
	/// Get SOAP Fault structure (NULL when absent)
	virtual	const SOAP_ENV__Fault *soap_fault();
	/// Get SOAP Fault string (NULL when absent)
	virtual	const char *soap_fault_string();
	/// Get SOAP Fault detail as string (NULL when absent)
	virtual	const char *soap_fault_detail();
	/// Force close connection (normally automatic, except for send_X ops)
	virtual	int soap_close_socket();
	/// Print fault
	virtual	void soap_print_fault(FILE*);
#ifndef WITH_LEAN
	/// Print fault to stream
	virtual	void soap_stream_fault(std::ostream&);
	/// Put fault into buffer
	virtual	char *soap_sprint_fault(char *buf, size_t len);
#endif

	/// Web service operation 'OpenSession' (returns error code or SOAP_OK)
	virtual	int OpenSession(_ns1__OpenSession *ns1__OpenSession, _ns1__OpenSessionResponse *ns1__OpenSessionResponse);

	/// Web service operation 'CloseSession' (returns error code or SOAP_OK)
	virtual	int CloseSession(_ns1__CloseSession *ns1__CloseSession, _ns1__CloseSessionResponse *ns1__CloseSessionResponse);

	/// Web service operation 'getLimit' (returns error code or SOAP_OK)
	virtual	int getLimit(_ns1__getLimit *ns1__getLimit, _ns1__getLimitResponse *ns1__getLimitResponse);

	/// Web service operation 'getObject' (returns error code or SOAP_OK)
	virtual	int getObject(_ns1__getObject *ns1__getObject, _ns1__getObjectResponse *ns1__getObjectResponse);
};
#endif