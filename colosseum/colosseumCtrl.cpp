// colosseumCtrl.cpp : Implementation of the CColosseumCtrl ActiveX Control class.

#include "stdafx.h"
#include "colosseum.h"
#include "colosseumCtrl.h"
#include "colosseumPropPage.h"
#include <assert.h>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/* An error indication value non-zero if error exists */
int		g_directXStatus = 0;

float	* g_pVerticesDeviceBuffer;

extern int		g_noVertices, g_noIndices, * g_pIndices;
extern float	* g_pVertices;

D3DXVECTOR3		g_vecOrigin;

///The temporary file name that is going to be filled with ifc objects
///Change the file here if you want
const std::string g_tempFileName = "C:\\temp.ifc";
IMPLEMENT_DYNCREATE(CColosseumCtrl, COleControl)



// Message map

BEGIN_MESSAGE_MAP(CColosseumCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_KEYDOWN()
	ON_WM_SHOWWINDOW()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// Dispatch map

BEGIN_DISPATCH_MAP(CColosseumCtrl, COleControl)
	
END_DISPATCH_MAP()



// Event map

BEGIN_EVENT_MAP(CColosseumCtrl, COleControl)
END_EVENT_MAP()



// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CColosseumCtrl, 1)
	PROPPAGEID(CcolosseumPropPage::guid)
END_PROPPAGEIDS(CColosseumCtrl)



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CColosseumCtrl, "COLOSSEUM.colosseumCtrl.1",
	0x70217189, 0x66e8, 0x4874, 0x9f, 0xd2, 0x53, 0x52, 0xfd, 0xf4, 0x67, 0x34)



// Type library ID and version

IMPLEMENT_OLETYPELIB(CColosseumCtrl, _tlid, _wVerMajor, _wVerMinor)



// Interface IDs

const IID BASED_CODE IID_Dcolosseum =
		{ 0xE8B8A0AD, 0x761C, 0x4631, { 0x88, 0xCF, 0xD5, 0xD2, 0xDD, 0xEA, 0xEE, 0x79 } };
const IID BASED_CODE IID_DcolosseumEvents =
		{ 0xE9D4851E, 0x590E, 0x4C56, { 0x9C, 0xEF, 0x9E, 0xC4, 0x95, 0x96, 0x1E, 0xDD } };



// Control type information

static const DWORD BASED_CODE _dwcolosseumOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CColosseumCtrl, IDS_COLOSSEUM, _dwcolosseumOleMisc)



// CColosseumCtrl::CColosseumCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CColosseumCtrl

BOOL CColosseumCtrl::CColosseumCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_COLOSSEUM,
			IDB_COLOSSEUM,
			afxRegApartmentThreading,
			_dwcolosseumOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CColosseumCtrl::CColosseumCtrl - Constructor

CColosseumCtrl::CColosseumCtrl() : m_width(0), m_height(0), m_server(""), MULTIPLY_RATIO(0.030f)
{
	InitializeIIDs(&IID_Dcolosseum, &IID_DcolosseumEvents);
	// TODO: Initialize your control's instance data here.
	
	g_pVertices = NULL;
	g_pIndices = NULL;
	g_pVerticesDeviceBuffer = NULL;


	m_pD3D = NULL;
	m_pd3dDevice = NULL;
	m_pVB = NULL;
	m_initialized = false;
	m_engineInteract = new CIFCEngineInteract();
	m_camera = new CCamera(D3DXVECTOR3(0,0,-2.5f));
	m_tempFile.open("C:\\temp.ifc");
	CObjectTransferer::getSingleton().setIFCEngine(m_engineInteract);
	
	/* Reset D3DPRESENT_PARAMETERS structure */
	memset( &m_d3dpp, 0, sizeof(m_d3dpp) );
}



