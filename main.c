#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"

int main() {
    Player players[Max_Player];
    int count;
    int choice;

    // Load player data from CSV file at the start
    if (loadPlayerFromCSV("PlayerDataset.csv", players, &count)) {
        printf("Player data loaded successfully\n");
    } else {
        printf("Error loading player data\n");
    }

    while (1) {
        //Clear the terminal screen
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        printf("\nxxxxxxxxxxxxxxxx Menu xxxxxxxxxxxxxxxxxx\n");
        printf("1. Search Players by Name, Club, League or Country\n");
        printf("2. Filter Players based on goals,assists or ratings\n");
        printf("3. Sort Players based on goals, assists, or match ratings\n");
        printf("4. View Players based on position or league\n");
        
        printf("xxxxxxxxxxxxx File Menu xxxxxxxxxxxxxxxxxx\n");
        printf("5. Add a new player\n");
        printf("6. Update player details\n");
        printf("7. Delete a player\n");
        // printf("8. Save player data to a new file\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        
        int num_successful = scanf("%d", &choice);
        printf("%d\n",num_successful);
        while (getchar()!='\n');
        

        switch (choice) {
            
            case 1:
                searchPlayers(players, count);
                break;
            case 2:
                filterPlayers(players, count);
                break;
            case 3:
                sortFunction(players, count);
                break;

            case 4:
                viewPlayers(players, count);
                break;
            // case 5:
            //     efficiencyRatings(players, count);
            //     break;
            case 5:
                addPlayer("PlayerDataset.csv",players, &count);
                break;
            case 6:
                updatePlayer("PlayerDataset.csv",players, &count);
                break;
            case 7:
                deletePlayer("PlayerDataset.csv", players, &count);
                break;
          
            case 0:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Enter a valid choice\n");
        }
    }

    return 0;
}