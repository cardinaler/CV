#include <iostream>
using namespace std;

const int N = 8;

#define black_pawn_step(X, Y, X1, Y1) (X1 == X && (Y1 - Y) == 1)

#define white_pawn_step(X, Y, X1, Y1) (X1 == X && (Y1 - Y) == -1)

#define knight_step(X, Y, X1, Y1) ((abs(X1 - X) == 1 && abs(Y1 - Y) == 2) || (abs(X1 - X) == 2 && abs(Y1 - Y) == 1))

#define bishop_step(X, Y, X1, Y1) (abs(X1 - X) == abs(Y1 - Y))

#define rook_step(X, Y, X1, Y1) (X1 == X || Y1 == Y)

#define King_step(X, Y, X1, Y1) (abs(X1 - X) <= 1 && abs(Y1 - Y) <= 1)

#define queen_step(X, Y, X1, Y1) (abs(X1 - X) == abs(Y1 - Y) || (X1 == X || Y1 == Y) || abs(X1 - X) <= 1 && abs(Y1 - Y) <= 1)

#define black_pawn_eat(X, Y, X1, Y1) (abs(X1 - X) == 1 && (Y1 - Y) == 1)

#define white_pawn_eat(X, Y, X1, Y1) (abs(X1 - X) == 1 && (Y1 - Y) == -1)

#define black_pawn(X, Y) new (struct piece)(piece(X, Y, "♟︎", 'b'))
#define white_pawn(X, Y) new (struct piece)(piece(X, Y, "♙", 'w'))
#define black_knight(X, Y) new (struct piece)(piece(X, Y, "♞", 'b'))
#define white_knight(X, Y) new (struct piece)(piece(X, Y, "♘", 'w'))
#define black_bishop(X, Y) new (struct piece)(piece(X, Y, "♝", 'b'))
#define white_bishop(X, Y) new (struct piece)(piece(X, Y, "♗", 'w'))
#define black_rook(X, Y) new (struct piece)(piece(X, Y, "♜", 'b'))
#define white_rook(X, Y) new (struct piece)(piece(X, Y, "♖", 'w'))
#define black_queen(X, Y) new (struct piece)(piece(X, Y, "♛", 'b'))
#define white_queen(X, Y) new (struct piece)(piece(X, Y, "♕", 'w'))
#define black_king(X, Y) new (struct piece)(piece(X, Y, "♚", 'b'))
#define white_king(X, Y) new (struct piece)(piece(X, Y, "♔", 'w'))

#define CELL_IS_CORRECT(a1, b1) ((a1 <= 'h' && a1 >= 'a') && (b1 <= 8 && b1 >= 1))

#define EXIT 0
#define ADD_FIGURE 1
#define REMOVE_FIGURE 2
#define PLAY 3
#define ADD_SET 4
#define READY 1
#define NO 0
#define YES 1
#define MAKE_STEP 1
#define True 1

bool can_add_set = NO;
bool can_play = NO;
bool can_remove_figure = NO;
struct piece *set[N * N / 2];

struct piece
{
    int x;
    int y;
    string name;
    char color;
    piece(int x1, int y1, string name1, char color1) : x(x1 - 'a'), y(N - y1), name(name1), color(color1) {}
    bool white_pawn_step_(int x, int y, int x1, int y1);
    bool step(int x1, int y1)
    {

        if ((name == "♙") && !(white_pawn_step(x, y, x1, y1) || white_pawn_eat(x, y, x1, y1)) ||
            (name == "♟︎") && !(black_pawn_step(x, y, x1, y1) || black_pawn_eat(x, y, x1, y1)) ||
            (name == "♘" || name == "♞") && !knight_step(x, y, x1, y1) ||
            (name == "♗" || name == "♝") && !bishop_step(x, y, x1, y1) ||
            (name == "♖" || name == "♜") && !rook_step(x, y, x1, y1) ||
            (name == "♔" || name == "♚") && !King_step(x, y, x1, y1) ||
            (name == "♕" || name == "♛") && !queen_step(x, y, x1, y1))
        {
            return 0;
        }
        x = x1;
        y = y1;
        return 1;
    }
};

// Описать ходы
// Deskcribe destructor
struct Desk
{
    struct piece *figure[N][N];
    Desk()
    {
        set_to_null_figures();
    }
    void add_figure(struct piece *figure);
    void remove_figure(int a, int b);
    void add_set(struct piece *set[]);
    void set_to_null_figures(void);
    void print_desk(void);
    void step(int x1, int y1, int x2, int y2);
};

