/** WRITTEN BY MACARTHUR DIBY 11763241
* program that is a lexical analyzer in C or C++ that can identify *lexemes and tokens found in a source code file provided
*by the user. Once the analyzer has identified the lexemes of the *language and matched them to a token group,
*the program should print each lexeme / token pair to the screen. 
*/

/* front.c - a lexical analyzer system for simple arithmetic expressions */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>




/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define LESSER_OP 27
#define GREATER_OP 28
#define EQUAL_OP 29
#define NEQUAL_OP 30
#define LEQUAL_OP 31
#define GEQUAL_OP 32
#define SEMICOLON 33
#define INC_OP 34
#define DEC_OP 35
#define KEY_READ 36
#define KEY_WRITE 37
#define KEY_DO 38
#define KEY_OD 39
#define KEY_WHILE 40



/* Global Variable */
int nextToken;
char *tokenNames;
bool file= true;


/* Local Variables */
static int charClass;
static char lexeme [100];
static char nextChar;
static int lexLen;
static FILE *in_fp;


/* Local Function declarations */
static void error();
static void addChar();
static void getChar();
static void getNonBlank();
int lex();
void P();
void S();
void C();
void E();
void Eprime();
void T();
void Tprime();
void F();
void O();
void exit();

/******************************************************/
int main(int argc, char*argv[]) 
{
    printf("DCooke Parser :: R<11763241> \n");
    /* Open the input data file and process its contents */
    if ((in_fp = fopen("front.in", "r")) == NULL) {
      if("front.in"== NULL){
        printf("user did not provide a file as input");
        exit (2);
      }
      else{
        printf(" user did provide a file as input but the file does not exist ");
        exit(3);
    } 

    
}
  else {
        getChar();
        
            lex();
            P();
    // if file is true and next token is EOF 
    if ( file&& nextToken== EOF){
    printf(" syntax validated \n");
    exit(0);
    }
    
    else{
      exit(1);
      }
    }

  
  
  return 0;

}
/*****************************************************/
/* lookup - a function to lookup operators and parentheses and return the 
 * token */
