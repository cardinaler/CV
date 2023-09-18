#include <iostream>
#include <cstring>
using namespace std;

enum type_of_lex
{
    LEX_NULL,      // 0
    LEX_AND,       // 1
    LEX_LCPAREN,   // 2
    LEX_BOOL,      // 3
    LEX_DO,        // 4
    LEX_ELSE,      // 5
    LEX_RCPAREN,   // 6
    LEX_IF,        // 7
    LEX_FALSE,     // 8
    LEX_INT,       // 9
    LEX_NOT,       // 10
    LEX_OR,        // 11
    LEX_PROGRAM,   // 12
    LEX_READ,      // 13
    LEX_THEN,      // 14
    LEX_TRUE,      // 15
    LEX_VAR,       // 16
    LEX_WHILE,     // 17
    LEX_WRITE,     // 18
    LEX_FIN,       // 19
    LEX_SEMICOLON, // 20
    LEX_COMMA,     // 21
    LEX_COLON,     // 22
    LEX_ASSIGN,    // 23
    LEX_LPAREN,    // 24
    LEX_RPAREN,    // 25
    LEX_EQ,        // 26
    LEX_LSS,       // 27
    LEX_GTR,       // 28
    LEX_PLUS,      // 29
    LEX_MINUS,     // 30
    LEX_TIMES,     // 31
    LEX_SLASH,     // 32
    LEX_LEQ,       // 33
    LEX_NEQ,       // 34
    LEX_GEQ,       // 35
    LEX_NUM,       // 36
    LEX_ID,        // 37
    POLIZ_LABEL,   // 38
    POLIZ_ADDRESS, // 39
    POLIZ_GO,      // 40
    POLIZ_FGO      // 41
};

class Lex
{ // Represents information about lexemes.
    type_of_lex t_lex;
    int v_lex;

public:
    Lex(type_of_lex t = LEX_NULL, int v = 0)
    {
        t_lex = t;
        v_lex = v;
    }
    type_of_lex get_type()
    {
        return t_lex;
    }
    int get_value()
    {
        return v_lex;
    }
    friend ostream &operator<<(ostream &s, Lex l)
    {
        s << '(' << l.t_lex << ',' << l.v_lex << ");";
        return s;
    }
};

class Ident
{ // Represents information about variables.
    char *name;
    bool declare;
    type_of_lex type;
    bool assign;
    int value;

public:
    Ident()
    {
        declare = false;
        assign = false;
    }
    char *get_name()
    {
        return name;
    }
    void put_name(const char *n)
    {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
    }
    bool get_declare()
    {
        return declare;
    }
    void put_declare()
    {
        declare = true;
    }
    type_of_lex get_type()
    {
        return type;
    }
    void put_type(type_of_lex t)
    {
        type = t;
    }
    bool get_assign()
    {
        return assign;
    }
    void put_assign()
    {
        assign = true;
    }
    int get_value()
    {
        return value;
    }
    void put_value(int v)
    {
        value = v;
    }
};

class tabl_ident
{ // Contains all the identifiers of program, like TID table.
    Ident *p;
    int size;
    int top;

public:
    tabl_ident(int max_size)
    {
        p = new Ident[size = max_size];
        top = 1;
    }
    ~tabl_ident()
    {
        delete[] p;
    }
    Ident &operator[](int k)
    {
        return p[k];
    }
    int put(const char *buf);
};

int tabl_ident::put(const char *buf)
{
    for (int j = 1; j < top; ++j)
        if (!strcmp(buf, p[j].get_name()))
            return j;
    p[top].put_name(buf);
    ++top;
    return top - 1;
}

class Scanner
{ // Represents a lexical analyzer
    enum state
    {
        H,
        IDENT,
        NUMB,
        COM,
        ALE,
        DELIM,
        NEQ
    };
    static const char *TW[];
    static type_of_lex words[];
    static const char *TD[];
    static type_of_lex dlms[];
    state CS;
    FILE *fp;
    char c;
    char buf[80];
    int buf_top;

    void clear()
    {
        buf_top = 0;
        for (int j = 0; j < 80; ++j)
            buf[j] = '\0';
    }
    void add()
    {
        buf[buf_top++] = c;
    }
    int look(const char *buf, const char **list)
    {
        int i = 0;
        while (list[i])
        {
            if (!strcmp(buf, list[i]))
                return i;
            ++i;
        }
        return 0;
    }
    void gc()
    {
        c = fgetc(fp);
    }

public:
    Lex get_lex();
    Scanner(const char *program)
    {
        fp = fopen(program, "r");
        CS = H;
        clear();
        gc();
    }
};

