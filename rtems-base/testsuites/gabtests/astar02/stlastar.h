/*
A* Algorithm Implementation using STL is
Copyright (C)2001-2005 Justin Heyes-Jones

Permission is given by the author to freely redistribute and 
include this code in any program as long as this credit is 
given where due.
 
  COVERED CODE IS PROVIDED UNDER THIS LICENSE ON AN "AS IS" BASIS, 
  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, 
  INCLUDING, WITHOUT LIMITATION, WARRANTIES THAT THE COVERED CODE 
  IS FREE OF DEFECTS, MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE
  OR NON-INFRINGING. THE ENTIRE RISK AS TO THE QUALITY AND 
  PERFORMANCE OF THE COVERED CODE IS WITH YOU. SHOULD ANY COVERED 
  CODE PROVE DEFECTIVE IN ANY RESPECT, YOU (NOT THE INITIAL 
  DEVELOPER OR ANY OTHER CONTRIBUTOR) ASSUME THE COST OF ANY 
  NECESSARY SERVICING, REPAIR OR CORRECTION. THIS DISCLAIMER OF 
  WARRANTY CONSTITUTES AN ESSENTIAL PART OF THIS LICENSE. NO USE 
  OF ANY COVERED CODE IS AUTHORIZED HEREUNDER EXCEPT UNDER
  THIS DISCLAIMER.
 
  Use at your own risk!
*/

/* GAB: Rewrite to encapsulate priority queue functions */
//#define GAB_HWPQ  1

// used for text debugging
//#include <iostream>
#include <stdio.h>
//#include <conio.h>
#include <assert.h>

// stl includes
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

// fast fixed size memory allocator, used for fast node memory management
#include "fsa.h"

// Fixed size memory allocator can be disabled to compare performance
// Uses std new and delete instead if you turn it off
#define USE_FSA_MEMORY 1

// disable warning that debugging information has lines that are truncated
// occurs in stl headers
//#pragma warning( disable : 4786 )

