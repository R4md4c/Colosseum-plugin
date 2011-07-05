#include "EndpointModel.h"



CEndpointModel::CEndpointModel(std::string endpoint, unsigned int fileNumber)
{
	m_endpoint = endpoint;
	m_fileNumber = fileNumber;
	m_fileStream = new std::ofstream();
	m_noIndices = -1;
	m_noVertices = -1;
}

CEndpointModel::~CEndpointModel()
{
	m_fileStream->close();
	delete m_fileStream;
}

std::string CEndpointModel::getEndpoint()
{
	return m_endpoint;
}


void CEndpointModel::setEndpoint(std::string endpoint)
{
	m_endpoint = endpoint;
}

unsigned int CEndpointModel::getFileNumber()
{
	return m_fileNumber;
}

void CEndpointModel::setFileNumber(unsigned int f)
{
	m_fileNumber = f;
}

void CEndpointModel::openFile(std::string fileName)
{
	m_fileStream->open(fileName.c_str());
}

void CEndpointModel::setFileName(const std::string& fileName)
{
	m_fileName = fileName;
}

std::string CEndpointModel::getFileName()
{
	return m_fileName;
}


std::ofstream& CEndpointModel::getFileStream()
{
	return *m_fileStream;
}