#include "Simple_window.h"    
#include "Graph.h" 
#include "std_lib_facilities.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <algorithm>
#include <fstream>

using namespace Graph_lib;

#define MAXINPUT 100

class TreeIso{
    private:
        struct TreeNode
        {
            vector<TreeNode> subNode;
            vector<TreeNode> parNode;
            pair<int, int> coor;//记录其在canvas上的质心坐标
            pair<int, int> range;//记录其子树坐标区间
            string name;
            string code ="";
            string isoCode = "";
            int buttonw = 10;//该节点按钮宽度
            TreeNode(string Name)
            {
                name = Name;
            }
            int level = 0;//深度，根节点深度为1
        };

        bool errorflag0 = false;//检查文件读入是否成功
        bool errorflag1 = false;//检查输入是否合法
        bool errorflag2 = false;//检查输入是否为一棵树
        bool isoflag = false;//检查两颗树是否同构
        vector<TreeNode> tree1;
        vector<TreeNode> tree2;
        int root1;//记录树1的根节点下标
        int root2;//记录树2的根节点下标
        int levelCount1 = 0;//树1深度
        int levelCount2 = 0;//树2深度
        string tree1FileName;//树1的文件名
        string tree2FileName;//树2的文件名

        void getInput();//读取文件输入
        void checkTreeSingleParent();//检查树是否只存在一个父节点
        int checkNodeExist(string name, vector<TreeNode> tree);//检查树中是否存在同名节点
        void assignCanonicalNames(TreeNode &node, vector<TreeNode> &tree);//从根节点开始对所有节点进行编码
        void assignCode(vector<TreeNode> &tree, int &root);//找出树的根节点（如果存在）编码包裹函数
        bool checkIso();//检查两树是否同构
        void getLevel();//获取每个节点深度
        void visualization();//对两树进行可视化
        int getIsoNode(string isocode, vector<TreeNode> tree);//获取同构节点index
        void matchIsoNode();//匹配两树同构节点
        void reshapeTree(vector<TreeNode> &tree, int root);//对两树的布局进行重塑

    public:
        void IsoTree();//包裹函数
};