/* Called when a key is pressed */
void CColosseumCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	/* This method is called by the MFC messaging system when a WM_ONKEYDOWN
	 * is sent this handles the keys pressed when using the control 
	 * The keys handled are
	 * W key for moving forward
	 * S for moving backward
	 * A for left strafing
	 * D for right straging
	 */
	CObjectTransfererThread *t = NULL;
	switch( nChar ) {
			case 0x57: //W KEY
				
				m_camera->moveForward(MULTIPLY_RATIO);
								
				if  (m_initialized) {
					render();
				}
				break;
			case 0x58:
				//CObjectTransferer::getSingleton().transferObject(IFC_WINDOW, m_fileNumber, m_tempFile);
				t = new CObjectTransfererThread(this->m_tempFile, m_objectVector, m_fileNumber);
				t->CreateThread();
				if(m_initialized) {
					render();
				}
				break;
			case 0x53: // S KEY
				/* Inverse the direction by multiplying with -1*/
				m_camera->moveForward(-1.0f * MULTIPLY_RATIO);
				
				if  (m_initialized) {
					render();
				}
				break;
			case 0x41:// A KEY
				/* Inverse the direction by multiplying with -1*/
				m_camera->moveRight(-1.0f * MULTIPLY_RATIO);
				if(m_initialized)
					render();
				break;
			
			case 0x44: // D KEY
				m_camera->moveRight( MULTIPLY_RATIO );
				if(m_initialized)
					render();
				break;
	 }
}

/* Called when the control is Shown*/
void CColosseumCtrl::OnShowWindow(BOOL bShow, UINT nStatus)
{
	/* This method is called the instance the control is show to the user
	 * What happens here is that we get the file name from m_server and convert it from
	 * CString to char* and send it to the CIFCEngineInteract object to retrieve information 
	 * from the file and initialize the CIFCEngineInteract object.
	 * We then initialize the m_width and m_height with the width and height of the control
	 * sent with <OBJECT> tag in the html file.
	 * After that we assign to m_hwndRenderWindow the handle of the window that we are going to draw
	 * in because we are going to use to initialize the DirectX device module and initialize the device buffer .
	 * Lastly we render the changes.
	 */
	/** Trying the web service */
	
	//CObjectTransferer::getSingleton().transferObject(IFC_WINDOW, m_fileNumber, f);
	//CObjectTransferer::getSingleton().transferObject(IFC_DOOR, m_fileNumber, f);
	//CObjectTransferer::getSingleton().transferObject(IFC_WALLSTANDARDCASE, m_fileNumber, f);
	
	if ( 0 == m_engineInteract->retrieveObjectGroups("C:\\temp1.ifc"))//(m_server.GetBuffer(0))))
		m_engineInteract->enrichObjectGroups();
	else	
		ASSERT(1==0);
	
	CObjectTransferer::getSingleton().setCtrl(this);
	
	CRect rc;
	GetWindowRect(&rc);
	m_width = rc.Width();
	m_height = rc.Height();
	
	m_hwndRenderWindow = this->m_hWnd;
	initializeDevice();
	initializeDeviceBuffer();
	m_objectVector.push_back(IFC_WINDOW);
	m_objectVector.push_back(IFC_DOOR);
	if(m_initialized)
			render();		
}

int		iZoomMouseX, iZoomMouseY;

void CColosseumCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	/* This method handle the mouse movement and adjust the view of the camera 
	 * according to the changes made to the coordinates
	 * NOTE: Remember the camera i am talking about is a First Person Shooter camera
	 */
	int iMouseX = point.x, 
		iMouseY = point.y;
	
	switch(nFlags)
	{
		case MK_LBUTTON:
			
			//SetCapture();
			SetCursor(NULL);
				
			m_camera->rotateCamera((float)(iMouseY-iZoomMouseY), (float)(iMouseX-iZoomMouseX)); 

			if (m_initialized) {
				render();
			}
			//ReleaseCapture();
			iZoomMouseX = iMouseX;
			iZoomMouseY = iMouseY;
			break;
	}
}

LRESULT CColosseumCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	 /* I left the WindowProc method so that leave the window rendering while 
	  * there are no messages to handle.
	  * I left some message handling to determine the coordinates of the previous frame 
	  * so that it is dealed with in the OnMouseMove method
	  */
	
	switch (message)
	{
		case WM_LBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_RBUTTONDOWN:
			/* Note the lParam is sent as 4 bytes each 2 bytes contain the X coordinates of the mouse 
			 * and Y coordinates of the mouse the lower 2 bytes are for the X component and the higher 2 bytes are 
			 * for the Y.
			 * Example:- 
			 * 0x010e01b5 the low bytes are 0x01b5 which is equal to 437 decimal therefore the X-Coordinate's value is 437
			 * the higher bytes are 0x010e which is equal to 270 decimal therefore the Y-Coordinates's value is 270
			 * hope that you got it right */
			iZoomMouseX = LOWORD(lParam); 
			iZoomMouseY = HIWORD(lParam);
			break;
	}
	if(m_initialized)
			render();
	return COleControl::WindowProc(message, wParam, lParam);
	
	
}



