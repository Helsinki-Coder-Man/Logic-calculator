#include <iostream>

bool lFlag = false;

class Token
{
public:
    char type;
    double value;
};

class tokenStream
{
public:
    Token get();
    void putback(Token t);
private:
    bool full = false;
    Token buffer{0};

};
tokenStream ts;
void tokenStream::putback(Token t) 
{
    if (full) std::cerr << "\tToken stream is full";
    buffer = t;
    full = true;
}

Token tokenStream::get()
{
    if (full)
    {
        full = false;
        return buffer;
    }
    char ch;
    std::cin >> ch;

    switch (ch)
    {
    case ';':
    case'q':
        case '{': case '}': case '(': case ')': case'|': case '&': case '^'://let each character represent itself.
        return Token{ ch };

    case'.':
    case'0':case'1':case'2':case'3':case'4':
    case'5':case'6':case'7':case'8':case'9':
    {
        std::cin.putback(ch);
        double val;
        std::cin >> val;
        return Token{ '8', val };
    }
    default:
        std::cerr << "\tBad token";
    }
}

bool expression();

double primary()
{

    Token t = ts.get();
    switch (t.type)
    {
            
    case '(':
    {
        double d = expression();
        t = ts.get();
        if (t.type != ')') std::cerr << "\t')' expected";
        return d;
    }
            
            case '{':
    {
        double d = expression();
        t = ts.get();
        if (t.type != '}') std::cerr << "\t'}' expected";
        return d;
    }
            
    case '8':
        return t.value;
    default:
        std::cerr << "\tPrimary expected";

    }
}

bool term() 
{
  
    double left = primary();
    Token t = ts.get();
    while (true) 
    {
	    
        switch (t.type) 
        {
        case '&':
            if(left == primary())
	    {
	    lFlag = true;
	    }
	    else
	    {
	    lFlag = false;
	    }
           t = ts.get();
            break;
        case '^':
        {
           
	if(left != primary())
	{
	lFlag = true;
	} else
	{
	lFlag = false;
	}

           t = ts.get();

            break;
        }

        default:
            ts.putback(t);
	    
            return lFlag;
        }
    
    }
}

bool expression()
{

    double left = term();
    Token t = ts.get();
    while (true)
    {
        switch (t.type)
        {
        case'|':
           lFlag = true;
            t = ts.get();
            break;
        default:
            ts.putback(t);
            return lFlag;
        }
    }
} 


int main()
{
 double val = 0;
    while (std::cin)
    {
        Token t = ts.get();
        if (t.type == 'q') break;
        if (t.type == ';')
        {
            std::cout << '=' << lFlag;
        } else
        {
            ts.putback(t);
	    val = expression();
        }
        std::cout << '\n';
    }
}
