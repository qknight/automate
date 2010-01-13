/*
    This file is part of automate.
      Copyright christoph.behle
      
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
  @author Christoph Behle <christoph.behle@student.uni-tuebingen.de>
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
