#ifndef OBJECT_TRANSFERER_H
#define OBJECT_TRANSFERER_H
#include "stdafx.h"
#include "ServiceConsumer.h"
#include "IFCEngineInteract.h"
#include "EndpointModel.h"
#include <fstream>
#include <vector>



/** This file is going to be the base for all transfering operations of 
 * all IFC Objects */

enum IFCObject {
	IFC_ANNOTATION = 0x01, //Annotations
	IFC_BEAM, //Beams
	IFC_BUILDING, //Buildings
	IFC_BUILDINGELEMENTPART, //Building Element Parts		
	IFC_BUILDINGELEMENTPROXY, //Building Element Proxies		
	IFC_BUILDINGSTOREY, //Building Stories
	IFC_CHAMFEREDGEFEATURE, //Chamfer Edge Features"));
	IFC_COLUMN, // Columns		
	IFC_COVERING, //Coverings
	IFC_CURTAINWALL, //Curtain Walls
	IFC_DISCRETEACCESSORY, //Discrete Accessories
	IFC_DISTRIBUTIONCHAMBERELEMENT, //Distribution Chamber Elements
	IFC_DISTRIBUTIONCONTROLELEMENT, //Distribution Control Elements
	IFC_DISTRIBUTIONELEMENT, //Distribution Elements
	IFC_DISTRIBUTIONFLOWELEMENT, //Distribution Flow Elements
	IFC_DISTRIBUTIONPORT, //Distribution Ports
	IFC_DOOR, //Doors		
	IFC_ELECTRICALELEMENT, //Electrical Elements		
	IFC_ELECTRICDISTRIBUTIONPOINT, //Electric Distribution Points
	IFC_ELEMENTASSEMBLY, //Element Assemblies	
	IFC_ENERGYCONVERSIONDEVICE, //Energy Conversion Devices	
	IFC_EQUIPMENTELEMENT, //Equipment Elements
	IFC_FASTENER, //Fasteners		
	IFC_FLOWCONTROLLER, //Flow Controllers
	IFC_FLOWFITTING, //Flow Fittings
	IFC_FLOWMOVINGDEVICE, //Flow Moving Devices
	IFC_FLOWSEGMENT, //Flow Segments
	IFC_FLOWSTORAGEDEVICE, //Flow Storage Devices
	IFC_FLOWTERMINAL, //Flow Terminals
	IFC_FLOWTREATMENTDEVICE, //Flow Treatment Devices
	IFC_FOOTING, //Footings
	IFC_FURNISHINGELEMENT, //Furnishing Elements
	IFC_GRID, //Grids
	IFC_MECHANICALFASTENER, //Mechanical Fasteners
	IFC_MEMBER, //Members
	IFC_OPENINGELEMENT, //Opening Elements
	IFC_PILE, //Piles
	IFC_PLATE, //Plates
	IFC_PROJECTIONELEMENT, //Projection Elements
	IFC_PROXY, //Proxies
	IFC_RAILING, //Railings
	IFC_RAMP, //Ramps
	IFC_RAMPFLIGHT, //Ramp Flights
	IFC_REINFORCINGBAR, //Reinforcing Bars
	IFC_REINFORCINGMESH, //Reinforcing Meshes
	IFC_ROOF, //Roofs
	IFC_ROUNDEDEDGEFEATURE, //Rounded Edge Features
	IFC_SITE, //Sites
	IFC_SLAB, //Slabs
	IFC_SPACE, //Spaces
	IFC_STAIR, //Stairs
	IFC_STAIRFLIGHT, //Stair Flights
	IFC_STRUCTURALCURVECONNECTION, //Structural Curve Connections
	IFC_STRUCTURALCURVEMEMBER, //Structural Curve Members
	IFC_STRUCTURALCURVEMEMBERVARYING, //Structural Curve Member Varyings
	IFC_STRUCTURALLINEARACTION, //Structural Linear Actions
	IFC_STRUCTURALLINEARACTIONVARYING, //Structural Linear Action Varyings
	IFC_STRUCTURALPLANARACTION, //Structural Planar Actions
	IFC_STRUCTURALPLANARACTIONVARYING, //Structural Planar Action Varyings
	IFC_STRUCTURALPOINTACTION, //Structural Point Actions
	IFC_STRUCTURALPOINTCONNECTION, //Structural Point Connections
	IFC_STRUCTURALPOINTREACTION, //Structural Point Reactions
	IFC_STRUCTURALSURFACECONNECTION, //Structural Surface Connections
	IFC_STRUCTURALSURFACEMEMBER, //Structural Surface Members
	IFC_STRUCTURALSURFACEMEMBERVARYING, //Structural Surface Member Varyings
	IFC_TENDON, //Tendons
	IFC_TENDONANCHOR, //Tendon Anchors
	IFC_TRANSPORTELEMENT, //Transport Elements
	IFC_VIRTUALELEMENT, //Virtual Elements
	IFC_WALL, //Walls
	IFC_WALLSTANDARDCASE, //Walls Standard Cases
	IFC_WINDOW //Windows
};

class CColosseumCtrl;

///Protected Inheritance to ensure composition
///and to not expose the CServiceConsumer functionality to the public
class CObjectTransferer
{
private:
	CServiceConsumer m_serviceConsumer;

protected:
	CObjectTransferer();
	/// This pointer is to communicate with IFC engine
	CIFCEngineInteract *m_engineInteract;
	/// A helper method to map the enum to its corresponding string representation
	std::string getIFCObject(IFCObject);
	CColosseumCtrl *m_ctrl;
	std::string m_uuid;

	///Total number of lines in the requested file
	unsigned long m_total_lines;
	
	///Number of lines downloaded
	unsigned long m_number_of_lines;

	///Counts the number of lines in the returned string
	unsigned long countLines(const std::string& returnedString);

public:
	
	virtual ~CObjectTransferer();
	
	///Returns a reference to the singleton
	static CObjectTransferer& getSingleton();
	
	///Invoke the GetObject method of the service
	///@param an enum for the object required
	///@param _fileId the file number
	///@param reference to the file object is written to
	BOOL transferObject(IFCObject, int _fileId, std::ofstream&);

	/// Set the endpoint of the service
	/// @param the server endpoint parameter
	void setEndpoint(const std::string& endpoint);
	
	///Sets the engine that will be communicated with
	///@param a pointer to an engine
	void setIFCEngine(CIFCEngineInteract *engine);
	void setCtrl(CColosseumCtrl *ctrl);
	
	///Refreshes the building information by parsing the file again and filling the 
	///building tree
	void refresh(const std::string&, int& noVertices, int& noIndices);
	
	///Opens session
	void OpenSession(int fileNumber);
	void CloseSession();
};

///This is the thread class that will run CObjectTransferer in the background
class CObjectTransfererThread : public CWinThread
{
	const std::vector<CEndpointModel*> &m_endpointModelVector;
public:
	CObjectTransfererThread(const std::vector<CEndpointModel*>& endpointModelVector);
	virtual ~CObjectTransfererThread();
	virtual BOOL InitInstance();
	virtual int Run();

};


#endif