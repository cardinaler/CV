#include <iostream>
#include <cstring>
using namespace std;
enum type_of_lex
{
    LEX_NULL,      // 0
    LEX_AND,       // 1
    LEX_DO,        // 2
    LEX_ELSE,      // 3
    LEX_IF,        // 4
    LEX_FALSE,     // 5
    LEX_INT,       // 6
    LEX_STRING,    // 7
    LEX_NOT,       // 8
    LEX_OR,        // 9
    LEX_PROGRAM,   // 10
    LEX_READ,      // 11
    LEX_TRUE,      // 12
    LEX_WHILE,     // 13
    LEX_FOR,       // 14
    LEX_STEP,      // 15
    LEX_UNTIL,     // 16
    LEX_WRITE,     // 17
    LEX_FIN,       // 18
    LEX_SEMICOLON, // 19
    LEX_COMMA,     // 20
    LEX_COLON,     // 21
    LEX_ASSIGN,    // 22
    LEX_LPAREN,    // 23
    LEX_RPAREN,    // 24
    LEX_EQ,        // 25
    LEX_LSS,       // 26
    LEX_GTR,       // 27
    LEX_PLUS,      // 28
    LEX_MINUS,     // 29
    LEX_TIMES,     // 30
    LEX_SLASH,     // 31
    LEX_LEQ,       // 32
    LEX_NEQ,       // 33
    LEX_GEQ,       // 34
    LEX_QUOTE,     // 35
    LEX_LCPAREN,   // 36
    LEX_RCPAREN,   // 37
    LEX_NUM,       // 38
    LEX_WORD,      // 39
    LEX_ID,        // 40
    POLIZ_LABEL,   // 41
    POLIZ_ADDRESS, // 42
    POLIZ_GO,      // 43
    POLIZ_FGO      // 44

};

class Lex
{
    type_of_lex t_lex;
    int v_lex;

public:
    Lex(type_of_lex t = LEX_NULL, int v = 0)
    {
        t_lex = t;
        v_lex = v;
    }
    type_of_lex get_type() { return t_lex; }
    int get_value() { return v_lex; }
    friend ostream &operator<<(ostream &s, Lex l)
    {
        s << '(' << l.t_lex << ',' << l.v_lex << ");";
        return s;
    }
};

