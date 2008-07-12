//
// C++ Implementation: automate_algorithms
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "meta_automate.h"
#include "orderedpair.h"

/*!
**
*/
void automate::completeDFA() {
    bool need_completion = false;
    unsigned int sinkNode;
    QSet<unsigned int> alphabet;
    for (int i=0;i<node_container.size();++i) {
        alphabet+=node_container[i]->getConnectonIndexes();
    }
    for (int i=0;i<node_container.size();++i) {
        QSet<unsigned int> node_syms=node_container[i]->getConnectonIndexes();
        if (node_syms!=alphabet) {
            if (!need_completion) {
                sinkNode = addNode(false,false);
                need_completion=true;
            }
            QSet<unsigned int> rem(alphabet-node_syms);
            for (QSet<unsigned int>::const_iterator it=rem.constBegin();
                    it!=rem.constEnd(); ++it) {
                connect(nodeptr2id(node_container[i]),sinkNode,*it);
            }
        }
    }
}

QString automate::getAutomateType()
{
  bool start=false; // a start node
  bool multistart=false; // more than one start node
  bool final=false; // a final node
  bool multifinal=false; // more than one final node
  bool epsilonconnection=false;
  bool multiconnection=false;
  bool complete=true; // all nodes have outgoing connections exceeding all index symbols
  QVector<unsigned int> index_symbol_container;

  for ( int i=0; i < node_container.size(); ++i )
  {
    if ( node_container[i]->getstart() )
      if ( start )
        multistart=true;
      else
        start=true;
    if ( node_container[i]->getfinal() )
      if ( final )
        multifinal=true;
      else
        final=true;
    for ( int c=0; c < node_container[i]->connection_container.size(); ++c )
    {
      if (i==0)
      {
        index_symbol_container.push_back(node_container[i]->connection_container[c]->symbol_index);
      }
      else
      {
        if (!index_symbol_container.contains(node_container[i]->connection_container[c]->symbol_index))
          complete=false;
      }
      if ( node_container[i]->connection_container[c]->symbol_index == 0 )
        return "NO automate, it contains a not defined connection!";

      if ( node_container[i]->connection_container[c]->symbol_index == 1 )
        epsilonconnection=true;

      for ( int k=0; k < node_container[i]->connection_container.size(); ++k )
      {
        if ( c==k )
          continue;
        if ( node_container[i]->connection_container[c]->symbol_index ==
                node_container[i]->connection_container[k]->symbol_index )
          if ( node_container[i]->connection_container[c]->next_node ==
                  node_container[i]->connection_container[k]->next_node )
            multiconnection=true;
      }
    }
  }

  // A DFA is complete if for every state Q and every symbol s,
  // there's an explicit transition from Q on s.
  if ( !epsilonconnection && start && !multistart && ( final || multifinal ) && !multiconnection  && complete)
    return "completeDFA";
  // If one of those possible transformations from at least one state Q ist missing
  // we consider this incomplete.
  if ( !epsilonconnection && start && !multistart && ( final || multifinal ) && !multiconnection && !complete)
    return "incompleteDFA";

  if ( !epsilonconnection && ( start || multistart ) && ( final || multifinal ))
  {
    if (complete)
      return "completeNFA";
    else
      return "incompleteNFA";
  }

  if ( epsilonconnection && ( start || multistart ) && ( final || multifinal ) )
  {
    if (complete)
      return "complete_eNFA";
    else
      return "incomplete_eNFA";
  }
  return "No automate at all?";
}
/*
** Converts the none-Epsilon-free NFA into a NFA
*/
QString automate::convert2NFA()
{
  if ( this->getAutomateType() == "eNFA" )
  {
    // Specification
    // |a   node is a start node
    //  a|  node is a final node
    // 1. remove all local epsilon loops as a->epsilon->a
    // 2. all b's as in |a->epsilon->b get extended to |b
    // 3. all a's as in a->epsilon->b| get extended to |a
    // 4. for all a->epsilon->b and b->?->Z
    //    1. remove a->epsilon->b connection
    //    2. link all b->?->Z also from a as a->?->Z

    for ( int i=0; i < node_container.size(); ++i )
    {
      std::cerr << i << "-> Processing node: " << node_container[i] << std::endl;
      bool dirty=false;

      unsigned int f=node_container[i]->connection_container.size();
      unsigned int c=0;
      while ( c<f )
      {
        std::cerr << " " << c << " -> connection: " << node_container[i] << " -> (" <<
        node_container[i]->connection_container[c]->symbol_index << ") -> " <<
        node_container[i]->connection_container[c]->next_node << std::endl;
        std::cerr << " connection: " << c << std::endl;
        if ( node_container[i]->connection_container[c]->symbol_index == 1 )
        {
          if ( node_container[i]->connection_container[c]->next_node == node_container[i] )
          {
            std::cerr << "  removing epsilon loop connection" << std::endl;
            node_container[i]->delconnection ( node_container[i]->connection_container[c]->next_node, node_container[i]->connection_container[c]->symbol_index );
            //                             delete node_container[i]->connection_container[c];
            //                             node_container[i]->connection_container.remove(c);
            continue;
          }
          if ( node_container[i]->connection_container[c]->next_node->getfinal() )
            node_container[i]->setfinal ( true );

          if ( node_container[i]->getstart() )
            node_container[i]->connection_container[c]->next_node->setstart ( true );

          node* a=node_container[i];
          node* b=node_container[i]->connection_container[c]->next_node;
          for ( unsigned int z=0; z < ( unsigned int ) b->connection_container.size(); ++z )
          {
            unsigned int index=b->connection_container[z]->symbol_index;
            a->addconnection ( b->connection_container[z]->next_node,
                               index );
            if ( index == 1 )
            {
              dirty=true;
              std::cerr << " dirty bit set" << std::endl;
            }
          }

          // remove epsilon connection
          node_container[i]->delconnection ( node_container[i]->connection_container[c]->next_node, node_container[i]->connection_container[c]->symbol_index );
          //                         delete node_container[i]->connection_container[c];
          //                         node_container[i]->connection_container.remove(c);

        } // is epsilon connection
        std::cerr << " index " << node_container[i]->connection_container[c]->symbol_index << " != 0, skipping" << std::endl;
        if ( dirty )
        {
          dirty=false;
          f=node_container[i]->connection_container.size();
        }
        else
        {
          ++c;
        }
      } // all node connection_containers
    } // all nodes

    return this->getAutomateType();
  }

  return "Conversion from eAutomate to NFA can NOT be done, not an eAutomate!";
}

