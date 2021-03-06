#include "ObjectTransferer.h"
#include "colosseumCtrl.h"


CObjectTransferer::CObjectTransferer() 
: m_engineInteract(0), m_ctrl(0), m_number_of_lines(0)
{}

CObjectTransferer::~CObjectTransferer()
{
	m_serviceConsumer.getProxy().destroy();
}

std::string CObjectTransferer::getIFCObject(IFCObject _object)
{
	std::string object_str;
	switch(_object) {
		case IFC_ANNOTATION:
			object_str = "IFCANNOTATION";
			break;
		case IFC_BEAM:
			object_str = "IFCBEAM";
			break;
		case IFC_BUILDING:
			object_str = "IFCBUILDING";
			break;
		case IFC_BUILDINGELEMENTPART:
			object_str = "IFCBUILDINGELEMENTPART";
			break;
		case IFC_BUILDINGELEMENTPROXY:
			object_str = "IFCBUILDINGELEMENTPROXY";
			break;
		case IFC_BUILDINGSTOREY:
			object_str = "IFCBUILDINGSTOREY";
			break;
		case IFC_CHAMFEREDGEFEATURE:
			object_str = "IFCCHAMFEREDGEFEATURE";
			break;
		case IFC_COLUMN:
			object_str = "IFCCOLUMN";
			break;
		case IFC_COVERING:
			object_str = "IFCCOVERING";
			break;
		case IFC_CURTAINWALL:
			object_str = "IFCCURTAINWALL";
			break;
		case IFC_DISCRETEACCESSORY:
			object_str = "IFCDISCRETEACCESSORY";
			break;
		case IFC_DISTRIBUTIONCHAMBERELEMENT:
			object_str = "IFCDISTRIBUTIONCHAMBERELEMENT";
			break;
		case IFC_DISTRIBUTIONCONTROLELEMENT:
			object_str = "IFCDISTRIBUTIONCONTROLELEMENT";
			break;
		case IFC_DISTRIBUTIONELEMENT:
			object_str = "IFCDISTRIBUTIONELEMENT";
			break;
		case IFC_DISTRIBUTIONFLOWELEMENT:
			object_str = "IFCDISTRIBUTIONFLOWELEMENT";
			break;
		case IFC_DISTRIBUTIONPORT:
			object_str = "IFCDISTRIBUTIONPORT";
			break;
		case IFC_DOOR:
			object_str = "IFCDOOR";
			break;
		case IFC_ELECTRICALELEMENT:
			object_str = "IFCELECTRICALELEMENT";
			break;
		case IFC_ELECTRICDISTRIBUTIONPOINT:
			object_str = "IFCELECTRICDISTRIBUTIONPOINT";
			break;
		case IFC_ELEMENTASSEMBLY:
			object_str = "IFCELEMENTASSEMBLY";
			break;
		case IFC_ENERGYCONVERSIONDEVICE:
			object_str = "IFCENERGYCONVERSIONDEVICE";
			break;
		case IFC_EQUIPMENTELEMENT:
			object_str = "IFCEQUIPMENTELEMENT";
			break;
		case IFC_FASTENER:
			object_str = "IFCFASTENER";
			break;
		case IFC_FLOWCONTROLLER:
			object_str = "IFCFLOWCONTROLLER";
			break;
		case IFC_FLOWFITTING:
			object_str = "IFCFLOWFITTING";
			break;
		case IFC_FLOWMOVINGDEVICE:
			object_str = "IFCFLOWMOVINGDEVICE";
			break;
		case IFC_FLOWSEGMENT:
			object_str = "IFCFLOWSEGMENT";
			break;
		case IFC_FLOWSTORAGEDEVICE:
			object_str = "IFCFLOWSTORAGEDEVICE";
			break;
		case IFC_FLOWTERMINAL:
			object_str = "IFCFLOWTERMINAL";
			break;
		case IFC_FLOWTREATMENTDEVICE:
			object_str = "IFCFLOWTREATMENTDEVICE";
			break;
		case IFC_FOOTING:
			object_str = "IFCFOOTING";
			break;
		case IFC_FURNISHINGELEMENT:
			object_str = "IFCFURNISHINGELEMENT";
			break;
		case IFC_GRID:
			object_str = "IFCGRID";
			break;
		case IFC_MECHANICALFASTENER:
			object_str = "IFCMECHANICALFASTENER";
			break;
		case IFC_MEMBER:
			object_str = "IFCMEMBER";
			break;
		case IFC_OPENINGELEMENT:
			object_str = "IFCOPENINGELEMENT";
			break;
		case IFC_PILE:
			object_str = "IFCPILE";
			break;
		case IFC_PLATE:
			object_str = "IFCPLATE";
			break;
		case IFC_PROJECTIONELEMENT:
			object_str = "IFCPROJECTIONELEMENT";
			break;
		case IFC_PROXY:
			object_str = "IFCPROXY";
			break;
		case IFC_RAILING:
			object_str = "IFCRAILING";
			break;
		case IFC_RAMP:
			object_str = "IFCRAMP";
			break;
		case IFC_RAMPFLIGHT:
			object_str = "IFCRAMPFLIGHT";
			break;
		case IFC_REINFORCINGBAR:
			object_str = "IFCREINFORCINGBAR";
			break;
		case IFC_REINFORCINGMESH:
			object_str = "IFCREINFORCINGMESH";
			break;
		case IFC_ROOF:
			object_str = "IFCROOF";
			break;
		case IFC_ROUNDEDEDGEFEATURE:
			object_str = "IFCROUNDEDEDGEFEATURE";
			break;
		case IFC_SITE:
			object_str = "IFCSITE";
			break;
		case IFC_SLAB:
			object_str = "IFCSLAB";
			break;
		case IFC_SPACE:
			object_str = "IFCSPACE";
			break;
		case IFC_STAIR:
			object_str = "IFCSTAIR";
			break;
		case IFC_STAIRFLIGHT:
			object_str = "IFCSTAIRFLIGHT";
			break;
		case IFC_STRUCTURALCURVECONNECTION:
			object_str = "IFCSTRUCTURALCURVECONNECTION";
			break;
		case IFC_STRUCTURALCURVEMEMBER:
			object_str = "IFCSTRUCTURALCURVEMEMBER";
			break;
		case IFC_STRUCTURALCURVEMEMBERVARYING:
			object_str = "IFCSTRUCTURALCURVEMEMBERVARYING";
			break;
		case IFC_STRUCTURALLINEARACTION:
			object_str = "IFCSTRUCTURALLINEARACTION";
			break;
		case IFC_STRUCTURALLINEARACTIONVARYING:
			object_str = "IFCSTRUCTURALLINEARACTIONVARYING";
			break;
		case IFC_STRUCTURALPLANARACTION:
			object_str = "IFCSTRUCTURALPLANARACTION";
			break;
		case IFC_STRUCTURALPLANARACTIONVARYING:
			object_str = "IFCSTRUCTURALPLANARACTIONVARYING";
			break;
		case IFC_STRUCTURALPOINTACTION:
			object_str = "IFCSTRUCTURALPOINTACTION";
			break;
		case IFC_STRUCTURALPOINTCONNECTION:
			object_str = "IFCSTRUCTURALPOINTCONNECTION";
			break;
		case IFC_STRUCTURALPOINTREACTION:
			object_str = "IFCSTRUCTURALPOINTREACTION";
			break;
		case IFC_STRUCTURALSURFACECONNECTION:
			object_str = "IFCSTRUCTURALSURFACECONNECTION";
			break;
		case IFC_STRUCTURALSURFACEMEMBER:
			object_str = "IFCSTRUCTURALSURFACEMEMBER";
			break;
		case IFC_STRUCTURALSURFACEMEMBERVARYING:
			object_str = "IFCSTRUCTURALSURFACEMEMBERVARYING";
			break;
		case IFC_TENDON:
			object_str = "IFCTENDON";
			break;
		case  IFC_TENDONANCHOR:
			object_str = "IFCTENDONANCHOR";
			break;
		case IFC_TRANSPORTELEMENT:
			object_str = "IFCTRANSPORTELEMENT";
			break;
		case IFC_VIRTUALELEMENT:
			object_str = "IFCVIRTUALELMENT";
			break;
		case IFC_WALL:
			object_str = "IFCWALL";
			break;
		case IFC_WALLSTANDARDCASE:
			object_str = "IFCWALLSTANDARDCASE";
			break;
		case IFC_WINDOW:
			object_str = "IFCWINDOW";
			break;
	}
	return object_str;
}


