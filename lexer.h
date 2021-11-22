#ifndef LEXER_H
#define LEXER_H
#include <string>
#include <iostream>

enum LogType{
                NONE,
                TOKEN,
                VERBOSE
            };

enum TokenType {
                //SPECIAL
                INVALID = -1,
                QUIT = 1,
                EOL,

                //PRIMITIVE TYPES
                INT_TYPE,
                FLOAT_TYPE,
                CHAR_TYPE,
                STRING_TYPE,
                NEW_FUNC,

                //KEYWORDS
                IDENTIFIER,
                INT_CONST,
                FLOAT_CONST,
                CHAR_CONST,
                STRING_CONST,

                //LOOPS + CONDITIONALS
                WHILE,
                FOR,
                LOOP,
                IF_COND,
                ELSE_COND,

                //OPERATORS
                ASSIGN,     // =
                NOT,        // !
                PLUS,       // +
                MINUS,      // -
                DIV,        // /
                MULT,       // *
                MOD,        // %
                GREAT,      // >
                LESS,       // <
                EQUALS,     // ==
                NOT_EQ,     // !=
                E_GREAT,    // >=
                E_LESS,     // <=
                OR,         // ||
                AND,        // &&

                //SPECIAL SIGNS
                L_PAREN,        // (
                R_PAREN,        // )
                L_BLOCK,        // { or :
                R_BLOCK,        // } or 'end'
                COMMA,          // ,
                DOT_SEPARATOR,  // .
                SEMICOLON,      // ; (can be ommited)
                };

extern int DISPLAY_TYPE;

typedef struct 
{
    std::string key;
    int value;
} Map;

extern Map TokenMap[];
extern int TOKENMAP_SIZE;

extern int TOKEN_TYPE_SIZE;
extern int TOKEN_KEYWORD_SIZE;
extern int TOKEN_SPECIAL_SIZE;
extern int TOKEN_OPERATOR_SIZE;
extern int TOKEN_MULTISIGN_SIZE;

extern std::string TOKEN_TYPE[];
extern std::string TOKEN_KEYWORD[];
extern std::string TOKEN_SPECIAL[];
extern std::string TOKEN_OPERATOR[];
extern std::string TOKEN_MULTISIGN[];

int get_next_token(std::string data, int& index);
void pass_to_parser(int token);
int check_string_array(std::string data, std::string source[], int arr_size);
std::string check_tokenmap(int val);

#endif