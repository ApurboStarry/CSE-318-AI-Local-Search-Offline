#include<bits/stdc++.h>
#include<exception>

using namespace std;

typedef pair<int, int> pii;
typedef vector<int> VI;
typedef vector<VI> VVI;

VI largestDegree(VVI g, int vertices) {
  VI degree(vertices + 1);
  for (int i = 1; i <= vertices; i++)
  {
    int count = 0;
    for (int j = 1; j <= vertices; j++)
    {
      if (g[i][j] == 1)
      {
        count++;
      }
    }
    degree[i] = count;
  }

  VI colors(vertices + 1, -1);
  int maxDegreeNode;
  int maxDegree = -1;

  for (int i = 1; i <= vertices; i++)
  {
    if (maxDegree < degree[i])
    {
      maxDegree = degree[i];
      maxDegreeNode = i;
    }
  }

  colors[maxDegreeNode] = 0;
  for(int asdf = 1; asdf < vertices; asdf++) {
    int maxDeg = -1;
    int maxDegNode;
    for(int i = 1; i <= vertices; i++) {
      if(colors[i] == -1 && maxDeg < degree[i]) {
        maxDeg = degree[i];
        maxDegNode = i;
      }
    }

    VI colorsAlreadyUsed;
    int vertexToBeColored = maxDegNode;

    for(int i = 1; i <= vertices; i++) {
      if(g[vertexToBeColored][i] == 1 && colors[i] != -1) {
        colorsAlreadyUsed.push_back(colors[i]);
      }
    }

    sort(colorsAlreadyUsed.begin(), colorsAlreadyUsed.end());
    
    // cout << "colors already used: ";
    // for(int x : colorsAlreadyUsed) {
    //   cout << x << " ";
    // }
    // cout << endl;
    // cout << "Vertex to be coloured: " << vertexToBeColored << endl;

    if(colorsAlreadyUsed.size() == 0) {
      colors[vertexToBeColored] = 0;
      continue;
    }

    if(colorsAlreadyUsed[0] != 0) {
      colors[vertexToBeColored] = 0;
    } else {
      for(int i = 0; i < colorsAlreadyUsed.size() - 1; i++) {
        if(colorsAlreadyUsed[i+1] - colorsAlreadyUsed[i] > 1) {
          colors[vertexToBeColored] = colorsAlreadyUsed[i] + 1;
        }
      }
    }

    if(colors[vertexToBeColored] == -1) {
      colors[vertexToBeColored] = colorsAlreadyUsed[colorsAlreadyUsed.size() - 1] + 1;
    }
  }

  return colors;
}

