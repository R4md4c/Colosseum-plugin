#ifndef IFCENGINEINTERACT_H
#define IFCENGINEINTERACT_H

/* This class handles the interaction between the control and the IFCEngine */

#include "IFCEngine.h"

#define		ITEM_UNCHECKED			0
#define		ITEM_PARTLY_CHECKED		1
#define		ITEM_CHECKED			2

/* Structure that will contain the building information */
typedef struct STRUCT_INSTANCES {
	int					id;
	char				* name;
	STRUCT_INSTANCES	* parent;
	STRUCT_INSTANCES	* next;
	HTREEITEM			hTreeItem;
	int					select;

	int					startVertex;
	int					startIndex;
	int					primitiveCount;
}	struct_type;


class CIFCEngineInteract
{
protected:
	STRUCT_INSTANCES	*m_firstInstance;
	STRUCT_INSTANCES	*m_lastInstance;
	///A flag indicates that the tree that contains the buffer is locked
	bool				 m_isLock;
public:
	CIFCEngineInteract();

	inline bool getLock() {
		return m_isLock;
	}

	inline void setLock(bool enabled = true) {
		m_isLock = enabled;
	}

	STRUCT_INSTANCES	* addObject(STRUCT_INSTANCES * parent, int id, char * name);
	void	retrieveObjects(char * ObjectSPFFName, char * ObjectGroupName);
	int		retrieveObjectGroups(char * fileName);
	void	enrichObjectGroups(int&, int&);
	STRUCT_INSTANCES  *getFirstInstance() const;	
	///Destroy the current object manually 
	void destroyManually();
	~CIFCEngineInteract();
};
#endif