#include "SuffTree.h"
#include <iostream>

TSuffTree::TNode::TNode(const int& fpos, const int& edgeLength, const std::shared_ptr<TNode>& parent) {
  this->firstPos = fpos;
  this->edgeLength = edgeLength;
  this->parent = parent;
}

TSuffTree::TSuffTree() {
  n = 0;
  pos = 0;
  root = std::make_shared<TNode>(TNode(0, INF, nullptr));
  root->parent = root;
}

void TSuffTree::AddLetter(const int& sym) {
  symPos.emplace_back(sym);
  n++;
  pos++;
  auto node = root;
  auto last = root;

  while (pos > 0) {

    while ((node->children.find(symPos[n - pos]) != node->children.end()) &&
           (pos > node->children[symPos[n - pos]]->edgeLength)) {
      node = node->children[symPos[n - pos]];
      pos -= node->edgeLength;
    }

    int edge = symPos[n - pos];
    auto child = node->children.find(edge);
    int t = (child == node->children.end()) ? -1 : symPos[child->second->firstPos + pos - 1];

    if (child == node->children.end()) {
      node->children[edge] = std::make_shared<TNode>(TNode(n - pos, INF, node));
      last->suffLink = node;
      last = root;
      
    } else if (t == sym) {
      last->suffLink = node;
      return;
    } else {
      auto splitNode = std::make_shared<TNode>(TNode(child->second->firstPos, pos - 1, child->second->parent));
      splitNode->children[sym] = std::make_shared<TNode>(TNode(n - 1, INF, splitNode));
      splitNode->children[t] = child->second;
      child->second->firstPos += pos - 1;
      child->second->edgeLength -= pos - 1;
      child->second->parent = splitNode;
      child->second = splitNode;
      last->suffLink = splitNode;
      last = splitNode;      
    }
    
    if (node == root) {
      pos--;
    } else {
      node = node->suffLink;
    }
  }

}

void TSuffTree::inorder(const std::shared_ptr<TNode>& node, const int& dpth) {
  for (int i = 0; i < dpth; i++) {
    putchar('\t');
  }
  std::string tmp;
  if (node != root) {
    for (int i = node->firstPos, k = 0; k < node->edgeLength && i < n; i++, k++) {
      tmp += symPos[i];
    }
  } else {
    tmp = "root";
  }

  std::cout << "node represents " << tmp <<" node is " << node << " sufflink is " << node->suffLink << " parent is "
            << node->parent <<" edge len " << node->edgeLength << " fpos " << node->firstPos << std::endl;
  for (const auto& i : node->children) {
    inorder(i.second, dpth + 1);
  }
}

std::shared_ptr<TSuffTree::TNode> TSuffTree::setFirst(int& ms, const std::string& pattern) {
  auto smth = pattern.find(pattern[0]);
  auto tmp = root;
  
  if (smth != std::string::npos) {
    auto child = tmp->children.find(pattern[0]);
    
    while (smth < pattern.size()) {
      if (child != tmp->children.end()) {
        for (int l = 0, i = child->second->firstPos;
             l < child->second->edgeLength && i < n && smth < pattern.size();
             i++, smth++, l++) {

          if (pattern[smth] != symPos[i]) {
            return tmp;
          }
          ms++;
        }

        tmp = child->second;
        child = child->second->children.find(pattern[smth]);
      } else {
        return tmp;
      }
    }
  }
  
  return tmp;
}

void TSuffTree::SetMs(std::vector<int>& ms, const std::string& text) {
  root->suffLink = root;
  auto b = setFirst(ms[0], text);
  
  for (size_t i = 1; i < ms.size(); i++) {
    if (ms[i - 1] == n) {
      std::cout << i << std::endl;
    }

    int begin = b->firstPos;
    int whatsLeft = n - b->firstPos;
    b = (b->edgeLength > n) ? b->parent->suffLink : b->suffLink;
    
    while (whatsLeft > b->edgeLength) {
      for (const auto& child: b->children) {
        if (child.second->firstPos == begin) {
          b = child.second;
          break;
        }
      }

      whatsLeft -= b->edgeLength;
      begin += n - b->firstPos;
    }
    
    for (int j = i, l = begin; j < text.size() && l < n; j++, l++) {
      if (text[j] != symPos[l]) {
        break;
      }

      ms[i]++;
      
      if (l == b->edgeLength) {
        auto child = b->children.find(text[j+1]);
        if (child != b->children.end()) {
          b = child->second;
          l = b->firstPos;
        } else {
          l = n + 1;
        }
      }
      
    }
    
  }
}

