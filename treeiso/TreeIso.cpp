
#include "TreeIso.h"
#include <stack>
#include <FL/Fl_Button.H>

int buttonpushed = 0;
int num = 0;

//---------------------------------获取输入并检查输入合法性------------------------------------
void TreeIso::getInput()
{
    cout<<"please input tree1 file name: "<<endl;
	getline(cin,tree1FileName);
    cout<<"please input tree2 file name: "<<endl;
    getline(cin,tree2FileName);

    ifstream inFile1(tree1FileName, ios::in);
    ifstream inFile2(tree2FileName, ios::in);
    if(!inFile1.is_open() || !inFile2.is_open())
    {
        errorflag0 = true;
        return;
    }

    //读入第一棵树
	string lineStr;//每次读入文件中的一行
    while(getline(inFile1,lineStr))
    {
        //跳过空行
        if(lineStr == "") continue;
        int i =0;
        string node1="";
        string node2="";
        //------------------------获取第一个节点名称---------------------------
        //strip前段空格
        while(i<lineStr.size() && lineStr[i] == ' ')
        {
            i++;
        }
        while(i<lineStr.size() &&lineStr[i] != '-')
        {
            node1 += lineStr[i];
            i++;
        }
        if(i >= lineStr.size())//不存在第二个节点，不是一棵树
        {
            errorflag1 = true;
            return;
        }
        //strip后段空格
        int stripcount = node1.size()-1;
        while(stripcount >0 && node1[stripcount] == ' ')
        {
            stripcount --;
        }
        string orinode = node1;
        node1 = orinode.substr(0,stripcount+1);
        //------------------------获取第二个节点名称----------------------------
        //跳过第一个node名称后的空格以及"->"符号
        if(i<lineStr.size() && lineStr[i] == '-')
        {
            i+=2;
        }
        else//越界，缺少节点
        {
           errorflag1 = true;
           return;
        }

        //舍去前段空格
        while(i<lineStr.size() && lineStr[i] == ' ')
        {
            i++;
        }
        while(i<lineStr.size())
        {
            node2 += lineStr[i];
            i++;
        }
        //strip后段空格
        stripcount = node2.size()-1;
        while(stripcount >0 && node2[stripcount] == ' ')
        {
            stripcount --;
        }
        orinode = node2;
        node2 = orinode.substr(0,stripcount+1);
        //-----------------------检查节点内容是否合法--------------------------
        //检查两个节点是否为空
        if(node1 == "" || node2 == "")
        {
            cout<<"tree1 has null node"<<endl;
            errorflag1 = true;
            return;
        }

        //树合法，构建相关节点
        //查看父节点是否已存在
        int index1 = checkNodeExist(node1, tree1);
        if(index1 == -1)
        {
            tree1.push_back(TreeNode(node1));
            tree1.back().subNode.push_back(TreeNode(node2));
        }
        else//父节点存在
        {
            tree1[index1].subNode.push_back(TreeNode(node2));
        }
        //查看子节点是否存在
        int index2 = checkNodeExist(node2, tree1);
        if(index2 == -1)
        {
            tree1.push_back(TreeNode(node2));
            tree1.back().parNode.push_back(TreeNode(node1));
        }
        else
        {
            tree1[index2].parNode.push_back(TreeNode(node1));
        }
    }

    //读入第二棵树
    while(getline(inFile2,lineStr))
    {
        if(lineStr == "") continue;
        int i =0;
        //char currChar = '';
        string node1="";
        string node2="";
        //------------------------获取第一个节点名称---------------------------
        //strip前段空格
        while(i<lineStr.size() && lineStr[i] == ' ')
        {
            i++;
        }
        while(i<lineStr.size() &&lineStr[i] != '-')
        {
            node1 += lineStr[i];
            i++;
        }
        if(i >= lineStr.size())//不存在第二个节点，不是一棵树
        {
            errorflag1 = true;
            return;
        }
        //strip后段空格
        int stripcount = node1.size()-1;
        while(stripcount >0 && node1[stripcount] == ' ')
        {
            stripcount --;
        }
        string orinode = node1;
        node1 = orinode.substr(0,stripcount+1);
        //------------------------获取第二个节点名称----------------------------
        //跳过第一个node名称后的空格以及"->"符号
        if(i<lineStr.size() && lineStr[i] == '-')
        {
            i+=2;
        }
        else//越界，缺少节点
        {
           errorflag1 = true;
           return;
        }

        //舍去前段空格
        while(i<lineStr.size() && lineStr[i] == ' ')
        {
            i++;
        }
        while(i<lineStr.size())
        {
            node2 += lineStr[i];
            i++;
        }
        //strip后段空格
        stripcount = node2.size()-1;
        while(stripcount >0 && node2[stripcount] == ' ')
        {
            stripcount --;
        }
        orinode = node2;
        node2 = orinode.substr(0,stripcount+1);
        //-----------------------检查节点内容是否合法--------------------------
        //检查两个节点是否为空
        if(node1 == "" || node2 == "")
        {
            cout<<"tree2 has null node."<<endl;
            errorflag1 = true;
            return;
        }
        //检查两个节点内容是否存在非法字符

        //树合法，构建相关节点
        //查看父节点是否已存在
        int index1 = checkNodeExist(node1, tree2);
        if(index1 == -1)
        {
            tree2.push_back(TreeNode(node1));
            tree2.back().subNode.push_back(TreeNode(node2));
        }
        else//父节点存在
        {
            tree2[index1].subNode.push_back(TreeNode(node2));
        }
        //查看子节点是否存在
        int index2 = checkNodeExist(node2, tree2);
        if(index2 == -1)
        {
            tree2.push_back(TreeNode(node2));
            tree2.back().parNode.push_back(TreeNode(node1));
        }
        else
        {
            tree2[index2].parNode.push_back(TreeNode(node1));
        }
    }
}
//-----------------------------------------------------------------------------------

