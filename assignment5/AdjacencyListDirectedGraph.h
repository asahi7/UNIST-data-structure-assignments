//
// AdjacencyListDirectedGraph.h - Version 1.0
//
// Please write your name, your student ID, and your email here.
// Moreover, please describe the implementation of your functions here.
// You will have to submit this file.
//
// Aibek Smagulov 20142028 smagulovaybek@gmail.com

#ifndef ASSIGNMENT5_ADJACENCYLISTDIRECTEDGRAPH_H
#define ASSIGNMENT5_ADJACENCYLISTDIRECTEDGRAPH_H

#include <iostream>
#include <list>
#include <stdexcept>

using namespace std;

template<typename V, typename E>
class AdjacencyListDirectedGraph {

  // ---------------------------------------------------------------------------------
  // You *cannot* add any additional public or private member functions in this class.
  // You *cannot* add any additional public or private member variables in this class.
  // ---------------------------------------------------------------------------------

public:

  // Define public data types of Vertex and Edge and the associated iterators.

  class Vertex;
  class Edge;

  typedef list<Vertex> VertexList;
  typedef list<Edge> EdgeList;
  typedef typename VertexList::iterator VertexItor;
  typedef typename EdgeList::iterator EdgeItor;
  typedef typename VertexList::const_iterator VertexConstItor;
  typedef typename EdgeList::const_iterator EdgeConstItor;

private:

  // Define private data types of VertexObject and EdgeObject and the associated iterators.
  // The type of IncidenceEdgesList and its iterator are defined as well.

  struct VertexObject;
  struct EdgeObject;

  typedef list<VertexObject> VertexObjectList;
  typedef list<EdgeObject> EdgeObjectList;
  typedef list<EdgeList> IncidenceEdgesList;

  typedef typename VertexObjectList::iterator VertexObjectItor;
  typedef typename EdgeObjectList::iterator EdgeObjectItor;
  typedef typename IncidenceEdgesList::iterator IncidenceEdgesItor;


  /*
   * VertexObject stores data of a vertex.
   */
  struct VertexObject {
    V elt;                             // the element stored at this vertex
    VertexObjectItor pos;              // position in vertex_collection
    IncidenceEdgesItor inc_edges_pos;  // position in inc_edges_collection

    VertexObject(V _elt) : elt(_elt) {}  // pos and inc_edges_pos are initially "NULL".
  };

  /*
   * VertexObject stores data of an edge.
   */
  struct EdgeObject {
    E elt;                          // the element stored at this edge
    Vertex origin_vertex;           // the vertex at the origin
    Vertex dest_vertex;             // the vertex at the destination
    EdgeObjectItor pos;             // position in edge_collection
    EdgeItor origin_inc_edges_pos;  // position in an edge list in inc_edges_collection
    EdgeItor dest_inc_edges_pos;    // position in an edge list in inc_edges_collection

    EdgeObject(const Vertex& v, const Vertex& w, E _elt) : origin_vertex(v), dest_vertex(w), elt(_elt) {} // pos origin_inc_edges_pos, and dest_inc_edges_pos are initially "NULL".
  };

  // ---------------------------------------------------------------------------------
  // This class should contain the following three member variables only:
  // vertex_collection, edge_collection, and inc_edges_collection
  // You are not allowed to define any other member variables (public or private).
  // ---------------------------------------------------------------------------------

  VertexObjectList vertex_collection;
  EdgeObjectList edge_collection;
  IncidenceEdgesList inc_edges_collection;

public:

  /*
   * Vertex is a position class of a vertex in AdjacencyListDirectedGraph.
   * Internally, a vertex is a pointer to an entry in vertex_collection.
   */
  class Vertex {

    VertexObject *v_obj;

  public:

    /*
     * The constructor of Vertex. This subsumes the default constructor.
     *
     * v - a pointer to a VertexObject
     */
    Vertex(VertexObject* v = NULL) : v_obj(v) {}


    /*
     * Return the element stored at this vertex.
     */
    V& operator*() const {
        return v_obj->elt; 
    }

    /*
     * Return a list of edges incident to this vertex.
     */
    EdgeList incidentEdges() const{
        return *(v_obj->inc_edges_pos); 
    }

    /*
     * Check whether a vertex is adjacent to this vertex.
     * This means whether there is an edge that has this vertex
     * and the given vertex as the end points.
     *
     * v - the given vertex
     */
    bool isAdjacentTo(const Vertex& v) const {
        //EdgeList& el1 = incidentEdges();
        EdgeList& el1 = *(v_obj->inc_edges_pos);
        //EdgeList& el2 = v.incidentEdges();
        EdgeList& el2 = *(v.v_obj->inc_edges_pos);
        EdgeList& el = (el1.size() < el2.size() ? el1 : el2);
        for(EdgeItor it = el.begin(); it != el.end(); it++){
            Edge e = (*it);
            if((e.origin() == (*this) && e.dest() == v) || (e.origin() == v && e.dest() == (*this))){
                 return true;
            }
        }
        return false;
    }

