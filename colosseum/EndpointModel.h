#ifndef ENDPOINT_MODEL_H
#define ENDPOINT_MODEL_H

#include <string>
#include <fstream>

/**
A data model for encapsulating the endpoint address and the requested file number
**/

class CEndpointModel {
private:
	std::string m_endpoint;
	unsigned int m_fileNumber;

	/* The number of indices in a model got from a web service endpoint */
	int m_noIndices;
	/* The number of vertices in a model got from a web service endpoint */
	int m_noVertices;
	/* Will be used to refresh the structure see CObjectTransferer class*/
	std::string m_fileName;
	/* Each endpoint will have a file to output the service output there */
	std::ofstream* m_fileStream;

public:
	CEndpointModel(std::string endpoint, unsigned int fileNumber);
	~CEndpointModel();
	std::string getEndpoint();
	void	setEndpoint(std::string endpoint);

	unsigned int getFileNumber();
	void	setFileNumber(unsigned int f);
	
	int& getVerticesNumber() {
		return m_noVertices;
	}

	int& getIndicesNumber() {
		return m_noIndices;
	}
	void setFileName(const std::string& fileName);
	std::string getFileName();

	void openFile(std::string fileName);
	std::ofstream& getFileStream();
};

#endif 