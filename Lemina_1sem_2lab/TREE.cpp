#include "TREE.h"

TREE::~TREE()
{
    clear(root);
}

void TREE::clear(Tree root)
{
    if (root)
    {
        clear(root->left);
        clear(root->right);
        delete root;
        root = nullptr;
    }
}

void TREE::fill(int n)
{
    std::queue<Tree> nodesQueue;
    int rootValue = n;
    --n;
    clear(root);
    root = new NODE(rootValue);
    nodesQueue.push(root);
    while (!nodesQueue.empty() && n > 0)
    {
        int value = n;
        --n;
        Tree current = nodesQueue.front();
        nodesQueue.pop();
        if (value != 0)
        {
            current->left = new NODE(value);
            nodesQueue.push(current->left);
        }
        if (n > 0)
        {
            int value = n;
            --n;
            current->right = new NODE(value);
            nodesQueue.push(current->right);
        }
    }

}

void TREE::print(Tree root, int level)
{
    if (root)
    {
        print(root->right, level + 1);
        for (int i = 0; i < level; ++i)
            std::cout << "    ";
        std::cout << root->info << '\n';
        print(root->left, level + 1);
    }
}

Tree TREE::get_root()
{
    return root;
}