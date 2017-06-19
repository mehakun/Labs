#ifdef TLIST_H

template <typename Q, typename O> TTree<Q, O>::TTree() {
  root = std::make_shared<Node>(Node());
  root->son = std::make_shared<Node>(Node());
}

template <typename Q, typename O> TTree<Q, O>::Node::Node() {
  son = sibling = nullptr;
  itemsInNode = 0;
}

template <typename Q, typename O> TTree<Q, O>::Node::Node(const O& item) {
  data.PushFront(item);
  itemsInNode = 1;
}

template <typename Q, typename O> void TTree<Q, O>::recRemByType(std::shared_ptr<Node>& node, const int& type) {
  if (node->itemsInNode) {

    for (int i = 0; i < 5; i++) {
      auto iter = node->data.begin();
      
      for (int k = 0; k < node->data.GetLength(); k++) {
        if (iter->type() == type) {
          node->data.Pop(k + 1);
          node->itemsInNode--;
          break;
        }
        ++iter;
      }
    }
    
    if (node->sibling) {
      recRemByType(node->sibling, type);
    }
    if (node->son) {
      recRemByType(node->son, type);
    }

  }
}

template <typename Q, typename O> void TTree<Q, O>::removeByType(const int& type) {
  recRemByType(root->son, type);
}

template <typename Q, typename O> void TTree<Q, O>::recInsert(std::shared_ptr<Node>& node, const O& item) {
  if (node->itemsInNode < 5) {
    node->data.PushFront(item);
    node->itemsInNode++;
  } else {
    auto sibl = node;
    
    for (int i = 0; i < 3; i++) {
      if (!sibl->sibling) {
        sibl->sibling = std::make_shared<Node>(Node(item));
        return;
      }
    
      if (sibl->sibling->itemsInNode < 5) {
        recInsert(sibl->sibling, item);
        return;
      }

      sibl = sibl->sibling;
    }

    if (node->son) {
      recInsert(node->son, item);
    } else {
      node->son = std::make_shared<Node>(Node(item));
    }
  }
}

template <typename Q, typename O> void TTree<Q, O>::insert(const O& item) {
  recInsert(root->son, item);
}

template <typename Q, typename O> void TTree<Q, O>::recInorder(const std::shared_ptr<Node>& node) {
  if (node->itemsInNode) {
    node->data.sort();
    for (const auto& i: node->data) {
      i->Print();
    }
    std::cout << "\n";
    
    if (node->sibling) {
      recInorder(node->sibling);
    }
    if (node->son) {
      recInorder(node->son);
    }
  }
}

template <typename Q, typename O> void TTree<Q, O>::inorder() {
  if (root->son->son || root->son->sibling) { 
    clear(root->son, root);
  }
  recInorder(root->son);
}

template <typename Q, typename O> void TTree<Q, O>::recRemLesser(std::shared_ptr<Node>& node, const double& sqr) {
  if (node->itemsInNode) {
    for (int i = 0; i < 5; i++) {
      auto iter = node->data.begin();
      
      for (int k = 0; k < node->data.GetLength(); k++) {
        if (iter->getSquare() < sqr) {
          node->data.Pop(k + 1);
          node->itemsInNode--;
          break;
        }
        ++iter;
      }
    }
    
    if (node->sibling) {
      recRemLesser(node->sibling, sqr);
    }
    if (node->son) {
      recRemLesser(node->son, sqr);
    }

  }
}

template <typename Q, typename O> void TTree<Q, O>::removeLesser(const double& sqr) {
  recRemLesser(root->son, sqr);
}

template <typename Q, typename O> void TTree<Q, O>::clear(std::shared_ptr<Node>& node, std::shared_ptr<Node>& parent) {
  if (node) {
    if (!node->itemsInNode) {
      auto orphan = node;
      auto orphanPar = parent;
      if (node->sibling) {
        orphan = node->sibling;
        orphanPar = node;
      } else if (node->son) {
        orphan = node->sibling;
        orphanPar = node;
      }

      while (orphan->sibling || orphan->son) {
        orphanPar = orphan;
        if (orphan->sibling) {
          orphan = orphan->sibling;
        } else if (orphan->son) {
          orphan = orphan->son;
        }
      }

      if (orphanPar->sibling == orphan) {
        std::swap(node->data, orphan->data);
        node->itemsInNode = orphan->itemsInNode;
        orphanPar->sibling = nullptr;
      } else if (orphanPar->son == orphan) {
        std::swap(node->data, orphan->data);
        node->itemsInNode = orphan->itemsInNode;
        orphanPar->son = nullptr;
      }
      
    }
  }
  
  if (node) {
    if (node->son) {
      clear(node->son, node);
    }
    if (node->sibling) {
      clear(node->sibling, node);
    }
  }
}

#endif
