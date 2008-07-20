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


// i hope i don't have the same issue as this post mentiones:
//  http://lists.trolltech.com/qt-interest/2007-06/thread00580-0.html
//
// problem: insertRows inserts the data and the QAbstractItemView updates well but the
//          QTreeView won't unless you call dataChanged()
// pos. sol: will try to test if it works with qt 4.2.3
/**
  @author Joachim Schiele <js@lastlog.de>
*/

#include "Model.h"

// a lot of code was taken from the simpletreemodel example and later
// heavily modified

// Documentation:
// /usr/share/qt4/examples/itemviews/simpletreemodel
// http://doc.trolltech.com/4.3/model-view-creating-models.html
// http://doc.trolltech.com/4.3/model-view-model-subclassing.html
// http://wiki.kde.org/tiki-index.php?page=ItemView+Tips

Model::Model( AbstractTreeItem* root, QObject* parent ) : QAbstractItemModel( parent ) {
  rootItem = root;
}

QModelIndex Model::index( int row, int column, const QModelIndex & parent ) const {
  /*
  index()
   Given a model index for a parent item, this function allows views
   and delegates to access children of that item. If no valid child item -
   corresponding to the specified row, column, and parent model index,
   can be found, the function must return QModelIndex(), which is an invalid
   model index.
  */
//     qDebug() << "index(" << row <<", " <<column<<")";

  if ( !hasIndex( row, column, parent ) )
    return QModelIndex();

  AbstractTreeItem* parentItem;

  //BUG, parent ist nie valid, darum fehler!
  if ( !parent.isValid() )
    parentItem = rootItem;
  else {
    parentItem = static_cast<AbstractTreeItem*>( parent.internalPointer() );
  }
  AbstractTreeItem* childItem = parentItem->child( row );
//     qDebug() << "index: parentItem==" << (unsigned int) parentItem;
//     qDebug() << "index:  childItem==" << (unsigned int) childItem;

  if ( childItem ) {
//       qDebug() << "createIndex(" << row << ", " << column << ", " << (unsigned int) childItem << ");";
    return createIndex( row, column, childItem );
  }

//     qDebug() << "invalid";
  return QModelIndex();
}

QModelIndex Model::parent( const QModelIndex & child ) const {
  /*
  parent()
    Provides a model index corresponding to the parent of any given child item.
    If the model index specified corresponds to a top-level item in the model,
    or if there is no valid parent item in the model, the function must return
    an invalid model index, created with the empty QModelIndex() constructor.
  */
  // fall 1: parentitem fuer invalid
//       qDebug() << "parent ";
//  << QString("%1").arg((unsigned int) child);

  if ( !child.isValid() ) {
    return QModelIndex();
  }
//     qDebug() << "parent2or3";

  AbstractTreeItem *childItem =
    static_cast<AbstractTreeItem*>( child.internalPointer() );
  AbstractTreeItem *parentItem = childItem->parent();

// fall 2: parentitem fuer rootItem
//   if ( parentItem == NULL )
//     return QModelIndex();

  if ( parentItem == rootItem )
    return QModelIndex();

// fall 3: parentitem fuer alle anderen
//     return index(r,c,parent model index);
  return createIndex( parentItem->row(), 0, parentItem );
}

