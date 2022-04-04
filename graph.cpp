#include <iostream>
#include <vector>
#include <string>
#include "graph.h"
#include <climits>
#include <algorithm>

//#include <utility> 
#include<fstream>   
#include <float.h>
#include <set>
#include <cmath>
#include <stack>

using namespace std;

GraphGenerator::GraphGenerator(string edge, string hobby){
    ifstream f;
    ifstream h;
    string line;
    string v1;
    string v2;
    string w1;
    int temp = 0;
    int temp2 = 0;
    int count = 0;
    s = 0;
    h.open(hobby);
    if(h.is_open()){
        while(getline(h,line)){
            s++;
        }
    }
    h.close();
    hS = 0;
    int l1 = line.find(",");
    while(l1 != -1){
        line = line.substr(l1+1,line.size());
        l1 = line.find(",");
        hS++;
    }
    hS = hS + 1;
    aList.resize(s+1);
    degree.resize(s+1);
    hobbyWeight.resize(s+1);
    for(int i = 0; i < aList.size();i++){
        aList[i] = NULL;
        degree[i] = 0;
    }
    hobbyWeight[0].resize(hS + 1);
    f.open(edge);
    if(f.is_open()){
        while(getline(f,line)){
            temp = line.find(",");
            v1 = line.substr(0,temp);
            temp2 = line.find(",",temp+1);
            v2 = line.substr(temp+1,temp2-temp-1);
            w1 = line.substr(temp2+1,line.size());
            AddEdge(stoi(v1),stoi(v2),stod(w1) );
            count++;
        }
        f.close();
    }

    h.open(hobby);
    int countR = 1;
    if(h.is_open()){
        while(getline(h,line)){
            hobbyWeight[countR].resize(hS+1);
            temp = line.find(",");
            v1 = line.substr(0,temp);
            hobbyWeight[countR][1] = stod(v1);
            hobbyWeight[0][1] = 0;
            for(int i = 2; i < hS+1;i++){
                temp2 = line.find(",",temp+1);
                v1 = line.substr(temp+1,temp2-temp-1);
                hobbyWeight[countR][i] = stod(v1);
                temp = temp2;
            }
            countR++;
        }
    }

    h.close();
}

void GraphGenerator::AddEdge(int f, int s, double w){
    insert(f,s,w);
    insert(s,f,w);
}

void GraphGenerator::insert(int f, int s, double w){
    if(!find(f,s)){
        node* in = new node();
        in->val = s;
        in->weight = w;
        node* temp = aList[f];
        aList[f] = in;
        in->next = temp;
        degree[f]++;
    }
}


