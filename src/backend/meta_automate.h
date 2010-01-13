/*
    This file is part of automate.
      Copyright Joachim Schiele
      
    automate is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License.

    automate is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with automate.  If not, see <http://www.gnu.org/licenses/>.
*/

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
class meta_automate {
  public: // Ctors
    /*! */
    meta_automate ( QList<node*> initNodes );
    /*! */
    ~meta_automate();

  public: // Functions
    /*! */
    bool convert();

  private: // Functions
    /*! */
    node* getNodePtr ( QList<node *> nodePtrList );

  private: // Members
    /*! */
    automate* am;
    /*! */
    QVector<meta_node*> meta_node_container;
    /*! */
    unsigned int stack_ptr;
};

#endif