/*!
** this code should be read as table of generic cases (where row/column doesn't matter)
** which is important for the graphicsView. for the treeView there is a part of code where
** row/column matters, see the very long switch statement.
*/
QVariant Model::data( const QModelIndex &index, int role ) const {
//   qDebug() << __FUNCTION__;
  if ( !index.isValid() )
    return QVariant();

  AbstractTreeItem* n = static_cast<AbstractTreeItem*>( index.internalPointer() );
  if ( role == customRole::CustomLabelRole )
    return n->getProperty( "CustomLabelRole" );
  if ( role == customRole::FinalRole )
    if ( n->getObjectType() == NODE )
      return n->getProperty( "final" );
  if ( role == customRole::StartRole )
    if ( n->getObjectType() == NODE )
      return n->getProperty( "start" );
  if ( role == customRole::SymbolIndexRole )
    if ( n->getObjectType() == NODE_CONNECTION ) {
      node_connection* nc = static_cast<node_connection*>( index.internalPointer() );
//       qDebug() << __FUNCTION__ << symbol( nc->symbol_index ) << nc->symbol_index;
      return symbol( nc->symbol_index() ) ;
    }
  if ( role == customRole::IdRole )
    if ( n->getObjectType() == NODE || n->getObjectType() == NODE_CONNECTION )
      return n->getId();
  switch ( index.column() ) {
  case 0:
    switch ( role ) {
    case Qt::DecorationRole:
      if ( n->getObjectType() == NODE )
        return QIcon( ":/icons/node.png" );
      if ( n->getObjectType() == NODE_CONNECTION )
        return QIcon( ":/icons/connect.png" );
    }
    break;
  case 1:
    switch ( role ) {
    case Qt::ToolTipRole:
      break;
    case Qt::WhatsThisRole:
      break;
    case Qt::TextAlignmentRole:
//           if (index.column() == 1)
//             return Qt::AlignHCenter;
//           if (index.column() == 2)
//             return Qt::AlignHCenter;
      break;
    case customRole::SortRole:
    case Qt::DecorationRole:
      if ( n->getObjectType() == NODE ) {
        if ( n->getProperty( "start" ).toBool() ) {
          if ( role == customRole::SortRole )
            return 1;
          return QIcon( ":/icons/startNode.png" );
        } else {
          if ( role == customRole::SortRole )
            return 0;
        }
      }
      break;
//     case Qt::BackgroundRole:
//       break;
    }
    break;
  case 2:
    switch ( role ) {
    case customRole::SortRole:
    case Qt::DecorationRole:
      if ( n->getObjectType() == NODE ) {
        if ( n->getProperty( "final" ).toBool() ) {
          if ( role == customRole::SortRole )
            return 1;
          return QIcon( ":/icons/finalNode.png" );
        } else {
          if ( role == customRole::SortRole )
            return 0;
        }
      }
      break;
    }
    break;
  case 3:
    switch ( role ) {
    case customRole::SortRole:
    case Qt::DisplayRole:
      if ( n->getObjectType() == NODE ) {
        if ( role == customRole::SortRole ) {
          return n->getId();
        }
        if ( role == Qt::DisplayRole )
          return QString( "n%1" ).arg( n->getId() );// "node";
      }
      if ( n->getObjectType() == NODE_CONNECTION ) {
        if ( role == customRole::SortRole )
          return n->getId();
        if ( role == Qt::DisplayRole )
          return QString( "c%1" ).arg( n->getId() );// "node_connection";
      }
      break;
    }
  case 4:
    switch ( role ) {
    case customRole::SortRole:
    case Qt::DisplayRole:
      if ( n->getObjectType() == NODE_CONNECTION ) {
        if ( role == customRole::SortRole )
          return ( static_cast<node_connection*>( n ) )->symbol_index();// "node_connection";
        if ( role == Qt::DisplayRole )
          return symbol(( static_cast<node_connection*>( n ) )->symbol_index() );// "node_connection";
      }
    }

    break;
  case 5:
    switch ( role ) {
    case Qt::BackgroundRole:
      if ( n->getObjectType() == NODE_CONNECTION )
        if ((static_cast<node_connection*>( n ) )->next_node() == NULL)
          return QBrush( QColor( 255, 0, 0, 250 ) );
      break;
    case customRole::SortRole:
    case Qt::DisplayRole:
      if ( n->getObjectType() == NODE_CONNECTION ) {
        if ((static_cast<node_connection*>( n ) )->next_node() == NULL)
          return "undefined";
        AbstractTreeItem* next_node = ( static_cast<node_connection*>( n ) )->next_node();
        if ( role == customRole::SortRole )
          return next_node->getId();// "node_connection";
        if ( role == Qt::DisplayRole )
          return QString( "n%1" ).arg( next_node->getId() );// "node_connection";
      }
    }
    break;
  case 6:
    if ( role == Qt::DisplayRole ) {
      return n->getProperty( "CustomLabelRole" );
    }
    break;
    /*  case 7:
        break;*/
  }
  if ( role == Qt::BackgroundRole ) {
    if ( n->getObjectType() == NODE )
      return QBrush( QColor( 50, 160, 170, 150 ) );
    if ( n->getObjectType() == NODE_CONNECTION )
      return QBrush( QColor( 180, 200, 200, 50 ) );
  }

  return QVariant();
}

