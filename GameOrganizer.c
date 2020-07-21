//  ===============================================================
//  = Names: Marcus Long                                         =
//  = Personal Project                                           =
//  = *** GAME ORGANIZER PROGRAM ***                             =
//  ===============================================================


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define PAUSE system("pause")
#define CLS system ("cls")
#define FLUSH while(getchar() != '\n')

typedef struct {
    char name[100];   // game title
    float hPlayed;    // how many hours played
    float hTotal;     // how long is the game
    float rating;     // rate the game
} GAME; // game record

// PROTOTYPE

int enterSize();
void addGames(GAME **games, int *eSize, int size);
void removeGames(GAME **games, int *eSize);
void sortGamesName(GAME **games, int eSize);
void sortGamesRating(GAME **games, int eSize);
void searchGames(GAME **games, int eSize);
void displayGames(GAME **games, int eSize, FILE *myTextFile);
int numberCheck(char checkNum);
void freeGames(GAME **games, int eSize);


GAME *makeNode();


int main()
{
    int size, eSize = 0, choice = 0, check, num;
    GAME **games;
    FILE *myTextFile;
  
    size = enterSize();

    games = calloc(size, sizeof(GAME*));

    if ( games == NULL ) {
        printf("Failed to allocate memory! Exiting the program.\n");
        exit(-1); // stop the program
    }

    printf("\n\n\t\t  *** GAMMERS DELIGHT ***\n");
    printf("\t===============================================\n");
    printf("\t  1. Add a new game record\n\t  2. Remove a game record\n\t  3. Sort game records by name\n\t  4. Search game records\n\t  5. Display all game records\n\t  6. Exit the program\n");
    printf("\t===============================================\n\n");

    do
    {
        scanf("%i", &choice);
 
        switch(choice)
        {
            case 1:
                FLUSH;
                addGames(games, &eSize, size);
                break;
                
            case 2:
                removeGames(games, &eSize);
                break;

            case 3:
                
                if (eSize == 0 || eSize == 1)
                    printf("\nYou need to add some records first.\n");
                else {
                printf("Do you want to sort it by Name (1) or by Rating (2)?\n");
                
                do
                {
                    check = 1;
                    printf("[type 1 or 2]: ");
                    scanf("%i", &num); FLUSH;
                    if (num < 1 || num > 2) // making sure the user types correct option
                    check = 0;
                }
                while (check == 0);
                
                if(num == 1)
                    sortGamesName(games, eSize);
                else  sortGamesRating(games, eSize);
                }
                break;
                
            case 4:
                searchGames(games, eSize);
                break;

            case 5:
                displayGames(games, eSize, myTextFile);
                break;

            case 6:
                freeGames(games, eSize);
                break;

            default:
                printf("Error! Operator is not correct.");
        }

        printf("\n\t[ 1. ADD | 2. REMOVE | 3. SORT | 4. SEARCH | 5. DISPLAY | 6. EXIT ]\n");
}

    while (choice != 6);

    return 0;
}



void addGames(GAME **games, int *eSize, int size){

   char addAnother, checkNum;
   char name[100];
   int check;
   float hPlayed, hTotal, rating;

   do {
       addAnother = 'N';
       if (*eSize == size)
       {
           printf(">> You can't enter more records.\n");
           PAUSE;
           return;
       } // end if

       printf("Enter game name: ");
       scanf("%[^\n]", &name); FLUSH;

        do {
            checkNum = ' ';
            printf("Enter game play hours: ");
            scanf("%f%c", &hPlayed, &checkNum);
            check = numberCheck(checkNum); // making sure the user types only numbers
        }
        while (check == 0);
       
       printf(" %.2f ", hPlayed);
       
       do {
            checkNum = ' ';
            printf("Enter how long is the game: ");
            scanf("%f%c", &hTotal, &checkNum);
            check = numberCheck(checkNum); // making sure the user types only numbers
        }
        while (check == 0);
       
       do
        {
            check = 1; rating = 0;
            printf("Rate the game [from 1 to 10]: ");
            scanf("%f", &rating); FLUSH;
            if (rating < 1 || rating > 10) // making sure the user types correct rating
            check = 0;
        }
        while (check == 0);

       games[*eSize] = makeNode();

       strcpy(games[*eSize]->name, name);
       games[*eSize]->hPlayed = hPlayed;
       games[*eSize]->hTotal = hTotal;
       games[*eSize]->rating = rating;

       *eSize = *eSize + 1;

       printf("\nWould you like to add another game [Y/N]: ");
       scanf("%c", &addAnother); FLUSH;
       
       addAnother = toupper(addAnother);
       
   } while(addAnother == 'Y');

} // end addGames