VI dSatur(VVI g, int vertices) {
  VI degree(vertices+1);
  for(int i = 1; i <= vertices; i++) {
    int count = 0;
    for(int j = 1; j <= vertices; j++) {
      if(g[i][j] == 1) {
        count++;
      }
    }
    degree[i] = count;
  }

  VI colors(vertices + 1, -1);
  int maxDegreeNode;
  int maxDegree = -1;

  for(int i = 1; i <= vertices; i++) {
    if(maxDegree < degree[i]) {
      maxDegree = degree[i];
      maxDegreeNode = i;
    }
  }

  colors[maxDegreeNode] = 0;
  for(int asdf = 1; asdf < vertices; asdf++) {
    // find vertex with highest degree saturation
    VI degreeOfSaturation(vertices+1, 0);
    for(int i = 1; i <= vertices; i++) {
      if(colors[i] == -1) {
        int count = 0;
        for(int j = 1; j <= vertices; j++) {
          if(g[i][j] == 1 && colors[j] != -1) {
            count++;
          }
        }
        degreeOfSaturation[i] = count;
      }
    }

    // cout << "Degree of saturation: ";
    // for(int i = 1; i <= vertices; i++) {
    //   cout << degreeOfSaturation[i] << " ";
    // }
    // cout << endl;

    // if there are multiple nodes with same highest degree of saturation,
    // consider the one with highest degree and later randomly
    VI nodesWithHighestSaturation;
    int maxSaturationValue = 0;
    for(int i = 1; i <= vertices; i++) {
      if(maxSaturationValue < degreeOfSaturation[i]) {
        maxSaturationValue = degreeOfSaturation[i];
      }
    }
    
    if(maxSaturationValue == 0) {
      int maxRemainingDegree = -1;
      int maxRemainingNode;
      for(int i = 1; i <= vertices; i++) {
        if(colors[i] == -1 && degree[i] > maxRemainingDegree) {
          maxRemainingDegree = degree[i];
          maxRemainingNode = i;
        }
      }
      // cout << maxRemainingDegree << " " << maxRemainingNode << endl;
      colors[maxRemainingNode] = 0;

      continue;
    }

    for(int i = 1; i <= vertices; i++) {
      if(degreeOfSaturation[i] == maxSaturationValue) {
        nodesWithHighestSaturation.push_back(i);
      }
    }

    // cout << "Nodes with highest saturation values: ";
    // for(int i: nodesWithHighestSaturation) {
    //   cout << i << " ";
    // }
    // cout << endl;

    int vertexToBeColored;
    if(nodesWithHighestSaturation.size() > 1) {
      // cout << "HERE\n";
      int maxDeg = 0;
      for(int i : nodesWithHighestSaturation) {
        if(degree[i] > maxDeg) {
          maxDeg = degree[i];
        }
      }
      // cout << "maximum degree: " << maxDeg << endl;

      VI tie;
      for(int i : nodesWithHighestSaturation) {
        if(degree[i] == maxDeg) {
          tie.push_back(i);
        }
      }

      if(tie.size() > 1) {
        vertexToBeColored = tie[rand() % tie.size()];
        // cout << "Vertex to be coloured: " << vertexToBeColored << endl;
      } else {
        vertexToBeColored = tie[0];
      }
    } else {
      vertexToBeColored = nodesWithHighestSaturation[0];
    }

    // color the vertex with first suitable color
    VI colorsAlreadyUsed;
    for(int i = 1; i <= vertices; i++) {
      if(g[vertexToBeColored][i] == 1 && colors[i] != -1) {
        colorsAlreadyUsed.push_back(colors[i]);
      }
    }

    sort(colorsAlreadyUsed.begin(), colorsAlreadyUsed.end());
    // cout << "colors already used: ";
    // for(int x : colorsAlreadyUsed) {
    //   cout << x << " ";
    // }
    // cout << endl;
    // cout << "Vertex to be coloured: " << vertexToBeColored << endl;

    if(colorsAlreadyUsed[0] != 0) {
      colors[vertexToBeColored] = 0;
    } else {
      for(int i = 0; i < colorsAlreadyUsed.size() - 1; i++) {
        if(colorsAlreadyUsed[i+1] - colorsAlreadyUsed[i] > 1) {
          colors[vertexToBeColored] = colorsAlreadyUsed[i] + 1;
        }
      }
    }

    if(colors[vertexToBeColored] == -1) {
      colors[vertexToBeColored] = colorsAlreadyUsed[colorsAlreadyUsed.size() - 1] + 1;
    }

    // cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n";
  }

  // cout << "Colors: ";
  // for(int i = 1; i <= vertices; i++) {
  //   cout << colors[i] << " ";
  // }
  // cout << endl;

  return colors;
}

double penalty(VVI coursesTakenByStudents, VI colors) {
  double totalPenalty = 0;

  for(int i = 0; i < coursesTakenByStudents.size(); i++) {
    for(int j = 1; j < coursesTakenByStudents[i].size(); j++) {
      int difference = abs(coursesTakenByStudents[i][j] - coursesTakenByStudents[i][j-1]);
      // printf("(%d, %d) ", coursesTakenByStudents[i][j], difference);

      if(difference <= 5) {
        totalPenalty += 1 << (5 - difference);
      }
    }
  }

  return totalPenalty / coursesTakenByStudents.size();
}

