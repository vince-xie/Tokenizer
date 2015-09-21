//
//  main.c
//  Tokenizer
//
//  Created by Vince Xie on 9/5/15.
//  Copyright (c) 2015 Vince Xie, Jacob Rizer. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
 * Contains the types of tokens available
 */
enum Type{
    WORD,
    DECIMAL,
    OCTAL,
    HEX,
    FLOATING_POINT,
    C_OPERATOR,
    C_KEYWORD,
    C_COMMENT,
    QUOTES,
    MAL
} type;

const char *KEYWORDS[32] = {"auto", "double", "int", "struct", "break", "else", "long", "switch" ,"case", "enum", "register", "typedef", "char", "extern", "return", "union", "const", "float", "short", "unsigned", "continue", "for", "signed", "void", "default", "goto", "sizeof", "volatile", "do", "if", "static", "while"};

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {
    char *current;
    char *token;
};

typedef struct TokenizerT_ TokenizerT;

/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 *
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate( char * ts ) {
    TokenizerT *token = (TokenizerT *)malloc(sizeof(TokenizerT));
    token->token = (char *)malloc(strlen(ts) + 1);
    token->current = ts;
    return token;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy( TokenizerT * tk ) {
    free(tk->token);
    free(tk);
}

/* Copies a substring from the input to the current token and sets the type
 * @params Pointer to tokenizer, length, type
 */
void copySubstringToTokenSetType(TokenizerT * tk, int index, enum Type newType){
    strncpy(tk->token, tk->current, index);
    tk->token[index] = '\0';
    tk->current+=index;
    type = newType;
}

/*
 * printOperator is called upon encountering a symbol in the string that belongs to a C Operator.
 * It uses a switch statement on the first character of the string and then determines the full operator using if-else structure,
 * which may be 1 2 or 3 characters long. It then prints that operator's name, makes the operator the new token, and shifts
 * the current string pointer past the operator to advance on to the next token.
 */
void printOperator(TokenizerT * tk){
    
    char first;
    
    char * token = tk->current;
    
    if(token == NULL){
        return;
    }
    
    first = token[0];
    
    switch(first){
            
        case '(':
            
            tk->token[0] = '(';
            tk->token[1] = '\0';
            
            printf("leftparenthesis");
            tk->current = tk->current+1;
            break;
            
        case ')':
            
            tk->token[0] = ')';
            tk->token[1] = '\0';
            
            printf("rightparenthesis");
            tk->current = tk->current+1;
            break;
            
        case '[':
            
            tk->token[0] = '[';
            tk->token[1] = '\0';
            
            printf("leftbrace");
            tk->current = tk->current+1;
            break;
            
        case ']':
            
            tk->token[0] = ']';
            tk->token[1] = '\0';
            
            printf("rightbrace");
            tk->current = tk->current+1;
            break;
            
        case '.':
            
            tk->token[0] = '.';
            tk->token[1] = '\0';
            
            printf("structuremember");
            tk->current = tk->current+1;
            break;
            
            
        case '=':
            
            tk->token[0] = '=';
            
            
            if(token[1] == '='){
                
                tk->token[1] = '=';
                tk->token[2] = '\0';
                
                printf("equals");
                tk->current = tk->current+2;
            }else{
                
                tk->token[1] = '\0';
                
                printf("assign");
                tk->current = tk->current+1;
            }
            
            break;
            
        case '+':
            
            tk->token[0] = '+';
            
            if(token[1] == '+'){
                
                tk->token[1] = '+';
                tk->token[2] = '\0';
                
                printf("increment");
                tk->current = tk->current+2;
            }else if(token[1] == '='){
                
                tk->token[1] = '=';
                tk->token[2] = '\0';
                
                printf("plusequals");
                tk->current = tk->current+2;
            }else{
                
                tk->token[1] = '\0';
                
                printf("plus");
                tk->current = tk->current+1;
            }
            
            
            break;
            
        case '-':
            
            tk->token[0] = '-';
            
            if(token[1] == '-'){
                
                tk->token[1] = '-';
                tk->token[2] = '\0';
                
                printf("decrement");
                tk->current = tk->current+2;
            }else if(token[1] == '='){
                
                tk->token[1] = '=';
                tk->token[2] = '\0';
                
                printf("minusequals");
                tk->current = tk->current+2;
            }else if(token[1] == '>'){
                
                tk->token[1] = '>';
                tk->token[2] = '\0';
                
                printf("structurepointer");
                tk->current = tk->current+2;
            }else{
                
                tk->token[1] = '\0';
                
                printf("minus");
                tk->current = tk->current+1;
            }
            
            
            break;
            
        case '*':
            
            tk->token[0] = '*';
            
            
            if(token[1] == '='){
                
                tk->token[1] = '=';
                tk->token[2] = '\0';
                
                printf("timesequals");
                tk->current = tk->current+2;
            }else{
                
                tk->token[1] = '\0';
                
                printf("multiply");
                tk->current = tk->current+1;
            }
            
            
            break;
            
        case '/':
            
            tk->token[0] = '/';
            
            if(token[1] == '='){
                
                tk->token[1] = '=';
                tk->token[2] = '\0';
                
                printf("divideequals");
                tk->current = tk->current+2;
            }else{
                
                tk->token[1] = '\0';
                
                printf("divide");
                tk->current = tk->current+1;
            }
            
            
            break;
            
        case '&':
            
            tk->token[0] = '&';
            
            if(token[1] == '='){
                
                tk->token[1] = '=';
                tk->token[2] = '\0';
                
                printf("bitwiseandequals");
                tk->current = tk->current+2;
            }else if(token[1] == '&'){
                
                tk->token[1] = '&';
                tk->token[2] = '\0';
                
                printf("logicaland");
                tk->current = tk->current+2;
            }else{
                
                tk->token[1] = '\0';
                
                printf("bitwiseand");
                tk->current = tk->current+1;
            }
            
            
            break;
            
        case '%':
            
            tk->token[0] = '%';
            
            if(token[1] == '='){
                
                tk->token[1] = '=';
                tk->token[2] = '\0';
                
                printf("modulusequals");
                tk->current = tk->current+2;
            }else{
                
                tk->token[1] = '\0';
                
                printf("modulus");
                tk->current = tk->current+1;
            }
            
            break;
            
        case '^':
            
            tk->token[0] = '^';
            
            
            if(token[1] == '='){
                
                tk->token[1] = '=';
                tk->token[2] = '\0';
                
                printf("bitwiseexclusiveorequals");
                tk->current = tk->current+2;
            }else{
                
                tk->token[1] = '\0';
                
                printf("bitwiseexclusiveor");
                tk->current = tk->current+1;
            }
            
            break;
            
            
        case '|':
            
            tk->token[0] = '|';
            
            
            if(token[1] == '='){
                
                tk->token[1] = '=';
                tk->token[2] = '\0';
                
                printf("bitwiseorequals");
                tk->current = tk->current+2;
            }else if(token[1] == '|'){
                
                tk->token[1] = '|';
                tk->token[2] = '\0';
                
                printf("logicalor");
                tk->current = tk->current+2;
            }else{
                
                tk->token[1] = '\0';
                
                printf("bitwiseor");
                tk->current = tk->current+1;
            }
            
            break;
            
            
        case '<':
            
            tk->token[0] = '<';
            
            if(token[1] == '='){
                
                tk->token[1] = '=';
                tk->token[2] = '\0';
                
                printf("lessorequal");
                tk->current = tk->current+2;
            }else if(token[1] == '<'){
                
                tk->token[1] = '<';
                
                if(token[2] == '='){
                    
                    tk->token[2] = '=';
                    tk->token[3] = '\0';
                    
                    printf("shiftleftequals");
                    tk->current = tk->current+3;
                }else{
                    
                    tk->token[2] = '\0';
                    
                    printf("shiftleft");
                    tk->current = tk->current+2;
                }
            }else{
                
                tk->token[1] = '\0';
                
                printf("lessthan");
                tk->current = tk->current+1;
            }
            
            break;
            
        case '>':
            
            tk->token[0] = '>';
            
            if(token[1] == '='){
                
                tk->token[1] = '=';
                tk->token[2] = '\0';
                
                printf("greaterorequal");
                tk->current = tk->current+2;
            }else if(token[1] == '>'){
                
                tk->token[1] = '>';
                
                if(token[2] == '='){
                    
                    tk->token[2] = '=';
                    tk->token[3] = '\0';
                    
                    printf("shiftrightequals");
                    tk->current = tk->current+3;
                }else{
                    
                    tk->token[2] = '\0';
                    
                    printf("shiftright");
                    tk->current = tk->current+2;
                }
            }else{
                
                tk->token[1] = '\0';
                
                printf("greaterthan");
                tk->current = tk->current+1;
            }
            
            break;
            
            
        case '!':
            
            tk->token[0] = '!';
            
            if(token[1] == '='){
                
                tk->token[1] = '=';
                tk->token[2] = '\0';
                
                printf("notequals");
                tk->current = tk->current+2;
            }else{
                
                tk->token[1] = '\0';
                
                printf("negate");
                tk->current = tk->current+1;
            }
            
            break;
            
            
        case '~':
            
            tk->token[0] = '~';
            tk->token[1] = '\0';
            
            printf("onescomplement");
            tk->current = tk->current+1;
            
            break;
            
    }
}

/* getNumber() is called when TKGetNextToken() encounters a digit.
 * getNumber() returns the type of numeric representation and sets the
 * next token equal to it. It returns an error if there is something wrong
 * with the number representation.
 * @param tokenizer tk
 */
void getNumber(TokenizerT *tk){
    int i, j, k;
    if(tk->current[0] == '0'){
        if(tk->current[1] == 'x' || tk->current[1] == 'X'){
            if(!isdigit(tk->current[2]) && tk->current[2] != 'a' && tk->current[2] != 'b' && tk->current[2] != 'c' && tk->current[2] != 'd' && tk->current[2] != 'e' && tk->current[2] != 'f' && tk->current[2] != 'A' && tk->current[2] != 'B' && tk->current[2] != 'C' && tk->current[2] != 'D' && tk->current[2] != 'E' && tk->current[2] != 'F'){
                tk->token[0] = '0';
                tk->token[1] = tk->current[1];
                tk->token[2] = '\0';
                tk->current += 2;
                type = MAL;
                printf("Malformed Hex");
                return;
            }
            for(i = 2; i <= strlen(tk->current); i++){
                if(!isdigit(tk->current[i]) && tk->current[i] != 'a' && tk->current[i] != 'b' && tk->current[i] != 'c' && tk->current[i] != 'd' && tk->current[i] != 'e' && tk->current[i] != 'f' && tk->current[i] != 'A' && tk->current[i] != 'B' && tk->current[i] != 'C' && tk->current[i] != 'D' && tk->current[i] != 'E' && tk->current[i] != 'F'){
                    copySubstringToTokenSetType(tk, i, HEX);
                    return;
                }
            }
        }
        if(isdigit(tk->current[1]) && tk->current[1] != '9' && tk->current[1] != '8'){
            for(i = 0; i <= strlen(tk->current); i++){
                if(!isdigit(tk->current[i])){
                    copySubstringToTokenSetType(tk, i, OCTAL);
                    return;
                }
                if(tk->current[i] == '8' || tk->current[i] == '9'){
                    for(j = i; j <= strlen(tk->current); j++){
                        if(!isdigit(tk->current[j])){
                            copySubstringToTokenSetType(tk, j, DECIMAL);
                            return;
                        }
                    }
                }
            }
        }
        if(tk->current[1] == '.'){
            if(isdigit(tk->current[2])){
                for(i = 2; i <= strlen(tk->current); i++){
                    if(!isdigit(tk->current[i])){
                        if(tk->current[i] == 'e' || tk->current[i] == 'E'){
                            if(tk->current[i + 1] == '+' || tk->current[i + 1] == '-'){
                                if(isdigit(tk->current[i + 2])){
                                    for(j = i + 2; j <= strlen(tk->current); j++){
                                        if(!isdigit(tk->current[j])){
                                            copySubstringToTokenSetType(tk, j, FLOATING_POINT);
                                            return;
                                        }
                                    }
                                } else {
                                    copySubstringToTokenSetType(tk, i + 2, MAL);
                                    printf("Malformed Floating Point Number");
                                    return;
                                }
                            } else if(isdigit(tk->current[i + 1])){
                                for(j = i + 1; j <= strlen(tk->current); j++){
                                    if(!isdigit(tk->current[j])){
                                        copySubstringToTokenSetType(tk, j, FLOATING_POINT);
                                        return;
                                    }
                                }
                            } else {
                                copySubstringToTokenSetType(tk, i + 1, MAL);
                                printf("Malformed Floating Point Number");
                                return;
                            }
                        }
                        copySubstringToTokenSetType(tk, i, FLOATING_POINT);
                        return;
                    }
                }
            } else {
                tk->token[0] = '0';
                tk->token[1] = '.';
                tk->token[2] = '\0';
                tk->current+=2;
                type = MAL;
                printf("Malformed Floating Point Number");
                return;
            }
        }
        tk->token[0] = '0';
        tk->token[1] = '\0';
        type = DECIMAL;
        tk->current++;
    } else {
        for(i = 0; i <= strlen(tk->current); i++){
            if(tk->current[i] == '.'){
                if(isdigit(tk->current[i + 1])){
                    for(j = i + 2; j <= strlen(tk->current); j++){
                        if(!isdigit(tk->current[j])){
                            if(tk->current[j] == 'e' || tk->current[j] == 'E'){
                                if(tk->current[j + 1] == '+' || tk->current[j + 1] == '-'){
                                    if(isdigit(tk->current[j + 2])){
                                        for(k = j + 2; k <= strlen(tk->current); k++){
                                            if(!isdigit(tk->current[k])){
                                                copySubstringToTokenSetType(tk, k, FLOATING_POINT);
                                                return;
                                            }
                                        }
                                    } else {
                                        copySubstringToTokenSetType(tk, j + 2, MAL);
                                        printf("Malformed Floating Point Number");
                                        return;
                                    }
                                } else if(isdigit(tk->current[j + 1])){
                                    for(k = j + 1; k <= strlen(tk->current); k++){
                                        if(!isdigit(tk->current[k])){
                                            copySubstringToTokenSetType(tk, k, FLOATING_POINT);
                                            return;
                                        }
                                    }
                                } else {
                                    copySubstringToTokenSetType(tk, j + 1, MAL);
                                    printf("Malformed Floating Point Number");
                                    return;
                                }
                            }
                            copySubstringToTokenSetType(tk, j, FLOATING_POINT);
                            return;
                        }
                    }
                }else {
                    tk->token[0] = tk->current[0];
                    tk->token[1] = '.';
                    tk->token[2] = '\0';
                    tk->current+=2;
                    type = MAL;
                    printf("Malformed Floating Point Number");
                    return;
                } 
            } else if(!isdigit(tk->current[i])){
                copySubstringToTokenSetType(tk, i, DECIMAL);
                return;
            }
        }
        for(i = 0; i <= strlen(tk->current); i++){
            if(tk->current[i] == 'e' || tk->current[i] == 'E'){
                if(tk->current[i + 1] == '+' || tk->current[i + 1] == '-'){
                    if(isdigit(tk->current[i + 2])){
                        for(j = i + 2; j <= strlen(tk->current); j++){
                            if(!isdigit(tk->current[j])){
                                copySubstringToTokenSetType(tk, j, FLOATING_POINT);
                                return;
                            }
                        }
                    } else {
                        copySubstringToTokenSetType(tk, i + 2, MAL);
                        printf("Malformed Floating Point Number");
                        return;
                    }
                } else if(isdigit(tk->current[i + 1])){
                    for(j = i + 1; j <= strlen(tk->current); j++){
                        if(!isdigit(tk->current[j])){
                            copySubstringToTokenSetType(tk, j, FLOATING_POINT);
                            return;
                        }
                    }
                } else {
                    copySubstringToTokenSetType(tk, i + 1, MAL);
                    printf("Malformed Floating Point Number");
                    return;
                }
            }
        }
        for(i = 0; i <= strlen(tk->current); i++){
            if(!isdigit(tk->current[i])){
                copySubstringToTokenSetType(tk, i, DECIMAL);
                return;
            }
        }
    }
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken( TokenizerT * tk ) {
    
    int i, j, index;
    
    for(i = 0; i < strlen(tk->current); i++){
        while(isspace(tk->current[i])){
            tk->current = &tk->current[1]; //deals with case of spaces in the beginning of input, multiple spaces
        }
        if(tk->current[i] == 0x27){  //checks if single quote
            for(j = 1; j < strlen(tk->current); j++){
                if(tk->current[j] == 0x27){
                    strncpy(tk->token, tk->current + 1, j - 1);
                    tk->token[j - 1] = '\0';
                    tk->current = &tk->current[j + 1];
                    type = QUOTES;
                    return tk->token;
                }
            }
        }
        if(tk->current[i] == 0x22){ //checks if double quote
            for(j = 1; j < strlen(tk->current); j++){
                if(tk->current[j] == 0x22){
                    strncpy(tk->token, tk->current + 1, j - 1);
                    tk->token[j - 1] = '\0';
                    tk->current = &tk->current[j + 1];
                    type = QUOTES;
                    return tk->token;
                }
            }
        }
        if(tk->current[i] == '/' && tk->current[i + 1] == '*'){ //checks if in-line comment
            for(j = 2; j < strlen(tk->current); j++){
                if(tk->current[j] == '*' && tk->current[j + 1] == '/'){
                    strncpy(tk->token, tk->current, j + 2);
                    tk->token[j + 2] = '\0';
                    tk->current = &tk->current[j + 2];
                    type = C_COMMENT;
                    return tk->token;
                }
            }
        }
        if(tk->current[i] == '/' && tk->current[i + 1] == '/'){ //checks if multi-line comment
            for(j = 2; j < strlen(tk->current); j++){
                if(tk->current[j] == '\n'){
                    strncpy(tk->token, tk->current, j + 2);
                    tk->token[j + 2] = '\0';
                    tk->current = &tk->current[j + 2];
                    type = C_COMMENT;
                    return tk->token;
                }
            }
            return NULL;
        }
        if(isalpha(tk->current[i])){ //checks if word
            for(j = i; j <= strlen(tk->current); j++){
                if(isspace(tk->current[j]) || !isalnum(tk->current[j]) || tk->current[j] == '\0'){
                    if(j == 0){ j = 1; }
                    strncpy(tk->token, tk->current, j);
                    tk->token[j] = '\0';
                    tk->current = &tk->current[j];
                    for(index = 0; index < sizeof(KEYWORDS) / sizeof(KEYWORDS[0]); index++){ //checks if C-keyword
                        if(strcmp(tk->token, KEYWORDS[index]) == 0){
                            type = C_KEYWORD;
                            break;
                        } else {
                            type = WORD;
                        }
                    }
                    return tk->token;
                }
            }
        }
        if(isdigit(tk->current[i])){ //checks if a numeric representation
            getNumber(tk);
            return tk->token;
        } else if(!isalpha(tk->current[i]) && !isdigit(tk->current[i]) && tk->current[i] != '\0'){ //checks if it is an operator
            printOperator(tk);
            type = C_OPERATOR;
            return tk->token;
        }
    }
    return NULL;
}

/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {
    if(argv[1] == NULL){
        return 1;
    }
    TokenizerT *tk = TKCreate(argv[1]);
    while(tk->current[0] != '\0'){
        char *token = TKGetNextToken(tk);
        if(token == NULL){
            break;
        }
        switch(type){
            case WORD:
                printf("Word");
                break;
            case DECIMAL:
                printf("Decimal");
                break;
            case OCTAL:
                printf("Octal");
                break;
            case HEX:
                printf("Hex");
                break;
            case FLOATING_POINT:
                printf("Floating Point");
                break;
            case C_OPERATOR:
                break;
            case C_KEYWORD:
                printf("\"%s\" Keyword\n", tk->token);
                break;
            case C_COMMENT:
                break;
            case QUOTES:
                printf("Quote");
                break;
            case MAL:
                break;
        }
        if(type != C_COMMENT && type != C_KEYWORD){
            printf(" \"%s\"\n", token);
        }
    }
    TKDestroy(tk);
    return 0;
}