//----------------------检查每个节点是否存在多余一个的父节点----------------------------
void TreeIso::checkTreeSingleParent()
{
    for (int i=0;i<tree1.size();i++)
    {
        if(tree1[i].parNode.size() > 1)
        {   
            cout<<"tree1 node["<<tree1[i].name<<"] has multi parents."<<endl;
            errorflag2 = true;
            return;
        }
    }
    for(int i=0;i<tree2.size();i++)
    {
        if(tree2[i].parNode.size() >1)
        {
            cout<<"tree2 node["<<tree2[i].name<<"] has multi parents."<<endl;
            errorflag1 = true;
            return;
        }
    }
}

//-----------用于在树内查找同名节点是否存在，若存在返回其下标，若不存在则返回-1------------
int TreeIso::checkNodeExist(string name, vector<TreeNode> tree)
{
    for(int i=0;i<tree.size();i++)
    {
        if(tree[i].name == name)
        {
            return i;
        }
    }
    return -1;
}
//------------------------------------------------------------------------------------

//------------------------------生成树节点唯一编码--------------------------------------
void TreeIso::assignCanonicalNames(TreeNode &node, vector<TreeNode> &tree)
{
    if(node.subNode.size()==0)//叶节点，直接赋值
    {
        node.code = "01";
    }
    else//非叶节点
    {
        for(int i=0;i<node.subNode.size();i++)
        {
            assignCanonicalNames(tree[checkNodeExist(node.subNode[i].name, tree)], tree);
            //tree[checkNodeExist(node.subNode[i].name, tree)].code = node.subNode[i].code;
        }
        //排序
        if(node.subNode.size()>1){
            for(int i=0;i<node.subNode.size();i++)
            {
                for(int j=0;j<node.subNode.size()-i-1;j++)
                {
                    if(tree[checkNodeExist(node.subNode[j].name , tree)].code > tree[checkNodeExist(node.subNode[j+1].name , tree)].code )
                    {
                    //交换位置
                        TreeNode tmp = node.subNode[j];
                        node.subNode[j] = node.subNode[j+1];
                        node.subNode[j+1] = tmp;
                    }
                }
            }
        }
        //生成当前节点的编码
        node.code += "0";
        for(int i=0;i<node.subNode.size();i++)
        {
            node.code += tree[checkNodeExist(node.subNode[i].name, tree)].code;
        }
        node.code += "1";
    }
}
//------------------------------------------------------------------------------------