unsigned long CObjectTransferer::countLines(const std::string& returnedString)
{
	unsigned long count = 0;
	std::string::const_iterator i = returnedString.begin();

	for( ; i != returnedString.end(); i++) {
		if( *i == ';')
			count++;
	}
	return count;
}

CObjectTransferer& CObjectTransferer::getSingleton()
{
	static std::auto_ptr<CObjectTransferer> instance(new CObjectTransferer);
	return *instance;
}

void CObjectTransferer::refresh(const std::string& fileName, int& noVertices, int& noIndices)
{
	if(m_engineInteract) {
		/* Locks the building data structure */
		m_engineInteract->setLock();
		/* Destroy the building to reinstantiate it again */
		m_engineInteract->destroyManually();
		if(m_ctrl) {
			m_ctrl->clearVertexBuffers();
			if ( 0 == m_engineInteract->retrieveObjectGroups(const_cast<char*>(fileName.c_str())))
				m_engineInteract->enrichObjectGroups(noVertices, noIndices);
			m_ctrl->fillVertexBuffer(noVertices, noIndices);
		}
		m_engineInteract->setLock(false);
		
	}
}

BOOL CObjectTransferer::transferObject(IFCObject _requiredObjects, int _fileId, std::ofstream& outFile)
{
	static int count = 0;
	try {
		int limit = m_serviceConsumer.getLimit();
		std::string objectRequired = getIFCObject(_requiredObjects);
		//std::string uuid = openSession(_fileId);
		//TRACE("UUID: %s", uuid.c_str());
		int offset = 0;
		bool notFinished = true;
		std::string returned = "";

		do {
			do {
				returned = m_serviceConsumer.getObject(m_uuid, objectRequired, offset);
				TRACE("%s\n", returned.c_str());
				outFile << returned;
				count += countLines(returned);
				offset += returned.length();				
			}while( returned.length() == limit);
			offset = 0;
			returned = m_serviceConsumer.getObject(m_uuid, objectRequired, offset);
			outFile.flush();
			//refresh();
			if(returned.length() <= 0)
				notFinished = false;
			else {
				TRACE("%s", returned.c_str());
				count += countLines(returned);
				outFile << returned;
			}
			outFile.flush();
		}while( notFinished );
		//closeSession(uuid);
		if(notFinished == false) {
				count += countLines(returned);
				m_ctrl->incrementProgressBar();
				return true;
		}
		
	}catch(std::exception &e) {
		outFile.close();
		ASSERT(1==0);
	}
	return false;
}

