//
// C++ Implementation: SymbolTable
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "SymbolTable.h"

SymbolTable::SymbolTable() {
  indexCount=0;
}

SymbolTable::~SymbolTable() {
}

int SymbolTable::setSymbol( QString symbol ) {
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

QString SymbolTable::symbol( int symbol_index ) {
  return hash.value(symbol_index);
}

void SymbolTable::dump() {
  QHash<int, QString>::const_iterator i = hash.constBegin();
  while (i != hash.constEnd()) {
    qDebug() << i.key() << ": " << i.value();
    ++i;
  }
}