//--对某树的所有节点进行编码，若该输入不是一棵树，则立刻将errorflag2置1并立刻返回-----------
void TreeIso::assignCode(vector<TreeNode> &tree, int &root)
{
    //找到父节点
    int index = -1;
    int count = 0;
    for(int i=0;i<tree.size();i++)
    {
        if(tree[i].parNode.size() == 0)
        {
            index = i;
            count ++;
        }
        
    }
    if(count != 1)
    {
        errorflag2 = true;
        return ;
    }
    root = index;
    assignCanonicalNames(tree[index], tree);
}
//------------------------------------------------------------------------------------

//----------------------检查两树是否同构-----------------------------------------------
bool TreeIso::checkIso()
{
    if(tree1[root1].code == tree2[root2].code)
        return true;
    else
        return false;
}
//------------------------------------------------------------------------------------

//----------------------------对两颗树进行同构节点匹配----------------------------------
void TreeIso::matchIsoNode()
{
    //根节点匹配
    tree1[root1].isoCode = "0";
    tree2[root2].isoCode = "0";
    int isoCount = 1;
    //逐层遍历
    //找出两树处于该层的所有节点   
    for(int i=2;i<=levelCount1;i++)
    {
        vector<int> t1;
        vector<int> t2;
        for(int j =0; j<tree1.size();j++)
        {
            if(tree1[j].level ==i) t1.push_back(j);
            if(tree2[j].level ==i) t2.push_back(j);
        }
        for(int i=0;i<t1.size();i++)
        {
            int parNode = checkNodeExist(tree1[t1[i]].parNode[0].name, tree1);
            for(int j =0;j<t2.size();j++)
            {
                //检查另外一棵树该层所有目前没有匹配的节点，若其父节点一致并且两节点的唯一编码一致，则认为其是同构节点
                int parNode2 = checkNodeExist(tree2[t2[j]].parNode[0].name, tree2);
                if(tree2[t2[j]].isoCode == "" && tree1[t1[i]].code == tree2[t2[j]].code && tree1[parNode].isoCode == tree2[parNode2].isoCode)
                {
                    tree1[t1[i]].isoCode = to_string(isoCount);
                    tree2[t2[j]].isoCode = to_string(isoCount);
                    isoCount++;
                    break;
                }
            }
        }
    }
}
//------------------------------------------------------------------------------------

//----------------------------返回同构节点索引-----------------------------------------
int TreeIso::getIsoNode(string isocode, vector<TreeNode> tree)
{ 
    for(int i=0;i<tree.size();i++)
    {
        if(tree[i].isoCode == isocode)
        {
            return i;
        }
    }
    return -1;
}
//-----------------------------------------------------------------------------------

//--------------------------------------回调函数--------------------------------------
void button_cb(Fl_Widget* w, void* p )
{
    w->color(FL_RED);
    cout<<"clicked label::"<<w->label()<<endl;
    ((Fl_Button*)p)->color(FL_YELLOW);
    cout<<"iso label::"<<((Fl_Button*)p)->label()<<endl;
    buttonpushed = true;
    Fl::redraw();
}

void quit_cb(Fl_Widget* w, void*)
{
    exit(0);
}

void clear_cb(Fl_Widget* w, void* p)
{
    Fl_Group* g = (Fl_Group*)p;
    for(int i=0;i<num;i++)
    {
        g->child(i)->color(FL_BACKGROUND_COLOR);
    }
    buttonpushed = true;
    Fl::redraw();
}
//------------------------------------------------------------------------------------