static int lookup(char ch) {
    /*characters identifiers*/
    /*switch case statement  that will allow character to match with their token Names*/
    switch (ch) {

      /*case when we have '('to match it with its token names "LEFT_PAREN"*/
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            tokenNames = "LEFT_PAREN";
            break;

      /*case when we have ')'to match it with its token names "RIGHT_PAREN"*/
        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            tokenNames = "RIGHT_PAREN";
            break;

      /*case when we have '*'to match it with its token names "MULT_OP"*/
        case '*':
            addChar();
            nextToken = MULT_OP;
            tokenNames = "MULT_OP";
            break;

      /*case when we have '/'to match it with its token names "DIV_OP"*/
        case '/':
            addChar();
            nextToken = DIV_OP;
            tokenNames = "DIV_OP";
            break;

      /*case when we have ';'to match it with its token names "SEMICOLON"*/
         case ';':
            addChar();
            nextToken = SEMICOLON;
            tokenNames = "SEMICOLON";
            break;

      /*case when we have '='to match it with its token names "EQUAL_OP"*/
        case '=':
            addChar();  
            nextToken = EQUAL_OP;
            tokenNames = "EQUAL_OP";
            break;
        
      /*case when we have '+'to match it with its token names "ADD_OP" and "++" to match it with "INC_OP"*/
        case '+':
          addChar();
          getChar();
          /* if statement to see if after "+"the following char is "+" if yes it becomes"++" that is "INC_OP"*/
            if (nextChar == '+'){
            addChar();
            nextToken = INC_OP;
            tokenNames = "INC_OP";}
          /* else statement if we just encounter only "+" to set it to "ADD_OP"*/
           else {
              ungetc(nextChar,in_fp);
              nextToken = ADD_OP;
              tokenNames = "ADD_OP";
            }
            break;
      

       /*case when we have '-'to match it with its token names "SUB_OP" and "--" to match it with "DEC_OP"*/
        case '-':
            addChar();
            getChar();
          /* if statement to see if after "-"the following char is "-" if yes it becomes"--" that is "DEC_OP"*/
            if (nextChar == '-'){
              addChar();
              nextToken = DEC_OP;
              tokenNames = "DEC_OP";
            }
            /* else statement if we just encounter only "-" to set it to "SUB_OP"*/
           else {
              ungetc(nextChar,in_fp);
              nextToken = SUB_OP;
              tokenNames = "SUB_OP";
            }
            break;      

      /*case when we have '<'to match it with its token names "LESSER_OP" and "<=" to match it with "LEQUAL_OP"*/
        case '<':
            addChar();
            getChar();

          /* if statement to see if after "<"the following char is "=" if yes it becomes"<=" that is "LEQUAL_OP"*/
            if (nextChar == '='){
              addChar();
              nextToken = LEQUAL_OP;
              tokenNames = "LEQUAL_OP";
            } 
            /* else statement if we just encounter only "<" to set it to "LESSER_OP"*/
           else {
              ungetc(nextChar,in_fp);
              nextToken = LESSER_OP;
              tokenNames = "LESSER_OP";
            }
            break;



      /*case when we have '>'to match it with its token names "GREATER_OP" and ">=" to match it with "GEQUAL_OP"*/
        case '>':
            addChar();
            getChar();
          
         /* if statement to see if after ">"the following char is "=" if yes it becomes">=" that is "GEQUAL_OP"*/   
            if (nextChar == '='){
              addChar();
              
              nextToken = GEQUAL_OP;
              tokenNames = "GEQUAL_OP";
            }
         /* else statement if we just encounter only ">" to set it to "GREATER_OP"*/     
            else{
            ungetc(nextChar, in_fp);
            nextToken= GREATER_OP;
            tokenNames="GREATER_OP";
          }
            break;
      
        /*case when we have ':='to match it with its token names "ASSIGN_OP" */
        case ':':
            addChar();
            getChar();
            tokenNames ="UNKNOWN";
          /* if statement to see if after ":"the following char is "=" if yes it becomes":=" that is "ASSIGN_OP"*/
            if (nextChar == '='){
              addChar();
              nextToken = ASSIGN_OP;
              tokenNames = "ASSIGN_OP";
              }
           
            break;
      
       /*case when we have '!='to match it with its token names "NEQUAL_OP" */
       case '!':
            addChar();
            getChar();
            tokenNames ="UNKNOWN";
           /* if statement to see if after "!"the following char is "=" if yes it becomes":=" that is "NEQUAL_OP"*/
            if (nextChar == '='){
              addChar();
              nextToken = NEQUAL_OP;
              tokenNames = "NEQUAL_OP";
            }
            break;
      
        /*default case to set any other characters to token names "UNKNOWN"*/
        default:
            addChar();
            tokenNames ="UNKNOWN"; 
            break;
    }
    return nextToken;// return the next token 
}



/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
static void addChar() {
    /* if statement to conditionate lexlen to less than 98 and if not less that 98 it goes to else where it print the error*/
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    } else {
        printf("Error - lexeme is too long \n");
    }
}

/*****************************************************/
/* getChar - a function to get the next character of input and determine its 
 * character class */
static void getChar() {
    /* if statement that look if the character is in the files and also if the char is not EOF so that it match it as a letter , a digit or an unknown, else it matches it as EOF*/
    if ((nextChar = getc(in_fp)) != EOF) {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else charClass = UNKNOWN;
    } else {
        charClass = EOF;
    }
}




/*****************************************************/
/* getNonBlank - a function to call getChar until it returns a non-whitespace 
 * character */
static void getNonBlank() {
    while (isspace(nextChar)) getChar();
}

