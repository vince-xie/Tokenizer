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
			
			
			//CONTINUE HERE
		
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
			
		
		case '~':
		
			tk->token[0] = '~';
			tk->token[1] = '\0';
		
			printf("onescomplement");
			tk->current = tk->current+1;
		
		
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
        while(tk->current[i] == 0x20 || tk->current[i] == 0x09 || tk->current[i] == 0x0b || tk->current[i] == 0x0c || tk->current[i] == 0x0a || tk->current[i] == 0x0d){
            tk->current = &tk->current[1]; //deals with case of spaces in the beginning of input, multiple spaces
        }
        if(tk->current[i] == 0x27){  //checks if quote
            for(j = 1; j < strlen(tk->current); j++){
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
            for(j = 1; j < strlen(tk->current); j++){
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
        if(tk->current[i] == '/' && tk->current[i + 1] == '/'){
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
                if(tk->current[j] == 0x20 || tk->current[j] == 0x09 || tk->current[j] == 0x0b || tk->current[j] == 0x0c || tk->current[j] == 0x0a || tk->current[j] == 0x0d || !isalpha(tk->current[j]) || tk->current[j] == '\0'){
                    if(j == 0){ j = 1; }
                    strncpy(tk->token, tk->current, j);
                    tk->token[j] = '\0';
                    tk->current = &tk->current[j];
                    for(index = 0; index < sizeof(KEYWORDS) / sizeof(KEYWORDS[0]); index++){
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
            if(i == 0){ i = 1; }
            strncpy(tk->token, tk->current, i);
            tk->token[i] = '\0';
            tk->current = &tk->current[i];
            type = DECIMAL; //temporary
            return tk->token;
        } else if(!isalpha(tk->current[i]) && !isdigit(tk->current[i]) && tk->current[i] != '\0'){ //checks if it is an operator
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