//----------------------------重塑树的布局（可视化美化）--------------------------------
void TreeIso::reshapeTree(vector<TreeNode> &tree, int root)
{
   
    for(int i=1;i<=levelCount1;i++)
    {
        vector<int> tnode;
        vector<int> xcordinate;
        //逐层遍历检查
        for(int j=0;j<tree.size();j++)
        {
            if(tree[j].level == i)
            {
                tnode.push_back(j);
                xcordinate.push_back(tree[j].coor.first);
            }
        }
        //按照质心坐标顺序进行排序
        int levelnum = xcordinate.size();
        for(int j =0;j<levelnum;j++)
        {
            int maxindex = 0;
            for(int k=0;k<levelnum-j;k++)
            {
                if(xcordinate[k]>xcordinate[maxindex])
                {
                    maxindex = k;
                }
            }
            int tmp1 = xcordinate[maxindex];
            int tmp2 = tnode[maxindex];
            xcordinate[maxindex] = xcordinate[levelnum-j-1];
            tnode[maxindex] = tnode[levelnum-j-1];
            xcordinate[levelnum-j-1] = tmp1;
            tnode[levelnum-j-1] = tmp2;
        }
        //检查该层所有节点，是否存在按钮宽度过窄节点
        int minButtonW =20;
        bool reshapeflag = false;
        for(int k=0;k<tnode.size();k++)
        {
            if(tree[tnode[k]].buttonw<15)
            {
                int pre = 0;
                if(k>0)
                {
                    pre = tree[tnode[k-1]].coor.first + 5 + tree[tnode[k-1]].buttonw/2;
                }
                else
                {
                    pre = tree[root].range.first;
                }
                tree[tnode[k]].coor.first = pre+minButtonW/2;
                //对于其之后的第一个按钮，如果其变宽后按钮存在重叠，则将其后所有按钮向右平移
                if(k+1<tnode.size() && (tree[tnode[k+1]].coor.first-tree[tnode[k+1]].buttonw/2) < (tree[tnode[k]].coor.first+minButtonW/2))
                {
                    for(int l =k+1;l<tnode.size();l++)
                    {
                        tree[tnode[l]].coor.first += 15;
                    }
                }
                tree[tnode[k]].buttonw = minButtonW;
                
            }
        }
    }
}

