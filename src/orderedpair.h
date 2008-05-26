// automate implements an automate class in c++ using qt4
// Copyright (C) 2007 Christoph Behle
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
  @author Christoph Behle
*/

#ifndef ORDEREDPAIR_H
#define ORDEREDPAIR_H

#include <qpair.h>

template<class T>
class OrderedPair {
    public: // Ctors
        OrderedPair(const T& a, const T& b);
        OrderedPair(QPair<T,T>);

    public: // Functions
        T getFirst() const;
        T getSecond() const;
        operator QPair<T,T>();

    private: // Members
        T m_a;
        T m_b;
};

template<class T>
OrderedPair<T>::OrderedPair(const T& a, const T& b) {
    m_a = a < b ? a : b;
    m_b = a < b ? b : a;
}

template<class T>
OrderedPair<T>::OrderedPair(QPair<T,T> p) {
    m_a = p.first < p.second ? p.first : p.second;
    m_b = p.first < p.second ? p.second : p.first;
}

template<class T>
T OrderedPair<T>::getFirst() const { return m_a; }

template<class T>
T OrderedPair<T>::getSecond() const { return m_b; }

template<class T>
OrderedPair<T>::operator QPair<T,T>() {
    return QPair<T,T>(m_a,m_b);
}

#endif /* ORDEREDPAIR_H */
