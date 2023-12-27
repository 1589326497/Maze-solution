/*
    地下迷宫2023/4/26完成
*/
#include <iostream>
using namespace std;
#include<stack>
#include<vector>
#include<algorithm>
//坐标类
typedef struct Postion
{
    int row;
    int col;
}PT;
stack<PT> st;
stack<PT> minst;
//输出栈里的坐标
void PrintPath(stack<PT>& st)
{
    //创建临时容器，用来接收栈里的元素
    vector<PT> temp;
    //将栈里的元素转移到temp中
    while (!st.empty())
    {
        temp.push_back(st.top());
        st.pop();
    }

    //打印temp
    int i = temp.size();
    while (i > 1)
    {
        cout << "[" << temp.at(i-1).row << "," << temp.at(i-1).col << "]" << ",";
        i--;
    }
    cout << "[" << temp.at(0).row << "," << temp.at(0).col << "]";


}
bool IsPass(int** maze, int n, int m, PT pos)
{
    if (pos.row >= 0 && pos.row < n
        && pos.col >= 0 && pos.col < m
        && maze[pos.row][pos.col] == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void GetMazePath(int** maze, int n, int m, PT cur, int p)
{
    //cur入栈
    st.push(cur);
    if (cur.row == 0 && cur.col == m - 1)
    {
        //找到了更短的路径，更新minst
        if (p>=0 && minst.empty() || st.size() < minst.size())
        {
            //stack容器底层就是深拷贝
            minst = st;
        }
    }

    //探测cur上下左右四个方向
    PT next;
    maze[cur.row][cur.col] = 2;
    //上
    next = cur;
    next.row -= 1;
    //判断是否可以通
    if (IsPass(maze, n, m, next))
    {
        GetMazePath(maze, n, m, next, p - 3);
    }
    //下
    next = cur;
    next.row += 1;
    if (IsPass(maze, n, m, next))
    {
        GetMazePath(maze, n, m, next, p);

    }
    //左
    next = cur;
    next.col -= 1;
    if (IsPass(maze, n, m, next))
    {
        GetMazePath(maze, n, m, next, p - 1);

    }
    //右 
    next = cur;
    next.col += 1;
    if (IsPass(maze, n, m, next))
    {
        GetMazePath(maze, n, m, next, p - 1);
    }
    //没有路了出栈
    maze[cur.row][cur.col] = 1;
    st.pop();
}
int main()
{
    int n = 0, m = 0;
    int p = 0;
    cin >> n >> m >> p;
    //开辟二维数组
    int** maze = new int* [n];
    for (int i = 0; i < n; i++)
    {
        maze[i] = new int[m];
    }
    //输入二维数组
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> maze[i][j];
        }
    }
    //开始迷宫
    PT entry = { 0,0 };
    GetMazePath(maze, n, m, entry, p);
    if (!minst.empty())
    {
        PrintPath(minst);
    }
    else
    {
        cout << "Can not escape!" << endl;
    }
    

    for (int i = 0; i < n; i++)
    {
        delete[] maze[i];
    }
    delete[] maze;
    maze = NULL;
    return 0;

}