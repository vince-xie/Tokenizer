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

void printOperator(TokenizerT * tk){
	
	char first;
	int bool;
	
	char * token = tk->token;
	
	if(token.length() == 0){
		return;
	}
	
	first = token[0];
	
	switch(first){
	
		case '(':
			printf("leftparenthesis");
			tk->token = token[1];
			break;
		
		case ')':
			printf("rightparenthesis");
			tk->token = token[1];
			break;
		
		case '[':
			printf("leftbrace");
			tk->token = token[1];
			break;
		
		case ']':
			printf("rightbrace");
			tk->token = token[1];
			break;
		
		case '.':
			printf("structuremember");
			tk->token = token[1];
			break;
		
		case '=':
			
			if(token[1] == '='){
				printf("equals");
				tk->token = token[2];
			}else{
				printf("assign");
				tk->token = token[1];
			}
			
		case '+':
		
			if(token[1] == '+'){
				printf("increment");
				tk->token = token[2];
			}else if(token[1] == '='){
				printf("plusequals");
				tk->token = token[2];
			}else{
				printf("plus");
				tk->token = token[1];
			}
		
			
			break;
		
		case '-':
		
			if(token[1] == '-'){
				printf("decrement");
				tk->token = token[2];
			}else if(token[1] == '='){
				printf("minusequals");
				tk->token = token[2];
			}else if(token[1] == '>'){
				printf("structurepointer");
				tk->token = token[2];
			}else{
				printf("minus");
				tk->token = token[1];
			}
		
			
			break;
			
		case '*':
		
			if(token[1] == '='){
				printf("timesequals");
				tk->token = token[2];
			}else{
				printf("multiply");
				tk->token = token[1];
			}
		
			
			break;
			
		case '/':
		
			if(token[1] == '='){
				printf("divideequals");
				tk->token = token[2];
			}else{
				printf("divide");
				tk->token = token[1];
			}
		
			
			break;	
			
		case '&':
		
			if(token[1] == '='){
				printf("bitwiseandequals");
				tk->token = token[2];
			}else if(token[1] == '&'){
				printf("logicaland");
				tk->token = token[2];
			}else{
				printf("bitwiseand");
				tk->token = token[1];
			}
		
			
			break;	
			
		case '%':
		
			if(token[1] == '='){
				printf("modulusequals");
				tk->token = token[2];
			}else{
				printf("modulus");
				tk->token = token[1];
			}
			
		case '^':
		
			if(token[1] == '='){
				printf("bitwiseexclusiveorequals");
				tk->token = token[2];
			}else{
				printf("bitwiseexclusiveor");
				tk->token = token[1];
			}
			

			
		
		case '|':
		
			if(token[1] == '='){
				printf("bitwiseorequals");
				tk->token = token[2];
			}else if(token[1] == '|'){
				printf("logicalor");
				tk->token = token[2];
			}else{
				printf("bitwiseor");
				tk->token = token[1];
			}
			
		
		case '<':
		
			if(token[1] == '='){
				printf("lessorequal");
				tk->token = token[2];
			}else if(token[1] == '<'){
				if(token[2] == '='){
					printf("shiftleftequals");
					tk->token = token[3];
				}else{
					printf("shiftleft");
					tk->token = token[2];
				}
			}else{
				printf("lessthan");
				tk->token = token[1];
			}
			
		case '>':
		
			if(token[1] == '='){
				printf("greaterorequal");
				tk->token = token[2];
			}else if(token[1] == '>'){
				if(token[2] == '='){
					printf("shiftrightequals");
					tk->token = token[3];
				}else{
					printf("shiftright");
					tk->token = token[2];
				}
			}else{
				printf("greaterthan");
				tk->token = token[1];
			}
		
		
		case '!':
		
			if(token[1] == '='){
				printf("notequals");
				tk->token = token[2];
			}else{
				printf("negate");
				tk->token = token[1];
			}
			
		
		case '~':
		
			printf("onescomplement");
			tk->token = token[1];
		
		
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
    for(int i = 0; i < strlen(tk->current); i++){
        while(tk->current[i] == 0x20 || tk->current[i] == 0x09 || tk->current[i] == 0x0b || tk->current[i] == 0x0c || tk->current[i] == 0x0a || tk->current[i] == 0x0d){
            tk->current = &tk->current[1]; //deals with case of spaces in the beginning of input, multiple spaces
        }
        if(tk->current[i] == 0x27){  //checks if quote
            for(int j = 1; j < strlen(tk->current); j++){
                if(tk->current[j] == 0x27){
                    strncpy(tk->token, tk->current, j + 1);
                    tk->token[j + 1] = '\0';
                    tk->current = &tk->current[j + 1];
                    type = QUOTES;
                    return tk->token;
                }
            }
        }
        if(tk->current[i] == 0x22){
            for(int j = 1; j < strlen(tk->current); j++){
                if(tk->current[j] == 0x22){
                    strncpy(tk->token, tk->current, j);
                    tk->token[j] = '\0';
                    tk->current = &tk->current[j];
                    type = QUOTES;
                    return tk->token;
                }
            }
        }
        if(tk->current[i] == '/' && tk->current[i + 1] == '*'){ //checks if comment
            for(int j = 2; j < strlen(tk->current); j++){
                if(tk->current[j] == '*' && tk->current[j + 1] == '/'){
                    strncpy(tk->token, tk->current, j + 2);
                    tk->token[j + 2] = '\0';
                    tk->current = &tk->current[j + 2];
                    type = C_COMMENT;
                    return tk->token;
                }
            }
        }
        if(tk->current[i] == '/' && tk->current[i + 1] == '/'){
            for(int j = 2; j < strlen(tk->current); j++){
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
            for(int j = i; j <= strlen(tk->current); j++){
                if(tk->current[j] == 0x20 || tk->current[j] == 0x09 || tk->current[j] == 0x0b || tk->current[j] == 0x0c || tk->current[j] == 0x0a || tk->current[j] == 0x0d || !isalpha(tk->current[j]) || tk->current[j] == '\0'){
                    if(j == 0){ j = 1; }
                    strncpy(tk->token, tk->current, j);
                    tk->token[j] = '\0';
                    tk->current = &tk->current[j];
                    for(int index = 0; index < sizeof(KEYWORDS) / sizeof(KEYWORDS[0]); index++){
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
        if(isnumber(tk->current[i])){ //checks if a numeric representation
            if(i == 0){ i = 1; }
            strncpy(tk->token, tk->current, i);
            tk->token[i] = '\0';
            tk->current = &tk->current[i];
            type = DECIMAL; //temporary
            return tk->token;
        } else if(!isalpha(tk->current[i]) && !isnumber(tk->current[i]) && tk->current[i] != '\0'){ //checks if it is an operator
            if(i == 0){ i = 1; }
            strncpy(tk->token, tk->current, i);
            tk->token[i] = '\0';
            tk->current = &tk->current[i];
            type = C_OPERATOR; //temporary
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
                printf("C Operator");
                break;
            case C_KEYWORD:
                printf("C Keyword");
                break;
            case C_COMMENT:
                break;
            case QUOTES:
                printf("Quotes");
                break;
            case MAL:
                printf("Error");
                break;
        }
        if(type != C_COMMENT){
            printf(" \"%s\"\n", token);
        }
    }
    TKDestroy(tk);
    return 0;
}
