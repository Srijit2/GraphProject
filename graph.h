#ifndef GRAPH_H
#define GRAPH_H

#include <set>


using namespace std;

struct node {
    int val;
    struct node* next;
    double weight;
};

class GraphGenerator{
    public:
        int s; //num vertex
        int hS; //num hobbies
        GraphGenerator(string edge, string hobby);
        void AddEdge(int f, int s, double w);
        vector<node*> aList;
        vector<int> degree;
        vector<vector<double> > hobbyWeight;
        void insert(int f, int s, double w);
        bool find(int f, int s);
        void printE(); //print adjacency list
        void printW();//print adjacency list but for weights
        void printH();
};

class GraphOperator{
    public:
        GraphOperator(string edge, string hobby);
        int size; //num vertex
        int hSize; //num hobbies
        //GraphGenerator test;
        vector<node*> nList; //adjacency list
        vector<int> d; //list of degrees for nodes
        vector<vector<double> > hw; //size by hSize list. Shows hobby weights. Each row represents a vertex
        vector<vector<double> > dist; //size by size. Shows the distance of one vertex from another. Ex: dist[1][5] is how far vertex 5 is from vertex 1. dist[20][5] is how far vert 20 is from 5
        int FindHighestInterest(int h);
        vector<int> FindHighestDegree();
        double FindAverageDegree();
        double FindTrianglesRatio();
        bool find(int f, int num);
        double Dijkstra(int f); //fills row f in dist array
        double minW(int f);
        int minWV(int f, set<int>& visit); //used in dijkstra to decide which node to visit next iteration
        void setD(int f, int c);//sets nodes next to curr node for dijkstra
        void printVector(vector<double>& v){
            for(int i = 1; i < v.size();i++){
                cout << v[i] << ", "; 
            }
            cout << endl;
        }
        int FindClosestNode(int f, double t, int h);
        double findHD(int f, int s);
        void DFS(int f, set<int>& v);
        int FindConnectedNumber();
        pair<int,int> FindDistanceRatio();
        vector<vector<int> > comp; //groups vertices in the same components together.
        vector<double> findParam(int x); //finds diameter,radius, center for component x
        int compCount;
        int findCenter(int x, double rad); //Dont think this is ever used
        vector<vector<double> > FindConnectedParameters();
        vector<set<double> > compSet;
        void printE();
};































#endif
