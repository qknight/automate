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

#ifndef SCENEITEM__TYPES__HH
#define SCENEITEM__TYPES__HH

#include <QGraphicsItem>

/*! a qgraphisscene has different items in it
 ** we use that to distinguish between different object types
 */
enum {
  SceneItem_NodeType = QGraphicsItem::UserType + 1,
  SceneItem_ConnectionType,
  SceneItem_ConnectionHandleType,
  SceneItem_LabelEditorType
};

#endif