    /*
     * Check whether there is a directed edge connecting this vertex to the given vertex.
     *
     * v - the given vertex
     */
    bool isOutgoingTo(const Vertex& v) const {
        //EdgeList& el = this->incidentEdges();
        EdgeList& el = *(v_obj->inc_edges_pos); 
        for(EdgeItor it = el.begin(); it != el.end(); it++){
            Edge e = (*it);
            if(e.origin() == (*this) && e.dest() == v) return true;
        }
        return false;
    }

    /*
     * Return a directed edge connecting this vertex to the given vertex.
     * If the directed edge does not exist, throw an exception.
     *
     * v - the given vertex
     * Return the directed edge connecting this vertex to the given vertex.
     */
    Edge outgoingEdge(const Vertex& v) const {
        //EdgeList& el = this->incidentEdges();
        EdgeList& el = *(v_obj->inc_edges_pos);
        for(EdgeItor it = el.begin(); it != el.end(); it++){
            Edge e = (*it);
            if(e.origin() == (*this) && e.dest() == v) return e;
        }
        throw runtime_error("Such edge doesn't exist!");
    }

    /*
     * Return the set of all directed edges connecting this vertex to any vertex.
     */
    EdgeList outgoingEdges() const {
        //EdgeList& el = this->incidentEdges();
        EdgeList& el = *(v_obj->inc_edges_pos);
        EdgeList ans;
        for(EdgeItor it = el.begin(); it != el.end(); it++){
            Edge e = (*it);
            if(e.origin() == (*this)) ans.push_back(e);
        }
        return ans;
    }

    /*
     * Check whether this vertex is the same as the given vertex
     *
     * v - the given vertex
     * Return true if this vertex is the same as the given vertex
     */
    bool operator==(const Vertex& v) const {
        return v_obj == v.v_obj;
    }

    /*
     * Declare friend to AdjacencyListDirectedGraph so that
     * AdjacencyListDirectedGraph can access to the private
     * member variables of this class.
     */
    friend class AdjacencyListDirectedGraph<V,E>;
  };

  /*
   * Edge is a position class of an edge in AdjacencyListDirectedGraph.
   * Internally, an edge is a pointer to an entry in edge_collection.
   */
  class Edge {

    EdgeObject *e_obj;

  public:

    /*
     * The constructor of Edge. This subsumes the default constructor.
     *
     * v - a pointer to a EdgeObject
     */
    Edge(EdgeObject* e = NULL) : e_obj(e) {}

    /*
     * Return the element stored at this edge.
     */
    E& operator*() const {
        return e_obj->elt;
    }

    /*
     * Return the vertices of this directed edge.
     * The first element of the vertex list is the vertex of the origin.
     * The second element of the vertex list is the vertex of the destination.
     */
    VertexList endVertices() const {
       VertexList vl;
       vl.push_back(e_obj->origin_vertex);
       vl.push_back(e_obj->dest_vertex);
       return vl;
    }

    /*
     * Return the vertex of this edge that is different from the given vertex.
     * If the given vertex is origin, return destination.
     * If the given vertex is destination, return origin.
     * If the given vertex is neither origin nor destination, throw an exception.
     *
     * v - the given vertex
     * Return the other vertex of this edge
     */
    Vertex opposite(const Vertex& v) const {
        if(v == e_obj->origin_vertex) return e_obj->dest_vertex;
        else if(v == e_obj->dest_vertex) return e_obj->origin_vertex;
        else throw runtime_error("The vertex is not incident on the edge!");
    }

    /*
     * Check whether a given edge is adjacent to this edge.
     * This means that whether the given edge and this edge
     * shared a vertex.
     *
     * edge - the given edge
     * Return true if the given edge is adajcent to this edge.
     */
    bool isAdjacentTo(const Edge& edge) const {
        return (edge.isIncidentOn(e_obj->origin_vertex) || edge.isIncidentOn(e_obj->dest_vertex));
    }

    /*
     * Check whether a vertex is incident on this edge.
     * This means that whether the vertex is a vertex of this edge.
     *
     * v - the given vertex
     * Return true if the given vertex is incident to this edge.
     */
    bool isIncidentOn(const Vertex& v) const {
        if(e_obj->origin_vertex == v || e_obj->dest_vertex == v) return true;
        return false;
    }

    /*
     * Return the vertex at the origin of this edge.
     */
    Vertex origin() const {
        return e_obj->origin_vertex; 
    }

