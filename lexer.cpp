#include "lexer.h"

int TOKEN_TYPE_SIZE = 4;
int TOKEN_KEYWORD_SIZE = 5;
int TOKEN_SPECIAL_SIZE = 7;
int TOKEN_OPERATOR_SIZE = 9;
int TOKEN_MULTISIGN_SIZE = 6;

std::string TOKEN_TYPE[] = {"int", "float", "char", "string"};
std::string TOKEN_KEYWORD[] = {"while", "for", "loop", "if", "else"};
std::string TOKEN_SPECIAL[] = {"(", ")", "{", "}", ",", ".", ";"};   //: and 'end' checked separately
std::string TOKEN_OPERATOR[] = {"=", "!", "+", "-", "/", "*", "%", ">", "<"};
std::string TOKEN_MULTISIGN[] = {"==", "!=", ">=", "<=", "||", "&&"};

int DISPLAY_TYPE = 1;
int TOKENMAP_SIZE = 40;

Map TokenMap[] = {{"INVALID", INVALID},
                         {"QUIT", QUIT},
                         {"EOL", EOL},
                         {"INT_TYPE", INT_TYPE},
                         {"FLOAT_TYPE", FLOAT_TYPE},
                         {"CHAR_TYPE", CHAR_TYPE},
                         {"STRING_TYPE", STRING_TYPE},
                         {"NEW_FUNC", NEW_FUNC},
                         {"IDENTIFIER", IDENTIFIER},
                         {"INT_CONST", INT_CONST},
                         {"FLOAT_CONST", FLOAT_CONST},
                         {"CHAR_CONST", CHAR_CONST},
                         {"STRING_CONST", STRING_CONST},
                         {"WHILE", WHILE},
                         {"FOR", FOR},
                         {"LOOP", LOOP},
                         {"IF_COND", IF_COND},
                         {"ELSE_COND", ELSE_COND},
                         {"ASSIGN", ASSIGN},
                         {"NOT", NOT},
                         {"PLUS", PLUS},
                         {"MINUS", MINUS},
                         {"DIV", DIV},
                         {"MULT", MULT},
                         {"MOD", MOD},
                         {"GREAT", GREAT},
                         {"LESS", LESS},
                         {"EQUALS", EQUALS},
                         {"NOT_EQ", NOT_EQ},
                         {"E_GREAT", E_GREAT},
                         {"E_LESS", E_LESS},
                         {"OR", OR},
                         {"AND", AND},
                         {"L_PAREN", L_PAREN},
                         {"R_PAREN", R_PAREN},
                         {"L_BLOCK", L_BLOCK},
                         {"R_BLOCK", R_BLOCK},
                         {"COMMA", COMMA},
                         {"DOT_SEPARATOR", DOT_SEPARATOR},
                         {"SEMICOLON", SEMICOLON}
};