void Desk::remove_figure(int a, int b)
{
    a = a - 'a';
    b = N - b;
    if (figure[b][a] != NULL)
    {
        delete (figure[b][a]);
        figure[b][a] = NULL;
    }
}

void Desk::add_figure(struct piece *fig)
{
    int a, b;
    a = fig->y;
    b = fig->x;
    if (figure[a][b] != NULL)
    {
        throw "fdf";
    }
    figure[a][b] = fig;
}

void Desk::add_set(struct piece *set[])
{
    int a, b;
    for (int i = 0; set[i] != NULL; ++i)
    {
        add_figure(set[i]);
    }
}

void Desk::set_to_null_figures(void)
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            figure[i][j] = NULL;
        }
    }
}

void Desk::print_desk(void)
{
    for (int i = 0; i < N; ++i)
    {
        cout << N - i << ' ';
        for (int j = 0; j < N; ++j)
        {
            if (figure[i][j] == NULL)
            {
                if ((i + j) % 2)
                    cout << "\033[0;41m"
                         << "  \033[0m"; // white color
                else
                    cout << "\033[0;47m"
                         << "  \033[0m"; // red color
            }
            else
            {
                string name = figure[i][j]->name;
                if ((i + j) % 2)
                {
                    cout << "\033[41;30m" << name << " \033[0m"; // black on white color
                }
                else
                    cout << "\033[47;30m" << name << " \033[0m"; // black on red color
            }
        }
        cout << endl;
    }
    cout << "  ";
    for (int i = 0; i < N; ++i)
    {
        cout << char('a' + i) << ' ';
    }
    cout << "\n\n";
}

void Desk::step(int x1, int y1, int x2, int y2)
{
    int a, b, c, d;
    a = N - y1;
    b = x1 - 'a';
    c = N - y2;
    d = x2 - 'a';
    if (figure[a][b] == NULL || !figure[a][b]->step(d, c))
    {
        throw "incorrect step";
    }
    if (figure[a][b]->name == "♙")
    {
        if (white_pawn_eat(b, a, d, c) && figure[c][d] == NULL || white_pawn_step(b, a, d, c) && figure[c][d] != NULL)
            throw "step fail";
    }
    else if (figure[a][b]->name == "♟︎")
    {
        if (black_pawn_eat(b, a, d, c) && figure[c][d] == NULL || black_pawn_step(b, a, d, c) && figure[c][d] != NULL)
            throw "step fail";
    }
    if (figure[c][d] == NULL)
    {
        figure[c][d] = figure[a][b];
        figure[a][b] = NULL;
    }
    else
    {
        if (figure[a][b]->color == figure[c][d]->color || figure[c][d]->name == "♔" || figure[c][d]->name == "♚") // same colors or trying to eat king
            throw "step fail";
        else // eated
        {
            delete (figure[c][d]);
            figure[c][d] = figure[a][b];
            figure[a][b] = NULL;
        }
    }
}

void welcome_window(void)
{
    int action;
    cout << "Welcome to the chess simulator!" << endl;
    cout << "Choose an action:" << endl;
    cout << "0:  Exit\n";
    cout << "1:  Start\n";
    while (True)
    {
        cin >> action;
        if (action == 1)
        {
            break;
        }
        else if (action == EXIT)
        {
            cout << "Goodbye!\n";
            exit(0);
        }
        else
        {
            cout << "Invalid action. Please try again.\n";
        }
    }
}

void add_figures_window(void)
{
    cout << "Choose an action:" << endl;
    cout << "0: Exit\n";
    cout << "1: Add figure\n";
    cout << "2: Remove figure\n";
    if (can_play)
        cout << "3: Play\n";
    if (can_add_set)
        cout << "4: Add set\n";
}

int user_choose(void)
{
    int action;
    while (True)
    {
        cin >> action;
        if (action == ADD_FIGURE)
        {
            can_add_set = NO;
            can_play = YES;
            return ADD_FIGURE;
        }
        else if (action == REMOVE_FIGURE)
        {
            return REMOVE_FIGURE;
        }
        else if (action == EXIT)
        {
            return EXIT;
        }
        else if (can_add_set && (action == ADD_SET))
        {
            can_add_set = NO;
            can_play = YES;
            return ADD_SET;
        }
        else if (can_play && (action == PLAY))
        {
            return PLAY;
        }
        else
        {
            cout << "Invalid choose. Try again\n";
            continue;
        }
    }
}

