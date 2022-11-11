//
//  History.h
//  project1
//
//  Created by Izma Zuberi on 4/3/22.
//

#ifndef History_h
#define History_h
#include "globals.h"

class History
    {
      public:
        History(int nRows, int nCols);
        bool record(int r, int c);
        void display() const;
    private:
        int rows;
        int cols;
        int grid[MAXROWS][MAXCOLS];
    };

#endif /* History_h */
