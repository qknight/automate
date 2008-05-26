/*
** a qgraphisscene has different items in it
** we use that to distinguish between different object types
*/

#ifndef SCENEITEM__TYPES__HH
#define SCENEITEM__TYPES__HH

#include <QGraphicsItem>

enum {
  SceneItem_NodeType = QGraphicsItem::UserType + 1,
  SceneItem_ConnectionType = QGraphicsItem::UserType + 2
};

#endif