int Model::rowCount( const QModelIndex & sibling ) const {
// returns how many siblings this "sibling" node has
  AbstractTreeItem *parentItem;

  if ( sibling.column() > 0 ) {
//       qDebug() << "rowcount=0";
    return 0;
  }

  if ( !sibling.isValid() )
    parentItem = rootItem;
  else
    parentItem = static_cast<AbstractTreeItem*>( sibling.internalPointer() );

//     qDebug() << "rowcount="<<parentItem->childCount();
  return parentItem->childCount();
}

int Model::columnCount( const QModelIndex & /*parent*/ ) const {
  return 7;
}

bool Model::insertRows( int row, int count, const QModelIndex & parent ) {
  if (count > 1)
    qDebug() << "WARNING: this might need some testing";

  if ( !parent.isValid() ) { // no valid parent -> it's a node to add
    AbstractTreeItem* abstractitem = rootItem;
//     qDebug() << "case node";
    beginInsertRows( parent, row, row + count - 1 );
    {
      node* n = new node( abstractitem );
      n->setProperty( "start", false );
      n->setProperty( "final", false );
      abstractitem->appendChild( n );
    }
    endInsertRows();
    return true;
  }
  if ( getTreeItemType( parent ) == NODE ) {
    AbstractTreeItem* abstractitem = static_cast<AbstractTreeItem*>( parent.internalPointer() );
//     int id = abstractitem->getId();
//     qDebug() << "beginInsertRows( n"  << id << " , " << row << ", " << row + count - 1 << ");";
    beginInsertRows( parent, row, row + count - 1 );
    {
      int i = count ;
      while ( i-- ) {
        node_connection* nc = new node_connection( abstractitem );
        abstractitem->appendChild( nc );
      }
    }
    endInsertRows();
    return true;
  }
  qDebug() << "can't add object to the automate class since i don't know what to do, exiting";
  exit(0);
  return false;
}

Qt::ItemFlags Model::flags( const QModelIndex & index ) const {
  //FIXME only make setData able fields editable
  if ( !index.isValid() )
    return 0;
  return QAbstractItemModel::flags( index ) | Qt::ItemIsEditable;
}

bool Model::setData( const QModelIndex & index, const QVariant & value, int role ) {
//   qDebug() << "setData " << index.column();
  if (( index.isValid() && getTreeItemType( index ) == NODE_CONNECTION && index.column() == 4 && role == Qt::EditRole ) ||
      ( index.isValid() && getTreeItemType( index ) == NODE_CONNECTION && role == customRole::SymbolIndexRole ) ) {
    AbstractTreeItem* n = static_cast<AbstractTreeItem*>( index.internalPointer() );
    node_connection* nc = static_cast<node_connection*>( n );
    nc->setSymbol_index( symbol( value.toString() ) );
//     qDebug() << __FUNCTION__ << value.toString() << " " << nc->symbol_index() << " " << symbol( nc->symbol_index() );
    emit dataChanged( index, index );
    return true;
  }
  if ( index.isValid() && getTreeItemType( index ) == NODE_CONNECTION && index.column() == 5 && role == Qt::EditRole ) {
    AbstractTreeItem* n = static_cast<AbstractTreeItem*>( index.internalPointer() );
    node_connection* nc = static_cast<node_connection*>( n );
    AbstractTreeItem* a = AbstractTreeItemFromId( value.toInt() );
    if ( a == NULL ) {
      qDebug() << "can't redirect connection because the given node id was not found in the graph, please try again later!";
      return false;
    }
    nc->setNext_node( a );
    emit dataChanged( index, index );
    return true;
  }
  if (( index.isValid() && index.column() == 6 && role == Qt::EditRole ) ||
      ( index.isValid() && role == customRole::CustomLabelRole ) ) {
    AbstractTreeItem* nItem = static_cast<AbstractTreeItem*>( index.internalPointer() );
    nItem->setProperty( "CustomLabelRole", value );
    emit dataChanged( index, index );
    return true;
  }

  if ( index.isValid() && getTreeItemType( index ) == NODE && (( role == customRole::StartRole ) || role == customRole::FinalRole ) ) {
    AbstractTreeItem* n = static_cast<AbstractTreeItem*>( index.internalPointer() );
    QModelIndex correctedIndex;
    if ( role == customRole::StartRole ) {
      n->setProperty( "start", value );
      correctedIndex = Model::index( index.row(), 1, index.parent() );
    }
    if ( role == customRole::FinalRole ) {
      n->setProperty( "final", value );
      correctedIndex = Model::index( index.row(), 2, index.parent() );
    }
    emit dataChanged( correctedIndex, correctedIndex );
    return true;
  }
  return false;
}

