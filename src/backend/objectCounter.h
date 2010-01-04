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


#ifndef OBJECTCOUNTER_H
#define OBJECTCOUNTER_H

#include <QDebug>

//!  A simple object counter
/*!
  using this instead of a local variable makes the code
  more readable: keep in mind that the internal id variable may be to small for your use case
*/
class objectCounter{
private:
    //! Enum variable.
    /*! internal storage of the value. */
    unsigned int value;
public:
    //! A constructor.
    objectCounter();
    //! A destructor.
    ~objectCounter();
    //! returns a new and uniq id
    unsigned int newID();
};

#endif
