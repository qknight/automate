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
