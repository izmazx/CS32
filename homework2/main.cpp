//
//  main.cpp
//  homework2
//
//  Created by Izma Zuberi on 4/22/22.
//
/*
#include <iostream>
#include <stack>

class Coord
{
  public:
    Coord(int rr, int cc) : m_row(rr), m_col(cc) {}
    int r() const { return m_row; }
    int c() const { return m_col; }
  private:
    int m_row;
    int m_col;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    std::stack<Coord> coordstack;
    
    Coord c(sr, sc);
    coordstack.push(c);
    maze[sr][sc] = '#';
    
    while(coordstack.size() != 0)
    {
        Coord current = coordstack.top();
        coordstack.pop();

        if(current.r() == er && current.c() == ec)
            return true;
        if (maze[current.r()][current.c() - 1] == '.')
        {
            Coord w(current.r(), current.c() - 1);
            coordstack.push(w);
            maze[current.r()][current.c() - 1] = '#';
        }
        if (maze[current.r() - 1][current.c()] == '.')
        {
            Coord n(current.r() - 1, current.c());
            coordstack.push(n);
            maze[current.r() - 1][current.c()] = '#';
        }
        if (maze[current.r()][current.c() + 1] == '.')
        {
            Coord e(current.r(), current.c() + 1);
            coordstack.push(e);
            maze[current.r()][current.c() + 1] = '#';
        }
        if (maze[current.r() + 1][current.c()] == '.')
        {
            Coord s(current.r() + 1, current.c());
            coordstack.push(s);
            maze[current.r() + 1][current.c()] = '#';
        }
    }
    return false;
}



int main()
{
    char mazex[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X' }, //0
        { 'X','.','X','.','.','.','X','.','.','X' }, //1
        { 'X','.','X','.','X','X','X','X','.','X' }, //2
        { 'X','.','X','.','.','X','.','X','.','X' }, //3
        { 'X','.','X','X','.','X','.','.','.','X' }, //4
        { 'X','.','.','.','.','.','.','X','X','X' }, //5
        { 'X','.','X','X','X','X','.','X','.','X' }, //6
        { 'X','.','.','.','.','X','X','X','.','X' }, //7
        { 'X','.','X','.','.','X','.','.','.','X' }, //8
        { 'X','X','X','X','X','X','X','X','X','X' }  //9
        // 0   1   2   3   4   5   6   7   8   9
    };

    if (pathExists(mazex, 5,6, 8,1))
        std::cout << "Solvable!" << std::endl;
    else
        std::cout << "Out of luck!" << std::endl;
    
}
*/
