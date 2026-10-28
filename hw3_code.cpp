#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>

using namespace std;

const int MAX_VERTICES = 20;

// Represents a weighted edge between two vertices.
class Edge{
    public:
        Edge(int first, int second, double edgeWeight);
        Edge(int first,int second);
        Edge();

        // Returns the first vertex.
        int getU ()const{
            return u;
        }

        // Returns the second vertex.
        int getV ()const{
            return v;
        }

        // Returns the weight of the edge.
        double getWeight()const{
            return weight;
        }
        static void setDefaultWeight(double newWeight);

        // Returns the current default weight.
        static double getDefaultWeight(){
            return defaultWeight;
        }
        friend bool operator ==(const Edge& e1, const Edge& e2);
        friend bool operator !=(const Edge& e1, const Edge& e2);
        friend bool operator <(const Edge& e1, const Edge& e2);
        friend ostream& operator<<(ostream& outs, const Edge& e);
        friend istream& operator>>(istream& ins, Edge& e);

    private:
        int u=0;
        int v=1;
        double weight=1.0;
        static double defaultWeight;
};

// Represents a graph using an adjacency matrix.
class Graph{
    public:
        Graph(int vertexCount);
        Graph();
        Graph(const Edge& e);
        Graph(int vertexCount, const vector<Edge>& edges);

        // Returns the number of vertices.
        int getNumVertices() const{
            return numVertices;
        }
        int getNumEdges() const;
        int degree(int vertex) const;
        double totalWeight() const;
        friend const Graph operator+(const Graph& g1, const Graph& g2);
        friend const Graph operator-(const Graph& g1, const Graph& g2);
        friend bool operator ==(const Graph& g1, const Graph& g2);
        friend bool operator !=(const Graph& g1, const Graph& g2);
        double operator ()(int first,int second) const;
        char& operator [](int vertex);
        const Graph operator-() const;
        Graph operator ++();
        Graph operator ++(int);

    private:
        int numVertices=0;
        double adj[MAX_VERTICES][MAX_VERTICES];
        char labels[MAX_VERTICES];
};

double Edge::defaultWeight = 1.0;

// Creates an edge with the given vertices and weight.
Edge :: Edge(int first, int second, double edgeWeight):u(first),v(second),weight(edgeWeight)
{
    if(first==second){
        cout << "Invalid vertex!" << endl;
        exit(1);
    }
    if (first<0 || second<0) {
        cout << "Invalid vertex!" << endl;
        exit(1);
    }    
    if(first>=MAX_VERTICES || second>=MAX_VERTICES ){
        cout << "Invalid vertex!" << endl;
        exit(1);
    } 
    if(edgeWeight<=0){
        cout << "Invalid weight!" << endl;
        exit(1);
    }
}

// Creates an edge using the default weight.
Edge :: Edge(int first,int second):Edge(first,second,defaultWeight){}

// Creates a default edge between vertices 0 and 1.
Edge :: Edge():Edge(0,1,defaultWeight){}

// Changes the default weight after checking its validity.
void Edge :: setDefaultWeight(double newWeight){
    if(newWeight<=0){
        cout<<"invalid default weight!"<<endl;
        exit(1);
    }else{
        defaultWeight=newWeight;
    }
}

// Checks if two edges are equal
bool operator ==(const Edge& e1, const Edge& e2){
    return (((e1.u==e2.u && e1.v==e2.v)||(e1.u==e2.v && e1.v==e2.u))
              &&(e1.weight==e2.weight));
}

// Checks if two edges are different.
bool operator !=(const Edge& e1, const Edge& e2){
    return !(((e1.u==e2.u && e1.v==e2.v)||(e1.u==e2.v && e1.v==e2.u))
              &&(e1.weight==e2.weight));
}

// Compares two edges by their weights.
bool operator <(const Edge& e1, const Edge& e2){
    return (e1.weight<e2.weight);
}

// Prints an edge in the required format.
ostream& operator<<(ostream& outs, const Edge& e){
    outs<<"("<<e.u<<", "<<e.v<<", "<<e.weight<<")";
    return outs;
}

// Reads an edge and checks its values using the constructor.
istream& operator>>(istream& ins, Edge& e){
    int readU;
    int readV;
    double readWeight;
    ins>>readU>>readV>>readWeight;
    e=Edge(readU, readV, readWeight);
    return ins;
}

// Creates a graph with the given number of vertices and no edges.
Graph :: Graph(int vertexCount):numVertices(vertexCount){
    if(vertexCount<0 || vertexCount>MAX_VERTICES){
        cout<<"Invalid number of vertices"<< endl;
        exit(1);
    }
    for(int i=0;i<MAX_VERTICES;i++){
        for(int j=0;j<MAX_VERTICES;j++){
            adj[i][j]=0;
        }
    }
    for(int k=0;k<MAX_VERTICES;k++){
        labels[k]='A'+k;
    }
}