VI kempeChain(VVI g, int vertices, VI colors) {
  // randomly choose a vertex;
  // among the other vertices connected to this vertex randomly choose
  // another vertex
  // try to extend the chain containing only two colours of this vertices
  int firstVertex = rand() % vertices + 1;
  VI connectedVertices;
  for(int i = 1; i <= vertices; i++) {
    if(g[firstVertex][i] == 1) {
      connectedVertices.push_back(i);
    }
  }
  int anotherVertex = connectedVertices[rand() % connectedVertices.size()];

  int firstColor = colors[firstVertex];
  int anotherColor = colors[anotherVertex];

  vector<bool> isInKempeChain(vertices+1, false);
  queue<int> q;
  q.push(firstVertex);
  q.push(anotherVertex);

  isInKempeChain[firstVertex] = true;
  isInKempeChain[anotherVertex] = true;

  // cout << firstVertex << " " << anotherVertex << endl;

  while(!q.empty()) {
    int s = q.front();
    q.pop();
    for(int i = 1; i <= vertices; i++) {
      if(g[s][i] == 1 && !isInKempeChain[i] && (colors[i] == firstColor || colors[i] == anotherColor)) {
        q.push(i);
        isInKempeChain[i] = true;
      }
    }
  }

  
  for(int i = 1; i <= vertices; i++) {
    if(isInKempeChain[i]) {
      if(colors[i] == firstColor) {
        colors[i] = anotherColor;
      } else {
        colors[i] = firstColor;
      }
    }
  }

  return colors;
}

int getNumberOfUniqueColors(VI colors) {
  // cout << "Colors: ";
  // for(int i = 1; i <= vertices; i++) {
  //   cout << colors[i] << " ";
  // }
  // cout << endl;

  set<int> c;
  for(int i = 1; i < colors.size(); i++) {
    c.insert(colors[i]);
  }

  return c.size();
}

int main(int argc, char** argv) {
  if(argc < 3) {
    cerr << "Please run this program as: <program> <course file> <student file>\n";
    return 0;
  }

  ifstream crs, stu;
  crs.open(argv[1], ifstream::in);
  stu.open(argv[2], ifstream::in);

  if(crs.fail()) {
    cerr << "Couldn't open course file\n";
    return 1;
  }

  if(stu.fail()) {
    cerr << "Couldn't open student file\n";
    return 1;
  }

  vector<pii> courses(1);

  while(crs >> courses.back().first >> courses.back().second) {
    courses.emplace_back();
  }
  courses.pop_back();

  sort(courses.begin(), courses.end());

  int vertices = courses.size();
  VVI g(vertices+1, VI(vertices+1, 0));
  
  VVI coursesTakenByStudents;

  string line;

  while(getline(stu, line)) {
    stringstream ss(line);
    VI enrolled;

    int c;
    while(ss >> c) {
      enrolled.push_back(c);
    }

    for(int i=0; i<(int) enrolled.size(); ++i) {
			for(int j=i+1; j<(int) enrolled.size(); ++j) {
				g[enrolled[i]][enrolled[j]] = g[enrolled[j]][enrolled[i]] = 1;
			}
		}

    coursesTakenByStudents.push_back(enrolled);
  }

  // cout << "courses taken by students: " << endl;
  // for(int i = 0; i < coursesTakenByStudents.size(); i++) {
  //   for(int j = 0; j < coursesTakenByStudents[i].size(); j++) {
  //     cout << coursesTakenByStudents[i][j] << " ";
  //   }
  //   cout << endl;
  // }
  // cout << endl;

  // cout << "    ";
  // for(int i = 1; i <= vertices; i++) {
  //   cout << i << " ";
  // }
  // cout << endl;

  // for(int i = 1; i <= vertices; i++) {
  //   cout << i << "-> ";
  //   for(int j = 1; j <= vertices; j++) {
  //     cout << g[i][j] << " ";
  //   }
  //   cout << endl;
  // }

  // Scheme 1: DSatur + Kempe Chain
  VI colors = dSatur(g, vertices);
  colors = kempeChain(g, vertices, colors);

  cout << "Scheme 1: " << endl;
  cout << "#########" << endl;
  cout << "Total Number of time slots: " << getNumberOfUniqueColors(colors) << endl;
  cout << "Penalty: " << penalty(coursesTakenByStudents, colors) << endl;

  // Scheme 2: Largest Degree + kempe chain
  VI colors2 = largestDegree(g, vertices);
  colors2 = kempeChain(g, vertices, colors2);

  cout << "\nScheme 2: " << endl;
  cout << "#########" << endl;
  cout << "Total Number of time slots: " << getNumberOfUniqueColors(colors2) << endl;
  cout << "Penalty: " << penalty(coursesTakenByStudents, colors2) << endl;

  crs.close();
  stu.close();

  return 0;

}


















