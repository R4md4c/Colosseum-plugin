#ifndef COLOSSEUM_CTRL_H
#define COLOSSEUM_CTRL_H

#pragma once

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iomanip>

// colosseumCtrl.h : Declaration of the CColosseumCtrl ActiveX Control class.
/* DirectX 9 header files */

#include <d3d9.h>
#include <d3dx9.h>
#include "Camera.h"
#include "ServiceConsumer.h"
#include "ObjectTransferer.h"
#include "DXUT.h"
#include "DXUTgui.h"
#include "DXUTsettingsdlg.h"
#include "EndpointModel.h"

/* The format of each vertex */

#define		D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_NORMAL)

typedef struct CUSTOMVERTEX {
	float	x;
	float	y;
	float	z;
	float	nx;
	float	ny;
	float	nz;
}	customvertex;

void CALLBACK OnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext );

// CColosseumCtrl : See colosseumCtrl.cpp for implementation.

class CColosseumCtrl : public COleControl
{
	DECLARE_DYNCREATE(CColosseumCtrl)

// Constructor
public:
	CColosseumCtrl();
	
	

// Overrides
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void OnShowWindow(BOOL bShow, UINT nStatus);
	void OnMouseMove(UINT nFlags, CPoint point);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual DWORD GetControlFlags();
	
	
	
	
// Implementation
protected:
	~CColosseumCtrl();
	

	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	

	DECLARE_OLECREATE_EX(CColosseumCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CColosseumCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CColosseumCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CColosseumCtrl)		// Type name and misc status

// Message maps
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	DECLARE_DISPATCH_MAP()

	

// Event maps
	DECLARE_EVENT_MAP()

//Attributes and Properties

	LONG m_width;
	LONG m_height;
	CString m_server;
	LONG m_fileNumber;
	/* A vector that holds the parameter */
	std::vector<CEndpointModel*> m_endpointModelVector;
	
	
	
	HWND m_hwndRenderWindow;
	bool m_initialized;
	CIFCEngineInteract *m_engineInteract;
	//For testing
	std::vector<IFCObject> m_objectVector;
	LPDIRECT3D9            m_pD3D;			// Used to create the D3DDevice
	LPDIRECT3DDEVICE9       m_pd3dDevice;	// Our rendering device
	LPDIRECT3DVERTEXBUFFER9 m_pVB;			// Buffer to hold vertices
	D3DPRESENT_PARAMETERS	m_d3dpp;



	/*GUI Stuff */
	CDXUTDialog			m_dialog;
	CDXUTDialogResourceManager			m_resourceManager;

	/* camera object */
	CCamera *m_camera;

public:
/* DirectX related functions */
	void	initializeDevice();
	void	initializeDeviceBuffer();
	
	void clearVertexBuffers();
	///Fills the vertex buffer with data
	void	fillVertexBuffer(const int& noVertices, const int& noIndices);
	
	void	incrementProgressBar(bool hide = false);
/* Initialize GUI Components */
	void	initializeGUI();
/* Used to handle GUI Events */
	void OnGuiEvent( UINT nEvent, int nControlID, CDXUTControl* pControl);
	
	/*	Release the global vertices and indices */
	void	releaseGlobals();
	void	render();
	int		setupLights();
	int		setupMatrices();

private:
	const float MULTIPLY_RATIO ;

// Dispatch and event IDs

protected:
	
	LONG GetWidth(void) const ; 
	
	LONG GetHeight(void) const ;
	
	BSTR GetServer(void) const;

	/* Parse the server parameter obtained from HTML and initialize the endpoint models */
	void parseParameters(const std::string& serverString);
	
};

#endif