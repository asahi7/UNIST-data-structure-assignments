//
// assignment5.h - Version 1.0
//
// Please write your name, your student ID, and your email here.
// Moreover, please describe the implementation of your functions here.
// You will have to submit this file.
// Aibek Smagulov 20142028 smagulovaybek@gmail.com

#include <iostream>
#include <string>
#include <stdexcept>
#include <queue>
#include <list>
#include <vector>
#include <map>
#include <limits>
#include <set>
#include "AdjacencyListDirectedGraph.h"
#include "FlightMap.h"

double FlightMap::calculateDistanceBetweenVertices(const FlightGraph::Vertex& vertex_origin, const FlightGraph::Vertex& vertex_dest){
    FlightGraph::Edge e = vertex_origin.outgoingEdge(vertex_dest);
    return *e;
}

double FlightMap::calcRouteDistance(const list<string> route) {
    double res = 0.0;
    FlightGraph::Vertex v;
    if(findAirport(v, route.front()) == false){
        throw runtime_error("The airport does not exist!");
    }
    list<string>::const_iterator prev = route.begin();
    list<string>::const_iterator cur = route.begin();
    cur++;
    for(; cur != route.end(); cur++){
        FlightGraph::Vertex to;
        if(findAirport(to, *cur) == false){
            throw runtime_error("The airport does not exist!");
        }      
        if(isConnectionExist(*prev, *cur) == false){
            throw runtime_error("Connection between airports does not exist!");
        }
        res += calculateDistanceBetweenVertices(v, to);
        v = to;
        prev++;
    }
    return res;
}

list<string> FlightMap::findRoute(const string &airport1, const string &airport2) {
    return findShortestRoute(airport1, airport2);
}

bool FlightMap::isInVisited(const FlightGraph::Vertex &v, FlightGraph::VertexList &visitedVertices){
    for(FlightGraph::VertexItor it = visitedVertices.begin(); it != visitedVertices.end(); it++){
        if((*it) == v) return true;
    }
    return false;
}


void FlightMap::findReachableAirports(const FlightGraph::Vertex &v, FlightGraph::VertexList &visitedVertices){
    visitedVertices.push_back(v);
    FlightGraph::EdgeList el = v.outgoingEdges();
    for(FlightGraph::EdgeItor it = el.begin(); it != el.end(); it++){
       if(isInVisited((*it).dest(), visitedVertices) == false){
            findReachableAirports((*it).dest(), visitedVertices);
       } 
    }
}

list<string> FlightMap::findReachableAirports(const string &airport) {
    FlightGraph::Vertex v;
    findAirport(v, airport); // Exception ???
    FlightGraph::VertexList visitedVertices;
    findReachableAirports(v, visitedVertices);
    list<string> names;
    for(FlightGraph::VertexItor it = visitedVertices.begin(); it != visitedVertices.end(); it++){
        if(((*it) == v) == false) names.push_back(**it);
    }
    return names;
}

list<string> FlightMap::findShortestRoute(const string &airport1, const string &airport2) {
    set<pair<double, string> > st;
    st.insert(make_pair(0, airport1));
    map<string, double> d;
    map<string, string> par;
    const double inf = 100000000;
    FlightGraph::VertexList vl = flight_graph.vertices(); 
    for(FlightGraph::VertexItor it = vl.begin(); it != vl.end(); it++){
        d[**it] = inf;
    }
    d[airport1] = 0;
    par[airport1] = "-1";
    bool found = 0;
    while(st.empty() == false){
        pair<double, string> pa = *(st.begin());
        st.erase(st.begin());
        string v_name = pa.second;
        if(v_name == airport2) {
            found = 1;
            break;
        }
        double tot_dist = pa.first;
        //cout << v_name << " " << tot_dist << endl; 
        FlightGraph::Vertex v;
        findAirport(v, v_name);
        FlightGraph::EdgeList el = v.outgoingEdges();
        for(FlightGraph::EdgeItor it = el.begin(); it != el.end(); it++){
            FlightGraph::Vertex to = (*it).dest();
            double new_dist = **it;
            if(tot_dist + new_dist < d[*to]){
                if(d[*to] != inf) st.erase(st.find(make_pair(d[*to], *to)));
                d[*to] = tot_dist + new_dist;
                par[*to] = v_name;
                st.insert(make_pair(d[*to], *to));
            }
        }
    }
    if(! found) return list<string>();
    string cur = airport2;
    list<string> ans;
    while(cur != "-1"){
        ans.push_back(cur);
        cur = par[cur];
    }
    ans.reverse();
    return ans;
}

void FlightMap::printAllShortestRoutes(const string &airport) {
    FlightGraph::Vertex v;
    if(findAirport(v, airport) == false){
        throw runtime_error("Airport does not exist!");
    }
    list<string> reachables = findReachableAirports(airport);
    for(list<string>::iterator it = reachables.begin(); it != reachables.end(); it++){
       string airport2 = *it;
       list<string> route = findShortestRoute(airport, airport2);
       printRoute(route);
       cout << " (Distance = " << calcRouteDistance(route) << ")" << endl;
    }
}