int get_next_token(std::string data, int& index)
{
    char ch = ' ';
    int mark = index, result;
    std::string word;
    while(index < data.length() && ch == ' ')
    {
        ch = data[index];
        ++index;
    }

    //no tokens found - EOL
    if(ch == ' ')
        return EOL;

    //check for numbers, can't start from 0
    else if(ch >= '1' && ch <= '9')
    {
        bool float_flag = false;
        bool err_flag = false;
        //all numbers - INT_CONST
        //numbers -> dot -> numbers - FLOAT_CONST
        //otherwise - INVALID
        while(index < data.length() && data[index] != ' ')
        {
            if(!err_flag)
            {
                ch = data[index];

                if(ch == '.')
                {
                    if(!float_flag && index+1 < data.length() && data[index+1] != ' ')
                        float_flag = true;
                    else
                        err_flag = true;
                    ++index;
                    continue;
                }

                std::string query{ch};
                result = check_string_array(query, TOKEN_SPECIAL, TOKEN_SPECIAL_SIZE);
                if(result != INVALID)
                    break;  //simply break the while loop, process the word and then process the symbol normally
                result = check_string_array(query, TOKEN_OPERATOR, TOKEN_OPERATOR_SIZE);
                if(result != INVALID)
                    break;
                if(index+1 < data.length())
                {
                   std::string query{ch, data[index+1]};
                    result = check_string_array(query, TOKEN_OPERATOR, TOKEN_OPERATOR_SIZE);
                    if(result != INVALID)
                        break;
                }                

                if(ch < '0' || ch > '9')
                {
                    if(DISPLAY_TYPE == VERBOSE)
                        std::cout<<"ILLEGAL: "<<ch<<std::endl;
                    err_flag = true;
                }
            }
            ++index;
        }

        if(err_flag)
            return INVALID;

        if(!float_flag)
            return INT_CONST;
        else
            return FLOAT_CONST;
    }

    //check for letters
    else if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
    {
        bool err_flag = false;
        //letters, numbers and/or underscores - scan KEYWORDs or IDENTIFIER
        //other special signs - INVALID
        mark = index-1;     //mark before the first character, used in substr
        while(index < data.length() && data[index] != ' ')
        {
            if(!err_flag)
            {
                ch = data[index];

                std::string query{ch};
                result = check_string_array(query, TOKEN_SPECIAL, TOKEN_SPECIAL_SIZE);
                if(result != INVALID)
                    break;  //simply break the while loop, process the word and then process the symbol normally
                result = check_string_array(query, TOKEN_OPERATOR, TOKEN_OPERATOR_SIZE);
                if(result != INVALID)
                    break;

                if(ch < '0' || (ch > '9' && ch < 'A') || (ch > 'Z' && ch < '_') || (ch > '_' && ch < 'a') || ch > 'z')  //check for illegal characters
                {
                    if(DISPLAY_TYPE == VERBOSE)
                        std::cout<<"ILLEGAL: "<<ch<<std::endl;
                    err_flag = true;
                }
            }
            ++index;
        }

        if(err_flag)
            return INVALID;

        word = data.substr(mark, index-mark);
        if(DISPLAY_TYPE == VERBOSE)
            std::cout<<"WORD: "<<word<<std::endl;
        
        if(word == "quit")
            return QUIT;

        else if(word == "fun")
            return NEW_FUNC;

        else if(word == "end")
            return R_BLOCK;

        result = check_string_array(word, TOKEN_KEYWORD, TOKEN_KEYWORD_SIZE);
        if(result != INVALID)
            return WHILE + result;  
        
        result = check_string_array(word, TOKEN_TYPE, TOKEN_TYPE_SIZE);
        if(result != INVALID)
            return INT_TYPE + result;  

        return IDENTIFIER;       //if both Type and Keyword mismatch, return Identifier
    }

    //check for string constant
    else if(ch == '\"')
    {
        mark = index;
        while(mark < data.length() && data[mark] != '\"')   //using mark instead of index to avoid disrupting the tokenization flow in case of a typo (INVALID TOKEN)
            ++mark;
        if(data[mark] == '\"')
        {
            index = mark+1;
            return STRING_CONST;
        }
        return INVALID;
    }
    //check for char constant
    else if(ch == '\'')
    {
        if(index+1 < data.length() && data[index+1] == '\'')
        {
            index += 2;
            return CHAR_CONST;
        }
        return INVALID;
    }

    //check if token is one or two signs
    else
    {
        if(ch == ':')
            return L_BLOCK;

        if(ch == '#')
            return EOL;

        //check if the token is multisymbol or single symbol
        bool one_symbol = false;
        if(index < data.length())
        {
            std::string query{ch, data[index]};
            result = check_string_array(query, TOKEN_MULTISIGN, TOKEN_MULTISIGN_SIZE);
            if (result != INVALID)
            {
                ++index;
                return EQUALS + result;
            }
            else
                one_symbol = true;
        }
        else
            one_symbol = true;

        //one symbol
        if(one_symbol)
        {
            std::string query{ch};
            result = check_string_array(query, TOKEN_SPECIAL, TOKEN_SPECIAL_SIZE);

            if(result != INVALID)
                return L_PAREN + result;

            result = check_string_array(query, TOKEN_OPERATOR, TOKEN_OPERATOR_SIZE);
            if(result != INVALID)
                return ASSIGN + result;
        }

        return INVALID;
    }
}

void pass_to_parser(int token)
{
    if(DISPLAY_TYPE == VERBOSE)
        std::cout<<"---->token: "<<token<<" - ";
    std::cout<<check_tokenmap(token)<<", ";
    if(DISPLAY_TYPE == VERBOSE)
        std::cout<<std::endl;
}

int check_string_array(std::string data, std::string source[], int arr_size)
{
    int counter = 0;
    while (counter < arr_size)
    {

        if (data == source[counter])
            return counter;
        ++counter;
    }
    return INVALID;
}

std::string check_tokenmap(int val)
{ 
    for(int i=0; i<TOKENMAP_SIZE; i++)
    {
        if(val == TokenMap[i].value)
            return TokenMap[i].key;
    }
    return "No corresponding key found in TokenMap";
    
    //return TokenMap[val-1].key;
}
