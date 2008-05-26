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

// Notice: most of this code was taken from the QT4 example code

#include "AbstractTreeItem.h"

AbstractTreeItem::AbstractTreeItem( AbstractTreeItem *parent ) {
//   qDebug() << "AbstractTreeItem Constructor called";
  parentItem = parent;
  ID = 0; //initialize the id, 0 is rootNode or
}

AbstractTreeItem::~AbstractTreeItem() {
//   qDebug() << "AbstractTreeItem Destructor called";
  qDeleteAll( childItems );
}

void AbstractTreeItem::appendChild( AbstractTreeItem *item ) {
  if ( item->parent() != this ) {
    qDebug( "ERROR: you can't add a child to a parent item where \
            the parent of the child doesn't match the parent you want to add it to!" );
  }
  childItems.append( item );
}

AbstractTreeItem *AbstractTreeItem::child( int row ) {
  return childItems.value( row );
}

int AbstractTreeItem::childCount() const {
  return childItems.count();
}

int AbstractTreeItem::columnCount() const {
  return itemData.count();
}

QVariant AbstractTreeItem::data( int column ) const {
  return itemData.value( column );
}

AbstractTreeItem *AbstractTreeItem::parent() {
  return parentItem;
}

int AbstractTreeItem::row() const {
//   qDebug() << (unsigned int) parentItem;
  if ( parentItem )
    return parentItem->childItems.indexOf( const_cast<AbstractTreeItem*>( this ) );

  return 0;
}

unsigned int AbstractTreeItem::getId() {
  return ID;
}