// Creates an empty graph.
Graph :: Graph():Graph(0){}

// Creates a graph containing a single edge.
Graph :: Graph(const Edge& e): Graph((e.getU() > e.getV() ? e.getU() : e.getV()) + 1){
   
    adj[e.getU()][e.getV()]=e.getWeight();
    adj[e.getV()][e.getU()]=e.getWeight();
}

// Creates a graph using a list of edges.
Graph :: Graph(int vertexCount, const vector<Edge>& edges):Graph(vertexCount){
    
    for(int i=0;i<edges.size();i++){

        if(edges[i].getU()>=vertexCount || edges[i].getV()>=vertexCount){
            cout<<"Invalid edge vertex"<<endl;
            exit(1);
        }else{
            adj[edges[i].getU()][edges[i].getV()]=edges[i].getWeight();
            adj[edges[i].getV()][edges[i].getU()]=edges[i].getWeight();
        } 
    }
}

// Counts the edges in the graph without counting them twice.
int Graph :: getNumEdges() const{

    int count=0;

    for(int i=0;i<numVertices;i++){
        for(int j=0;j<numVertices;j++){
            if(adj[i][j]!=0){
                count++;
            }
        }
    }
    return count/2;
}

// Counts the edges connected to a vertex.
int Graph :: degree(int vertex) const{

    int count=0;

    if(vertex<0 || vertex>=numVertices){
        cout<<"invalid vertex"<<endl;
        exit(1);
    }
    for(int i=0;i<numVertices;i++){
        if(adj[vertex][i]!=0){
            count++;
        }
    }
    return count;
}

// Calculates the total weight of all edges.
double Graph :: totalWeight() const{

    double total=0;

    for(int i=0;i<numVertices;i++){
        for(int j=0;j<numVertices;j++){
            total += adj[i][j];
        } 
    }
    return total/2;
}

// Combines two graphs and keeps the first graph's weights for common edges.
const Graph operator+(const Graph& g1, const Graph& g2){
    int n,i,j;
    if(g1.numVertices>g2.numVertices){
        n=g1.numVertices;
    }else{
        n=g2.numVertices;
    }
    Graph result(n);

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(g1.adj[i][j]!=0){
                result.adj[i][j]=g1.adj[i][j];
            }
            else if(g2.adj[i][j]!=0){
                result.adj[i][j]=g2.adj[i][j];
            }
            
        }
    }
    for(i=0;i<n;i++){
        if(i < g1.numVertices){
            result.labels[i]=g1.labels[i];

        }else{
            result.labels[i]=g2.labels[i];
        }
    }
    return result;
}

// Removes the edges of the second graph from the first graph.
const Graph operator-(const Graph& g1, const Graph& g2){
    Graph result =g1;
    int i,j;
    for(i=0;i<g1.numVertices;i++){
        for(j=0;j<g1.numVertices;j++){
            if(g2.adj[i][j] != 0){
                result.adj[i][j]=0;
                result.adj[j][i]=0;
            }
        }
    }
    return result;
}

// Checks if two graphs have the same vertices and edges.
bool operator==(const Graph& g1, const Graph& g2){
    int i,j;

    if(g1.numVertices!=g2.numVertices){
        return false;
    }

    for(i=0;i<g1.numVertices;i++){
        for(j=0;j<g1.numVertices;j++){
            if(g1.adj[i][j] != g2.adj[i][j] ){
              return false ;
            }
        }
    }  
    return true;
}

// Checks if two graphs are different.
bool operator!=(const Graph& g1, const Graph& g2){
    return !(g1==g2);
}

// Returns the weight between two vertices.
double Graph :: operator()(int first, int second) const{
    if((first<0 || first>=numVertices) || (second<0 || second>=numVertices)){
        cout<<"invalid vertex"<<endl;
        exit(1);
    }else{
        return adj[first][second];
    }
}

// Returns a reference to a vertex label.
char& Graph :: operator[](int vertex){
    if(vertex<0 || vertex>=numVertices){
        cout<<"Invalid vertex"<<endl;
        exit(1);
    }else{
        return labels[vertex];
    }
}

// Creates a graph with edges where the original graph has none.
const Graph  Graph:: operator-() const{
    int i,j;
    Graph g(numVertices);
    for(i=0; i<numVertices; i++){
        g.labels[i]=labels[i];
    }
    for(i=0;i<numVertices;i++){
        for(j=0;j<numVertices;j++){
            if((adj[i][j]==0) && i!=j){
                g.adj[i][j]=1;
                g.adj[j][i]=1;

            }
        }
    }
    return g;
}

