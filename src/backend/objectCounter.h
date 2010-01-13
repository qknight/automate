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
