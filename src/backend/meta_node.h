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

#ifndef META_NODE_H
#define META_NODE_H

/*
** meta node contains all processed new nodes which are
** associated with their node ids'
**
** meta_nodes are used for e-free-NFA to DFA conversion
*/

#include <QSet>
#include "node.h"

//!  TODO description short
/*!
  TODO description long
*/
class meta_node
{
  public: // Ctors
    /*! */
    meta_node(QList<node*> a);

  public: // Operators
    /*! */
    bool operator== ( const meta_node& a );
  public: // Functions
    /*! */
    QSet<node*> node_container; // contains node* from the old automate (NFA)
    /*! */
    void addNode ( node* n );
    /*! */
    int size();
  public: // Member
    /*! */
    node* node_ptr; // node* to a node in the new automate (DFA)
};

#endif
