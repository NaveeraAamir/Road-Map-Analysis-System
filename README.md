# 🗺️ Road Map Analysis System

A comprehensive C++ application utilizing **Graph Data Structures** to model, analyze, and visually map inter-city road networks. This project was developed as a 3rd-semester Data Structures and Algorithms (DSA) project.

---

## 🎓 Academic Context
* **Institution:** Department of Computer Engineering (CE), UET
* **Semester:** 3rd Semester
* **Course Instructor:** Pro. Mujtaba Kamal Pasha
* **Developed By:** * Afnan
  * Naveera Aamir

---

## 📝 Project Overview
The **Road Map Analysis System** is a console-based C++ application designed to represent geographical locations (cities) and highways (roads) as a mathematical graph. It allows users to dynamically build a network, analyze its structural integrity, find optimal travel routes, and even generate a visual representation of the map using Graphviz.

---

## 🧠 Core Concepts & Data Structures Used

This project heavily relies on graph theory and fundamental data structures:

* **Adjacency List (`std::map` & `std::vector`):** The graph is implemented dynamically using a map where each city (key) points to a vector of its connected neighboring cities (values). This ensures memory efficiency and fast lookups.
* **Breadth-First Search (BFS):** * Used in **Network Connectivity** to traverse the graph layer by layer and verify if all nodes are reachable from a single source component.
  * Used in **Shortest Path** routing to guarantee the minimum number of stops (unweighted edges).
* **Cycle Detection:** Utilizes BFS along with parent-node tracking (`parentMap`) to detect redundant paths or closed loops within the undirected graph.
* **File I/O (`fstream`):** Implements data persistence by saving network topologies to a `.txt` file and loading them automatically upon initialization.
* **Process Execution (`system()`):** Interfaces with the OS to execute Graphviz CLI commands, translating `.dot` language files into rendered `.png` images.

---

## ✨ Key Features

1. **Add Roads:** Create bidirectional connections between any two cities.
2. **Network Connectivity Check:** Determine if every city in the network is reachable, or if there are isolated components/islands.
3. **Cycle Detection:** Analyze the map to find redundant routes or closed loops (e.g., City A -> City B -> City C -> City A).
4. **Shortest Path Routing:** Calculate and display the optimal route between a starting city and a destination, showing the exact traversal path and total stops.
5. **Console Map Visualization:** View an ASCII-style tree diagram of the adjacency list directly in the terminal.
6. **Graphviz Image Export:** Automatically generate a visual diagram (`roadmap_visual.png`) of the entire network using the Graphviz rendering engine.
7. **Data Persistence:** Network states are safely saved to `roadmap_data.txt` on exit and reloaded on the next startup.

---

## 🛠️ Prerequisites & Installation

To compile and run this project, you will need:

1. **C++ Compiler:** GCC, Clang, or MSVC (supports C++11 or higher).
2. **Graphviz:** Required for the map image generation feature. 
   * Download and install from [Graphviz Official Site](https://graphviz.org/download/).
   * **Important:** Ensure the `dot` command is added to your system's Environment Variables (PATH).

### How to Run:
1. Clone the repository:
   ```bash
   git clone [https://github.com/yourusername/roadmap-analysis-system.git](https://github.com/yourusername/roadmap-analysis-system.git)
   cd roadmap-analysis-system