QString automate::convert2DFA()
{
  /*
  ** 1. accumulate all start nodes in one meta_node (first meta_node)
  **    afterwards put it into the meta_automate with getNodePtr(meta_node)
  ** 2. process every outgoing symbol -> connection from the first meta_node
  **    while creating other nodes, put them in the meta_automate's meta_node_container
  ** 3.
  */

  std::cerr << "convert2DFA called" << std::endl;

//   if ( this->getAutomateType() != "NFA" )
//   {
//     std::cerr << "Error, not an epsilon-free NFA" << std::endl;
//     return "Error, not an epsilon-free NFA";
//   }
//
//    build initial meta_node
//
  QList<node*> n;
  for ( int i=0; i < this->node_container.size(); ++i )
  {
    if ( node_container[i]->getstart() )
      n.push_back ( node_container[i] );
  }

  meta_automate* ma=new meta_automate ( n );

  if ( ma->convert() == true )
  {
    std::cerr << "convert() called with success" << std::endl;
//    return the new automate & clear the previous
//    this->~automate(); // wipe this automate callin it's destructor
//    delete this;
//    *this=&a;

  }
  else
  {
    std::cerr << "convert() error" << std::endl;
  }

  delete ma;

  return "Success, automate was converted into a DFA";
}

/*
**
*/
QString automate::convert2delUnreachableStates()
{

  return "";
}

/*
** Specification
** http://www-fs.informatik.uni-tuebingen.de/lehre/ss05/proseminar/Folien/MinDFA.pdf
**
*/

QString automate::convert2completeAutomate()
{

  return "foo";
}

QString automate::convert2miniDFA() {
  if ( this->getAutomateType() != "completeDFA" )
  {
    return "Error, not an DFA -> can't minimize then!";
  }

    QSet<unsigned int> alph;
    for ( int i=0; i < this->node_container.size(); ++i ) {
        alph += node_container[i]->getConnectonIndexes();
    }

    typedef OrderedPair<node*> node_p_pairs_t;
    // Set of state pairs known to be not equivalent
    QSet<QPair<node*,node*> > non_equi;
    // Initialize set with pairs of states where one state is final and the other
    // not.
    for (unsigned int i = 0; i < nodeCount; ++i) {
        for (unsigned int j = 0; j < i; ++j) {
            if (node_container[i]->getfinal() != node_container[j]->getfinal()) {
                node_p_pairs_t tmp(node_container[i], node_container[j]);
                non_equi.insert(tmp);
            }
        }
    }

  return "Not implemented";
}

void automate::dump()
{

ff  std::cerr << "============ DUMPING AUTOMATE ===========" << std::endl;
  for ( int i=0; i < node_container.size(); ++i )
  {
    std::cerr << node_container[i];
    if ( node_container[i]->getstart() )
      std::cerr << " s";
    else
      std::cerr << "  ";
    if ( node_container[i]->getfinal() )
      std::cerr << " f";
    std::cerr << std::endl;
    for ( int c=0; c < node_container[i]->connection_container.size(); ++c )
    {
      std::cerr << "      -> " << node_container[i]->connection_container[c]->next_node << ", "<< node_container[i]->connection_container[c]->symbol_index << std::endl;
    }
    for ( int c=0; c < node_container[i]->reverse_connection_container.size(); ++c )
    {
      std::cerr << "      <- " << node_container[i]->reverse_connection_container[c]->next_node << ", "<< node_container[i]->reverse_connection_container[c]->symbol_index << std::endl;
    }
  }
}