// CColosseumCtrl::~CColosseumCtrl - Destructor

CColosseumCtrl::~CColosseumCtrl()
{
	// TODO: Cleanup your control's instance data here.
	m_tempFile.close();
	if( m_engineInteract ) {
		delete m_engineInteract;
		m_engineInteract = NULL;
	}
	if( m_camera ) {
		delete m_camera;
		m_camera = NULL;
	}

	if( m_pVB != NULL ) {
			if( FAILED( m_pVB->Release() ) ) {
				g_directXStatus = -1;
				ASSERT(1==0);
				return;
			}
		}

		if( m_pd3dDevice != NULL ) {
			if( FAILED( m_pd3dDevice->Release() ) ) {
				g_directXStatus = -1;
				ASSERT(1==0);
				return;
			}
		}

		if( m_pD3D != NULL ) {
			if( FAILED( m_pD3D->Release() ) ) {
				g_directXStatus = -1;
				ASSERT(1==0);
				return;
			}
		}
		//_CrtDumpMemoryLeaks();

		
		//_CrtDumpMemoryLeaks();

}



// CColosseumCtrl::OnDraw - Drawing function

void CColosseumCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;
	
}


// CColosseumCtrl::DoPropExchange - Persistence support

void CColosseumCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);
	// TODO: Call PX_ functions for each persistent custom property.
	
	
	PX_String(pPX, _T("Server"), m_server, _T("http://localhost:2222/Service1.svc"));
	PX_Long(pPX, _T("File"), m_fileNumber);
	
	
}



// CColosseumCtrl::GetControlFlags -
// Flags to customize MFC's implementation of ActiveX controls.
//
DWORD CColosseumCtrl::GetControlFlags()
{
	DWORD dwFlags = COleControl::GetControlFlags();


	// The control will not be redrawn when making the transition
	// between the active and inactivate state.
	dwFlags |= noFlickerActivate;
	return dwFlags;
}



// CColosseumCtrl::OnResetState - Reset control to default state

void CColosseumCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
	
	// TODO: Reset any other control state here.
}


// CColosseumCtrl message handlers

LONG CColosseumCtrl::GetHeight() const
{
	return m_height;
}

LONG CColosseumCtrl::GetWidth() const
{
	return m_width;
}

BSTR CColosseumCtrl::GetServer() const
{
	return m_server.AllocSysString();
}

void	CColosseumCtrl::initializeDevice()
{
		if( m_pVB != NULL ) {
			if( FAILED( m_pVB->Release() ) ) {
				g_directXStatus = -1;
				ASSERT(1==0);
				return;
			}
		}

		if( m_pd3dDevice != NULL ) {
			if( FAILED( m_pd3dDevice->Release() ) ) {
				g_directXStatus = -1;
				ASSERT(1==0);
				return;
			}
		}

		if( m_pD3D != NULL ) {
			if( FAILED( m_pD3D->Release() ) ) {
				g_directXStatus = -1;
				ASSERT(1==0);
				return;
			}
		}

		m_pD3D = Direct3DCreate9( D3D_SDK_VERSION );
		ASSERT(m_pD3D);

		m_d3dpp.Windowed = TRUE;
		m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		m_d3dpp.hDeviceWindow = this->GetSafeHwnd();
		m_d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
		m_d3dpp.EnableAutoDepthStencil = TRUE;
		m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

		if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hwndRenderWindow,
										  D3DCREATE_HARDWARE_VERTEXPROCESSING,
										  &m_d3dpp, &m_pd3dDevice ) ) )
		{
			if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hwndRenderWindow,
											  D3DCREATE_SOFTWARE_VERTEXPROCESSING,
											  &m_d3dpp, &m_pd3dDevice ) ) )
			{
				ASSERT(1==0);
				return;
			}
		}
		
		ASSERT(m_pd3dDevice);

		m_initialized = true;

		if( FAILED( m_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE ) ) ) {
			ASSERT(1==0);
			return;
		}
		
		if( FAILED( m_pd3dDevice->SetRenderState( D3DRS_MULTISAMPLEANTIALIAS, TRUE) ) ) {
			ASSERT(1==0);
			return;
		}

		// Turn on the zbuffer
		if( FAILED( m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE ) ) ) {
			ASSERT(1==0);
			return;
		}
}

