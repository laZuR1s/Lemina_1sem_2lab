
#include <iostream>
#include <fstream>
#include <queue>

using Tinfo = int;
struct  NODE
{

    Tinfo info;
    NODE* left, * right;
    NODE(Tinfo info = 0, NODE* ptr_left = nullptr, NODE* ptr_right = nullptr) : info(info), left(ptr_left), right(ptr_right) {}

    ~NODE()
    {
        left = right = nullptr;
    }
};
using Tree = NODE*;
struct TREE
{
private:
    Tree root = nullptr;
public:
    TREE() : root(nullptr) {}
    ~TREE();
    void clear(Tree& root);
    void fill(int n);
    void print(Tree root, int level);
    Tree fillFromFile(int count, std::ifstream& file);
    Tree get_root();
};