bool GraphGenerator::find(int f, int s){
    node* temp = aList[f];
    while(temp != NULL){
        if(temp->val == s){
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void GraphGenerator::printE(){
    for(int i = 1; i< s+1; i++){
        if(aList[i] == NULL){
            cout << 0 << " " << endl;
        }else{
              node* temp = aList[i];
              cout << i << "     ";
             while(temp != NULL){
                cout << temp->val << " -> ";
                temp = temp->next;
             }
             cout << endl;
         }
    }
}

void GraphGenerator::printW(){
    for(int i = 1; i< s+1; i++){
        if(aList[i] == NULL){
            cout << 0 << " " << endl;
        }else{
              node* temp = aList[i];
             while(temp != NULL){
                cout << temp->weight << " -> ";
                temp = temp->next;
             }
             cout << endl;
         }
    }
}

void GraphGenerator::printH(){
    for(int i = 1; i< s+1; i++){
        for(int j = 1; j < hS+1; j++){
            cout << hobbyWeight[i][j] << ", "; 
        }
        cout << endl;
    }
}


int GraphOperator::FindHighestInterest(int h){
    int max = 0;
    int maxI = 0;
    for(int i = 1; i < hw.size();i++){
        if(hw[i][h] > max){
            max = hw[i][h];
            maxI = i;
        }
    }

    return maxI;
}

vector<int> GraphOperator::FindHighestDegree(){
    int max = 0;
    vector<int> ans;
    for(int i = 1; i < d.size();i++){
        if(d[i] == max){
            ans.push_back(i);
        }
        if(d[i] > max){
            max = d[i];
            ans.clear();
            ans.push_back(i);
            
        }
    }

    return ans;
}

double GraphOperator::FindAverageDegree(){
    double sum = 0;
    for(int i = 1; i < d.size();i++){
        sum = sum + d[i];
    }

    sum = sum/size;

    return sum;
}

bool GraphOperator::find(int f, int num){
    node* temp = nList[f];
    while(temp != NULL){
        if(temp->val == num){
            return true;
        }
        temp = temp->next;
    }
    return false;
}

double GraphOperator::FindTrianglesRatio(){
    double tri = 0;
    int miss = 0;
    for(int i = 1; i < nList.size(); i++){
        node* temp = nList[i];
        node* curr;
        while(temp != NULL){
            curr = temp->next;
            while(curr != NULL){
                if(find(temp->val, curr->val)){
                    tri++;
                }else{
                    miss++;
                }
                curr = curr->next;
            }
            temp = temp->next;
        }
    }
    // cout << miss << endl;
    // cout << tri << endl;
    return (miss/tri) * 3;
    
}

double GraphOperator::minW(int f){
    double min = DBL_MAX;
    node* temp = nList[f];
    while(temp != NULL){
        if(temp->weight < min){
            min = temp->weight;
        }
        temp = temp->next;
    }
    return min;
}

int GraphOperator::minWV(int f, set<int>& visit){
    double min = INT_MAX;
    int minI = 0;
    for(int i = 1; i < dist[f].size();i++){
        if( (dist[f][i] < min) && (visit.find(i) == visit.end())){
            min = dist[f][i];
            minI = i;
        }
    }

    return minI;
}

void GraphOperator::setD(int f, int c){
    node* temp = nList[c];
    while(temp != NULL){
        if(((temp->weight + dist[f][c]) < dist[f][temp->val])){
            dist[f][temp->val] = (temp->weight + dist[f][c]);
        }
        temp = temp->next;
    }
}

double GraphOperator::Dijkstra(int f){
    set<int> visited;
    for(int i = 1; i < dist[0].size(); i++){
        if(i!=f){
            dist[f][i] = DBL_MAX;
        }else{
            dist[f][i] = 0;
        }
    }
    int curr = f;
    int count = 0;
    visited.insert(f);
    while(visited.size() < size && count < size){
        setD(f,curr);
        curr = minWV(f,visited);
        visited.insert(curr);
        count++;
        if(curr <= 0){
            break;
        }
    }
    return 0;
}

int GraphOperator::FindClosestNode(int f, double t, int h){
    vector< vector<double> > temp;
    vector<double> v;
    for(int i = 1; i < size; i++){
        v.push_back(dist[f][i]);
        v.push_back(i);
        temp.push_back(v);
        v.clear();
    }
    sort(temp.begin(), temp.end());
    for(int i = 0; i < temp.size();i++){
        if(hw[temp[i][1]][h] >= t){
            return temp[i][1];
        }
    }
    cout << endl;

    return f;
}

void GraphOperator::DFS(int f, set<int>& v){
    stack<int> curr;
    if(v.find(f) != v.end()){
        return;
    }else{
        v.insert(f);
        if(compSet[compCount].find(f) == compSet[compCount].end()){
            comp[compCount].push_back(f);
        }
        compSet[compCount].insert(f);
    }
    curr.push(f);
    bool remove = true;
    int count = 0;
    while(!curr.empty() && count < 500){
        count++;
        node* temp = nList[curr.top()];
        remove = true;
        while(temp != NULL){
            if(v.find(temp->val) == v.end()){
                curr.push(temp->val);
                v.insert(temp->val);
                if(compSet[compCount].find(temp->val) == compSet[compCount].end()){
                    comp[compCount].push_back(temp->val);
                }
                compSet[compCount].insert(temp->val);
                remove = false;
                break;
            }
            temp = temp->next;
        }
        if(remove){
            curr.pop();
        }
    }
}

int GraphOperator::FindConnectedNumber(){
    set<int> visited;
    int count = 0;
    compCount = 0;
    for(int i = 1; i < size+1; i++){
        if(visited.find(i) == visited.end()){
             // move this to dfs also maybe add a compCount variable
            DFS(i,visited);
            compCount++;
            count++;
        }
    }
    return count;
}

double GraphOperator::findHD(int f, int s){
    double sum = 0;
    double curr = 0;
    for(int i = 1; i < hSize+1;i++){
        curr = hw[f][i] - hw[s][i];
        curr = curr * curr;
        sum = sum + curr;
    }
    sum = sqrt(sum);
    return sum;
}

pair<int,int> GraphOperator::FindDistanceRatio(){
    vector<vector<double> > hd;
    hd.resize(size+1);
    for(int i = 1; i < hd.size();i++){
        hd[i].resize(size+1);
        for(int j = 1; j < hd.size(); j++){
            hd[i][j] = findHD(i,j);
        }
    }

    double min = DBL_MAX;
    int minI = 0;
    int minJ = 0;
    for(int i = 1; i < hd.size();i++){
        for(int j = 1; j < hd.size(); j++){
            if(dist[i][j] != DBL_MAX){
                if(min > (hd[i][j]/dist[i][j]) ){
                    min = hd[i][j]/dist[i][j];
                    minI = i;
                    minJ = j;
                }
            }
        }
    }

    pair<int,int> ans = make_pair(minI,minJ);

    return ans;



}

vector<double> GraphOperator::findParam(int x){
    bool add = false;
    vector<double> p;
    if(x >= comp.size()){
        return p;
    }
    double max = 0;
    double min = DBL_MAX;
    vector<int> center;
    for(int i = 0; i < comp[x].size();i++){
         vector<double> temp = dist[comp[x][i]];
        sort(temp.begin(), temp.end());
        for(int j= 1; j < temp.size();j++){
            add = false;
            if(temp[j] == DBL_MAX && temp[j-1] != DBL_MAX){
                if(min == temp[j-1]){
                    center.push_back(comp[x][i]);
                }else if(abs(min-temp[j-1]) < 0.001){
                    center.push_back(comp[x][i]);
                    add = true;
                }
                if(min > temp[j-1] && add == false){
                    min = temp[j-1];
                    center.clear();
                    center.push_back(comp[x][i]);
                }
                if(max < temp[j-1]){
                    max = temp[j-1];
                }
            }
        }
    }
    p.push_back(max);
    p.push_back(min);
    sort(center.begin(),center.end());
    for(int i = 0; i < center.size();i++){
        p.push_back(center[i]);
    }

    return p;
}

vector<vector<double> > GraphOperator::FindConnectedParameters(){
    vector<vector<double> >  ans;
    vector<double> temp;
    for(int i =0; i < comp.size();i++){
        temp = findParam(i);
        ans.push_back(temp);
    }

    return ans;
}

GraphOperator::GraphOperator(string edge, string hobby){
    GraphGenerator g = GraphGenerator(edge,hobby);
    size = g.s;
    hSize = g.hS;
    nList = g.aList;
    d = g.degree;
    hw = g.hobbyWeight;
    dist.resize(size+1);
    for(int i = 0; i < dist.size();i++){
        dist[i].resize(size+1);
    }



    for(int i = 1; i < size+1; i++){
        Dijkstra(i);
    }



    comp.resize(size);
    compSet.resize(size);
    int a = FindConnectedNumber();
    comp.resize(a);
    compSet.resize(a);
}



int main(int argc, char* argv[]){


    GraphOperator g = GraphOperator(argv[1], argv[2]);
    cout << "The average degree:" << endl;
    double t = g.FindAverageDegree();
    int t1 = t * 100;
    t = t1/100.00;
    cout << t  << endl;
    cout << "The vertex with the highest degree:" << endl;
    vector<int> high = g.FindHighestDegree();
    for(int i = 0; i < high.size();i++){
        if(i == high.size()-1){
           cout << high[i]; 
        }else{
            cout << high[i] << ", ";
        }
    }
    cout << endl;
    cout << "Ther number of connected components:" << endl;
    cout << g.FindConnectedNumber() << endl;
    cout << "The diameter, radius, and center (s) if each component:" << endl;
    vector<vector<double> > p = g.FindConnectedParameters();
    sort(p.begin(),p.end());
    for(int i = 0; i < p.size();i++){
        for(int j = 0; j < p[i].size();j++){
            if(j == p[i].size() -1){
                cout << p[i][j];
            }else{
               cout << p[i][j] << ", ";
            }
        }
        cout << endl;
    }
    cout << "The ratio between the number of open and closed triangles:" << endl;
    t = g.FindTrianglesRatio();
    t1 = t * 10000;
    t = t1/10000.00;
    cout << t << endl;
    cout << "The closest node:" << endl;
    cout << g.FindClosestNode(39,0.5,7) << endl;
    cout << "A closest with the highest interest:" << endl;
    cout << g.FindHighestInterest(7) << endl;
    cout << "The pair of nodes x and y:" << endl;
    pair<int,int> p1 = g.FindDistanceRatio();
    cout << p1.first << ", " << p1.second << endl;



//Code to get the outputs for the documentation

//     for(int i =0;i<10;i++){
//         cout << "run #" << count << " :" << endl;
//  auto t_start = std::chrono::high_resolution_clock::now();
//     GraphOperator g = GraphOperator("testcase3.txt", "testcasehobbies3.txt");
// auto t_end = std::chrono::high_resolution_clock::now();
//  cout << "time diff construct " << std::chrono::duration<double, std::milli>(t_end-t_start).count() << endl;
//     // GraphOperator g = GraphOperator(argv[1], argv[2]);
    
//      t_start = std::chrono::high_resolution_clock::now();

//      g.FindAverageDegree();
//      t_end = std::chrono::high_resolution_clock::now();
//     cout << "time diff avg deg: " << std::chrono::duration<double, std::milli>(t_end-t_start).count() << endl;

//     t_start = std::chrono::high_resolution_clock::now();
//      g.FindHighestDegree();
//     t_end = std::chrono::high_resolution_clock::now();
//     cout << "time diff high deg: " << std::chrono::duration<double, std::milli>(t_end-t_start).count() << endl;

//     t_start = std::chrono::high_resolution_clock::now();
//      g.FindConnectedNumber();
//     t_end = std::chrono::high_resolution_clock::now();
//     cout << "time diff con numb: " << std::chrono::duration<double, std::milli>(t_end-t_start).count() << endl;

//     t_start = std::chrono::high_resolution_clock::now();
//      g.FindConnectedParameters();
//     t_end = std::chrono::high_resolution_clock::now();
//     cout << "time diff con param: " << std::chrono::duration<double, std::milli>(t_end-t_start).count() << endl;

//     t_start = std::chrono::high_resolution_clock::now();
//     g.FindTrianglesRatio();
//     t_end = std::chrono::high_resolution_clock::now();
//     cout << "time diff tri: " << std::chrono::duration<double, std::milli>(t_end-t_start).count() << endl;

//     t_start = std::chrono::high_resolution_clock::now();
//     g.FindClosestNode(2,2,2);
//     t_end = std::chrono::high_resolution_clock::now();
//     cout << "time diff closeNode: " << std::chrono::duration<double, std::milli>(t_end-t_start).count() << endl;
    
//     t_start = std::chrono::high_resolution_clock::now();
//     g.FindHighestInterest(7);
//     t_end = std::chrono::high_resolution_clock::now();
//     cout << "time diff High Int: " << std::chrono::duration<double, std::milli>(t_end-t_start).count() << endl;

//      t_start = std::chrono::high_resolution_clock::now();
//     g.FindDistanceRatio() ;
//     t_end = std::chrono::high_resolution_clock::now();
//     cout << "time diff dis ratio: " << std::chrono::duration<double, std::milli>(t_end-t_start).count() << endl;
//     count++;
//     }


    return 0;
}