void	CColosseumCtrl::initializeDeviceBuffer()
{
	if	(g_noVertices) {
		if	(!g_directXStatus) {
			if( FAILED( m_pd3dDevice->CreateVertexBuffer( g_noIndices * sizeof(CUSTOMVERTEX),
														  0, D3DFVF_CUSTOMVERTEX,
														  D3DPOOL_DEFAULT, &m_pVB, NULL ) ) )
			{
				ASSERT(1==0);
				return;
			}

			if( FAILED( m_pVB->Lock( 0, 0, (void **)&g_pVerticesDeviceBuffer, 0 ) ) ) {
				ASSERT(1==0);
				return;
			}

			int i = 0;
			int z;
			while  (i < g_noIndices) {
				z = g_pIndices[i];
				ASSERT(g_pIndices[i] < g_noVertices);
				memcpy(&(((CUSTOMVERTEX *) g_pVerticesDeviceBuffer)[i]), &(((CUSTOMVERTEX *) g_pVertices)[g_pIndices[i]]), sizeof(CUSTOMVERTEX));

				i++;
			}

			if	(FAILED( m_pVB->Unlock())) {
				ASSERT(1==0);
				return;
			}
		}
	}
}

void CColosseumCtrl::releaseVertexBuffer()
{
	if(m_pVB) {
		m_pVB->Release();
		m_pVB = NULL;
	}
	if( g_pVertices ) {
		free(g_pVertices);
		g_pVertices = NULL;
		g_noVertices = 0;
	}

	if( g_pIndices ) {
		free(g_pIndices);
		g_pIndices = NULL;
		g_noIndices = 0;
	}

	/*if( g_pVerticesDeviceBuffer ) {
		free(g_pVerticesDeviceBuffer);
		g_pVerticesDeviceBuffer = NULL;
	}*/

}

void	CColosseumCtrl::render()
{
	if	(m_initialized) {
		// Clear the backbuffer and the zbuffer
		if( FAILED( m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
										 D3DCOLOR_XRGB(0,0,255), 1.0f, 0 ) ) ) {
			g_directXStatus = -1;
			return;
		}
		
		// Begin the scene
		if	(SUCCEEDED(m_pd3dDevice->BeginScene()))
		{
			// Setup the lights and materials
			if	(setupLights()) {
				g_directXStatus = -1;
				return;
			}

			// Setup the world, view, and projection matrices
			if	(setupMatrices()) {
				g_directXStatus = -1;
				return;
			}


			if	(m_pd3dDevice->SetStreamSource(0, m_pVB, 0, sizeof(CUSTOMVERTEX))) {
				g_directXStatus = -1;
				return;
			}

			m_pd3dDevice->SetVertexShader(NULL);
			m_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);


			D3DMATERIAL9	mtrl;
			mtrl.Diffuse.r = mtrl.Ambient.r = mtrl.Specular.r = 0.4f;
			mtrl.Diffuse.g = mtrl.Ambient.g = mtrl.Specular.g = 0.1f;
			mtrl.Diffuse.b = mtrl.Ambient.b = mtrl.Specular.b = 0.7f;
			mtrl.Diffuse.a = mtrl.Ambient.a = mtrl.Specular.a = 1.0f;
			mtrl.Emissive.r = 0.1f;
			mtrl.Emissive.g = 0.4f;
			mtrl.Emissive.b = 0.02f;
			mtrl.Emissive.a = 0.5f;

			m_pd3dDevice->SetMaterial(&mtrl);
			
			if(!m_engineInteract->getLock()) {
				STRUCT_INSTANCES	* instance = m_engineInteract->getFirstInstance();
				while  (instance) {
					if	( (instance->parent)  &&
						  (instance->select == ITEM_CHECKED) ){
						m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, instance->startIndex, instance->primitiveCount);  
					}

					instance = instance->next;
				}
			}

			// End the scene
			if( FAILED( m_pd3dDevice->EndScene() ) ) {
				g_directXStatus = -1;
				return;
			}
		}

		// Present the backbuffer contents to the display
		if( FAILED( m_pd3dDevice->Present( NULL, NULL, NULL, NULL ) ) ) {
			g_directXStatus = -1;
			return;
		}
		
	}
	
}