const char *Scanner::TW[] =
    { // Table of M-language service words
        "",
        "and",
        "{",
        "bool",
        "do",
        "else",
        "}",
        "if",
        "false",
        "int",
        "not",
        "or",
        "program",
        "read",
        "then",
        "true",
        "var",
        "while",
        "write",
        NULL};

const char *Scanner::TD[] =
    { // Table of M-language limiters
        "", "@", ";", ",", ":",
        ":=", "(", ")", "=", "<",
        ">", "+", "-", "*", "/",
        "<=", "!=", ">=", NULL};

tabl_ident TID(100);

type_of_lex Scanner::words[] =
    { // Lexemes for service words
        LEX_NULL, LEX_AND, LEX_LCPAREN, LEX_BOOL, LEX_DO,
        LEX_ELSE, LEX_RCPAREN, LEX_IF, LEX_FALSE, LEX_INT,
        LEX_NOT, LEX_OR, LEX_PROGRAM, LEX_READ, LEX_THEN,
        LEX_TRUE, LEX_VAR, LEX_WHILE, LEX_WRITE, LEX_NULL};

type_of_lex Scanner::dlms[] =
    { // Lexemes for limiters
        LEX_NULL, LEX_FIN, LEX_SEMICOLON, LEX_COMMA, LEX_COLON,
        LEX_ASSIGN, LEX_LPAREN, LEX_RPAREN, LEX_EQ, LEX_LSS,
        LEX_GTR, LEX_PLUS, LEX_MINUS, LEX_TIMES, LEX_SLASH,
        LEX_LEQ, LEX_NEQ, LEX_GEQ, LEX_NULL};

Lex Scanner::get_lex()
{ // Builing of new single lexeme from source M-language code
    int d, j;
    CS = H;
    do
    {
        switch (CS)
        {
        case H:
            if (c == ' ' || c == '\n' || c == '\r' || c == '\t')
                gc();
            else if (isalpha(c) || c == '{' || c == '}')
            {
                clear();
                add();
                gc();
                CS = IDENT;
            }
            else if (isdigit(c))
            {
                d = c - '0';
                gc();
                CS = NUMB;
            }
            //    else if (c == '{')
            //    {
            //        gc();
            //        CS = COM;
            //    }
            else if (c == ':' || c == '<' || c == '>')
            {
                clear();
                add();
                gc();
                CS = ALE;
            }
            else if (c == '@')
                return Lex(LEX_FIN);
            else if (c == '!')
            {
                clear();
                add();
                gc();
                CS = NEQ;
            }
            else
                CS = DELIM;
            break;

        case IDENT:
            if (isalpha(c) || isdigit(c))
            {
                add();
                gc();
            }
            else if (j = look(buf, TW))
                return Lex(words[j], j);
            else
            {
                j = TID.put(buf);
                return Lex(LEX_ID, j);
            }
            break;

        case NUMB:
            if (isdigit(c))
            {
                d = d * 10 + (c - '0');
                gc();
            }
            else
                return Lex(LEX_NUM, d);
            break;

        case ALE:
            if (c == '=')
            {
                add();
                gc();
                j = look(buf, TD);
                return Lex(dlms[j], j);
            }
            else
            {
                j = look(buf, TD);
                return Lex(dlms[j], j);
            }
            break;

        case NEQ:
            if (c == '=')
            {
                add();
                gc();
                j = look(buf, TD);
                return Lex(LEX_NEQ, j);
            }
            else
                throw '!';
            break;

        case DELIM:
            clear();
            add();
            if (j = look(buf, TD))
            {
                gc();
                return Lex(dlms[j], j);
            }
            else
                throw c;
            break;
        }
    } while (true);
}

template <class T, int max_size>
class Stack
{
    T s[max_size];
    int top;

public:
    Stack() { top = 0; }
    void reset() { top = 0; }
    void push(T i);
    T pop();
    bool is_empty() { return top == 0; }
    bool is_full() { return top == max_size; }
};

template <class T, int max_size>
void Stack<T, max_size>::push(T i)
{
    if (!is_full())
    {
        s[top] = i;
        ++top;
    }
    else
        throw "Stack_is_full";
}

template <class T, int max_size>
T Stack<T, max_size>::pop()
{
    if (!is_empty())
    {
        --top;
        return s[top];
    }
    else
        throw "Stack_is_empty";
}

