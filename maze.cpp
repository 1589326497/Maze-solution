/*
    �����Թ�2023/4/26���
*/
#include <iostream>
using namespace std;
#include<stack>
#include<vector>
#include<algorithm>
//������
typedef struct Postion
{
    int row;
    int col;
}PT;
stack<PT> st;
stack<PT> minst;
//���ջ�������
void PrintPath(stack<PT>& st)
{
    //������ʱ��������������ջ���Ԫ��
    vector<PT> temp;
    //��ջ���Ԫ��ת�Ƶ�temp��
    while (!st.empty())
    {
        temp.push_back(st.top());
        st.pop();
    }

    //��ӡtemp
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
    //cur��ջ
    st.push(cur);
    if (cur.row == 0 && cur.col == m - 1)
    {
        //�ҵ��˸��̵�·��������minst
        if (p>=0 && minst.empty() || st.size() < minst.size())
        {
            //stack�����ײ�������
            minst = st;
        }
    }

    //̽��cur���������ĸ�����
    PT next;
    maze[cur.row][cur.col] = 2;
    //��
    next = cur;
    next.row -= 1;
    //�ж��Ƿ����ͨ
    if (IsPass(maze, n, m, next))
    {
        GetMazePath(maze, n, m, next, p - 3);
    }
    //��
    next = cur;
    next.row += 1;
    if (IsPass(maze, n, m, next))
    {
        GetMazePath(maze, n, m, next, p);

    }
    //��
    next = cur;
    next.col -= 1;
    if (IsPass(maze, n, m, next))
    {
        GetMazePath(maze, n, m, next, p - 1);

    }
    //�� 
    next = cur;
    next.col += 1;
    if (IsPass(maze, n, m, next))
    {
        GetMazePath(maze, n, m, next, p - 1);
    }
    //û��·�˳�ջ
    maze[cur.row][cur.col] = 1;
    st.pop();
}
int main()
{
    int n = 0, m = 0;
    int p = 0;
    cin >> n >> m >> p;
    //���ٶ�ά����
    int** maze = new int* [n];
    for (int i = 0; i < n; i++)
    {
        maze[i] = new int[m];
    }
    //�����ά����
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> maze[i][j];
        }
    }
    //��ʼ�Թ�
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