#include <stdio.h>
#include <stdlib.h>
#include "list.h"
const int M_ROWS = 9;
const int M_COLUMN = 9;

typedef struct{
   int sudo[9][9];
}Node;


Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}


Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

//funcion para verificar si existe un unico numero dado.
int has_unique_rows(int sudoku[M_ROWS][M_COLUMN], int row)
{
  int *verify = (int*) calloc(10, sizeof(int));

  for(int i = 0 ; i < 9 ; i++)
  { 
    if(sudoku[row][i] != 0)
    {
      verify[sudoku[row][i]] +=1;

      if(verify[sudoku[row][i]] == 2) 
      {
        free(verify);
        return 0;
      }
      
    }
  }

  free(verify);
  return 1;
}

int has_unique_columns(int sudoku[M_ROWS][M_COLUMN], int column)
{
  int *verify = (int*) calloc(10, sizeof(int));

  for(int i = 0 ; i < 9 ; i++)
  { 
    if(sudoku[i][column] != 0)
    {
      verify[sudoku[i][column]] +=1;

      if(verify[sudoku[i][column]] == 2) 
      {
        free(verify);
        return 0;
      }
    }
  }

  free(verify);
  return 1;
}


int has_valid_submatrix(int sudoku[M_ROWS][M_COLUMN], int k)
{  
  int *verify = (int*) calloc(10, sizeof(int));


  for(int p=0 ; p<9 ; p++){
    int i=3*(k/3) + (p/3) ;
    int j=3*(k%3) + (p%3) ;

    if(sudoku[i][j] != 0)
    {
      verify[sudoku[i][j]] +=1;

      if(verify[sudoku[i][j]] == 2) 
      {
        free(verify);
        return 0;
      }
      
    }
  }

  free(verify);
  return 1;
}


int is_valid(Node* n){
  
  for(int i = 0 ; i < 9 ; i++)
  {
    if(has_unique_rows(n->sudo, i) == 0) return 0;
    for(int j = 0 ; j < 9; j++)
    {
      if(has_unique_columns(n->sudo, j) == 0) return 0;
    }
  }

  for(int k = 0 ; k < 9; k++)
  {
    if(has_valid_submatrix(n->sudo, k) == 0) return 0;
  }


  return 1;
}


List* get_adj_nodes(Node* n){
 
  List* list=createList();
  Node *newNode = createNode();
  int valido=0;

  for(int i = 0 ; i < 9 ; i++)
  {
    for(int j = 0 ; j < 9 ;j++)
    { 
      if(n->sudo[i][j] == 0)
      {
        for(int k = 1 ; k <= 9 ; k++)
        { 

          newNode= copy(n);
          valido = 1;

          newNode->sudo[i][j] = k;
          //print_node(newNode);
          if(is_valid(newNode) == 1)
          {
            pushBack(list, newNode);
            //printf("-----\n");
            //print_node(newNode);

          }
          else{
            free(newNode);
          }
          
        }
        break;
      }
           
    }
    if(valido == 1)
    {
      break;
    }
    
  }

  
  return list;
}


int is_final(Node* n){

  for(int i = 0 ; i < 9 ; i++)
  {
    for(int j = 0 ; j < 9 ; j++)
    {
      if(n->sudo[i][j] == 0) return 0;
    }
  }
  
    return 1;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/