#ifndef GRAPH_H
#define GRAPH_H
#include <stack>
#include <list>
#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>

using std::find;
using std::list;
using std::endl;
using std::cout;
using std::ostream;
using std::stack;
using std::vector;


struct adjList {
	adjList(int i) {
		index = i;
	}

	int index;
	vector<int> adjacent;
};

template <typename T>
class Graph;

template <typename T>
ostream& operator << (ostream & out, Graph<T> g);

template <typename T>
class Graph{
    private:
      //Declare any variables needed for your graph
		int size;
		vector<T> graph;
		vector<adjList> adjacentList;
		int numVert;
		int numEdges;
		/*std::list<edge>* edges;*/

    public:
      Graph();
	  Graph(const Graph& other);
	  Graph& operator=(const Graph& other);
	  ~Graph();
      Graph(int);
      void addVertex(T vertex);
      void addEdge(T source, T target);
      vector<T> getPath(T, T);
      int findVertexPos(T item);
      int getNumVertices();
      friend ostream& operator << <>(ostream & out, Graph<T> g);
};



/*********************************************
* Constructs an empty graph with a max number of verticies of 100
* 
*********************************************/
template<typename T>
Graph<T>::Graph(){
	numVert = 0;
	size = 100;
}


/*********************************************
* Constructs an empty graph with a given max number of verticies
* 
*********************************************/
template<typename T>
Graph<T>::Graph(int maxVerticies){
	numVert = 0;
	size = maxVerticies;
}

template<typename T>
Graph<T>::Graph(const Graph& other) {
	if (other.graph.empty()) return;


	numVert = 0;
	size = other.size;
	for (int i = 0; i < other.numVert; i++) {
		if (!other.graph.empty()) {
			auto temp = other.graph[i];
			graph.push_back(temp);
			adjacentList.push_back(adjList(i));
			numVert++;
		}
	}
	for (int i = 0; i < other.adjacentList.size(); i++) {			
		if (!other.adjacentList[i].adjacent.empty()) {
			for (int j = 0; j < other.adjacentList[i].adjacent.size(); j++) {
					int source = other.adjacentList[i].index;
					int target = other.adjacentList[i].adjacent[j];
					
					adjacentList[i].adjacent.push_back(target);
					numEdges++;
			}
		}
	}
}

template<typename T>
Graph<T>& Graph<T>::operator=(const Graph& other) {

	size = other.size;
	for (int i = 0; i < other.numVert; i++) {
		if (!other.graph.empty()) {
			auto temp = other.graph[i];
			graph.push_back(temp);
			adjacentList.push_back(adjList(i));
			numVert++;
		}
	}
	for (int i = 0; i < other.adjacentList.size(); i++) {
		if (!other.adjacentList[i].adjacent.empty()) {
			for (int j = 0; j < other.adjacentList[i].adjacent.size(); j++) {
				int source = other.adjacentList[i].index;
				int target = other.adjacentList[i].adjacent[j];

				adjacentList[i].adjacent.push_back(target);
				numEdges++;
			}
		}
	}
}

template<typename T>		//destructor
Graph<T>::~Graph() {
	if (!graph.empty()) {
		graph.clear();
		adjacentList.clear();
	}
}

/*********************************************
* Adds a Vertex to the GraphIf number of verticies is less than the 
* Max Possible number of verticies.  
*********************************************/
template <typename T>
void Graph<T>::addVertex(T vertex){
	if (numVert < size) {
				graph.push_back(vertex);
				adjacentList.push_back(adjList(numVert));
				numVert++;
				return;
	}
}

/*********************************************
* Returns the current number of vertices
* 
*********************************************/
template<typename T>
int Graph<T>::getNumVertices(){
  return numVert;
}

/*********************************************
* Returns the position in the verticies list where the given vertex is located, -1 if not found.
* 
*********************************************/
template <typename T>
int Graph<T>::findVertexPos(T item){
   
	for (int i = 0; i < numVert; i++) {
		if (graph[i] == item) {
			return i;
		}
	}
    return -1; //return negative one
}//End findVertexPos

/*********************************************
* Adds an edge going in the direction of source going to target
* 
*********************************************/
template <typename T>
void Graph<T>::addEdge(T source, T target){
	int sourceInd = findVertexPos(source);
	int targetInd = findVertexPos(target);

	adjacentList[sourceInd].adjacent.push_back(targetInd);
	numEdges++;
}