class Poliz
{
    Lex *p;
    int size;
    int free;

public:
    Poliz(int max_size)
    {
        p = new Lex[size = max_size];
        free = 0;
    }
    ~Poliz()
    {
        delete[] p;
    }
    void put_lex(Lex l)
    {
        p[free] = l;
        ++free;
    }
    void put_lex(Lex l, int place)
    {
        p[place] = l;
    }
    void blank()
    {
        ++free;
    }
    int get_free()
    {
        return free;
    }
    Lex &operator[](int index)
    {
        if (index > size)
            throw "POLIZ:out of array";
        else if (index > free)
            throw "POLIZ:indefinite element of array";
        else
            return p[index];
    }
    void print()
    {
        for (int i = 0; i < free; ++i)
            cout << p[i] << ' ';
        cout << endl;
    }
};

class Parser
{
    Lex curr_lex; // Current lexeme
    type_of_lex c_type;
    int c_val;
    Scanner scan;
    Stack<int, 100> st_int;
    Stack<type_of_lex, 100> st_lex;

    // Procedures for recursive descent
    void P();
    void D1();
    void D();
    void B();
    void S();
    void E();
    void E1();
    void T();
    void F();

    void dec(type_of_lex type); // Semantic actions
    void check_id();
    void check_op();
    void check_not();
    void eq_type();
    void eq_bool();
    void check_id_in_read();
    void gl() // Get a new lexeme
    {
        curr_lex = scan.get_lex();
        c_type = curr_lex.get_type();
        c_val = curr_lex.get_value();
    }

public:
    Poliz prog; // Internal presentation of the program
    Parser(const char *program) : scan(program), prog(1000) {}
    void analyze(); // Analyzer with actions
};

void Parser::analyze()
{
    gl();
    P();
    cout << "Reverse Polish notation:\n";
    prog.print();
}

void Parser::P()
{
    if (c_type == LEX_PROGRAM)
        gl();
    else
        throw curr_lex;
    D1();
    if (c_type == LEX_SEMICOLON)
        gl();
    else
        throw curr_lex;
    B();
    if (c_type != LEX_FIN)
        throw curr_lex;
}

void Parser::D1()
{
    if (c_type == LEX_VAR)
    {
        gl();
        D();
        while (c_type == LEX_COMMA)
        {
            gl();
            D();
        }
    }
    else
        throw curr_lex;
}

void Parser::D()
{
    st_int.reset();
    if (c_type != LEX_ID)
        throw curr_lex;
    else
    {
        st_int.push(c_val);
        gl();
        while (c_type == LEX_COMMA)
        {
            gl();
            if (c_type != LEX_ID)
                throw curr_lex;
            else
            {
                st_int.push(c_val);
                gl();
            }
        }
        if (c_type != LEX_COLON)
            throw curr_lex;
        else
        {
            gl();
            if (c_type == LEX_INT)
            {
                dec(LEX_INT);
                gl();
            }
            else if (c_type == LEX_BOOL)
            {
                dec(LEX_BOOL);
                gl();
            }
            else
                throw curr_lex;
        }
    }
}

void Parser::B()
{
    if (c_type == LEX_LCPAREN)
    {
        gl();
        S();
        while (c_type == LEX_SEMICOLON)
        {
            gl();
            S();
        }
        if (c_type == LEX_RCPAREN)
            gl();
        else
            throw curr_lex;
    }
    else
        throw curr_lex;
}

