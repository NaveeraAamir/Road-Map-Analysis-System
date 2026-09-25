#include <iostream>
#include<vector>
  #include <map>
#include <queue>
#include<fstream>
 #include <string>
 #include <cstdlib>

using namespace std;


class RoadMap {
  public:
    map<string, vector<string>> adjList;


  public:
    
    void addRoad(string city1, string city2) {
        adjList[city1].push_back(city2);
          adjList[city2].push_back(city1); 
    }

   
  bool isConnected() {
      if(adjList.empty()) return true;

      map<string, bool> visited;
        queue<string> q;
        
      string startNode = adjList.begin()->first;
        q.push(startNode);
      visited[startNode] = true;

      int visitedCount = 0;
        
       while(!q.empty()) {
            string curr = q.front();
             q.pop();
            visitedCount++;

            for (string neighbor : adjList[curr]) {
                if(!visited[neighbor]) {
                    visited[neighbor] = true;
                     q.push(neighbor);
                }
            }
        }
        
      bool ans = visitedCount == adjList.size();
      return ans;
  }

    
    bool hasCycle() {
        map<string, bool> visited;
        map<string, string> parentMap; 
        
          for (auto const& pair : adjList) {
            if (!visited[pair.first]) {
                
                queue<string> q;
                q.push(pair.first);
                visited[pair.first] = true;
                parentMap[pair.first] = "";

                while (!q.empty()) {
                    string curr = q.front();
                    q.pop();

                    for (string neighbor : adjList[curr]) {
                        if (!visited[neighbor]) {
                            visited[neighbor] = true;
                            parentMap[neighbor] = curr;
                            q.push(neighbor);
                        } 
                        else if (neighbor != parentMap[curr]) {
                            
                            cout << "\nCYCLE DETECTEDD!!\n   Loop nodes: ";
                            
                            string myParent = parentMap[curr];
                            string neighborParent = parentMap[neighbor];

                            if (myParent == neighborParent) {
                               
                                cout << curr << " <-> " << neighbor << " <-> " 
                                     << myParent << " <-> " << curr << "\n";
                            } else {
                                cout << curr << " <-> " << neighbor << " <-> " 
                                     << neighborParent << " <-> ... <-> " << curr << "\n";
                            }
                            
                            return true;
                        }
                    }
                }
              }
        }
        return false;
    }


    void exportToGraphviz(string filename) {
        ofstream file(filename);
        if (!file) {
            cout << "Error: Could not create Graphviz file.\n";
            return;
        }

        file << "graph RoadNetwork {\n";
        file << "    node [style=filled, fillcolor=lightblue, fontname=\"Arial\"];\n";
        file << "    edge [color=black, penwidth=6];\n\n";

        for (auto const& pair : adjList) {
            for (string neighbor : pair.second) {
                if (pair.first < neighbor) {
                    file << "    \"" << pair.first << "\" -- \"" << neighbor << "\";\n";
                }
            }
        }

        file << "}\n";
        file.close();
       cout << "\n   Generating PNG image...\n";
        
        int result = system("dot -Tpng roadmap.dot -o roadmap_visual.png");
        
        if(result == 0) {
             cout << "   SUCCESS! 'roadmap_visual.png' has been created in your project folder!\n";
        } else {
             cout << "   Oohoo! PNG generation failed.\n";
        }
    }

    void shortestPath(string start, string end) {
        if(adjList.find(start) == adjList.end() || adjList.find(end) == adjList.end()) {
             cout << "Error: cities not in map.\n";
            return;
        }

      map<string, bool> visited;
       map<string, string> parent; 
        queue<string> q;

        q.push(start);
       visited[start] = true;

        bool found = false;

      while (!q.empty()) {
          string curr = q.front();
            q.pop();

            if (curr == end) {
              found = true;
               break;
            }

          for (string neighbor : adjList[curr]) {
              if (!visited[neighbor]) {
                    visited[neighbor] = true;
                  parent[neighbor] = curr;
                   q.push(neighbor);
                }
            }
        }

        if (!found) {
            cout << "No path found between " << start << " and " << end << ".\n";
            return;
        }

        
        vector<string> path;
      for (string at = end; at != ""; at = parent[at]) {
            path.push_back(at);
        }
      cout << "\nShORTEST ROUTE FOUND!!\n   ";
        for (int i = path.size() - 1; i >= 0; i--) {
            cout << "(" << path[i] << ")" << (i == 0 ? "" : " ===> ");
        }
        cout << "\n   Total Stops: " << path.size() - 1 << "\n\n";
    }

    
    void displayMap() {
        if (adjList.empty()) {
            cout << "Map is emptyyy .\n";
            return;
        }
        cout << "\n\t -----ROAD MAP DIAGRAM----\n\n";
        
        
        for (auto const& city : adjList) {
            cout << city.first << "\n"; 
            for(int i=0; i < city.second.size(); i++) {
                    cout << "    |-------> ( " << city.second[i] << " )\n";
            }
            cout << "\n";
        }
        cout << "\t-----------------\n";
    }


    void saveToFile(string filename) {
        ofstream file(filename);
        if (!file) {
            cout << "Error saving file.\n";
            return;
        }
        
        for (auto const& pair : adjList) {
            for (string neighbor : pair.second) {
                
                if (pair.first < neighbor) {
                    file << pair.first << "," << neighbor << "\n";
                }
            }
        }
        file.close();
        cout << "Map successfully saved to " << filename << "\n";
    }


    void loadFromFile(string filename) {
        ifstream file(filename);
        if (!file) {
            return; 
        }
        
        adjList.clear(); 
        string city1, city2;
        

        while (getline(file, city1, ',') && getline(file, city2)) {
            addRoad(city1, city2);
        }
        file.close();
        cout << "map successsfully loaded from " << filename << "\n";
    }
};

int main() {
    RoadMap rm;
    int choice;
    string city1, city2;

    rm.loadFromFile("roadmap_data.txt");
    

    do {
      cout << "\n===================================\n";
      cout << "    ROAD MAP ANALYSIS SYSTEM       \n";
      cout << "      2024CE03 & 2024CE93      \n";
      cout << "===================================\n";
        cout << "  1. Add a road \n";
       cout << "  2. Check Network connectivity\n";
        cout << "  3. Detect cycles\n";
      cout << "  4. Find shortest path\n";
        cout << "  5. Show diagram\n";
        cout << "  6. Export Map to Image File\n";
      cout << "  0. Exit \n";
      cout << "-----------------------------------\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "City 1: ";
                cin >> ws; 
                getline(cin, city1);
                cout << "City 2: ";
                getline(cin, city2);
                  rm.addRoad(city1, city2);
                cout << "Added!\n";
                break;
            case 2:
                if (rm.isConnected())
                     cout << "Yess, everything is connected.\n";
                else
                     cout << "No, some cities are disconnected.\n";
                break;
            case 3:
                if (!rm.hasCycle())
                    cout << "NO CYCLES.\n";
                break;
            case 4:
                cout << "Start: ";
                cin >> ws;
                getline(cin, city1);
                  cout << "End: ";
                getline(cin, city2);
                rm.shortestPath(city1, city2);
                break;
            case 5:
                  rm.displayMap();
                break;
            case 6:
                     rm.exportToGraphviz("roadmap.dot");
                     break;
            case 0:
                rm.saveToFile("roadmap_data.txt");
                cout << "byie!\n";
                break;
            default:
                cout << "invalid input\n";
        }
    } while (choice != 0);

    return 0;
}