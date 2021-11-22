#include "unit_tests.h"

void run_unit_tests()
{
    int idx = 0;

    std::string data1 = "int var, user_input";
    std::string data2 = "fun full_rotation_remainder (angle : float):";
    std::string data3 = "turtle.rotate(full_rotation_remainder(20.0))";

    assert(get_next_token(data1, idx) == INT_TYPE);
    assert(get_next_token(data1, idx) == IDENTIFIER);
    assert(get_next_token(data1, idx) == COMMA);
    assert(get_next_token(data1, idx) == IDENTIFIER);

    idx = 0;
    assert(get_next_token(data2, idx) == NEW_FUNC);
    assert(get_next_token(data2, idx) == IDENTIFIER);
    assert(get_next_token(data2, idx) == L_PAREN);
    assert(get_next_token(data2, idx) == IDENTIFIER);
    assert(get_next_token(data2, idx) == L_BLOCK);
    assert(get_next_token(data2, idx) == FLOAT_TYPE);
    assert(get_next_token(data2, idx) == R_PAREN);
    assert(get_next_token(data2, idx) == L_BLOCK);

    idx = 0;
    assert(get_next_token(data3, idx) == IDENTIFIER);
    assert(get_next_token(data3, idx) == DOT_SEPARATOR);
    assert(get_next_token(data3, idx) == IDENTIFIER);
    assert(get_next_token(data3, idx) == L_PAREN);
    assert(get_next_token(data3, idx) == IDENTIFIER);
    assert(get_next_token(data3, idx) == L_PAREN);
    assert(get_next_token(data3, idx) == FLOAT_CONST);
    assert(get_next_token(data3, idx) == R_PAREN);
    assert(get_next_token(data3, idx) == R_PAREN);

    assert(check_tokenmap(IDENTIFIER) == "IDENTIFIER");
    assert(check_tokenmap(WHILE) == "WHILE");

    assert(check_string_array("while", TOKEN_KEYWORD, TOKEN_KEYWORD_SIZE) != INVALID);
    assert(check_string_array("string", TOKEN_KEYWORD, TOKEN_KEYWORD_SIZE) == INVALID);
    assert(check_string_array("string", TOKEN_TYPE, TOKEN_TYPE_SIZE) != INVALID);

    std::cout<<"All assertions passed."<<std::endl;
}