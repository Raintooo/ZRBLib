#ifndef QUEEN_H
#define QUEEN_H

namespace ZRBLib
{
template <int SIZE>
class Queen : public Object
{
    enum { N = SIZE + 2};
    struct Pos : public Object
    {
        Pos(int _x = 0, int _y = 0) : x(_x), y(_y){ }
        int x;
        int y;
    };

    int m_chessboard[N][N];
    Pos m_direction[3];
    int m_count;
    LinkList<Pos> m_list;

    void init()
    {
        m_count = 0;

        for(int i = 0; i < N; i+=N-1)
        {
            for(int j = 0; j < N; j++)
            {
                m_chessboard[i][j] = 2;
                m_chessboard[j][i] = 2;
            }
        }
        for(int i = 1; i <= SIZE; i++)
        {
            for(int j = 1; j <= SIZE; j++)
            {
                m_chessboard[i][j] = 0;
            }
        }

        m_direction[0].x =-1;
        m_direction[0].y =-1;
        //向下
        m_direction[1].x =0;
        m_direction[1].y =-1;
        //右下角
        m_direction[2].x =1;
        m_direction[2].y =-1;
    }

    void print()
    {
        for(m_list.move(0); !m_list.end(); m_list.next())
        {
            cout<< "( "<< m_list.current().x<< ","<< m_list.current().y<< " )  ";
        }
        cout<< endl;
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < N; j++)
            {
                switch (m_chessboard[i][j])
                {
                    case 0: cout<< "  "; break;
                    case 1: cout<< "# "; break;
                    case 2: cout<< "* "; break;
                    default: break;
                }
            }
            cout<< endl;
        }
    }

    bool check(int x, int y, int dir)
    {
        bool flag = true;

        do
        {
            x += m_direction[dir].x;
            y += m_direction[dir].y;
            flag = flag && (m_chessboard[x][y] == 0);
        }while(flag);

        bool ret = (m_chessboard[x][y] == 2);
        return ret;
    }

    void run(int j)
    {
        if(j <= SIZE)
        {
            for(int i = 1; i <= SIZE; i++)
            {
                if(check(i, j, 0) && check(i, j, 1) && check(i, j, 2))
                {
                    m_chessboard[i][j] = 1;
                    m_list.insert(Pos(i , j));

                    run(j + 1);

                    m_chessboard[i][j] = 0;
                    m_list.remove(m_list.length() - 1);
                }
            }
        }
        else
        {
            m_count++;
            print();
        }
    }

public:
    Queen()
    {
        init();
    }
    void run()
    {
        run(1);
        cout<< "Total "<< m_count<< endl;
    }
};
}

#endif // QUEEN_H
