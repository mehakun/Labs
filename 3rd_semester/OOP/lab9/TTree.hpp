#ifdef TLIST_H

template <typename Q> TTree<Q>::TTree(const unsigned int& n) {
  root = std::make_shared<Node>(Node());
  root->son = std::make_shared<Node>(Node());
  N = n;
}

template <typename Q> TTree<Q>::Node::Node() {
  son = sibling = nullptr;
}

template <typename Q> TTree<Q>::Node::Node(Q item) {
  data = item;
}

template <typename Q> void TTree<Q>::recInsert(std::shared_ptr<Node>& node, Q item) {
  if (!node->data) {
    node->data = item;
  } else {
    auto sibl = node;
    
    for (unsigned int i = 0; i < N; i++) {
      if (!sibl->sibling) {
        sibl->sibling = std::make_shared<Node>(Node(item));
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

template <typename Q> void TTree<Q>::insert(Q item) {
  recInsert(root->son, item);
}

template <typename Q> void TTree<Q>::recInorder(const std::shared_ptr<Node>& node) {
  if (node) {
    auto future = std::async(std::launch::async, *(node->data));
    future.get();
    
    if (node->sibling) {
      recInorder(node->sibling);
    }
    if (node->son) {
      recInorder(node->son);
    }
  }
}

template <typename Q> void TTree<Q>::inorder() {
  recInorder(root->son);
}

#endif
