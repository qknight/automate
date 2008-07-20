//
// C++ Interface: AutomateRoot
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
/**
  @author Joachim Schiele <js@lastlog.de>
*/

#ifndef AUTOMATEROOT_H
#define AUTOMATEROOT_H

#include "AbstractTreeItem.h"
#include "objectCounter.h"
#include "SymbolTable.h"

/*! */
class AutomateRoot : public AbstractTreeItem, protected SymbolTable {
  public:
    AutomateRoot( AbstractTreeItem* parent = 0 );
    /*! WARNING: never delete objects as for instance childItems in the structure here
     ** since this will create inconsistencies between the model and this data structure.<br>
     ** A better way is to fail with exit(0) and a meaningful error message meant for
     ** developrs: since this problem must be handled with great care! */
    ~AutomateRoot();
    void dump();
    unsigned int getObjectType();
    void removeChild( unsigned int index );
  private:
    objectCounter* objCnt_node;
    objectCounter* objCnt_automateroot;
    objectCounter* objCnt_nodeconnection;
    unsigned int generateUniqueID( unsigned int );
};

#endif
