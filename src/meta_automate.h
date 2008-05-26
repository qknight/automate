// automate implements an automate class in c++ using qt4
// Copyright (C) 2007 Joachim Schiele
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// version 2 as published by the Free Software Foundation
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

#ifndef META__AUTOMATE__HH__
#define META__AUTOMATE__HH__

/*
** This automate is used for e-free-NFA to DFA conversion
*/
#include <QSet>
#include <QMultiMap>

// #include "meta_node.h"
#include "automate.h"

//!  TODO description short
/*!
  TODO description long
*/
class meta_automate
{
  public: // Ctors
    meta_automate ( QList<node*> initNodes );
    ~meta_automate();

  public: // Functions
    bool convert();

  private: // Functions
    node* getNodePtr ( QList<node *> nodePtrList );

  private: // Members
    automate* am;
    QVector<meta_node*> meta_node_container;
    unsigned int stack_ptr;
};

#endif
