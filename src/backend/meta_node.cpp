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


#include "meta_node.h"

void meta_node::addNode ( node* n )
{
  node_container.insert ( n );
}
int meta_node::size()
{
  qDebug("%i", node_container.size());
  return node_container.size();
}

meta_node::meta_node(QList<node*> a){
//     std::cerr << "meta_node(QList<node*> a) CTOR called with QList<node*> argument, ";
//     std::cerr << a.size() << " nodes added" << std::endl;
    for(int i=0; i < a.size(); ++i) {
      node_container.insert(a[i]);
    }
//     std::cerr << "node_container contains: " << size() << " nodes now" << std::endl;
  }

    bool meta_node::operator== ( const meta_node& a )
    {
      if ( a.node_container.size() == this->node_container.size() )
      {
        return ( a.node_container==this->node_container );
      }
      return false;
    }
