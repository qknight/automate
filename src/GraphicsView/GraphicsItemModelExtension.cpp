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

#include "GraphicsItemModelExtension.h"
#include "GraphicsScene.h"

QVariant GraphicsItemModelExtension::modelData(  QGraphicsScene* scene, const QModelIndex &index, int role ) const {
  if (scene == NULL) // might happen if an item is currently not in any scene
    return QVariant();
  GraphicsScene* m_scene = (GraphicsScene*) scene;
//   GraphicsScene* m_scene = static_cast<GraphicsScene*> (scene);
  return m_scene->data( index, role );
}

bool GraphicsItemModelExtension::setModelData( QGraphicsScene* scene, const QModelIndex & index, const QVariant & value, int role ) {
  if (scene == NULL) // might happen if an item is currently not in any scene
    return false;
  GraphicsScene* m_scene = (GraphicsScene*) scene;
//   GraphicsScene* m_scene = static_cast<GraphicsScene*> (scene);
  return m_scene->setData( index, value, role );
}

