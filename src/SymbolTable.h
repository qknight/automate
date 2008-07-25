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

#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <QString>
#include <QHash>
#include <QDebug>

/*! the symbol table was introduced since algorithms operating on the data (automate) need to
** compare connections based on their symbol fast and elegant. since int compares are much faster
** than QString compares this is the way to go.*/
class SymbolTable{
  friend class Model;
  friend class automatehandler;
  public:
    /*! constructor */
    SymbolTable();
    /*! destructor */
    ~SymbolTable();
  protected:
    /*! query the internal 'int' representation of a symbol */
    int symbol(QString symbol);
    /*! query the internal 'QString' representation of a 'int'*/
    QString symbol(int symbol_index) const;
    /*! modifies a symbol position which is already in use. this function is not complete yet. */
    int modifySymbol( int position, QString newsymbol);
    /*! returns the amount of used symbol. can be bigger than it is in reality since we don't remove
    ** symbol representations after they are not used anymore.*/
    int size();
    /*! dumps out the table for debugging usage */
    void dump();
  private:
    /*! internl container to store the data */
    QHash<int,QString> hash;
    /*! needed to keep track of the last symbol position we added */
    unsigned int indexCount;
};

#endif