AbstractTreeItem* Model::AbstractTreeItemFromId( unsigned int id ) {
  foreach( AbstractTreeItem* item, rootItem->childItems() )
  if ( item->getId() == id )
    return item;
  return NULL;
}

QVariant Model::headerData( int section, Qt::Orientation orientation, int role ) const {
  if ( orientation == Qt::Horizontal && ( role == Qt::DisplayRole || role == Qt::ToolTipRole ) ) {
    switch ( section ) {
    case 0:
      if ( role == Qt::DisplayRole )
        return "?";
      else
        if ( role == Qt::ToolTipRole )
          return "don't ask!?";
    case 1:
      if ( role == Qt::DisplayRole )
        return "s";
      else
        if ( role == Qt::ToolTipRole )
          return "Is this node a startnode?";
    case 2:
      if ( role == Qt::DisplayRole )
        return "f";
      else
        if ( role == Qt::ToolTipRole )
          return "Is this node a final?";
    case 3:
      if ( role == Qt::DisplayRole )
        return "Node";
      else
        if ( role == Qt::ToolTipRole )
          return "AbstractTreeItem -> can be a NODE or a NODE_CONNECTION";
    case 4:
      if ( role == Qt::DisplayRole )
        return "Symbol";
      else
        if ( role == Qt::ToolTipRole )
          return "Symbol for outgoing connection";
    case 5:
      if ( role == Qt::DisplayRole )
        return "DestNode";
      else
        if ( role == Qt::ToolTipRole )
          return "The node this connection points to";
    case 6:
      if ( role == Qt::DisplayRole )
        return "label";
      else
        if ( role == Qt::ToolTipRole )
          return "A custom label for nodes/connection";
    }
  }
  return QVariant();
}

unsigned int Model::getSelectedItemType( const QModelIndex& a ) {
  AbstractTreeItem* n = static_cast<AbstractTreeItem*>( a.internalPointer() );
  if ( n )
    return n->getObjectType();
  else
    return UNKNOWN;
};

bool Model::removeRows( int row, int count, const QModelIndex & parent ) {
//   qDebug() << "want to remove " << count << " item(s) beginning at row " << row;
  AbstractTreeItem* abstractitem;
  if ( !parent.isValid() ) {
    abstractitem = rootItem;
  } else {
    abstractitem = static_cast<AbstractTreeItem*>( parent.internalPointer() );
  }

//   qDebug() << "The id of the object to delete is id::" << abstractitem->getId();
  int from_row = row;
  int to_row = row + count - 1;
//   qDebug() << "  beginRemoveRows(parent, row_first, row_last);" << from_row << " " <<  to_row;
  beginRemoveRows( parent, from_row, to_row );
  {
    int i = count;
    // FIXME deleting could be speeded up by better code design here
    while ( i-- )
      abstractitem->removeChild( row );
  }
  endRemoveRows();
  return true;
}

QModelIndex Model::getQModelIndexFromAbstractNodeItem( AbstractTreeItem* item ) {
  AbstractTreeItem* t;
  QModelIndex ret;
  QModelIndex z;
  switch ( item->getObjectType() ) {
  case AUTOMATE_ROOT:
    break;
  case NODE:
    ret = index( item->row(), 0, QModelIndex() );
//     qDebug() << NODE << " NODE with row()=" << item->row() << " with id n" << item->getId();
    t = static_cast<AbstractTreeItem*>( ret.internalPointer() );
//     qDebug() << ( unsigned int ) t << "id = " << t->getId();
//     qDebug() << objectTypeQString(t->getObjectType());
//     qDebug() << "this NODE has " << t->childCount() << " childs" ;
    return ret;
  case NODE_CONNECTION:
    z = getQModelIndexFromAbstractNodeItem( item->parent() );
    ret = index( item->row(), 0, z );
//     qDebug() << NODE_CONNECTION  << " NODE_CONNECTION with row()=" << item->row() << " with id c" << item->getId();
    t = static_cast<AbstractTreeItem*>( ret.internalPointer() );
//     qDebug() << ( unsigned int ) t;
    return ret;
  default:
    qDebug() << "In " << __FILE__ << ", " << __FUNCTION__ << " something went very wrong!";
    exit( 0 );
  }
  return QModelIndex();
}

