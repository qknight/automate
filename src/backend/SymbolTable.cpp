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

#include "SymbolTable.h"

SymbolTable::SymbolTable() {
  indexCount=0;
  symbol("¿"); // undefined
  symbol(QChar('e')); // epsilon
}

SymbolTable::~SymbolTable() {
}

// FIXME this function must emit dataChanged() for all modified QModelIndex'es so
// that all views have to update the symbol
int SymbolTable::modifySymbol( int symbol_index, QString newsymbol ) {
  // fist: check if symbol modification is successful, otherwise return -1;

  // second: traverse the tree starting at root_node and find all connections with equal
  //         symbol_index and find out it's QModelIndex, next emit dataChanged(index,index);
  qDebug() << "not implemented yet";
  return -1;
}

/*
** either add a new symbol_index OR if symbol already exists return the symbol_index for this symbol
** in most cases it will already exist and we return the position to the changed symbol
*/
int SymbolTable::symbol( QString symbol ) {
  // if already defined, return the index
  QHash<int, QString>::const_iterator i = hash.constBegin();
  while (i != hash.constEnd()) {
//     qDebug() << i.key() << ": " << i.value() << endl;
    if (i.value() == symbol)
      return i.key();
    ++i;
  }

  // if new, add symbol and return the index to the new element
  unsigned int newIndex = indexCount++;
  hash.insert(newIndex,symbol);
  return newIndex;
}

QString SymbolTable::symbol( int symbol_index ) const {
  return hash.value(symbol_index);
}

void SymbolTable::dump() {
  qDebug() << "------------------------------";
  QHash<int, QString>::const_iterator i = hash.constBegin();
  while (i != hash.constEnd()) {
    qDebug() << i.key() << ": " << i.value();
    ++i;
  }
//   for(int i=0; i < 8; ++i) {
//     qDebug() << i << " " << symbol(i) << symbol(symbol(i));
//   }
}

int SymbolTable::size() {
  return hash.size();
}