/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic expressions */
int lex() {
    lexLen = 0;
    
    getNonBlank();
    /*switch case statement to match any charclass to its parse identifiers*/
    switch (charClass) {
      
        /* Parse identifiers */

      /*case statements that match any groups of charclass that begins with a letter and contains a digits or no to tokenNames"IDENT" except for "do","while","read","write","od" which is going to match to their respectives KEY*/
        case LETTER:
            addChar();
            getChar();

              /*while loop to see if char class is letter or digit so it add*/
                while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
                  }
              /*if statement to see if lexeme is "do"so it mtches it to "KEY_DO"*/  
                if (strcmp(lexeme, "do") == 0) {
                nextToken = KEY_DO;
                tokenNames = "KEY_DO";
                
                }
              /*else if statement to see if lexeme is "od"so it mtches it to "KEY_OD"*/
              else if (strcmp(lexeme, "od") == 0) {
                nextToken = KEY_OD;
                tokenNames = "KEY_OD";
                
               }
              /*else if statement to see if lexeme is "do"so it mtches it to "KEY_DO"*/
              else if (strcmp(lexeme, "while") == 0) {
                nextToken = KEY_WHILE;
                tokenNames = "KEY_WHILE";
                
               }

              /*else if statement to see if lexeme is "read"so it mtches it to "KEY_READ"*/
              else if (strcmp(lexeme, "read") == 0) {
                nextToken = KEY_READ;
                tokenNames = "KEY_READ";
                
               }
              /*else if statement to see if lexeme is "write"so it mtches it to "KEY_WRITE"*/
              else if (strcmp(lexeme, "write") == 0) {
                nextToken = KEY_WRITE;
                tokenNames = "KEY_WRITE";
                
               }
              /*if statement to set if lexeme different than any above to be set as "IDENT"*/
              if (strcmp(lexeme, "do") != 0 && strcmp(lexeme, "od") != 0  &&           strcmp(lexeme, "while") != 0  && strcmp(lexeme, "write") != 0  && strcmp(lexeme, "read") != 0 )        {

                nextToken = IDENT;
                tokenNames = "IDENT";
              }
            break;
      

        /* Parse integer literals */
        /*case statement that set any groups of DIGIT as "INT_LIT"*/
        case DIGIT:
            addChar();
            getChar();

            /* while loop to see if charclass is digit so it adds*/
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
            tokenNames= "INT_LIT";
            break;

        /* Parentheses and operators */
        /*any others char is set to "UNKNOWN"*/
        case UNKNOWN:
            lookup(nextChar);
            getChar();
            break;

              
        /* EOF */
        case EOF:
            nextToken = EOF;
            lexeme[0] = 'E';
            lexeme[1] = 'O';
            lexeme[2] = 'F';
            lexeme[3] = 0;
            break;
            
    } /* End of switch */
    
  /* End of function lex */
}


/*Parser written by Macarthur Diby  based upon  the following following grammar rule
P ::= S
S ::= V:=E | read(V) | write(V) | while (C) do S od | O | S;S
C ::= E < E | E > E | E = E | E != E | E <= E | E >= E
E ::= T | E + T | E - T
T ::= F | T * F | T / F
F ::= (E) | O | N | V
O ::= ++V | --V
V ::= a | b | … | y | z | aV | bV | … | yV | zV
N ::= 0 | 1 | … | 8 | 9 | 0N | 1N | … | 8N | 9N*/



/*P ::= S*/
void P() 
{
  
    /* Parse the first S */
    S();

} /* End of function P */


/*S ::= V:=E | read(V) | write(V) | while (C) do S od | O | S;S*/
void S() 
{
  // V:=E
  //if nexxt token is Ident call lex
  if(nextToken== IDENT){
    lex();
    //if after Ident it is assign op call lex and E()
    if(nextToken== ASSIGN_OP){
      lex();
      E();
      //if after V:=E we have ; then call lex and S
      if (nextToken== SEMICOLON){
        lex();
        S();
      }
    }
    // if after seeing an Ident we do not see Assign OP it call error
    else {
      error();
    }
    
  }// end V:=E

  
  //read(V) | write(V)
  // else if we see KEY Read or KEy write we call lex
 else if( nextToken== KEY_READ || nextToken== KEY_WRITE){
   lex();
   //after seeing read and write  if we see Left paren we call lex
   if(nextToken== LEFT_PAREN){
     lex();
     //after seeing read and write and Left paren we verify if we see an ident and call lex
     if(nextToken== IDENT){
       lex();
      //after seeing read and write , Left paren , ident we verify if we see an right paren and call lex
      if (nextToken== RIGHT_PAREN){
       lex();
        //after seeing read and write , Left paren , ident, right we verify if we see a ; and call lex and S
       if(nextToken== SEMICOLON){
         lex();
         S();
       }
     }
     }
   }
    //if after seeing read or write  we do not see left paren it goes to error
   else{
     error();
   }
 }// end of read(V) | write(V)

  // while (C) do S od
  // else if we have while call lex
  else if (nextToken== KEY_WHILE){
    lex();
    //if after while we have left paren call C
    if(nextToken== LEFT_PAREN){
      lex();
      C();
      // if after while left paren C we have close paren call lex
      if(nextToken== RIGHT_PAREN){
        lex();
        // if after while left paren C w close paren we have do call lex and S
        if(nextToken== KEY_DO){
          lex();
          S();
          
          //if after while(c)do S we have od call lex
          if (nextToken== KEY_OD){
            lex();
            // if after while(c)do S od we have semi colon call lex and S
            if (nextToken== SEMICOLON){
              lex();
              S();
            }
            
          }
          // else we see while(c)do S but no od it is error
          else{
           error();
          }
        }
        // else we see while(c) but no do it is error
        else{
            error();
          }
      }
      // else we see while (c no ) it is an error
      else{
            error();
          }
    }
    // else we see while  but no( it is an error
    else{
            error();
          }
    
  }// end of while (C) do S od

  
  // O
  // else if we see ++ or -- we get lex
  else if (nextToken== INC_OP ||nextToken== DEC_OP){
    lex();
    // if we see ++ or -- we verify to see if we have an ident 
    if(nextToken== IDENT){
      lex();
      // if we see ++IDent and a semicolon we call lex and S
      if (nextToken== SEMICOLON){
        lex();
        S();
        }
    }
    // else we se ++ and not an Ident it is error
    else{
      error();
    }
    
  }// end of O

  // else when next token is not EOF error
  else {
    if (nextToken!= EOF)
      error();
    
    
  }

  
}/*END OF VOICE S*/


