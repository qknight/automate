//
// C++ Interface: SymbolTable
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <QString>
#include <QHash>
#include <QDebug>

/**
  @author Joachim Schiele <js@lastlog.de>
 */

class SymbolTable{
  friend class Model;
  friend class automatehandler;
  public:
    SymbolTable();
    ~SymbolTable();
  protected:
    int symbol(QString symbol);
    QString symbol(int symbol_index) const;
    int modifySymbol( int position, QString newsymbol);
    int size();
    void dump();
  private:
    QHash<int,QString> hash;
    unsigned int indexCount;
};

#endif