    /*
     * Return the vertex at the destination of this edge.
     */
    Vertex dest() const {
        return e_obj->dest_vertex; 
    }

    /*
     * Return true if this is a directed edge.
     * In this class, it should always return true.
     */
    bool isDirected() const {
        return true; 
    }

    /*
     * Check whether this edge is the same as the given edge.
     *
     * edge - the given edge
     * Return true if this edge is the same as the given edge.
     */
    bool operator==(const Edge& edge) const {
        return edge.e_obj == e_obj;
    }

    /*
     * Declare friend to AdjacencyListDirectedGraph so that
     * AdjacencyListDirectedGraph can access to the private
     * member variables of this class.
     */
    friend class AdjacencyListDirectedGraph<V,E>;
  };


public:

  /*
   * Return the list of vertices in this graph.
   */
  VertexList vertices() {
        VertexList vl;
        for(VertexObjectItor it = vertex_collection.begin(); it != vertex_collection.end(); it++){
            VertexObject& vo = (*it);
            Vertex v_new;
            v_new.v_obj = &vo;
            vl.push_back(v_new);
        }
        return vl;
  }

  /*
   * Return the list of edges in this graph.
   */
  EdgeList edges() {
        EdgeList el;
        for(EdgeObjectItor it = edge_collection.begin(); it != edge_collection.end(); it++){
            EdgeObject& eo = (*it);
            Edge e_new;
            e_new.e_obj = &eo;
            el.push_back(e_new);
        }
        return el;
  }

  /*
   * Add a new vertex to this graph.
   *
   * x - the element to be stored in the new vertex.
   * Return the newly created vertex.
   */
  Vertex insertVertex(const V& x) {
        VertexObject vo(x); // ???
        vertex_collection.push_back(vo);
        VertexObjectItor it = vertex_collection.end();
        it--;
        VertexObject& vo1 = (*it);
        vo1.pos = it; // !!!
        inc_edges_collection.push_back(EdgeList());
        IncidenceEdgesItor iet = inc_edges_collection.end();
        iet--;
        vo1.inc_edges_pos = iet; // !!!
        Vertex v_new;
        v_new.v_obj = &vo1;
        return v_new;
  }

  /*
   * Add a new edge to this graph. Throw an exception
   * if an edge has already existed between v and w.
   *
   * v - the vertex at the origin
   * w - the vertex at the destination
   * x - the element to be stored in the new edge.
   * Return the newly created edge.
   */
  Edge insertDirectedEdge(const Vertex& v, const Vertex& w, E x) {
        if(v.isOutgoingTo(w)) throw runtime_error("The edge already exists!");

        EdgeObject eo(v, w, x);
        edge_collection.push_back(eo);
        EdgeObjectItor it = edge_collection.end();
        it--;
        EdgeObject& eo1 = (*it);
        eo1.pos = it; // !!!
        
        VertexObject& vo = *(v.v_obj);
        VertexObject& wo = *(w.v_obj);
        
        IncidenceEdgesItor ietV = vo.inc_edges_pos;
        IncidenceEdgesItor ietW = wo.inc_edges_pos;

        EdgeList& eOfV = (*ietV);
        EdgeList& eOfW = (*ietW);

        /* Creating new Edge pointin to the new Edge object*/
        Edge e_new;
        e_new.e_obj = &eo1;
        /*End of creating*/

        eOfV.push_back(e_new);
        eOfW.push_back(e_new);

        eo1.origin_inc_edges_pos = --(eOfV.end());
        eo1.dest_inc_edges_pos = --(eOfW.end());
        return e_new;
  }

  /*
   * Remove a vertex from this graph. All edges that contain
   * v as one of their vertices are also removed.
   *
   * v - a vertex
   */
  void eraseVertex(const Vertex& v) {
        VertexObject& vo = *(v.v_obj);
        EdgeList& el = *(vo.inc_edges_pos);

        for(EdgeItor it = el.begin(); it != el.end();){
            Edge& e = *it;
            cout << "origin: " << *(e.origin()) << " dest: " << *(e.dest()) << " " << *e << endl;
            it++;
            eraseEdge(e);
        }
        vertex_collection.erase(vo.pos);
        //delete v;  
  }

  /*
   * Remove an edge from this graph.
   *
   * e - an edge
   */
  void eraseEdge(const Edge& e) {
        EdgeObject& eo = *(e.e_obj);
        (*(eo.origin_vertex.v_obj->inc_edges_pos)).erase(eo.origin_inc_edges_pos); 
        (*(eo.dest_vertex.v_obj->inc_edges_pos)).erase(eo.dest_inc_edges_pos); 
        edge_collection.erase(eo.pos);
        //delete e;
  }

};


#endif //ASSIGNMENT5_ADJACENCYLISTDIRECTEDGRAPH_H
