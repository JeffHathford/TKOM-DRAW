#include "lexer.h"
#include "unit_tests.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <fstream>
#include <vector>

std::string FILE_INPUT = "";

template <typename T>
void print(T data)
{
    std::cout<<data<<std::endl;
}

template <typename T>
void error(T data)
{
    std::cerr<<data<<std::endl;
}

void check_program_arguments(int argc, char** argv, int& display_type, std::string& file_input)
{
    //if the first argument is "test" or "assert"
    if(argc >= 2)
    {
        std::string arg1(argv[1]);
        if(arg1 == "test" || arg1 == "assert")
        {
            run_unit_tests();
            exit(EXIT_SUCCESS);
        }
    }
    //if the program was invoked without specifying a file to compile
    if(argc < 3)
        print("No input file was specified, reading lines from keyboard input...");
    if(argc >= 2)
        sscanf (argv[1], "%d", &display_type);
    if(argc >= 3)
    {
        std::string arg1(argv[2]);
        file_input = arg1;
    }
}

int main(int argc, char** argv)
{
    int token = 0, last_token = 0, index, line = 0;
    std::string user_input;
    std::ifstream file_handler;

    //check program arguments and set up control variables;
    check_program_arguments(argc, argv, DISPLAY_TYPE, FILE_INPUT);

    std::cout<<DISPLAY_TYPE<<std::endl<<FILE_INPUT;
    if(argc >= 3)
    {
        file_handler.open(FILE_INPUT);
        if(!file_handler)
        {
            error("Failed to open file");
            exit(EXIT_FAILURE);
        }

    }
    
    do
    {
        ++line;
        index = 0;
        token = 0;

        print("");

        if(argc >= 3 && !file_handler.eof())
            std::getline (file_handler, user_input);
        else if(file_handler.eof())
            break;
        else
            std::getline (std::cin, user_input);

        while(token != EOL && token != QUIT)
        {
            if(DISPLAY_TYPE == VERBOSE)
                std::cout<<"i "<<index<<std::endl;

            last_token = token;
            token = get_next_token(user_input, index);

            if(token == R_BLOCK && last_token != SEMICOLON)
                pass_to_parser(SEMICOLON);

            if(token != EOL && token != QUIT)
                pass_to_parser(token);
        }
        if(last_token != L_BLOCK && last_token != R_BLOCK && last_token != SEMICOLON && token != QUIT)
        {
            pass_to_parser(SEMICOLON);
        }
    }
    while(token != QUIT);

    return 0;
}