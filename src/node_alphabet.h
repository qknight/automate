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

/**
  @author Joachim Schiele <js@lastlog.de>
*/

#ifndef NODE_ALPHABET_H
#define NODE_ALPHABET_H

//!  TODO description short
/*!
  TODO description long
*/
class node_alphabet {
    node_alphabet() {
        addSymbol(63);  // symbol refering to a not defined connection
        addSymbol(949); // symbol for epsilon
    }
public:
    void addSymbol(QChar c) {
        symbolcontainer.push_back(c);
    }
private:
    QVector<QChar> symbolcontainer;
};

#endif