void CObjectTransferer::setIFCEngine(CIFCEngineInteract* engine)
{
	m_engineInteract = engine;
}

void CObjectTransferer::OpenSession(int fileNumber)
{
	try{
		m_uuid = m_serviceConsumer.openSession(fileNumber);
		m_total_lines = 0; //Remove that
	}catch(std::exception &e) {
		TRACE("%s", e.what());
		ASSERT(1==0);
	}
}

void CObjectTransferer::CloseSession()
{
	try {
		m_serviceConsumer.closeSession(m_uuid);
	}catch(std::exception &e) {
		TRACE("%s", e.what());
		ASSERT(1==0);
	}
}

void CObjectTransferer::setEndpoint(const std::string& _endpoint)
{
	m_serviceConsumer.setEndpointString(_endpoint);
}


void CObjectTransferer::setCtrl(CColosseumCtrl *ctrl)
{
	m_ctrl = ctrl;
}

//----------------------------------------------------------------------------------
/* Begining of the CObjectTransfererThread Definition */


CObjectTransfererThread::CObjectTransfererThread(const std::vector<CEndpointModel*>& endpointModelVector):
m_endpointModelVector(endpointModelVector)
{}

BOOL CObjectTransfererThread::InitInstance()
{
	return TRUE;
}

CObjectTransfererThread::~CObjectTransfererThread()
{
	
}

int CObjectTransfererThread::Run()
{
	for(size_t i = 0; i < m_endpointModelVector.size(); i++) {
		CObjectTransferer::getSingleton().setEndpoint(m_endpointModelVector[i]->getEndpoint());
		CObjectTransferer::getSingleton().OpenSession(m_endpointModelVector[i]->getFileNumber());
		for(int j = 1; j <= 72; ++j)
			CObjectTransferer::getSingleton().transferObject(static_cast<IFCObject>(j), m_endpointModelVector[i]->getFileNumber(), m_endpointModelVector[i]->getFileStream());
		
		CObjectTransferer::getSingleton().CloseSession();
		//Added that to initialize the building structure
		CObjectTransferer::getSingleton().refresh(m_endpointModelVector[i]->getFileName(), \
			m_endpointModelVector[i]->getVerticesNumber(), \
			m_endpointModelVector[i]->getIndicesNumber());
	}

	return 0;
}