/*********************************************
* Returns a display of the graph in the format
* vertex: edge edge
Your display will look something like the following
    9: 8 5
    2: 7 0
    1: 4 0
    7: 6 2
    5: 6 8 9 4
    4: 5 1
    8: 6 5 9
    3: 6 0
    6: 7 8 5 3
    0: 1 2 3
*********************************************/
template <typename T>
ostream& operator << (ostream & out, Graph<T> g){
	if (g.numVert > 0) {
		for (int i = 0; i < g.graph.size(); i++) {
			out << g.graph[i] << ": ";
			for (int j = 0; j < g.adjacentList[i].adjacent.size(); j++) {
					int find = g.adjacentList[i].adjacent[j];
					out << g.graph[find] << " ";
			}
			out << std::endl;
		}
	}
    return out;
}




/*
  getPath will return the shortest path from source to dest.  
  If you would like a challenge, use a depth first search to traverse
  graph to find the solution.  With that sais, you are not limited to
  that altorihtm, you may use breadth first, shortest path first, or any
  other graph algorithm.
  You will return a vector with the solution.  The source will be in position 1
  the destination is in the last position of the solution, and each node in between 
  are the verticies it will travel to get to the destination.  There will not be any
  other verticies in the list.

  Given the test graph:
  
[0]-----------[2]
|  \            \
|   \            \
[1]  [3]----[6]---[7]   
|          /  \
|         /    \
|        /      \
|     [5]--------[8]
|    /   \       /
|   /     \     /
|  /       \   /
[4]         [9]

getPath(0, 5) should return 
0 -> 1 -> 4 -> 5   or   0 -> 3 -> 6 -> 5
    
  Hint: As you find the solution store it in a stack, pop all the items of the stack 
  into a vector so it will be in the correct order.

*/
template <typename T>
vector<T> Graph<T>::getPath(T source, T dest){
  vector<T> solution;
  vector<T> frontierQueue;
  bool* visited = new bool[numVert];
  stack<T> holder;
  int* dist = new int[numVert];
  int level = 1;		//keep track of how far away from the start you are
  int sourceInt = findVertexPos(source);
  int destInt = findVertexPos(dest);

  for (int i = 0; i < numVert; i++) {		//set the distance to 0 for the source and max for everything else
	  if (i == findVertexPos(source)) {
		  dist[i] = 0;
		  visited[i] = true;
	  }
	  else {
		  dist[i] = INT8_MAX;
		  visited[i] = false;
	  }
  }
  

  frontierQueue.push_back(source);		//store the first node in the queue
  int currentNode = findVertexPos(frontierQueue.back());	//keep track of which node you're searching

  while (!frontierQueue.empty()) {
	  currentNode = findVertexPos(frontierQueue.back());	//at the start of the loop change the current node
	  frontierQueue.pop_back();				//pop the node you're searching from the queue

	  for (int i = 0; i < adjacentList[findVertexPos(graph[currentNode])].adjacent.size(); i++) {	//loops as long as the current node has more nodes adjacent to it.
			  if (visited[adjacentList[currentNode].adjacent[i]] == false) {	//check if the node has already been visited
				  dist[adjacentList[findVertexPos(graph[currentNode])].adjacent[i]] = level;
				  frontierQueue.push_back(graph[adjacentList[currentNode].adjacent[i]]);	//add the node to the queue
				  visited[adjacentList[currentNode].adjacent[i]] = true;		//set that you've visited it
			  }
	  }
	  level++;	//once you're done with that level increment the level to show you're going deeper down the graph
	  
  }	//end of while loop

  currentNode = destInt;	//start from the destination and work your way back up the graph

  while (currentNode != sourceInt) {	//go until you get to the last node
	  holder.push(graph[currentNode]);	//push the node onto the stack for storage
	  for (int i = 0; i < adjacentList.size(); i++) {
		  if (std::find(adjacentList[i].adjacent.begin(), adjacentList[i].adjacent.end(), currentNode) != adjacentList[i].adjacent.end() && dist[i] < dist[currentNode])
		  {
			  //go back through the list and find where the current node is adjacent to it. also make sure the distance is less than the currentNode.
			  currentNode = i;
			  break;
		  }
	  }
  }

  holder.push(graph[currentNode]);

  while (!holder.empty()) {	//go until the holder is empty
	  solution.push_back(holder.top());	//push the top of the holder into solution
	  holder.pop();		//pop the top of holder and continue
  }

  delete[] visited;		//make sure to deallocate memory after using the new keyword
  delete[] dist;
  
  return solution;
}

#endif