int		CColosseumCtrl::setupLights()
{
	float	max = 1;
    // Set up a white, directional light, with an oscillating direction.
    // Note that many lights may be active at a time (but each one slows down
    // the rendering of our scene). However, here we are just using one. Also,
    // we need to set the D3DRS_LIGHTING renderstate to enable lighting
    D3DXVECTOR3 vecDir;
    D3DLIGHT9 light;
    ZeroMemory(&light, sizeof(D3DLIGHT9));
    light.Type       = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r  = 3.4f;
	light.Diffuse.g  = 3.4f;
	light.Diffuse.b  = 3.4f;
	light.Diffuse.a  = 3.4f;
	light.Specular.r = 0.1f;
	light.Specular.g = 0.1f;
	light.Specular.b = 0.1f;
	light.Specular.a = 0.5f;
	light.Ambient.r  = 0.5f;
	light.Ambient.g  = 0.5f;
	light.Ambient.b  = 0.5f;
	light.Ambient.a  = 1.0f;
    light.Position.x = (float) -2.0f;
    light.Position.y = (float) -2.0f;
    light.Position.z = (float) -2.0f;
    vecDir.x = -2.0f;
    vecDir.y = -6.0f;
    vecDir.z = -1.0f;
    D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);
    light.Range       = 5.0f;
	if	(FAILED(m_pd3dDevice->SetLight(0, &light))) {
		g_directXStatus = -1;
		return	1;
	}

	if	(FAILED(m_pd3dDevice->LightEnable(0, TRUE))) {
		g_directXStatus = -1;
		return	1;
	}

    D3DLIGHT9 light1;
    ZeroMemory(&light1, sizeof(D3DLIGHT9));
    light1.Type       = D3DLIGHT_DIRECTIONAL;
	light1.Diffuse.r  = 3.4f;
	light1.Diffuse.g  = 3.4f;
	light1.Diffuse.b  = 3.4f;
	light1.Diffuse.a  = 3.4f;
	light1.Specular.r = 0.1f;
	light1.Specular.g = 0.1f;
	light1.Specular.b = 0.1f;
	light1.Specular.a = 0.5f;
	light1.Ambient.r  = 0.5f;
	light1.Ambient.g  = 0.5f;
	light1.Ambient.b  = 0.5f;
	light1.Ambient.a  = 1.0f;
    light1.Position.x = (float) 2.0f;
    light1.Position.y = (float) 2.0f;
    light1.Position.z = (float) 2.0f;
    vecDir.x = 2.0f;
    vecDir.y = 6.0f;
    vecDir.z = 1.0f;
    D3DXVec3Normalize((D3DXVECTOR3*)&light1.Direction, &vecDir);
    light1.Range       = 5.0f;
	if	(FAILED(m_pd3dDevice->SetLight(1, &light1))) {
		g_directXStatus = -1;
		return	1;
	}

	if	(FAILED(m_pd3dDevice->LightEnable(1, TRUE))) {
		g_directXStatus = -1;
		return	1;
	}

	if	(FAILED(m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE))) {
		g_directXStatus = -1;
		return	1;
	}

    // Finally, turn on some ambient light.
    m_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0x00707070);

	return	0;
}

int	CColosseumCtrl::setupMatrices()
{
	D3DXMATRIX	matWorld;
    D3DXMatrixIdentity( &matWorld );
	
	matWorld._22 = -1.0f;

	D3DXVec3TransformCoord((D3DXVECTOR3 *) &matWorld._41, &g_vecOrigin, &matWorld);

	if( FAILED( m_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld ) ) ) {
		g_directXStatus = -1;
		return	1;
	}


    // For the projection matrix, we set up a perspective transform (which
    // transforms geometry from 3D view space to 2D viewport space, with
    // a perspective divide making objects smaller in the distance). To build
    // a perpsective transform, we need the field of view (1/4 pi is common),
    // the aspect ratio, and the near and far clipping planes (which define at
    // what distances geometry should be no longer be rendered).
    D3DXMATRIX matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4,  (float) m_width/(float) m_height, 0.03f, 10.0f );
	if( FAILED( m_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj ) ) ) {
		g_directXStatus = -1;
		return	1;
	}

	D3DXMATRIXA16 matrix;
	//Calculate the new view matrix for the camera
	this->m_camera->calculateViewMatrix(&matrix);
	
	if( FAILED( m_pd3dDevice->SetTransform( D3DTS_VIEW, &matrix ) ) ) {
		g_directXStatus = -1;
	}

	return	0;
}
