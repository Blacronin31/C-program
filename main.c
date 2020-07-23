//  ===============================================================
//  = Names: Marcus Long,                                         =
//  = Crossword puzzle                                                =
//  ===============================================================


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define PAUSE system("pause")
    
#define NUMBER_OF_WORDS 16
#define MAX_STRING_SIZE 11
#define GRID_SIZE 20


// Function to sort the words in an alphabetical order & to print 4*4 grid.
void sortArray(char arr[NUMBER_OF_WORDS][MAX_STRING_SIZE], FILE *);

    
int main()
{
    // temporary fill the array with words so we don't have to type them everytime
    char words[NUMBER_OF_WORDS][MAX_STRING_SIZE] =
    { "basketball","football","cricket","wrestling","fencing","rowing","volleyball","baseball", "hockey","racing","running","bobsleigh","curling","dancing","bowling","tennis"};

    char grid[GRID_SIZE][GRID_SIZE] = {0};
    int i, j, r, count, a;
    
    //outputing a text file with a word search game inside the text document
    FILE *ptr;
    ptr = fopen("myTextFile.txt", "w");
    if (ptr == NULL){
        printf("Error Opening Output file.\n");
        system("pause");
        exit(-1);
    }
 
// Ask a user to input 16 words.
// temporary disable so it's easy to troublshoot

/*    printf("Please enter 16 words with 10 or fewer letters.\n");
 
    for (i = 0; i < NUMBER_OF_WORDS; i++)
        {
            scanf("%s", words[i]);
        }
*/

    sortArray(words, ptr);
    
// Converting all words into uppercase.
    for (i = 0; i < NUMBER_OF_WORDS; i++)
        {
            for (j = 0; words[i][j] != '\0'; j++)
                {
                   words[i][j] = toupper(words[i][j]);
                };
        };

    for (i = 1; i < NUMBER_OF_WORDS; i = i + 2) // placing words horizontally from left to right.
        {
            r = rand() % 10 + 1;
            for (j = 0; words[i][j] != '\0'; j++)
                {
                    grid[i - 1][j + r] = words[i][j];
                };
        };
    
    for (i = NUMBER_OF_WORDS; i >= 0; i = i - 2) // horizontally from right to left, backwards.
        {
            r = rand() % 10 + 1;
        
            // Calculating string length
            count = 0;
            while (words[i][count] != '\0')
                count++;
            
            for (j = count, a = r; j >= 0; j--, a++)
                {
                    grid[i+1][a] = words[i][j];
                };
        };
        
        
        r = rand() % 11; // vertically from top to bottom.
        for (j = 0; words[0][j] != '\0'; j++)
            {
                grid[j + r][0] = words[0][j];
            };
        
            
        count = 0; // vertically, backwards.
            while (words[NUMBER_OF_WORDS - 1][count] != '\0')
                count++;
      
        r = rand() % 11;
        for (j = count, a = r; j >= 0; j--, a++)
            {
                grid[a][GRID_SIZE-1] = words[NUMBER_OF_WORDS - 1][j];
            };


    
// Print the main 20*20 grid.
// Only random letters

    fprintf(ptr, "\n     ");
    for (i = 0; i < GRID_SIZE; i++)
        {
            fprintf(ptr, " %2d ", i + 1);
        }
    fprintf(ptr, "\n--------------------------------------------------------------------------------------");
    

    for (i = 0; i < GRID_SIZE; i++)
        {
            fprintf(ptr, "\n%2d | ", i + 1);
            for (j = 0; j < GRID_SIZE; j++)
            {
                
                if (grid[i][j] >='a' && grid[i][j]<='z' || grid[i][j] >='A' && grid[i][j]<='Z')
                    {}
                else grid[i][j] = (rand() % 26) + 65;
                
                fprintf(ptr, "%3c ", *(&(grid[i][j])));
            }
            fprintf(ptr, "   |");
        };

    fprintf(ptr, "\n--------------------------------------------------------------------------------------\n");
    
   
  
    
        return 0;
        
}; // End of Main

// Function to sort the words in an alphabetical order & to print 4*4 grid.
void sortArray(char arr[NUMBER_OF_WORDS][MAX_STRING_SIZE], FILE *ptr)
    {
        char temp[MAX_STRING_SIZE];
        int i, j;
        
        for (i = 0; i < NUMBER_OF_WORDS - 1 ; i++)
        {
            for (j = i + 1; j < MAX_STRING_SIZE; j++)
            {
                if (strcmp(arr[i], arr[j]) > 0)
                {
                    strcpy(temp, arr[i]);
                    strcpy(arr[i], arr[j]);
                    strcpy(arr[j], temp);
                }
            }
        }
        
        fprintf(ptr, "--------------------------------------------------------------------------------------\n");
    
        for (i = 0; i < 4; i++)
            {
                for (j = i; j < NUMBER_OF_WORDS; j = j + 4)
                {
                    fprintf(ptr, "%11s \t", arr[j]);
                }
                fprintf(ptr, "\n");
            }
        fprintf(ptr, "--------------------------------------------------------------------------------------\n\n");
    }