//---------------------------------可视化------------------------------------------
void TreeIso::visualization()
{
    num = tree1.size();
    //-------------------基本布局---------------------
    Point p(100,100);           
    Simple_window win(p,1600,1000,"Canvas");
    //tree1图标
    Graph_lib::Rectangle legend1(Point(50, 50), 100, 40);
    legend1.set_color(Color::yellow);
    legend1.set_fill_color(Color::yellow);
    win.attach(legend1);
    Text name1(Point(67, 77), "Tree1");
    name1.set_font_size(22);
    win.attach(name1); 
    //tree2图标
    Graph_lib::Rectangle legend2(Point(850, 50), 100, 40);
    legend2.set_color(Color::yellow);
    legend2.set_fill_color(Color::yellow);
    win.attach(legend2);
    Text name2(Point(867, 77), "Tree2");
    name2.set_font_size(22);
    win.attach(name2); 
    //退出按钮
    win.begin();
    Fl_Widget* QuitButton = new Fl_Button(1400, 10, 100, 40, "Exit");
    QuitButton->callback(quit_cb, (void*)QuitButton);
    //清除颜色按钮
    Fl_Widget* ClearButton = new Fl_Button(1000, 10, 150, 40, "Clear Tree1");
    Fl_Widget* ClearButton2 = new Fl_Button(1200, 10, 150, 40, "Clear Tree2");
    win.end();
    //-----------------------------树1布局-----------------------------

    int maxButtonW = 100;
    int minInterval = 800;

    tree1[root1].coor.second = 200;
    tree1[root1].coor.first = 400;
    tree1[root1].range.first = 10;
    tree1[root1].range.second = 790;
    tree1[root1].buttonw = maxButtonW;
    stack<int> stk;
    stk.push(root1);
    while(!stk.empty())
    {
        TreeNode tmp = tree1[stk.top()];
        stk.pop();
        int rangelen = tmp.range.second-tmp.range.first;
        if(minInterval > rangelen)
        {
            minInterval = rangelen;
        }
        int subNodeNum = tmp.subNode.size();
        for(int i=0;i<subNodeNum;i++)//对于其每个子节点,计算其质心坐标和区间，并将其入栈
        {
            int indextmp = checkNodeExist(tmp.subNode[i].name,tree1);
            stk.push(indextmp);
            tree1[indextmp].range.first = tmp.range.first + i * rangelen/subNodeNum;
            tree1[indextmp].range.second = tree1[indextmp].range.first + rangelen/subNodeNum;
            tree1[indextmp].coor.first = tree1[indextmp].range.first + (rangelen/subNodeNum)/2;
            tree1[indextmp].coor.second = 200 + (tree1[indextmp].level-1)*100;
            int buttonw = 0.95*(tree1[indextmp].range.second-tree1[indextmp].range.first);
            //重塑
            if(buttonw > maxButtonW)
            {
                tree1[indextmp].buttonw = maxButtonW;
            }
            else
            {
                tree1[indextmp].buttonw = buttonw;
            }
        }
    }
    //树1重塑
    reshapeTree(tree1,root1);

    //将树1的节点连线
    win.begin();
    for(int i=0;i<tree1.size();i++)
    {
        for(int j =0;j<tree1[i].subNode.size();j++){
            int x1 = tree1[i].coor.first;
            int y1 = tree1[i].coor.second;
            int x2 = tree1[checkNodeExist(tree1[i].subNode[j].name, tree1)].coor.first;
            int y2 = tree1[checkNodeExist(tree1[i].subNode[j].name, tree1)].coor.second;
            Line* l = new Line(Point(x1,y1), Point(x2, y2));
            win.attach(*l);
        }
    }
    win.end();
    //将树1的节点附加在窗口上
    win.begin();
    Fl_Group *Group1 = new Fl_Group(0,0, 800, 1000, "\0");
    for(int i=0;i<tree1.size();i++)
    {
        TreeNode tmp = tree1[i];
        Fl_Button* button = new Fl_Button(tmp.coor.first-tmp.buttonw/2,tmp.coor.second-20, tmp.buttonw, 40, tmp.name.c_str());
        Group1->insert(*button,i);
    }
    Group1->end();
    win.end();
    //按钮名称需要重新覆盖一次，否则全部为该循环最后一次赋值的名称
    for(int i=0;i<tree1.size();i++)
    {
        Group1->child(i)->label(tree1[i].name.c_str());
    }
   
    //----------------------------------树2布局---------------------------------------
    minInterval = 800;

    tree2[root2].coor.second = 200;
    tree2[root2].coor.first = 1185;
    tree2[root2].range.first = 810;
    tree2[root2].range.second = 1560;
    tree2[root2].buttonw = maxButtonW;
    stk.push(root2);
    while(!stk.empty())
    {
        TreeNode tmp = tree2[stk.top()];
        stk.pop();
        int rangelen = tmp.range.second-tmp.range.first;
        if(minInterval > rangelen)
        {
            minInterval = rangelen;
        }
        int subNodeNum = tmp.subNode.size();
        for(int i=0;i<subNodeNum;i++)//对于其每个子节点,计算其质心坐标和区间，并将其入栈
        {
            int indextmp = checkNodeExist(tmp.subNode[i].name,tree2);
            stk.push(indextmp);
            tree2[indextmp].range.first = tmp.range.first + i * rangelen/subNodeNum;
            tree2[indextmp].range.second = tree2[indextmp].range.first + rangelen/subNodeNum;
            tree2[indextmp].coor.first = tree2[indextmp].range.first + (rangelen/subNodeNum)/2;
            tree2[indextmp].coor.second = 200 + (tree2[indextmp].level-1)*100;
            int buttonw = 0.95*(tree2[indextmp].range.second-tree2[indextmp].range.first);
            if(buttonw>maxButtonW)
            {
                tree2[indextmp].buttonw = maxButtonW;
            }
            else
            {
                tree2[indextmp].buttonw = buttonw;
            }
        }
    }
    //树2重塑
    reshapeTree(tree2,root2);

    //将树2的节点连线
    for(int i=0;i<tree2.size();i++)
    {
        for(int j =0;j<tree2[i].subNode.size();j++){
            int x1 = tree2[i].coor.first;
            int y1 = tree2[i].coor.second;
            int x2 = tree2[checkNodeExist(tree2[i].subNode[j].name, tree2)].coor.first;
            int y2 = tree2[checkNodeExist(tree2[i].subNode[j].name, tree2)].coor.second;
            Line* l = new Line(Point(x1,y1), Point(x2, y2));
            win.attach(*l);
        }
    }
    
    
    //将树2的节点附加在窗口上
    win.begin();
    Fl_Group *Group2 = new Fl_Group(800,0, 800, 1000, "\0");
    for(int i=0;i<tree2.size();i++)
    {
        TreeNode tmp = tree2[i];
        Fl_Button* button = new Fl_Button(tmp.coor.first-tmp.buttonw/2,tmp.coor.second-20, tmp.buttonw, 40, tmp.name.c_str());
        //button->callback(button_cb, (void*)button);
        Group2->insert(*button, i);
    }
    Group2->end();
    win.end();
    //按钮名称需要重新覆盖一次，否则全部为该循环最后一次赋值的名称
    for(int i=0;i<tree2.size();i++)
    {
        Group2->child(i)->label(tree2[i].name.c_str());
    }
    
    //-------------------------若同构将同构树的匹配按钮之间进行链接----------------------
    if(isoflag)
    {
        for(int i=0;i<tree1.size();i++)
        {
            string currNodeName(Group1->child(i)->label());
            int currIndex = checkNodeExist(currNodeName, tree1);
            int isoIndex = getIsoNode(tree1[currIndex].isoCode, tree2);
            (Group1->child(i))->callback(button_cb, (void*)(Group2->child(isoIndex)));
        }
        for(int i=0;i<tree2.size();i++)
        {
            string currNodeName(Group2->child(i)->label());
            int currIndex = checkNodeExist(currNodeName, tree2);
            int isoIndex = getIsoNode(tree2[currIndex].isoCode, tree1);
            (Group2->child(i))->callback(button_cb, (void*)(Group1->child(isoIndex)));
        }
    }

    //----------------------------------设置清空-------------------------------------
    ClearButton->callback(clear_cb, (void*)Group1);
    ClearButton2->callback(clear_cb, (void*)Group2);
    //-----------------------------------事件循环-------------------------------------
    
    Fl::run();
    while(1){
    while(buttonpushed = false)
    {
        Fl::wait();
    }
    buttonpushed = false;
    }
}