void Parser::S()
{
    int pl0, pl1, pl2, pl3;
    if (c_type == LEX_IF) // Case : if E then S else S
    {
        gl();
        E();
        eq_bool();
        pl2 = prog.get_free();
        prog.blank();
        prog.put_lex(Lex(POLIZ_FGO));
        S();
        pl3 = prog.get_free();
        prog.blank();
        prog.put_lex(Lex(POLIZ_GO));
        prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), pl2);
        if (c_type == LEX_ELSE)
        {
            gl();
            S();
            prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), pl3);
        }
        else
            throw curr_lex;
    }
    else if (c_type == LEX_WHILE) // Case : while E do S
    {
        pl0 = prog.get_free();
        gl();
        E();
        eq_bool();
        pl1 = prog.get_free();
        prog.blank();
        prog.put_lex(Lex(POLIZ_FGO));
        S();
        prog.put_lex(Lex(POLIZ_LABEL, pl0));
        prog.put_lex(Lex(POLIZ_GO));
        prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), pl1);
    }
    else if (c_type == LEX_READ) // Case : read(I)
    {
        gl();
        if (c_type == LEX_LPAREN)
        {
            gl();
            if (c_type == LEX_ID)
            {
                check_id_in_read();
                prog.put_lex(Lex(POLIZ_ADDRESS, c_val));
                gl();
            }
            else
                throw curr_lex;
            if (c_type == LEX_RPAREN)
            {
                gl();
                prog.put_lex(Lex(LEX_READ));
            }
            else
                throw curr_lex;
        }
        else
            throw curr_lex;
    }
    else if (c_type == LEX_WRITE) // Case: write(E)
    {
        gl();
        if (c_type == LEX_LPAREN)
        {
            gl();
            E();
            if (c_type == LEX_RPAREN)
            {
                gl();
                prog.put_lex(Lex(LEX_WRITE));
            }
            else
                throw curr_lex;
        }
        else
            throw curr_lex;
    }
    else if (c_type == LEX_ID) // Case: I := E
    {
        check_id();
        prog.put_lex(Lex(POLIZ_ADDRESS, c_val));
        gl();
        if (c_type == LEX_ASSIGN)
        {
            gl();
            E();
            eq_type();
            prog.put_lex(Lex(LEX_ASSIGN));
        }
        else
            throw curr_lex;
    }
    else
        B();
}

void Parser::E()
{
    E1();
    if (c_type == LEX_EQ || c_type == LEX_LSS || c_type == LEX_GTR ||
        c_type == LEX_LEQ || c_type == LEX_GEQ || c_type == LEX_NEQ)
    {
        st_lex.push(c_type);
        gl();
        E1();
        check_op();
    }
}

void Parser::E1()
{
    T();
    while (c_type == LEX_PLUS || c_type == LEX_MINUS || c_type == LEX_OR)
    {
        st_lex.push(c_type);
        gl();
        T();
        check_op();
    }
}

void Parser::T()
{
    F();
    while (c_type == LEX_TIMES || c_type == LEX_SLASH || c_type == LEX_AND)
    {
        st_lex.push(c_type);
        gl();
        F();
        check_op();
    }
}

void Parser::F()
{
    if (c_type == LEX_ID)
    {
        check_id();
        prog.put_lex(Lex(LEX_ID, c_val));
        gl();
    }
    else if (c_type == LEX_NUM)
    {
        st_lex.push(LEX_INT);
        prog.put_lex(curr_lex);
        gl();
    }
    else if (c_type == LEX_TRUE)
    {
        st_lex.push(LEX_BOOL);
        prog.put_lex(Lex(LEX_TRUE, 1));
        gl();
    }
    else if (c_type == LEX_FALSE)
    {
        st_lex.push(LEX_BOOL);
        prog.put_lex(Lex(LEX_FALSE, 0));
        gl();
    }
    else if (c_type == LEX_NOT)
    {
        gl();
        F();
        check_not();
    }
    else if (c_type == LEX_LPAREN)
    {
        gl();
        E();
        if (c_type == LEX_RPAREN)
            gl();
        else
            throw curr_lex;
    }
    else
        throw curr_lex;
}

// Semantic movements

void Parser::dec(type_of_lex type)
{ // Variables declaration control
    int i;
    while (!st_int.is_empty())
    {
        i = st_int.pop();
        if (TID[i].get_declare())
            throw "twice";
        else
        {
            TID[i].put_declare();
            TID[i].put_type(type);
        }
    }
}

void Parser::check_id()
{ // Check if variable is declared and put it's type into stack
    if (TID[c_val].get_declare())
        st_lex.push(TID[c_val].get_type());
    else
        throw "not declared";
}

void Parser::check_op()
{ // Check types in: operand <-> operation <-> operand
    type_of_lex t1, t2, op, t = LEX_INT, r = LEX_BOOL;
    t2 = st_lex.pop();
    op = st_lex.pop();
    t1 = st_lex.pop();
    if (op == LEX_PLUS || op == LEX_MINUS || op == LEX_TIMES || op == LEX_SLASH)
        r = LEX_INT;
    if (op == LEX_OR || op == LEX_AND)
        t = LEX_BOOL;
    if (t1 == t2 && t1 == t)
        st_lex.push(r);
    else
        throw "wrong types are in operation";
    prog.put_lex(Lex(op));
}

