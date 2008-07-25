// automate implements an automate class in c++ using qt4
// Copyright (C) 2007 Joachim Schiele
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// version 3 as published by the Free Software Foundation
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

/**
  @author Joachim Schiele <js@lastlog.de>
*/

#ifndef AUTOMATEROOT_H
#define AUTOMATEROOT_H

#include "AbstractTreeItem.h"
#include "objectCounter.h"
#include "SymbolTable.h"

/*! this class is only instantiated once for every automate
 ** this is the only instance which is able to give valid IDs */
class AutomateRoot : public AbstractTreeItem, protected SymbolTable {
  public:
    AutomateRoot( AbstractTreeItem* parent = 0 );
    /*! WARNING: never delete objects as for instance childItems in the structure here
     ** since this will create inconsistencies between the model and this data structure.<br>
     ** A better way is to fail with exit(0) and a meaningful error message meant for
     ** developrs: since this problem must be handled with great care! */
    ~AutomateRoot();
    /*! dumps out all needed information about the data for debugging */
    void dump();
    /*! helper to identify what kind of object 'this' is */
    unsigned int getObjectType();
    /*! removes a node at index position [index]
     - if index is valid, then the item at pos index is removed
     - if index is invalid then the program stops with exit(0) */
    void removeChild( unsigned int index );
  private:
    /*! counts all node objects */
    objectCounter* objCnt_node;
    /*! counts all automateroot objects */
    objectCounter* objCnt_automateroot;
    /*! counts all nodeconnetions */
    objectCounter* objCnt_nodeconnection;
    /*! will generate a uniq id for the caller object */
    unsigned int generateUniqueID( unsigned int );
};

#endif