// Adds a vertex and returns the updated graph.
Graph Graph :: operator ++(){
    int i,j;
    if(numVertices==MAX_VERTICES){
        cout<<"invalid vertex"<<endl;
        exit(1);
    }
    numVertices++;

    Graph g(numVertices);

    for(i=0;i<numVertices;i++){
        for(j=0;j<numVertices;j++){
                g.adj[i][j]=adj[i][j];
        }
    }
    for(i=0;i<numVertices;i++){
        g.labels[i]=labels[i];
    }
    return g;
}

// Adds a vertex and returns the graph before the change.
Graph Graph :: operator ++(int){
    int newnum;
    int i,j;
    if(numVertices==MAX_VERTICES){
        cout<<"invalid vertex"<<endl;
        exit(1);
    }
    newnum=numVertices;
    numVertices++;

    Graph g(newnum);

    for(i=0;i<newnum;i++){
        for(j=0;j<newnum;j++){
                g.adj[i][j]=adj[i][j];
        }
    }
    for(i=0;i<newnum;i++){
        g.labels[i]=labels[i];
    }
    return g;

}

int main( )
{
    cout << "--- Part 1: Edge ---" << endl;
    Edge e1;                       // default constructor
    Edge e2(2, 3);                 // uses the static default weight
    Edge e3(3, 2, 1.0);
    cout << e1 << " " << e2 << " " << e3 << endl;
    cout << "e2 == e3: " << (e2 == e3) << endl;
    cout << "e1 != e2: " << (e1 != e2) << endl;
    Edge::setDefaultWeight(2.5);
    Edge e4(0, 4);
    cout << "default weight now " << Edge::getDefaultWeight()
         << ", e4 = " << e4 << endl;
    cout << "e4 < e2: " << (e4 < e2) << ", e2 < e4: " << (e2 < e4) << endl;
    Edge::setDefaultWeight(1.0);

    cout << "--- Part 2: Graph constructors ---" << endl;
    Graph empty;
    Graph g(4);
    Graph single(Edge(1, 3, 7));
    vector<Edge> list;
    list.push_back(Edge(0, 1, 2));
    list.push_back(Edge(1, 2));
    list.push_back(Edge(2, 0, 4));
    Graph tri(3, list);

    cout << "--- Part 3: + and - ---" << endl;
    g = g + Edge(0, 1, 2) + Edge(1, 2) + Edge(2, 0, 4);   // Graph + Edge
    cout << "g == tri: " << (g == tri) << endl;
    Graph h = Edge(3, 1, 9) + g;                          // Edge + Graph
    cout << "h != g: " << (h != g) << endl;
    Graph u = tri + single;                               // Graph + Graph
    Graph d = u - Edge(0, 2);                             // remove edge 0-2
    cout << "edges in u - Edge(0, 2): " << d.getNumEdges() << endl;

    cout << "--- Part 4: (), [], unary - ---" << endl;
    cout << "u(1,3) = " << u(1, 3) << ", u(3,1) = " << u(3, 1)
         << ", u(0,3) = " << u(0, 3) << endl;
    cout << "degree(1) = " << u.degree(1) << ", edges = " << u.getNumEdges()
         << ", total weight = " << u.totalWeight() << endl;
    u[0] = 'S';
    u[3] = 'T';
    cout << "labels: " << u[0] << u[1] << u[2] << u[3] << endl;

    cout << "--- Part 5: ++ ---" << endl;
    Graph before = tri++;
    cout << before.getNumVertices() << " " << tri.getNumVertices() << endl;
    Graph after = ++tri;
    cout << after.getNumVertices() << " " << tri.getNumVertices() << endl;

    cout << "--- Part 6: reading from a file ---" << endl;
    ifstream inStream;
    inStream.open("roads.txt");
    if (inStream.fail( ))
    {
        cout << "Cannot open roads.txt" << endl;
        exit(1);
    }
    int n, m;
    inStream >> n >> m;                // number of vertices and edges
    vector<Edge> roadList;
    for (int k = 0; k < m; k++)
    {
        Edge e;
        inStream >> e;                 // uses Edge's >>
        roadList.push_back(e);
    }
    inStream.close( );
    Graph roads(n, roadList);
    Graph cut = roads - Edge(2, 3) - Edge(3, 4);
    cout << "roads == cut + Edge(2,3,8) + Edge(3,4,3): "
         << (roads == cut + Edge(2, 3, 8) + Edge(3, 4, 3)) << endl;
    return 0;
}