QString Model::objectTypeQString( unsigned int input ) {
  switch ( input ) {
  case AUTOMATE_ROOT:
    return "AUTOMATE_ROOT";
  case NODE:
    return "NODE";
  case NODE_CONNECTION:
    return "NODE_CONNECTION";
  case UNKNOWN:
    return "UNKNOWN";
  }
  return "?";
}

unsigned int Model::getTreeItemType( const QModelIndex& item ) {
  if ( !item.isValid() )
    return UNKNOWN;

  AbstractTreeItem* t = static_cast<AbstractTreeItem*>( item.internalPointer() );

  return ( t->getObjectType() );
}

bool Model::hasChildren ( const QModelIndex & parent ) const {
//   qDebug() << "one is calling me" << __FUNCTION__;
  if (!parent.isValid())
    return true;
  AbstractTreeItem* item = static_cast<AbstractTreeItem*>( parent.internalPointer() );
  if (item->childCount() > 0)
    return true;
  return false;
}

// returns the QModelIndex of the next_node from cItem
QModelIndex Model::next_nodeModelIndex( QModelIndex cItem ) {
  if ( getTreeItemType( cItem ) == NODE_CONNECTION ) {
    node_connection* t = static_cast<node_connection*>( cItem.internalPointer() );
    if ( t->next_node() != NULL )
      return getQModelIndexFromAbstractNodeItem( t->next_node() );
  }
  return QModelIndex();
}

/*
** inserts a connection to the given node
**  if a vaild endItem is given modifications are made in place to point to the endItem
**  if not then a local loop is created
*/
bool Model::insertConnection( QModelIndex startItem, QModelIndex endItem ) {
//   qDebug() << "startitem: n" << data( startItem, customRole::IdRole ).toInt();
  int row = rowCount( startItem );
  bool success = insertRows( row, 1, startItem );
  if ( success && endItem.isValid() ) {
//     qDebug() << "enditem: n" << data( endItem, customRole::IdRole ).toInt();

    QModelIndex cItem = index( row, 0, startItem );
//     qDebug() << "cItem: c" << data( cItem, customRole::IdRole ).toInt();
    AbstractTreeItem* dest_ptr = static_cast<AbstractTreeItem*>( endItem.internalPointer() );

    AbstractTreeItem* n = static_cast<AbstractTreeItem*>( cItem.internalPointer() );
    node_connection* nc = static_cast<node_connection*>( n );

    nc->setNext_node( dest_ptr );
    emit dataChanged( cItem, cItem );
  }
  return success;
}

bool Model::removeConnection( QPersistentModelIndex connection ) {
  if ( !connection.isValid() ) {
    qDebug() << "connection is not a valid QModelIndex (anymore?), not deleting anything";
    return true;
  }

//   qDebug() << "removing a connection";
  return removeRow( connection.row(), connection.parent() );
}

bool Model::removeConnections( QList<QPersistentModelIndex> nodeList ) {
//   qDebug() << __FUNCTION__;
  bool s = true;
  foreach( QModelIndex item, nodeList ) {
    if ( !item.isValid() ) {
      // this can happen when you delete a node since all connections to and from it are deleted implicitly
      // but the selection still has some connections in the list of items to be deleted
//       qDebug() << __FUNCTION__ << "WARNING: QModelIndex is not valid anymore, skipping a deletion";
      continue;
    } else {
      if ( !removeConnection( item ) && s )
        s = false;
    }
  }
  return s;
}