struct piece *user_figure_choose(int a, int b)
{
    int figure = 0;
    while (True)
    {
        cin >> figure;
        if (figure < 1 || figure > 12)
            cout << "Invalid input. Try again\n";
        else
            break;
    }

    switch (figure)
    {
    case 1:
        return white_pawn(a, b);
    case 2:
        return black_pawn(a, b);
    case 3:
        return white_knight(a, b);
    case 4:
        return black_knight(a, b);
    case 5:
        return white_bishop(a, b);
    case 6:
        return black_bishop(a, b);
    case 7:
        return white_rook(a, b);
    case 8:
        return black_rook(a, b);
    case 9:
        return white_queen(a, b);
    case 10:
        return black_queen(a, b);
    case 11:
        return white_king(a, b);
    case 12:
        return black_king(a, b);
    }
    return 0;
}

void handle_figure_action(int action, struct Desk *desk)
{
    string cell;
    int a, b, status;
    status = !READY;
    if (action == ADD_FIGURE || action == REMOVE_FIGURE)
    {
        while (status != READY)
        {
            cout << "Input cell:\n";
            cin >> cell;
            if (cell.size() != 2)
            {
                cout << "Invalid input. Try again\n";
                continue;
            }
            a = cell[0];
            b = cell[1] - '0';
            if (!CELL_IS_CORRECT(a, b))
            {
                cout << "Invalid input. Try again\n";
                continue;
            }
            if (desk->figure[N - b][a - 'a'] != NULL && action == ADD_FIGURE)
            {
                cout << "Sorry, it is busy here. Try again\n";
            }
            else if (desk->figure[N - b][a - 'a'] == NULL && action == REMOVE_FIGURE)
            {
                cout << "Sorry, there is not any figures. Try again\n";
                status = READY;
            }
            else
            {
                if (action == ADD_FIGURE)
                {
                    cout << "1  2  3  4  5  6  7  8  9  10  11  12\n";
                    cout << "♙  ♟  ♘  ♞  ♗  ♝  ♖  ♜  ♕  ♛   ♔   ♚\n";
                    desk->add_figure(user_figure_choose(a, b));
                }
                else
                {
                    desk->remove_figure(a, b);
                }
                status = READY;
            }
        }
    }
    else if (action == ADD_SET)
    {
        desk->add_set(set);
    }
    else if (action == EXIT)
    {
        cout << "Goodbye\n";
        exit(0);
    }
}

int user_step_choose(void)
{
    int action;
    cout << "Choose, please.\n";
    cout << "0: Exit\n";
    cout << "1: Make step\n";
    while (True)
    {
        cin >> action;
        if (action == EXIT || action == MAKE_STEP)
            return action;
        else
            cout << "Invalid input. Try again\n";
    }
}

void handle_step_action(int action, struct Desk *desk)
{
    if (action == MAKE_STEP)
    {
        int a1, b1, a2, b2;
        bool not_correct = YES;
        string step_str;
        cout << "Input your step. For example a4:b1\n";
        cin >> step_str;
        if (step_str.size() == 5)
        {
            a1 = step_str[0];
            b1 = step_str[1] - '0';
            a2 = step_str[3];
            b2 = step_str[4] - '0';
            if (CELL_IS_CORRECT(a1, b1) && CELL_IS_CORRECT(a2, b2))
                desk->step(a1, b1, a2, b2);
            else
                cout << "Invalid step. Try again\n";
        }
        else
        {
            cout << "Invalid step. Try again\n";
        }
    }
    else if (action == EXIT)
    {
        cout << "Goodbye\n";
        exit(0);
    }
}

using namespace std;
int main()
{
    int action = !PLAY;
    set[0] = black_pawn('c', 5);
    set[1] = white_pawn('d', 4);
    set[2] = black_pawn('c', 4);
    set[3] = white_pawn('d', 3);
    set[4] = NULL;
    can_add_set = YES;

    welcome_window();
    Desk desk;
    desk.print_desk();
    while (action != PLAY)
    {
        add_figures_window();
        action = user_choose();
        handle_figure_action(action, &desk);
        desk.print_desk();
    }
    // action == PLAY
    while (True)
    {
        try
        {
            action = user_step_choose();
            handle_step_action(action, &desk);
            desk.print_desk();
        }
        catch (const char *s)
        {
            cout << s << endl;
        }
    }
}