class Ident
{
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
{
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

char *W[100];
int top_word = 0;

class Scanner
{
    enum state
    {
        H,
        IDENT,
        NUMB,
        COM,
        ALE,
        DELIM,
        NEQ,
        WORD
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
    {
        "",        // 0
        "and",     // 1
        "do",      // 2
        "else",    // 3
        "if",      // 4
        "false",   // 5
        "int",     // 6
        "string",  // 7
        "not",     // 8
        "or",      // 9
        "program", // 10
        "read",    // 11
        "true",    // 12
        "while",   // 13
        "for",     // 14
        "step",    // 15
        "until",   // 16
        "write",   // 17
        NULL};

const char *Scanner::TD[] =
    {
        "",   // 18
        "@",  // 19
        ";",  // 20
        ",",  // 21
        "=",  // 22
        "(",  // 23
        ")",  // 24
        "==", // 25
        "<",  // 26
        ">",  // 27
        "+",  // 28
        "-",  // 29
        "*",  // 30
        "/",  // 31
        "<=", // 32
        "!=", // 33
        ">=", // 34
        "\"", // 35
        "{",  // 36
        "}",  // 37
        NULL};

tabl_ident TID(100);
type_of_lex Scanner::words[] =
    {
        LEX_NULL,    // 0
        LEX_AND,     // 1
        LEX_DO,      // 2
        LEX_ELSE,    // 3
        LEX_IF,      // 4
        LEX_FALSE,   // 5
        LEX_INT,     // 6
        LEX_STRING,  // 7
        LEX_NOT,     // 8
        LEX_OR,      // 9
        LEX_PROGRAM, // 10
        LEX_READ,    // 11
        LEX_TRUE,    // 12
        LEX_WHILE,   // 13
        LEX_FOR,     // 14
        LEX_STEP,    // 15
        LEX_UNTIL,   // 16
        LEX_WRITE,   // 17
};

type_of_lex Scanner::dlms[] =
    {
        LEX_NULL,      // 18
        LEX_FIN,       // 19
        LEX_SEMICOLON, // 20
        LEX_COMMA,     // 21
        LEX_ASSIGN,    // 22
        LEX_LPAREN,    // 23
        LEX_RPAREN,    // 24
        LEX_EQ,        // 25
        LEX_LSS,       // 26
        LEX_GTR,       // 27
        LEX_PLUS,      // 28
        LEX_MINUS,     // 29
        LEX_TIMES,     // 30
        LEX_SLASH,     // 31
        LEX_LEQ,       // 32
        LEX_NEQ,       // 33
        LEX_GEQ,       // 34
        LEX_QUOTE,     // 35
        LEX_LCPAREN,   // 36
        LEX_RCPAREN    // 37
};

// char *Scanner::W[100];

// int Scanner::top_word = 0;

Lex Scanner::get_lex()
{
    int d, j;
    char s[100];
    int k = 0;
    CS = H;
    do
    {
        switch (CS)
        {
        case H:
            if (c == ' ' || c == '\n' || c == '\r' || c == '\t')
                gc();
            else if (isalpha(c))
            {
                clear(); // очистить буфер
                add();   // добавить в буфер
                gc();
                CS = IDENT;
            }
            else if (isdigit(c))
            {
                d = c - '0';
                gc();
                CS = NUMB;
            }
            else if (c == '\"')
            {
                gc();
                CS = WORD;
            }
            else if (c == '=' || c == '<' || c == '>')
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
        case WORD:
            while (c != '\"')
            {
                s[k] = c;
                gc();
                ++k;
            }
            s[k] = '\0';
            gc();
            W[top_word] = s; // значение сохраняется в специальной таблице для слов (констант)
            ++top_word;
            return Lex(LEX_WORD, top_word - 1);
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
        // end switch
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
    //   type_of_lex tmp_type;
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
    void V();

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
    prog.print();
    cout << endl
         << "Yes!!!" << endl;
}

void Parser::P()
{
    if (c_type == LEX_PROGRAM)
    {
        gl();
        if (c_type == LEX_LCPAREN)
        {
            gl();
            D1();
            if (c_type == LEX_SEMICOLON)
            {
                gl();
                B();
                if (c_type != LEX_RCPAREN)
                    throw curr_lex;
            }
            else
                throw curr_lex;
        }
        else
            throw curr_lex;
    }
    else
        throw curr_lex;
}

void Parser::D1()
{
    D();
    //    while (c_type == LEX_SEMICOLON)
    while (c_type == LEX_COMMA)
    {
        gl();
        D();
    }
}

void Parser::D()
{
    type_of_lex tmp_type;
    st_int.reset();
    if (c_type != LEX_INT && c_type != LEX_STRING)
    {
        throw curr_lex;
    }
    else
    {
        tmp_type = c_type;
        do
        {
            gl();
            V();
        } while (c_type == LEX_COMMA);
        dec(tmp_type); // Опасный момент, велик риск
    }
}

void Parser::V()
{
    if (c_type != LEX_ID)
    {
        throw curr_lex;
    }
    else
    {
        st_int.push(c_val); // значение лексемы-идентификатора
        gl();
        if (c_type == LEX_ASSIGN)
        {
            gl();
            E();
            eq_type();
            prog.put_lex(Lex(LEX_ASSIGN));
        }
    }
}

void Parser::B()
{
    S();
    while (c_type == LEX_SEMICOLON)
    {
        gl();
        S();
    }
}

void Parser::S()
{
    int pl0, pl1, pl2, pl3;

    if (c_type == LEX_IF)
    {
        gl();
        if (c_type == LEX_LPAREN)
        {
            gl(); //
            E();
            eq_bool();
            pl2 = prog.get_free();
            prog.blank();
            prog.put_lex(Lex(POLIZ_FGO));
            if (c_type == LEX_RPAREN)
            {
                gl();
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
            else
                throw curr_lex;
        }
        else
            throw curr_lex;
    }
    else if (c_type == LEX_WHILE)
    {
        pl0 = prog.get_free();
        gl();
        if (c_type == LEX_LPAREN)
        {
            E();
            eq_bool();
            pl1 = prog.get_free();
            prog.blank();
            prog.put_lex(Lex(POLIZ_FGO));
            if (c_type == LEX_RPAREN)
            {
                gl();
                S();
                prog.put_lex(Lex(POLIZ_LABEL, pl0));
                prog.put_lex(Lex(POLIZ_GO));
                prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), pl1);
            }
            else
                throw curr_lex;
        }
        else
            throw curr_lex;
    }
    else if (c_type == LEX_READ)
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
                //          if (c_type == LEX_SEMICOLON)
                //        {
                prog.put_lex(Lex(LEX_READ));
                //      }
                //    else
                //      throw curr_lex;
            }
            else
                throw curr_lex;
        }
        else
            throw curr_lex;
    } // end read
    else if (c_type == LEX_WRITE)
    {
        gl();
        if (c_type == LEX_LPAREN)
        {
            gl();
            E();
            if (c_type == LEX_RPAREN)
            {
                gl();
                //             if (c_type == LEX_SEMICOLON)
                //           {
                prog.put_lex(Lex(LEX_WRITE));
                //         }
                //       else
                //         throw curr_lex;
            }
            else
                throw curr_lex;
        }
        else
            throw curr_lex;
    } // end write
    else if (c_type == LEX_ID)
    {
        check_id();
        prog.put_lex(Lex(POLIZ_ADDRESS, c_val));
        gl();
        if (c_type == LEX_ASSIGN)
        {
            gl();
            E();
            eq_type();
            //       if (c_type == LEX_SEMICOLON)
            //     {
            prog.put_lex(Lex(LEX_ASSIGN));
            //           gl();
            //   }
            //    else
            //      throw curr_lex;
        }
        else
            throw curr_lex;
    } // assign-end
    else if (c_type == LEX_DO)
    {
        pl0 = prog.get_free();
        gl();
        S();
        if (c_type == LEX_WHILE)
        {
            gl();
            if (c_type == LEX_LPAREN)
            {
                E();
                eq_bool();
                pl1 = prog.get_free();
                prog.blank();
                prog.put_lex(Lex(POLIZ_FGO));
                if (c_type == LEX_RPAREN)
                {
                    gl();
                    prog.put_lex(Lex(POLIZ_LABEL, pl0));
                    prog.put_lex(Lex(POLIZ_GO));
                    prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), pl1);
                }
                else
                    throw curr_lex;
            }
            else
                throw curr_lex;
        }
        else
            throw curr_lex;
    }
    else if (c_type == LEX_FOR)
    {
        gl();
        if (c_type == LEX_LPAREN)
        {
            gl();
            if (c_type != LEX_SEMICOLON)
            {
                E();
                eq_bool();
                if (c_type != LEX_SEMICOLON)
                    throw curr_lex;
            }
            prog.blank();
            pl0 = prog.get_free();
            gl();
            if (c_type != LEX_SEMICOLON)
            {
                E();
                eq_bool();
                if (c_type != LEX_SEMICOLON)
                    throw curr_lex;
            }
            // Вставить заведомо истинное условие, так как Е может не быть.
            gl();
            pl1 = prog.get_free();
            prog.blank();
            prog.put_lex(Lex(POLIZ_FGO));
        }
        else
            throw curr_lex;
        if (c_type != LEX_RPAREN)
        {
            E();
            eq_bool();
            if (c_type != LEX_RPAREN)
                throw curr_lex;
        }
        gl();
        S();
        prog.put_lex(Lex(POLIZ_LABEL, pl0));
        prog.put_lex(Lex(POLIZ_GO));
        prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), pl1);
    }
    // Добавить еще один for
    else if (c_type == LEX_LCPAREN)
    {
        gl();
        B();
        if (c_type != LEX_RCPAREN)
            throw curr_lex;
        gl();
    }
    else
        throw curr_lex;
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
    else if (c_type == LEX_WORD)
    {
        st_lex.push(LEX_STRING);
        prog.put_lex(curr_lex);
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

void Parser::dec(type_of_lex type)
{
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
{
    if (TID[c_val].get_declare())
        st_lex.push(TID[c_val].get_type());
    else
        throw "not declared";
}

void Parser::check_op()
{
    type_of_lex t1, t2, op, r;
    t2 = st_lex.pop();
    op = st_lex.pop();
    t1 = st_lex.pop();
    prog.put_lex(Lex(op));
    if (t1 == t2 && t1 == LEX_STRING)
    {
        if (op != LEX_PLUS)
            throw "wrong types are in operation";
        r = LEX_STRING;
        st_lex.push(r);
    }
    else if (t1 == t2 && t1 == LEX_INT)
    {
        r = LEX_INT;
        st_lex.push(r);
    }
    else
        throw "wrong types are in operation";
}

void Parser::check_not()
{
    if (st_lex.pop() != LEX_INT)
        throw "wrong type is in not";
    else
    {
        st_lex.push(LEX_INT);
    }
}

void Parser::eq_type()
{
    if (st_lex.pop() != st_lex.pop())
        throw "wrong types are in =";
}

void Parser::eq_bool()
{
    if (st_lex.pop() != LEX_INT)
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
                throw "POLIZ: indefinite identifier";
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
            i = args.pop();
            cout << args.pop() << endl;
            break;
        case LEX_READ:
        {
            int k;
            i = args.pop();
            if (TID[i].get_type() == LEX_INT)
            {
                cout << "Input int value for ";
                cout << TID[i].get_name() << endl;
                cin >> k;
            }
            else if (TID[i].get_type() == LEX_STRING)
            {
                char j[100];
            rep:
                cout << "Input string";
                //               cout << "(true or false) for";
                //               cout << TID[i].get_name() << endl;
                cin >> j;
                W[top_word] = j;
                k = top_word;
                top_word++;
                // if (!strcmp(j, "true"))
                //     k = 1;
                // else if (!strcmp(j, "false"))
                //     k = 0;
                // else
                // {
                //     cout << "Error in input:true/false";
                //     cout << endl;
                //     goto rep;
                // }
            }
            else
                throw "error";
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
            if (!i)
            {
                args.push(args.pop() / i);
                break;
            }
            else
                throw "POLIZ:divide by zero";
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
        }
        // end of switch
        ++index;
    };
    // end of while
    cout << "Finish of executing!!!" << endl;
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
        Interpretator I("string.txt");
        I.interpretation();
        return 0;
    }
    catch (char c)
    {
        cout << "unexpected symbol " << c << endl;
        return 1;
    }
    catch (Lex l)
    {
        cout << "unexpected lexeme";
        cout << l << endl;
        return 1;
    }
    catch (const char *source)
    {
        cout << source << endl;
        return 1;
    }
}