void TreeIso::getLevel()
{
    //----------------------------------安排树1的布局-------------------------------------------
    //需要逐层遍历确定每一层的节点个数以及总层数
    stack<int> stk;
    tree1[root1].level = 1;
    for(int i=0;i<tree1[root1].subNode.size();i++)
    {
        stk.push( checkNodeExist(tree1[root1].subNode[i].name, tree1));
    }
    while(!stk.empty())
    {
        int index = stk.top();
        stk.pop();
        TreeNode tmp = tree1[index];
        int parlevel = tree1[checkNodeExist(tmp.parNode[0].name,tree1)].level;
        tree1[checkNodeExist(tmp.name,tree1)].level = parlevel + 1;
        if (levelCount1 < parlevel +1)
        {
            levelCount1 = parlevel + 1;
        }
        for(int i=0;i<tmp.subNode.size();i++)
        {
            stk.push(checkNodeExist (tmp.subNode[i].name, tree1));
        }
    }

    //----------------------------------安排树2的布局-------------------------------------------
    stack<int> stk2;
    tree2[root2].level = 1;
    for(int i=0;i<tree2[root2].subNode.size();i++)
    {
        stk2.push( checkNodeExist(tree2[root2].subNode[i].name, tree2));
    }
    while(!stk2.empty())
    {
        int index = stk2.top();
        stk2.pop();
        TreeNode tmp = tree2[index];
        int parlevel = tree2[checkNodeExist(tmp.parNode[0].name,tree2)].level;
        tree2[checkNodeExist(tmp.name,tree2)].level = parlevel + 1;
        if (levelCount2 < parlevel +1)
        {
            levelCount2 = parlevel + 1;
        }
        for(int i=0;i<tmp.subNode.size();i++)
        {
            stk2.push(checkNodeExist (tmp.subNode[i].name, tree2));
        }
    }
}

void TreeIso::IsoTree()
{
    getInput();
    assignCode(tree1, root1);
    assignCode(tree2, root2);
    checkTreeSingleParent();
    if(!errorflag0 && !errorflag1 && !errorflag2)
    {   
        isoflag = checkIso();
        getLevel();
        if(isoflag) matchIsoNode();
        visualization();
    }
    else
    {
        if(errorflag0) cout<<"Open file failed."<<endl;
        if(errorflag1) cout<<"Illigal input."<<endl;
        if(errorflag2) cout<<"Not a tree."<<endl;
    }
}