void Parser::check_not()
{
    if (st_lex.pop() != LEX_BOOL)
        throw "wrong type is in not";
    else
    {
        st_lex.push(LEX_BOOL);
    }
    prog.put_lex(Lex(LEX_NOT));
}

void Parser::eq_type()
{
    if (st_lex.pop() != st_lex.pop())
        throw "wrong types are in :=";
}

void Parser::eq_bool()
{
    if (st_lex.pop() != LEX_BOOL)
        throw "expression is not boolean";
}

void Parser::check_id_in_read()
{
    if (!TID[c_val].get_declare())
        throw "not declared";
}

class Executer
{
    Lex pc_el;

public:
    void execute(Poliz &prog);
};

void Executer::execute(Poliz &prog)
{
    Stack<int, 100> args;
    int i, j, index = 0, size = prog.get_free();

    while (index < size)
    {
        pc_el = prog[index];
        switch (pc_el.get_type())
        {
        case LEX_TRUE:
        case LEX_FALSE:
        case LEX_NUM:
        case POLIZ_ADDRESS:
        case POLIZ_LABEL:
            args.push(pc_el.get_value());
            break;
        case LEX_ID:
            i = pc_el.get_value();
            if (TID[i].get_assign())
            {
                args.push(TID[i].get_value());
                break;
            }
            else
                throw "indefinite identifier";
        case LEX_NOT:
            args.push(!args.pop());
            break;
        case LEX_OR:
            i = args.pop();
            args.push(args.pop() || i);
            break;
        case LEX_AND:
            i = args.pop();
            args.push(args.pop() && i);
            break;
        case POLIZ_GO:
            index = args.pop() - 1;
            break;
        case POLIZ_FGO:
            i = args.pop();
            if (!args.pop())
                index = i - 1;
            break;
        case LEX_WRITE:
            cout << args.pop() << endl;
            break;
        case LEX_READ:
        {
            int k;
            i = args.pop();
            if (TID[i].get_type() == LEX_INT)
            {
                cout << "Input int value for ";
                cout << TID[i].get_name() << ": ";
                cin >> k;
            }
            else
            {
                char j[20];
            rep:
                cout << "Input boolean value (true or false) for ";
                cout << TID[i].get_name() << ": ";
                cin >> j;
                if (!strcmp(j, "true"))
                    k = 1;
                else if (!strcmp(j, "false"))
                    k = 0;
                else
                {
                    cout << "Error in input:true/false" << endl;
                    goto rep;
                }
            }
            TID[i].put_value(k);
            TID[i].put_assign();
            break;
        }
        case LEX_PLUS:
            args.push(args.pop() + args.pop());
            break;
        case LEX_TIMES:
            args.push(args.pop() * args.pop());
            break;
        case LEX_MINUS:
            i = args.pop();
            args.push(args.pop() - i);
            break;
        case LEX_SLASH:
            i = args.pop();
            if (i)
            {
                args.push(args.pop() / i);
                break;
            }
            else
                throw "divide by zero";
        case LEX_EQ:
            args.push(args.pop() == args.pop());
            break;
        case LEX_LSS:
            i = args.pop();
            args.push(args.pop() < i);
            break;
        case LEX_GTR:
            i = args.pop();
            args.push(args.pop() > i);
            break;
        case LEX_LEQ:
            i = args.pop();
            args.push(args.pop() <= i);
            break;
        case LEX_GEQ:
            i = args.pop();
            args.push(args.pop() >= i);
            break;
        case LEX_NEQ:
            i = args.pop();
            args.push(args.pop() != i);
            break;
        case LEX_ASSIGN:
            i = args.pop();
            j = args.pop();
            TID[j].put_value(i);
            TID[j].put_assign();
            break;
        default:
            throw "POLIZ: unexpected elem";
        } // end of switch
        ++index;
    } // end of while
}

class Interpretator
{
    Parser pars;
    Executer E;

public:
    Interpretator(const char *program) : pars(program){};
    void interpretation();
};

void Interpretator::interpretation()
{
    pars.analyze();
    E.execute(pars.prog);
}

int main()
{
    try
    {
        Interpretator I("program2.txt");
        I.interpretation();
        return 0;
    }
    catch (char c)
    {
        cout << "Lexical error: Unexpected symbol " << c << endl;
        return 1;
    }
    catch (Lex l)
    {
        cout << "Syntax error: Unexpected lexeme" << l << endl;
        return 1;
    }
    catch (const char *source)
    {
        cout << "Error: " << source << endl;
        return 1;
    }
}
