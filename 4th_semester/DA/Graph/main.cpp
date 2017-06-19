#include <iostream>
#include <vector>
#include <algorithm>
std::vector<std::vector<unsigned int> > graph;
std::vector<std::vector<unsigned int> > components;
std::vector<bool> visited;
void dfs(const size_t& node);

int main() {
  unsigned int vertexAmount, edgeAmount, firstTmp, secondTmp;
  std::cin >> vertexAmount >> edgeAmount;
  graph = std::vector<std::vector<unsigned int> >(vertexAmount);
  visited = std::vector<bool>(vertexAmount);
  
  for (size_t i = 0; i < edgeAmount; ++i) {
    std::cin >> firstTmp >> secondTmp;

    graph[firstTmp - 1].push_back(secondTmp - 1);
    graph[secondTmp - 1].push_back(firstTmp - 1);
  }

  for (size_t i = 0; i < vertexAmount; ++i) {
    if (!visited[i]) {
      components.emplace_back(std::vector<unsigned int>());

      dfs(i);
    }
  }

  size_t compSize = components.size();

  for (size_t i = 0; i < compSize; ++i) {
    std::sort(components[i].begin(), components[i].end());
  }

  std::sort(components.begin(), components.end(),
            [](const std::vector<unsigned int>& a, const std::vector<unsigned int>& b) {
              return a[0] < b[0];
            });
  
  for (size_t i = 0; i < compSize; ++i) {
    std::cout << components[i][0] + 1;
    
    for (size_t j = 1; j < components[i].size(); ++j) {
      std::cout <<  ' ' << components[i][j] + 1;
    }
    
    std::cout << '\n';
  }
  
  return 0;
}

void dfs(const size_t& node) {
  visited[node] = true;
  components.back().push_back(node);

  for (const auto& child: graph[node]) {
    if (!visited[child]) dfs(child);
  }
}

