#include<bits/stdc++.h>
#include<exception>

using namespace std;

typedef pair<int, int> pii;
typedef vector<int> VI;
typedef vector<VI> VVI;

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
    cout << endl;
  }

  return totalPenalty / coursesTakenByStudents.size();
}

VI kempeChain(VVI g, int vertices, VI colors) {
  
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

  VI colors = dSatur(g, vertices);
  colors = kempeChain(g, vertices, colors);

  cout << "Colors: ";
  for(int i = 1; i <= vertices; i++) {
    cout << colors[i] << " ";
  }
  cout << endl;

  cout << penalty(coursesTakenByStudents, colors) << endl;

  crs.close();
  stu.close();

  return 0;

}


















