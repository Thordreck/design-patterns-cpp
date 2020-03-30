#include <vector>
#include <iostream>

template <typename T>
struct BinaryTree;

template <typename T>
struct Node
{
    T value {};

    Node<T>* left   { nullptr };
    Node<T>* right  { nullptr };
    Node<T>* parent { nullptr };

    BinaryTree<T>* tree { nullptr };

    Node(T value) : value(value) {}

    Node(T value, Node<T>* left, Node<T>* right)
        : value(value)
        , left(left)
        , right(right)
    {
        this->left->tree  = tree;
        this->right->tree = tree;

        this->left->parent  = this;
        this->right->parent = this;
    }

    void set_tree(BinaryTree<T>* new_tree)
    {
        tree = new_tree;

        if(left)  { left->set_tree(new_tree); }
        if(right) { right->set_tree(new_tree); }
    }

    ~Node()
    {
        if(left)  { delete left;  }
        if(right) { delete right; }
    }
};

template <typename T>
struct BinaryTree
{
    Node<T>* root { nullptr };

    BinaryTree(Node<T>* root)
        : root(root)
    {
        root->set_tree(this);
    }

    ~BinaryTree()
    {
        if(root) { delete root; }
    }

    template <typename U>
    struct PreOrderIterator
    {
        Node<U>* current;

        PreOrderIterator(Node<U>* current) : current(current) {};

        bool operator!=(const PreOrderIterator<U>& other)
        {
            return current != other.current;
        }

        PreOrderIterator<U>& operator++()
        {
            if(current->right)
            {
                current = current->right;

                while(current->left)
                {
                    current = current->left;
                }
            }
            else
            {
                Node<T>* p = current->parent;

                while(p && current == p->right)
                {
                    current = p;
                    p = p->parent;
                }

                current = p;
            }

            return *this;
        }

        Node<U>& operator*() { return *current; }

    }; // PreOrderIterator

    using iterator = PreOrderIterator<T>;

    iterator begin()
    {
        Node<T>* n = root;

        if(n)
        {
            while(n->left)
            {
                n = n->left;
            }
        }

        return iterator { n };
    }

    iterator end()
    {
        return iterator { nullptr };
    }
};

int main()
{
    BinaryTree<std::string> family
    {
        new Node<std::string>
        {
            "me",
            new Node<std::string>
            {
                "mother",
                new Node<std::string> { "mother's mother" },
                new Node<std::string> { "mother's father" }
            },
            new Node<std::string> { "father" }
        }
    };

    for(auto&& node : family)
    {
        std::cout << node.value << std::endl;
    }

    return 0;
}
