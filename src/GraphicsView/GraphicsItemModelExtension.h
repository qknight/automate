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

#ifndef ABSTRACTMVCGRAPHICSITEM_H
#define ABSTRACTMVCGRAPHICSITEM_H

#include <QPersistentModelIndex>

#include <QGraphicsScene>
/*!
 * this class extends all normal QGraphicsItem(s) with another data/setData function, both yet different
 * class definitions can be used simultaneously since the parameterlist is different. 
 *
 * and this is a central place for all items to query the model for data/setData
 */
class GraphicsItemModelExtension {
  public:
    /*! a wrapper function for all items in the scene, so that they can call data() directly */
    QVariant modelData( QGraphicsScene* scene, const QModelIndex &index, int role ) const;
    /*! a wrapper function for all items in the scene, so that they can call setData() directly */
    bool setModelData( QGraphicsScene* scene, const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
};
#endif // ABSTRACTMVCGRAPHICSITEM_H
