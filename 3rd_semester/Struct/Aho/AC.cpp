#include "AC.h"
#include <queue>
#include <iostream>

TFinitaAuto::TNode::TNode() : fail(nullptr) {}

TFinitaAuto::TFinitaAuto() {
  root = std::make_shared<TNode>(TNode());
  root->fail = root;
  withoutJoker = 0;
}

void TFinitaAuto::Build(const std::vector<std::string>& patterns) {
  int patternNumber = 0;
  int patLen = patterns.size();
  substrLens.resize(patLen);
  int i;

  auto currentNode = root;

  for (i = 0; i < patLen; i++) {
    if (patterns[i] == "?") {
      if (currentNode != root) {
        currentNode->out.emplace_back(patternNumber);
        substrLens[patternNumber] = i - patternNumber;
        withoutJoker++;
        currentNode = root;
      }

      patternNumber = i + 1;
      continue;
    }

    auto nodeToInsert = currentNode->to.find(std::stoul(patterns[i]));
    
    if (nodeToInsert != currentNode->to.end()) {
      currentNode = nodeToInsert->second;
    } else {
      auto newNode = std::make_shared<TNode>(TNode());
      currentNode->to[std::stoul(patterns[i])] = newNode;
      currentNode = newNode;
    }

  }

  if (currentNode != root) {
    currentNode->out.emplace_back(patternNumber);
    substrLens[patternNumber] = i - patternNumber;
    withoutJoker++;
  }
  
  InitFailFunc();
}


void TFinitaAuto::InitFailFunc() {
  auto currentNode = root;
  std::queue<std::shared_ptr<TNode> > BFSQueue;
  BFSQueue.push(currentNode);

  while (!BFSQueue.empty()) {
    currentNode = BFSQueue.front();
    BFSQueue.pop();
    
    for (auto& iter : currentNode->to) {
      auto child = iter.second;
      auto parentFail = currentNode->fail;
      auto subPattern = iter.first;
      
      BFSQueue.push(child);
      
      for (;;) {
        auto existingNode = parentFail->to.find(subPattern);

        if (existingNode != parentFail->to.end()) {
          child->fail = (existingNode->second != child) ? existingNode->second : root;
          child->out.insert(child->out.end(),
                            child->fail->out.begin(),
                            child->fail->out.end());
          break;
        }

        if (parentFail == root) {
          child->fail = root;
          break;
        } else {
          parentFail = parentFail->fail;
        }
        
      }
    }

  }
}

void TFinitaAuto::Search(const std::vector<unsigned long>& text, std::vector< std::pair<int, int> >& result, const int& patternLen) {
  int textLen = text.size();
  std::vector<int> entry(textLen, 0);
  auto currentNode = root;
  int i;
  
  for(i = 0; i < textLen; i++) {
    auto existingNode = currentNode->to.find(text[i]);

    while (existingNode == currentNode->to.end()) {
      currentNode = currentNode->fail;
      existingNode = currentNode->to.find(text[i]);
      if (currentNode == currentNode->fail)
        break;
    }

    if (existingNode != currentNode->to.end()) {
      currentNode = existingNode->second;

      if (!currentNode->out.empty()) {
        for (const auto& it : currentNode->out) {
          int patternId = i - substrLens[it] - it + 1;
          if (patternId < 0)
            continue;
          entry[patternId]++;
        }
      }
    }
  }

  for (i = 0; i < textLen; i++) {
    if ((entry[i] == withoutJoker) && (i + patternLen <= textLen)) {
        std::cout << result[i].first << ", " <<
          result[i].second << std::endl;
    }
  }
}
  