/*C ::= E < E | E > E | E = E | E != E | E <= E | E >= E*/
void C() 
{
    

    /* Parse the E */
    E();

    /* if the next token is >,<,=>,=< ,=,!= get
    the next token and parse E */
    if (nextToken == LEQUAL_OP || nextToken == GEQUAL_OP|| nextToken ==LESSER_OP || nextToken ==EQUAL_OP|| nextToken ==GREATER_OP|| nextToken ==NEQUAL_OP) {
        lex();
        E();
    }
  
  

    
} /* End of function C */


/*E ::= TE'*/
void E() 
{
    

    /* Parse the T then Eprime()*/
    T();
    Eprime();
    

} /* End of function E */


/*E'::=+TE'|-TE'*/
void Eprime(){
  // if next token is +or - lex then T and E prime
  if (nextToken == ADD_OP || nextToken == SUB_OP) {
        lex();
        T();
        Eprime();
    }
  

}// end of Eprime


/*T ::= FT'*/
void T() 
{
    

    /* Parse T then T' */
    F();

    Tprime();

    
} /* End of function T */

/*T'= *FT'|/FT'*/
void Tprime(){
   if (nextToken == MULT_OP || nextToken == DIV_OP) {
        lex();
        F();
        Tprime();
      
    }
    
  
  
  
  
}// end of Tprime

/*F ::= (E) | O | N | V*/
void F(){
//(E)
// if we see letf paren call lex and E
if (nextToken== LEFT_PAREN){
  lex();
  E();
            //if after left paren , E, we have ) call lex
            if (nextToken == RIGHT_PAREN) {
                lex(); 
            }
            //else we see left paren E but not right paren we have error 
            else { 
                error();
            }
  
      }
  
//O
//else if we see ++ and -- we call lex
else if (nextToken== INC_OP|| nextToken== DEC_OP){
  lex();
  // when we see ++ and -- if we see ident we call lex
  if (nextToken== IDENT){
    lex();
  }
  // when we see ++ but not an ident we go to error
  else{
    error();
  }
}

//V
else if(nextToken== IDENT){
  lex();  
}

//N
else if(nextToken== INT_LIT){
  lex();  
}
// else it is not everything up it is an error
else{
 error();
}  
}//end of void F



/*O ::= ++V | --V*/
void O() 
{
    /*if  next token is ++ or --, get
    the next token  */
     if (nextToken == INC_OP || nextToken == DEC_OP) {
        lex();
        //if after ++ we have an ident call lex
        if (nextToken== IDENT){
          lex();
        }
        // else after ++ it s not an ident error
       else{
         error();
       }
    }

} /* End of function O */






static void error() 
{
      // bool file is set to false
      file = false;
    // print the error that we encounter and the lexeme error and the token names
    printf("Error encounter: The next lexeme was %s and the next token was %s\n",lexeme,tokenNames);
}

void exit (int status);


