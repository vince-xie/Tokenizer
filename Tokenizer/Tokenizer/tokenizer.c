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
    TokenizerT *token = (TokenizerT *)malloc(sizeof(TokenizerT *));
    token->token = (char *)malloc(sizeof(char *));
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
        if(tk->current[i] == ' '){
            if(i != 0){
               strncpy(tk->token, tk->current, i);
               tk->token[i] = '\0';
               tk->current = &tk->current[i + 1];
               return tk->token;
            } else {
                tk->current = &tk->current[i + 1];
            }
        }
        if(tk->current[i + 1] == '\0'){
            strncpy(tk->token, tk->current, i + 1);
            tk->token[i + 1] = '\0';
            tk->current = &tk->current[i + 1];
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
    printf("%s", argv[1]);
    TokenizerT *tk = TKCreate(argv[1]);
    while(tk->current[0] != '\0'){
        char *token = TKGetNextToken(tk);
        printf("\n%s", token);
    }
    TKDestroy(tk);
    return 0;
}