// The AStar search class. UserState is the users state space type
template <class UserState> class AStarSearch
{

public: // data

	enum
	{
		SEARCH_STATE_NOT_INITIALISED,
		SEARCH_STATE_SEARCHING,
		SEARCH_STATE_SUCCEEDED,
		SEARCH_STATE_FAILED,
		SEARCH_STATE_OUT_OF_MEMORY,
		SEARCH_STATE_INVALID
	};


	// A node represents a possible state in the search
	// The user provided state type is included inside this type

	public:

	class Node
	{
		public:

			Node *parent; // used during the search to record the parent of successor nodes
			Node *child; // used after the search for the application to view the search in reverse
			
			float g; // cost of this node + it's predecessors
			float h; // heuristic estimate of distance to goal
			float f; // sum of cumulative cost of predecessors and self and heuristic

			Node() :
				parent( 0 ),
				child( 0 ),
				g( 0.0f ),
				h( 0.0f ),
				f( 0.0f )
			{			
			}

			UserState m_UserState;
	};

#if GAB_HWPQ
#else
	// For sorting the heap the STL needs compare function that lets us compare
	// the f value of two nodes

	class HeapCompare_f 
	{
		public:

			bool operator() ( const Node *x, const Node *y ) const
			{
				return x->f > y->f;
			}
	};
#endif

public: // methods


	// constructor just initialises private data
	AStarSearch( int MaxNodes = 1000 ) :
		m_State( SEARCH_STATE_NOT_INITIALISED ),
		m_CurrentSolutionNode( NULL ),
#if USE_FSA_MEMORY
		m_FixedSizeAllocator( MaxNodes ),
#endif
		m_AllocateNodeCount(0),
		m_CancelRequest( false )
	{
	}

	// call at any time to cancel the search and free up all the memory
	void CancelSearch()
	{
		m_CancelRequest = true;
	}

	// Set Start and goal states
	void SetStartAndGoalStates( UserState &Start, UserState &Goal )
	{
		m_CancelRequest = false;

		m_Start = AllocateNode();
		m_Goal = AllocateNode();

		assert((m_Start != NULL && m_Goal != NULL));
		
		m_Start->m_UserState = Start;
		m_Goal->m_UserState = Goal;

		m_State = SEARCH_STATE_SEARCHING;
		
		// Initialise the AStar specific parts of the Start Node
		// The user only needs fill out the state information

		m_Start->g = 0; 
		m_Start->h = m_Start->m_UserState.GoalDistanceEstimate( m_Goal->m_UserState );
		m_Start->f = m_Start->g + m_Start->h;
		m_Start->parent = 0;

		// Push the start node on the Open list

    /* GAB: enqueue ( m_Start ) */
#if GAB_HWPQ
    HWDS_ENQUEUE( m_OpenList, m_Start->f, m_Start );
#else
		m_OpenList.push_back( m_Start ); // heap now unsorted

		// Sort back element into heap
		push_heap( m_OpenList.begin(), m_OpenList.end(), HeapCompare_f() );
#endif

		// Initialise counter for search steps
		m_Steps = 0;
	}

	// Advances search one step 
	unsigned int SearchStep()
	{
		// Firstly break if the user has not initialised the search
		assert( (m_State > SEARCH_STATE_NOT_INITIALISED) &&
				(m_State < SEARCH_STATE_INVALID) );

		// Next I want it to be safe to do a searchstep once the search has succeeded...
		if( (m_State == SEARCH_STATE_SUCCEEDED) ||
			(m_State == SEARCH_STATE_FAILED) 
		  )
		{
			return m_State; 
		}

		// Failure is defined as emptying the open list as there is nothing left to 
		// search...
		// New: Allow user abort
    /* GAB: if ( !first( open ) || m_CancelRequest ) */
#if GAB_HWPQ
    Node *n = NULL;
    HWDS_FIRST( m_OpenList, n );
    if( !n || m_CancelRequest ) {
#else
		if( m_OpenList.empty() || m_CancelRequest ) {
#endif
			FreeAllNodes();
			m_State = SEARCH_STATE_FAILED;
			return m_State;
		}
		
		// Incremement step count
		m_Steps ++;

    /* GAB: n = first( open ) */
#if GAB_HWPQ
  /* Not a shared queue so don't do anything already have n */
#else
		// Pop the best node (the one with the lowest f) 
		Node *n = m_OpenList.front(); // get pointer to the node
#endif

    /* GAB: extract( n, open ) */
#if GAB_HWPQ
    HWDS_EXTRACT ( m_OpenList, n );
#else
		pop_heap( m_OpenList.begin(), m_OpenList.end(), HeapCompare_f() );
		m_OpenList.pop_back();
#endif

		// Check for the goal, once we pop that we're done
		if( n->m_UserState.IsGoal( m_Goal->m_UserState ) )
		{
			// The user is going to use the Goal Node passed in 
			// so copy the parent pointer of n 
			m_Goal->parent = n->parent;

			// A special case is that the goal was passed in as the start state
			// so handle that here
			if( false == n->m_UserState.IsSameState( m_Start->m_UserState ) )
			{
				FreeNode( n );

				// set the child pointers in each node (except Goal which has no child)
				Node *nodeChild = m_Goal;
				Node *nodeParent = m_Goal->parent;

				do 
				{
					nodeParent->child = nodeChild;

					nodeChild = nodeParent;
					nodeParent = nodeParent->parent;
				
				} 
				while( nodeChild != m_Start ); // Start is always the first node by definition

			}

			// delete nodes that aren't needed for the solution
			FreeUnusedNodes();

			m_State = SEARCH_STATE_SUCCEEDED;

			return m_State;
		}
		else // not goal
		{

			// We now need to generate the successors of this node
			// The user helps us to do this, and we keep the new nodes in
			// m_Successors ...

			m_Successors.clear(); // empty vector of successor nodes to n

			// User provides this functions and uses AddSuccessor to add each successor of
			// node 'n' to m_Successors
			bool ret = n->m_UserState.GetSuccessors( this, n->parent ? &n->parent->m_UserState : NULL ); 

			if( !ret )
			{

			    typename vector< Node * >::iterator successor;

				// free the nodes that may previously have been added 
				for( successor = m_Successors.begin(); successor != m_Successors.end(); successor ++ )
				{
					FreeNode( (*successor) );
				}

				m_Successors.clear(); // empty vector of successor nodes to n

				// free up everything else we allocated
				FreeAllNodes();

				m_State = SEARCH_STATE_OUT_OF_MEMORY;
				return m_State;
			}
			
			// Now handle each successor to the current node ...
			for( typename vector< Node * >::iterator successor = m_Successors.begin(); successor != m_Successors.end(); successor ++ )
			{

				// 	The g value for this successor ...
				float newg = n->g + n->m_UserState.GetCost( (*successor)->m_UserState );

				// Now we need to find whether the node is on the open or closed lists
				// If it is but the node that is already on them is better (lower g)
				// then we can forget about this successor

				// First linear search of open list to find node

        /* GAB: openlist_result = find( (*successor)->m_UserState, open ) */
#if GAB_HWPQ
        Node **openlist_result = NULL;
        Node *olist_r = NULL;
        /* TODO: can't compare on embedded fields in hw */
        HWDS_FIND( m_openList, (*successor)->m_UserState, olist_r );
        openlist_result = &olist_r;
#else
				typename vector< Node * >::iterator openlist_result;

				for( openlist_result = m_OpenList.begin(); openlist_result != m_OpenList.end(); openlist_result ++ )
				{
					if( (*openlist_result)->m_UserState.IsSameState( (*successor)->m_UserState ) )
					{
						break;					
					}
				}
#endif

        /* GAB: if (openlist_result) */
#if GAB_HWPQ
        if( *openlist_result ) {
#else
				if( openlist_result != m_OpenList.end() ) {
#endif
					// we found this state on open

					if( (*openlist_result)->g <= newg )
					{
						FreeNode( (*successor) );

						// the one on Open is cheaper than this one
						continue;
					}
				}
        
        /* GAB: closedlist_result = find( (*successor)->m_UserState, closed ) */
#if GAB_HWPQ
        Node **closedlist_result = NULL;
        Node *clist_r = NULL;
        /* TODO: can't compare on embedded fields in hw */
        HWDS_FIND( m_closedList, (*successor)->m_UserState, clist_r );
        closedlist_result = &clist_r;
#else
				typename vector< Node * >::iterator closedlist_result;

				for( closedlist_result = m_ClosedList.begin(); closedlist_result != m_ClosedList.end(); closedlist_result ++ )
				{
					if( (*closedlist_result)->m_UserState.IsSameState( (*successor)->m_UserState ) )
					{
						break;					
					}
				}
#endif
        /* GAB: if (closedlist_result) */
#if GAB_HWPQ
        if( *closedlist_result ) {
#else
				if( closedlist_result != m_ClosedList.end() ) {
#endif
					// we found this state on closed

					if( (*closedlist_result)->g <= newg )
					{
						// the one on Closed is cheaper than this one
						FreeNode( (*successor) );

						continue;
					}
				}

				// This node is the best node so far with this particular state
				// so lets keep it and set up its AStar specific data ...

				(*successor)->parent = n;
				(*successor)->g = newg;
				(*successor)->h = (*successor)->m_UserState.GoalDistanceEstimate( m_Goal->m_UserState );
				(*successor)->f = (*successor)->g + (*successor)->h;

				// Remove successor from closed if it was on it
        /* GAB: if (closedlist_result) */
#if GAB_HWPQ
        if( *closedlist_result ) {
          HWDS_EXTRACT( m_closedList, (*closedlist_result) );
					FreeNode(  (*closedlist_result) );
        }
#else
				if( closedlist_result != m_ClosedList.end() ) {
					// remove it from Closed
					FreeNode(  (*closedlist_result) );
					m_ClosedList.erase( closedlist_result );
				}
#endif
				// Update old version of this node
        /* GAB: if (openlist_result) */
#if GAB_HWPQ
        if( *openlist_result ) {
          HWDS_EXTRACT( m_openList, (*openlist_result) );
          FreeNode( (*openlist_result) );
        }
#else
				if( openlist_result != m_OpenList.end() )
				{	   
					FreeNode( (*openlist_result) ); 
			   		m_OpenList.erase( openlist_result );

					// re-make the heap 
					// make_heap rather than sort_heap is an essential bug fix
					// thanks to Mike Ryynanen for pointing this out and then explaining
					// it in detail. sort_heap called on an invalid heap does not work
					make_heap( m_OpenList.begin(), m_OpenList.end(), HeapCompare_f() );
				}
#endif

        /* GAB: insert( *successor, open ) */
#if GAB_HWPQ
        HWDS_INSERT( m_OpenList, (*successor)->f, (*successor) );
#else
				// heap now unsorted
				m_OpenList.push_back( (*successor) );

				// sort back element into heap
				push_heap( m_OpenList.begin(), m_OpenList.end(), HeapCompare_f() );
#endif
			}

			// push n onto Closed, as we have expanded it now
#if GAB_HWPQ      
      /* GAB: insert(n,closed) */
      HWDS_INSERT( m_ClosedList, n->f, n );
#else
			m_ClosedList.push_back( n );
#endif
		} // end else (not goal so expand)

 		return m_State; // Succeeded bool is false at this point. 

	}

	// User calls this to add a successor to a list of successors
	// when expanding the search frontier
	bool AddSuccessor( UserState &State )
	{
		Node *node = AllocateNode();

		if( node )
		{
			node->m_UserState = State;

			m_Successors.push_back( node );

			return true;
		}

		return false;
	}

	// Free the solution nodes
	// This is done to clean up all used Node memory when you are done with the
	// search
	void FreeSolutionNodes()
	{
		Node *n = m_Start;

		if( m_Start->child )
		{
			do
			{
				Node *del = n;
				n = n->child;
				FreeNode( del );

				del = NULL;

			} while( n != m_Goal );

			FreeNode( n ); // Delete the goal

		}
		else
		{
			// if the start node is the solution we need to just delete the start and goal
			// nodes
			FreeNode( m_Start );
			FreeNode( m_Goal );
		}

	}

	// Functions for traversing the solution

	// Get start node
	UserState *GetSolutionStart()
	{
		m_CurrentSolutionNode = m_Start;
		if( m_Start )
		{
			return &m_Start->m_UserState;
		}
		else
		{
			return NULL;
		}
	}
	
	// Get next node
	UserState *GetSolutionNext()
	{
		if( m_CurrentSolutionNode )
		{
			if( m_CurrentSolutionNode->child )
			{

				Node *child = m_CurrentSolutionNode->child;

				m_CurrentSolutionNode = m_CurrentSolutionNode->child;

				return &child->m_UserState;
			}
		}

		return NULL;
	}
	
	// Get end node
	UserState *GetSolutionEnd()
	{
		m_CurrentSolutionNode = m_Goal;
		if( m_Goal )
		{
			return &m_Goal->m_UserState;
		}
		else
		{
			return NULL;
		}
	}
	
	// Step solution iterator backwards
	UserState *GetSolutionPrev()
	{
		if( m_CurrentSolutionNode )
		{
			if( m_CurrentSolutionNode->parent )
			{

				Node *parent = m_CurrentSolutionNode->parent;

				m_CurrentSolutionNode = m_CurrentSolutionNode->parent;

				return &parent->m_UserState;
			}
		}

		return NULL;
	}

	// For educational use and debugging it is useful to be able to view
	// the open and closed list at each step, here are two functions to allow that.

	UserState *GetOpenListStart()
	{
		float f,g,h;
		return GetOpenListStart( f,g,h );
	}

	UserState *GetOpenListStart( float &f, float &g, float &h )
	{
    /* GAB: iterDbgOpen = first( open ) */
#if GAB_HWPQ
    HWDS_FIRST( m_OpenList, iterDbgOpen_ptr );
    iterDbgOpen = &iterDbgOpen_ptr;
#else
		iterDbgOpen = m_OpenList.begin();
#endif

#if GAB_HWPQ
    if( *iterDbgOpen ) {
#else
		if( iterDbgOpen != m_OpenList.end() )	{
#endif
			f = (*iterDbgOpen)->f;
			g = (*iterDbgOpen)->g;
			h = (*iterDbgOpen)->h;
			return &(*iterDbgOpen)->m_UserState;
		}

		return NULL;
	}

	UserState *GetOpenListNext()
	{
		float f,g,h;
		return GetOpenListNext( f,g,h );
	}

	UserState *GetOpenListNext( float &f, float &g, float &h )
	{
    /* GAB: iterDbgOpen = next( iterDbgOpen, open ) */
#if GAB_HWPQ
    HWDS_NEXT( m_OpenList, iterDbgOpen_ptr, iterDbgOpen_ptr );
#else
		iterDbgOpen++;
#endif
    /* GAB: if iterDbgOpen */
#if GAB_HWPQ
    if( *iterDbgOpen ) {
#else
		if( iterDbgOpen != m_OpenList.end() ) {
#endif
			f = (*iterDbgOpen)->f;
			g = (*iterDbgOpen)->g;
			h = (*iterDbgOpen)->h;
			return &(*iterDbgOpen)->m_UserState;
		}

		return NULL;
	}

	UserState *GetClosedListStart()
	{
		float f,g,h;
		return GetClosedListStart( f,g,h );
	}

	UserState *GetClosedListStart( float &f, float &g, float &h )
	{
    /* GAB: iterDbgClosed = first( closed ) */
#if GAB_HWPQ
    HWDS_FIRST( m_ClosedList, iterDbgClosed_ptr );
    iterDbgClosed = &iterDbgClosed_ptr;
#else
		iterDbgClosed = m_ClosedList.begin();
#endif
    /* GAB: if iterDbgClosed */
#if GAB_HWPQ
    if( *iterDbgClosed ) {
#else
		if( iterDbgClosed != m_ClosedList.end() ) {
#endif
			f = (*iterDbgClosed)->f;
			g = (*iterDbgClosed)->g;
			h = (*iterDbgClosed)->h;

			return &(*iterDbgClosed)->m_UserState;
		}

		return NULL;
	}

	UserState *GetClosedListNext()
	{
		float f,g,h;
		return GetClosedListNext( f,g,h );
	}

	UserState *GetClosedListNext( float &f, float &g, float &h )
	{
    /* GAB: iterDbgClosed = next ( iterDbgClosed, closed ) */
#if GAB_HWPQ
    HWDS_NEXT( m_ClosedList, iterDbgClosed_ptr, iterDbgClosed_ptr );
#else
		iterDbgClosed++;
#endif
#if GAB_HWPQ
    if( iterDbgClosed ) {
#else
		if( iterDbgClosed != m_ClosedList.end() ) {
#endif
			f = (*iterDbgClosed)->f;
			g = (*iterDbgClosed)->g;
			h = (*iterDbgClosed)->h;

			return &(*iterDbgClosed)->m_UserState;
		}

		return NULL;
	}

	// Get the number of steps

	int GetStepCount() { return m_Steps; }

	void EnsureMemoryFreed()
	{
#if USE_FSA_MEMORY
		assert(m_AllocateNodeCount == 0);
#endif

	}

private: // methods

	// This is called when a search fails or is cancelled to free all used
	// memory 
	void FreeAllNodes()
	{
		// iterate open list and delete all nodes
    /* GAB: while ( first ( open ) ) free(extract(first(open),open)); */
#if GAB_HWPQ
    Node *n = NULL;
    HWDS_FIRST( m_OpenList, n );
    while( n ) {
      HWDS_EXTRACT( m_OpenList, n );
      FreeNode( n );
      HWDS_FIRST( m_OpenList, n );
    }
#else
		typename vector< Node * >::iterator iterOpen = m_OpenList.begin();

		while( iterOpen != m_OpenList.end() )
		{
			Node *n = (*iterOpen);
			FreeNode( n );

			iterOpen ++;
		}

		m_OpenList.clear();
#endif

		// iterate closed list and delete unused nodes
    /* GAB: while ( first (closed ) ) free(extract(first(closed),closed)) */
#if GAB_HWPQ
    Node *n = NULL;
    HWDS_FIRST( m_ClosedList, n );
    while( n ) {
      HWDS_EXTRACT( m_ClosedList, n );
      FreeNode( n );
      HWDS_FIRST( m_ClosedList,  n );
    }
#else
		typename vector< Node * >::iterator iterClosed;

		for( iterClosed = m_ClosedList.begin(); iterClosed != m_ClosedList.end(); iterClosed ++ )
		{
			Node *n = (*iterClosed);
			FreeNode( n );
		}

		m_ClosedList.clear();
#endif
		// delete the goal

		FreeNode(m_Goal);
	}


	// This call is made by the search class when the search ends. A lot of nodes may be
	// created that are still present when the search ends. They will be deleted by this 
	// routine once the search ends
	void FreeUnusedNodes()
	{
    /* GAB: while ( first ( open ) ) if ( unused ) free(extract(first(open),open)); */
#if GAB_HWPQ
    Node *n = NULL;
    HWDS_FIRST( m_OpenList, n );
    while ( n ) {
      Node *m = NULL;
      HWDS_NEXT( m_OpenList, n, m );
      if ( !n->child ) {
        HWDS_EXTRACT( m_OpenList, n );
        FreeNode( n );
      }
      n = m;
    }
#else
		// iterate open list and delete unused nodes
		typename vector< Node * >::iterator iterOpen = m_OpenList.begin();

		while( iterOpen != m_OpenList.end() )
		{
			Node *n = (*iterOpen);

			if( !n->child )
			{
				FreeNode( n );

				n = NULL;
			}

			iterOpen ++;
		}

		m_OpenList.clear();
#endif

    /* GAB: while ( first (closed ) ) if () free(extract(first(closed),closed)) */
#if GAB_HWPQ
    Node *n = NULL;
    HWDS_FIRST( m_ClosedList, n );
    while ( n ) {
      Node *m = NULL;
      HWDS_NEXT( m_ClosedList, n, m );
      if ( !n->child ) {
        HWDS_EXTRACT( m_ClosedList, n );
        FreeNode( n );
      }
      n = m;
    }
#else
    // iterate closed list and delete unused nodes
		typename vector< Node * >::iterator iterClosed;

		for( iterClosed = m_ClosedList.begin(); iterClosed != m_ClosedList.end(); iterClosed ++ )
		{
			Node *n = (*iterClosed);

			if( !n->child )
			{
				FreeNode( n );
				n = NULL;

			}
		}

		m_ClosedList.clear();
#endif
	}

	// Node memory management
	Node *AllocateNode()
	{

#if !USE_FSA_MEMORY
		Node *p = new Node;
		return p;
#else
		Node *address = m_FixedSizeAllocator.alloc();

		if( !address )
		{
			return NULL;
		}
		m_AllocateNodeCount ++;
		Node *p = new (address) Node;
		return p;
#endif
	}

	void FreeNode( Node *node )
	{

		m_AllocateNodeCount --;

#if !USE_FSA_MEMORY
		delete node;
#else
		m_FixedSizeAllocator.free( node );
#endif
	}

private: // data


#if GAB_HWPQ
  /* tag for a hq pq */
  int m_OpenList;

  /* tag for a hw pq */
  int m_ClosedList;
#else
// Heap (simple vector but used as a heap, cf. Steve Rabin's game gems article)
	vector< Node *> m_OpenList;

	// Closed list is a vector.
	vector< Node * > m_ClosedList; 
#endif

// Successors is a vector filled out by the user each type successors to a node
	// are generated
	vector< Node * > m_Successors;

	// State
	unsigned int m_State;

	// Counts steps
	int m_Steps;

	// Start and goal state pointers
	Node *m_Start;
	Node *m_Goal;

	Node *m_CurrentSolutionNode;

#if USE_FSA_MEMORY
	// Memory
 	FixedSizeAllocator<Node> m_FixedSizeAllocator;
#endif
	
#if GAB_HWPQ
  Node **iterDbgOpen;
  Node *iterDbgOpen_ptr;
  Node **iterDbgClosed;
  Node *iterDbgClosed ptr;
#else
	//Debug : need to keep these two iterators around
	// for the user Dbg functions
	typename vector< Node * >::iterator iterDbgOpen;
	typename vector< Node * >::iterator iterDbgClosed;
#endif

	// debugging : count memory allocation and free's
	int m_AllocateNodeCount;
	
	bool m_CancelRequest;

};

