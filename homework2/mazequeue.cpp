//
//  mazequeue.cpp
//  homework2
//
//  Created by Izma Zuberi on 4/23/22.
//

 #include <queue>

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
     std::queue<Coord> coordqueue;
     
     Coord c(sr, sc);
     coordqueue.push(c);
     maze[sr][sc] = '#';
     
     while(coordqueue.size() != 0)
     {
         Coord current = coordqueue.front();
         coordqueue.pop();
         
         if(current.r() == er && current.c() == ec)
             return true;
         if (maze[current.r()][current.c() - 1] == '.')
         {
             Coord w(current.r(), current.c() - 1);
             coordqueue.push(w);
             maze[current.r()][current.c() - 1] = '#';
         }
         if (maze[current.r() - 1][current.c()] == '.')
         {
             Coord n(current.r() - 1, current.c());
             coordqueue.push(n);
             maze[current.r() - 1][current.c()] = '#';
         }
         if (maze[current.r()][current.c() + 1] == '.')
         {
             Coord e(current.r(), current.c() + 1);
             coordqueue.push(e);
             maze[current.r()][current.c() + 1] = '#';
         }
         if (maze[current.r() + 1][current.c()] == '.')
         {
             Coord s(current.r() + 1, current.c());
             coordqueue.push(s);
             maze[current.r() + 1][current.c()] = '#';
         }
     }

     return false;
 }