/*
** This function can be called with [node and node_connection model indexes in arbitrary order]
**  - first all nodes get deleted BUT this list isn't altered so there might be connections in
**    the list which are already deleted because when a NODE is deleted all incomming/outgoing
**    connections are deleted implicitly. however having a list of connections with valid and invalid
**    QModelIndex is no problem as only those get deleted which are still deletable.
**  - if a NODE is deleted all incomming/outgoing connections are deleted implicitly,
**     see: bool removeNode( QPersistentModelIndex node );
*/
bool Model::removeItems( QList<QPersistentModelIndex> itemList ) {
  QList<QPersistentModelIndex> nodeItems;
  QList<QPersistentModelIndex> connectionItems;
  foreach( QModelIndex m, itemList ) {
    if ( !m.isValid() ) {
      qDebug() << __FUNCTION__ << "FATAL ERROR: QModelIndex is not valid anymore, may|must NOT happen here!, exiting";
      exit(0);
    }
    if ( getTreeItemType( m ) == NODE )
      nodeItems.append( QPersistentModelIndex( m ) );

    if ( getTreeItemType( m ) == NODE_CONNECTION )
      connectionItems.append( QPersistentModelIndex( m ) );
  }
  return removeNodes( nodeItems ) && removeConnections( connectionItems );
}

/// this function is provided for convenience
bool Model::removeNodes( QList<QPersistentModelIndex> nodeList ) {
  bool s = true;
  foreach( QModelIndex item, nodeList ) {
    if ( !item.isValid() ) {
      // this should never happen
      qDebug() << __FUNCTION__ << "FATAL ERROR: QModelIndex for a node is not valid anymore";
      exit(0);
    } else {
      if ( !removeNode( item ) && s )
        s = false;
    }
  }
  return s;
}

/*
** removeNodes removes NODEs only
** removing a node implies:
**  - delete all outgoing connections
**  - delete all incomming connections (references)
**  - delete the node itself
*/
bool Model::removeNode( QPersistentModelIndex abstractQModelIndex ) {
//   qDebug() << __FUNCTION__;
  // FIXME code below should be removable
  if ( !abstractQModelIndex.isValid() ) {
    qDebug() << "FATAL ERROR: abstractQModelIndex is not a valid QModelIndex (anymore?), exiting";
    exit(0);
  }

  if ( getSelectedItemType( abstractQModelIndex ) == NODE ) {
//     qDebug() << "   ###### object to delete is a node ######";
    // for all childs which are connections
    //     delete connection
//     qDebug() << "     ###### step one: delete all childs ######";
    node* n = static_cast<node*>( abstractQModelIndex.internalPointer() );
    if ( n->childCount() ) {
//       qDebug() << "removing " << n->childCount() << " child items";
      removeRows( 0, n->childCount(), abstractQModelIndex );
    }

    //   for all reverse connections to this connection
//     qDebug() << "     ###### step two: delete all references (connections) to this node ######";

//     qDebug() << "n" << n->getId() << " has " << n->reverseChildItems().size() << " reverse connections";
    while ( n->reverseChildItems().size() ) {
//       qDebug() << "deleting the first connection from " << n->reverseChildItems().size()  << " which are to be deleted";
      node_connection* r_item = static_cast<node_connection*>( n->reverseChildItems().first() );

      // find the f_item for this r_item
      node_connection* f_item = r_item->inverseConnection;
      QModelIndex f_itemIndex = getQModelIndexFromAbstractNodeItem( f_item );
      if ( f_itemIndex == QModelIndex() ) {
        qDebug() << __FUNCTION__ << "FATAL ERROR: object f_item was expected to be a valid node* item but something is wrong.";
        exit( 0 );
      }
      removeConnection( f_itemIndex );
    }

//     qDebug() << "     ###### step three: delete this node ######";
//       qDebug() << "found " << objectTypeQString( getSelectedItemType( abstractQModelIndex.parent() ) );
    removeRow( abstractQModelIndex.row(), abstractQModelIndex.parent() );
  } else {
    qDebug() << "WARNING: removeNodes should remove an object which is no NODE?! maybe use removeItems(...)";
    exit( 0 );
  }
//   qDebug() << __FUNCTION__ << "END: return success";
  return true;
}

QString Model::symbol( int symbol_index ) const {
  return (( AutomateRoot* )rootItem )->symbol( symbol_index );
}

int Model::symbol( QString symbol ) {
  return (( AutomateRoot* )rootItem )->symbol( symbol );
}

int Model::modifySymbol( int position, QString newsymbol ) {
  return (( AutomateRoot* )rootItem )->modifySymbol( position, newsymbol );
}

int Model::size() {
  return (( AutomateRoot* )rootItem )->size();
}

bool Model::insertNode() {
  return insertRows( rowCount( QModelIndex() ), 1 );
}