void displayGames(GAME **games, int eSize, FILE *myTextFile){

  float gameCompletion, totalHours;
  myTextFile = fopen("myTextFile.txt", "w");

  if (eSize == 0) {
       printf("Go add games first.\n");
       PAUSE;
       return;
   }
   
   printf("\n\n");
   
    for (int i = 0; i < eSize; i++){
    gameCompletion = (games[i]->hPlayed * 100) / games[i]->hTotal;
    totalHours = totalHours + games[i]->hPlayed;
   
    printf("============ %i ============\n", i+1);
    printf("- Game Title:\t\t%s\n- Game Completion:\t%.0f%%\n- Rating:\t\t%.1f\n", games[i]->name, gameCompletion, games[i]->rating);
    printf("===========================\n\n");
        
    fprintf(myTextFile, "============ %i ============\n", i+1);
    fprintf(myTextFile, "- Game Title:\t\t%s\n- Game Completion:\t%.0f%%\n- Rating:\t\t%.1f\n", games[i]->name, gameCompletion, games[i]->rating);
    fprintf(myTextFile, "===========================\n\n");

   } // end for
   
   printf("---------------------------------------------------\n");
   printf("You spent %.2f hours playing %i game(s).\n", totalHours, eSize);
   printf("---------------------------------------------------\n\n");
    
   fprintf(myTextFile, "---------------------------------------------------\n");
   fprintf(myTextFile, "You spent %.2f hours playing %i game(s).\n", totalHours, eSize);
   fprintf(myTextFile, "---------------------------------------------------\n\n");
    
   fclose(myTextFile);
   PAUSE;

} // end displayGames



void removeGames(GAME **games, int *eSize){
    
    char removeAnother;
    int check, index;

    if (*eSize == 0) {
    printf("You need to add game records first.\n");
    PAUSE;
    return;
    }

    do {
       removeAnother = 'N';

       do
        {
            check = 1;
            printf("Enter index of the game that you want to remove");
            printf(" [from 1 to %i]: ", *eSize);
            scanf("%i", &index); FLUSH;
            if (index < 1 || index > *eSize) // making sure the user types correct index
            check = 0;
        }
        while (check == 0);
        
        for(int i = index - 1; i < *eSize - 1; i++)
            games[i] = games[i+1];
        *eSize = *eSize - 1;
        
        if (*eSize == 0) {
        printf("\nYou removed all the records.\n");
        PAUSE;
        return;
        }
        
        printf("\nWould you like to remove another game [Y/N]: ");
        scanf("%c", &removeAnother); FLUSH;
       
        removeAnother = toupper(removeAnother);
        
    } while (removeAnother != 'N');

} // end removeGames



void sortGamesName(GAME **games, int eSize){

    int bottom = eSize - 1;
    char swapped;
    GAME **temp;

        do {
            swapped = 'N';
            for (int i = 0; i < bottom; i++) {
                if (strcmp(games[i]->name, games[i + 1]->name) > 0) {
                    swapped = 'Y';
                    temp = games[i];
                    games[i] = games[i + 1];
                    games[i + 1] = temp;
                } // end if
            } // end for
            bottom--;
        } while (swapped == 'Y');
        printf("Games are sorted.\n");
   
} // end sortGamesName



void sortGamesRating(GAME **games, int eSize){

    int bottom = eSize - 1;
    char swapped;
    GAME **temp;

        do {
            swapped = 'N';
            for (int i = 0; i < bottom; i++) {
                if (games[i]->rating < games[i + 1]->rating) {
                    swapped = 'Y';
                    temp = games[i];
                    games[i] = games[i + 1];
                    games[i + 1] = temp;
                } // end if
            } // end for
            bottom--;
        } while (swapped == 'Y');
        printf("Games are sorted.\n");
   
} // end sortGamesRating



void searchGames(GAME **games, int eSize){

    char search[100], searchMore;
    float gameCompletion;

    do {
        searchMore = 'N';
           
        if (eSize == 0) {
            printf("You need to add game records first.\n");
            PAUSE;
            return;
        }
    
        FLUSH;
        printf("Enter game name: ");
        scanf("%[^\n]", &search); FLUSH;
                
        for(int i = 0; i < eSize; i++){
            
            if(strcmp(games[i]->name, search) == 0){
            
            gameCompletion = (games[i]->hPlayed * 100) / games[i]->hTotal;
            
            printf("\n============ %i ============\n", i+1);
            printf("- Game Title:\t\t%s\n- Game Completion:\t%.0f%\n- Rating:\t\t%.1f\n", games[i]->name, gameCompletion, games[i]->rating);
            printf("===========================\n\n");
            
            }
            
        }
        printf("\nWould you like to search for another game [Y/N]: ");
        scanf("%c", &searchMore); FLUSH;
       
        searchMore = toupper(searchMore);
    }
    while (searchMore == 'Y');
   
} // end searchGames



int enterSize(){
    int check, size;
    char checkNum;
    
    do {
            printf("Enter how many game records you want to store: ");
            scanf("%i%c", &size, &checkNum);
            check = numberCheck(checkNum);
            }
            while (check == 0);
    
    return size;
} // end enterSize


GAME *makeNode() {
    GAME* result;
    result = calloc(1, sizeof(GAME));

    if (result == NULL) {
        printf("No more room for anything");
        PAUSE;
        exit(-1);
    }
    return result;
}  // end make node



int numberCheck(char checkNum){
    int check = 1;
    
    if(checkNum != '\n')
            {
                printf(">> failure\n"); FLUSH;
                check = 0;
            }
    return check;
} // end numberCheck


void freeGames(GAME** games, int eSize) {
   for (int i = 0; i < eSize; i++)
       free(games[i]);

   free(games);

} // end free games
