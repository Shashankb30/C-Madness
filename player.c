#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"

#define EXPECTED_TOKENS 11 // Number of expected tokens in each line

void printPlayerData(Player players[], int count) {
    for (int i = 0; i < count; i++) {
        printf("Country: %s\n", players[i].country);
        printf("Name: %s\n", players[i].name);
        printf("Club: %s\n", players[i].club);
        printf("League: %s\n", players[i].league);
        printf("Matches Played: %d\n", players[i].matches_played);
        printf("Goals: %d\n", players[i].goals);
        printf("Assists: %d\n", players[i].assists);
        printf("Minutes Played: %d\n", players[i].minutes_played);
        printf("xG: %.2f\n", players[i].xG);
        printf("Position: %s\n", players[i].position);
        printf("Ratings: %.2f\n", players[i].ratings); 
        printf("\n");
    }
}

int loadPlayerFromCSV(const char *filename, Player players[], int *count) {
    FILE *file = fopen(filename, "r");

    if (!file) {
        printf("Error: couldn't open file\n");
        return 0;
    }

    char line[256];
    *count = 0;
    fgets(line, sizeof(line), file); // Skip the header line

    while (fgets(line, sizeof(line), file)) {
        if (*count >= Max_Player) {
            break;
        }

        int token_count = 0;
        
        char *token = strtok(line, ",");
        if (token != NULL) token_count++;
        if (token == NULL) { printf("Error: missing country\n"); printPlayerData(players, *count); continue; }
        strcpy(players[*count].country, token);

        token = strtok(NULL, ",");
        if (token != NULL) token_count++;
        if (token == NULL) { printf("Error: missing league\n"); printPlayerData(players, *count); continue; }
        strcpy(players[*count].league, token);

        

        token = strtok(NULL, ",");
        if (token != NULL) token_count++;
        if (token == NULL) { printf("Error: missing club\n"); printPlayerData(players, *count); continue; }
        strcpy(players[*count].club, token);


       

        token = strtok(NULL, ",");
        if (token != NULL) token_count++;
        if (token == NULL) { printf("Error: missing name\n"); printPlayerData(players, *count); continue; }
        strcpy(players[*count].name, token);

        
      

        

        token = strtok(NULL, ",");
        if (token != NULL) token_count++;
        if (token == NULL) { printf("Error: missing matches played\n"); printPlayerData(players, *count); continue; }
        players[*count].matches_played = atoi(token);

        token = strtok(NULL, ",");
        if (token != NULL) token_count++;
        if (token == NULL) { printf("Error: missing goals\n"); printPlayerData(players, *count); continue; }
        players[*count].goals = atoi(token);

        token = strtok(NULL, ",");
        if (token != NULL) token_count++;
        if (token == NULL) { printf("Error: missing assists\n"); printPlayerData(players, *count); continue; }
        players[*count].assists = atoi(token);

        token = strtok(NULL, ",");
        if (token != NULL) token_count++;
        if (token == NULL) { printf("Error: missing minutes played\n"); printPlayerData(players, *count); continue; }
        players[*count].minutes_played = atoi(token);

        token = strtok(NULL, ",");
        if (token != NULL) token_count++;
        if (token == NULL) { printf("Error: missing xG\n"); printPlayerData(players, *count); continue; }
        players[*count].xG = atof(token);

        token = strtok(NULL, ",");
        if (token != NULL) token_count++;
        if (token == NULL) { printf("Error: missing position\n"); printPlayerData(players, *count); continue; }
        strcpy(players[*count].position, token);

        token = strtok(NULL, ",");
        if (token != NULL) token_count++;
        if (token == NULL) {  printf("Error: missing Ratings\n"); printPlayerData(players, *count); continue; }
        players[*count].ratings = atof(token); 
        

        if (token_count != EXPECTED_TOKENS) {
            printf("Error: incorrect number of tokens in line: %s\n", line);
            printPlayerData(players, *count);
            continue;
        }

        (*count)++;
    }

    fclose(file);
    return 1;
}

void searchPlayers(Player players[], int count) {
    char search[Max_Len];
    int choice;

    while (1) {
        // Clear the terminal screen
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        printf("\nMenu:\n");
        printf("1. Search Players by Name\n");
        printf("2. Search Players by Club\n");
        printf("3. Search Players by Country\n");
        printf("4. Search Players by League\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice < 1 || choice >4) {
            printf("Exiting search...\n");
            break;
        }
        
        else{
        printf("Enter the prefix to search for: ");
        scanf(" %[^\n]", search); // Read input with spaces

        printf("Search results:\n");

        int found = 0; // Flag to track if any players are found

        for (int i = 0; i < count; i++) {
            switch (choice) {
                case 1:
                    if (strncmp(players[i].name, search, strlen(search)) == 0) {
                        printf("Name: %s, Club: %s, Country: %s, League: %s\n", players[i].name, players[i].club, players[i].country, players[i].league);
                        found = 1;
                    }
                    break;
                case 2:
                    if (strncmp(players[i].club, search, strlen(search)) == 0) {
                        printf("Name: %s, Club: %s, Country: %s, League: %s\n", players[i].name, players[i].club, players[i].country, players[i].league);
                        found = 1;
                    }
                    break;
                case 3:
                    if (strncmp(players[i].country, search, strlen(search)) == 0) {
                        printf("Name: %s, Club: %s, Country: %s, League: %s\n", players[i].name, players[i].club, players[i].country, players[i].league);
                        found = 1;
                    }
                    break;
                case 4:
                    if (strncmp(players[i].league, search, strlen(search)) == 0) {
                        printf("Name: %s, Club: %s, Country: %s, League: %s\n", players[i].name, players[i].club, players[i].country, players[i].league);
                        found = 1;
                    }
                    break;
                default:
                    printf("Invalid choice\n");
                    break;
            }
        }

        if (!found) {
            printf("Player not found\n");
        }

        printf("Press Enter to continue...");
        getchar(); // To consume the newline character left by scanf
        getchar(); // To wait for the user to press Enter
    }
    }
}
void filterPlayers(Player players[], int count){
    int choice;

    while (1) {
        // // Clear the terminal screen
        // #ifdef _WIN32
        //     system("cls");
        // #else
        //     system("clear");
        // #endif

        printf("\nMenu:\n");
        printf("1. Filter Players by Goals\n");
        printf("2. Filter Players by Assists\n");
        printf("3. Filter Players by Xg\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (!(choice<4 && choice>0)) {
            printf("Exiting Filter...\n");
            break;
        }
        if(choice<4 && choice>0){
            printf("Enter the minimum value: ");
            int min;
            scanf("%d", &min);
            printf("Enter the maximum value: ");
            int max;
            scanf("%d", &max);
            printf("Search results:\n");

            int found = 0; //tracks if any players are found

            for (int i = 0; i < count; i++) {
                

                switch (choice) {
                    case 1:
                        if (players[i].goals >= min && players[i].goals <= max) {
                            printf("Name: %s, Club: %s, Country: %s, Goals: %d\n", players[i].name, players[i].club, players[i].country, players[i].goals);
                            found = 1;
                        }
                        break;
                    case 2:
                        if (players[i].assists >= min && players[i].assists <= max) {
                            printf("Name: %s, Club: %s, Country: %s, Assists: %d\n", players[i].name, players[i].club, players[i].country, players[i].assists);
                            found = 1;
                        }
                        break;
                    case 3:
                        if (players[i].xG >= min && players[i].xG <= max) {
                            printf("Name: %s, Club: %s, Country: %s, xG: %.2f\n", players[i].name, players[i].club, players[i].country, players[i].xG);
                            found = 1;
                        }
                        break;
                    }   
                }
                if (!found) {
                    printf("Player not found\n");
                }
            }
         
            printf("Press Enter to continue...");
        getchar(); //  consumes the newline character left by scanf
        getchar(); //normal enter to wait for user to press enter
        }
    }





// Comparator functions for sorting
int compareByGoals(const void *a, const void *b) {
    return ((Player *)b)->goals - ((Player *)a)->goals;
}

int compareByAssists(const void *a, const void *b) {
    return ((Player *)b)->assists - ((Player *)a)->assists;
}

int compareByRatings(const void *a, const void *b) {
    if (((Player *)b)->ratings > ((Player *)a)->ratings) return 1;
    if (((Player *)b)->ratings < ((Player *)a)->ratings) return -1;
    return 0;
}

void sortFunction(Player players[], int count) {
    int choice; int n;

    while (1) {
        // Clear the terminal screen
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        printf("\nSort Players Menu:\n");
        printf("1. Sort by Goals\n");
        printf("2. Sort by Assists\n");
        printf("3. Sort by Ratings\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (!(choice>0 && choice<4 )) {
            printf("Exiting Sort Menu...\n");
            break;
        }

        printf("Enter the number of top players to display: ");
        scanf("%d",&n);

        if (n > count) {
            printf("The number exceeds the total number of players (%d). Showing all players instead.\n", count);
            n = count;
        }

        // Sort based on the user's choice
        switch (choice) {
            case 1:
                qsort(players, count, sizeof(Player), compareByGoals);
                printf("\nTop %d Players by Goals:\n", n);
                break;
            case 2:
                qsort(players, count, sizeof(Player), compareByAssists);
                printf("\nTop %d Players by Assists:\n", n);
                break;
            case 3:
                qsort(players, count, sizeof(Player), compareByRatings);
                printf("\nTop %d Players by Ratings:\n", n);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                continue;
        }

        // Display the top `n` players
        for (int i = 0; i < n; i++) {
            printf("Name: %s, Club: %s, Country: %s, Goals: %d, Assists: %d, Ratings: %.2f\n",
                   players[i].name, players[i].club, players[i].country, players[i].goals, players[i].assists, players[i].ratings);
        }

        printf("\nPress Enter to continue...");
        getchar(); // Consume the newline character left by scanf
        getchar(); // Wait for the user to press Enter
    }
}


void viewPlayers(Player players[], int count) {
    int choice;

    while (1) {
        // Clear the terminal screen
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        printf("\nView Players Menu:\n");
        printf("1. View Players by League\n");
        printf("2. View Players by Position\n");
        printf("0. Exit to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice!= 1 && choice!=2) {
            printf("Returning to Main Menu...\n");
            break;
        }

        if (choice == 1) {
            int leagueChoice;
            printf("\nSelect a League:\n");
            printf("1. Premier League\n");
            printf("2. La Liga\n");
            printf("3. Ligue 1\n");
            printf("4. Bundesliga\n");
            printf("5. Serie A\n");
            printf("6. MLS\n");
            printf("0. Back to Previous Menu\n");
            printf("Enter your choice: ");
            scanf("%d", &leagueChoice);

            if (leagueChoice == 0) {
                continue;
            }

            char league[Max_Len];
            switch (leagueChoice) {
                case 1: strcpy(league, "Premier League"); break;
                case 2: strcpy(league, "La Liga"); break;
                case 3: strcpy(league, "Ligue 1"); break;
                case 4: strcpy(league, "Bundesliga"); break;
                case 5: strcpy(league, "Serie A"); break;
                case 6: strcpy(league, "MLS"); break;
                default:
                    printf("Invalid choice. Returning to previous menu...\n");
                    continue;
            }

            printf("\nSearch Results for League: %s\n", league);
            int found = 0;

            for (int i = 0; i < count; i++) {
                
                if (strcasecmp(players[i].league, league) == 0) {
                    printf("Name: %s, Country: %s, Club: %s, League: %s, Position: %s, Goals: %d, Assists: %d, Ratings: %.2f\n",
                           players[i].name, players[i].country, players[i].club, players[i].league, players[i].position,
                           players[i].goals, players[i].assists, players[i].ratings);
                    found = 1;
                }
            }

            if (!found) {
                printf("No players found in the league: %s\n", league);
            }

        } else if (choice == 2) {
            int positionChoice;
            printf("\nSelect a Position:\n");
            printf("1. CF\n");
            printf("2. ST\n");
            printf("3. LW\n");
            printf("4. CAM\n");
            printf("5. CDM\n");
            printf("6. RW\n");
            printf("7. CB\n");
            printf("8. CM\n");
            printf("9. RB\n");
            printf("10.LB\n");
            printf("11.GK\n");
            printf("0. Back to Previous Menu\n");
            printf("Enter your choice: ");
            scanf("%d", &positionChoice);

            if (positionChoice == 0) {
                continue;
            }

            char position[Max_Len];
            switch (positionChoice) {
                case 1: strcpy(position, "CF"); break;
                case 2: strcpy(position, "ST"); break;
                case 3: strcpy(position, "LW"); break;
                case 4: strcpy(position, "CAM"); break;
                case 5: strcpy(position, "CDM"); break;
                case 6: strcpy(position, "RW"); break;
                case 7: strcpy(position, "CB"); break;
                case 8: strcpy(position, "CM"); break;
                case 9: strcpy(position, "RB"); break;
                case 10: strcpy(position, "LB"); break;
                case 11: strcpy(position, "GK"); break;
                default:
                    printf("Invalid choice. Returning to previous menu...\n");
                    continue;
            }

            printf("\nSearch Results for Position: %s\n", position);
            int found = 0;

            for (int i = 0; i < count; i++) {
                if (strcasecmp(players[i].position, position) == 0) {
                    printf("Name: %s, Country: %s, Club: %s, League: %s, Position: %s, Goals: %d, Assists: %d, Ratings: %.2f\n",
                           players[i].name, players[i].country, players[i].club, players[i].league, players[i].position,
                           players[i].goals, players[i].assists, players[i].ratings);
                    found = 1;
                }
            }

            if (!found) {
                printf("No players found for the position: %s\n", position);
            }

        } else {
            printf("Invalid choice. Please try again.\n");
        }

        printf("\nPress Enter to continue...");
        getchar(); // Consume the newline character left by scanf
        getchar(); // Wait for the user to press Enter
    }
}
void addPlayer(const char *filename, Player players[], int *count) {
    if (*count >= Max_Player) {
        printf("Error: Maximum number of players reached.\n");
        return;
    }

    Player newPlayer;
    char buffer[Max_Len];

    printf("Enter the following details for the new player:\n");

    // Get Country
    printf("Country: ");
    scanf(" %[^\n]", newPlayer.country);

     // Get League
     printf("League: ");
     scanf(" %[^\n]", newPlayer.league);

     // Get Club
     printf("Club: ");
     scanf(" %[^\n]", newPlayer.club);
    
     // Get Name
    printf("Name: ");
    scanf(" %[^\n]", newPlayer.name);

    // Get Matches Played
    while (1) {
        printf("Matches Played: ");
        if (scanf("%d", &newPlayer.matches_played) == 1 && newPlayer.matches_played >= 0) break;
        printf("Invalid input. Please enter a valid non-negative integer.\n");
        while (getchar() != '\n'); // Clear input buffer
    }

    // Get Goals
    while (1) {
        printf("Goals: ");
        if (scanf("%d", &newPlayer.goals) == 1 && newPlayer.goals >= 0) break;
        printf("Invalid input. Please enter a valid non-negative integer.\n");
        while (getchar() != '\n'); // Clear input buffer
    }

    // Get Assists
    while (1) {
        printf("Assists: ");
        if (scanf("%d", &newPlayer.assists) == 1 && newPlayer.assists >= 0) break;
        printf("Invalid input. Please enter a valid non-negative integer.\n");
        while (getchar() != '\n'); // Clear input buffer
    }

    // Get Minutes Played
    while (1) {
        printf("Minutes Played: ");
        if (scanf("%d", &newPlayer.minutes_played) == 1 && newPlayer.minutes_played >= 0) break;
        printf("Invalid input. Please enter a valid non-negative integer.\n");
        while (getchar() != '\n'); // Clear input buffer
    }

    // Get xG
    while (1) {
        printf("xG: ");
        if (scanf("%f", &newPlayer.xG) == 1 && newPlayer.xG >= 0) break;
        printf("Invalid input. Please enter a valid non-negative float.\n");
        while (getchar() != '\n'); // Clear input buffer
    }

    // Get Position
    printf("Position: ");
    scanf(" %[^\n]", newPlayer.position);

    // Get Ratings
    while (1) {
        printf("Ratings: ");
        if (scanf("%f", &newPlayer.ratings) == 1 && newPlayer.ratings >= 0 && newPlayer.ratings <= 10) break;
        printf("Invalid input. Please enter a valid float between 0 and 10.\n");
        while (getchar() != '\n'); // Clear input buffer
    }

    // Add the new player to the array
    players[*count] = newPlayer;
    (*count)++;



    // Append the new player to the CSV file
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: Couldn't open file to append.\n");
        return;
    }

    qsort(players, *count, sizeof(Player), compareByRatings);
    fprintf(file, "Country,League,Club,Name,Matches Played,Goals,Assists,Minutes Played,xG,Position,Ratings\n");
    for (int i = 0; i < *count; i++) {
        fprintf(file, "%s,%s,%s,%s,%d,%d,%d,%d,%.2f,%s,%.2f\n",
            players[i].country, players[i].league, players[i].club, players[i].name,
            players[i].matches_played, players[i].goals, players[i].assists,
            players[i].minutes_played, players[i].xG, players[i].position, players[i].ratings);
    }
    fclose(file);

    printf("Player added successfully!\n");
}

void deletePlayer(const char *filename, Player players[], int *count) {
    char search[Max_Len];
    printf("Enter the name of the player to delete: ");
    scanf(" %[^\n]", search);

    while(getchar()!='\n'); //Clear buffer

    int found = -1;
    for (int i = 0; i < *count; i++) {
        if (strcasecmp(players[i].name, search) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Player not found.\n");
        printf("Press Enter to continue...\n");
        getchar(); // Wait for the user to press Enter
        return;
    }

    // Show the player details
    printf("Player found:\n");
    printPlayerData(&players[found], 1);

    // Confirm deletion
    char confirm;
    printf("Are you sure you want to delete this player? (y/n): ");
    scanf(" %c", &confirm);

    if (confirm != 'y' && confirm != 'Y') {
        printf("Deletion canceled.\n");
        return;
    }

    // Remove the player from the array
    for (int i = found; i < *count - 1; i++) {
        players[i] = players[i + 1];
    }
    (*count)--;

    // Update the CSV file
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: Couldn't open file to update.\n");
        return;
    }

    // Write updated data back to the file
    fprintf(file, "Country,Name,Club,League,Matches Played,Goals,Assists,Minutes Played,xG,Position,Ratings\n");
    for (int i = 0; i < *count; i++) {
        fprintf(file, "%s,%s,%s,%s,%d,%d,%d,%d,%.2f,%s,%.2f\n",
            players[i].country, players[i].league, players[i].club, players[i].name,
            players[i].matches_played, players[i].goals, players[i].assists,
            players[i].minutes_played, players[i].xG, players[i].position, players[i].ratings);
    }

    fclose(file);
    printf("Player deleted successfully and CSV file updated.\n");
}

void updatePlayer(const char *filename, Player players[], int *count) {
    char search[Max_Len];
    printf("Enter the name of the player to update: ");
    scanf(" %[^\n]", search);

    int found = -1;
    for (int i = 0; i < *count; i++) {
        if (strcasecmp(players[i].name, search) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Player not found.\n");
        return;
    }

    // Show the player details
    printf("Player found:\n");
    printPlayerData(&players[found], 1);

    // Confirm update
    char confirm;
    printf("Are you sure you want to update this player? (y/n): ");
    scanf(" %c", &confirm);

    if (confirm != 'y' && confirm != 'Y') {
        printf("Update canceled.\n");
        return;
    }

    // Update the player's details
    printf("Enter the updated details for the player:\n");

  

    

    // Get Matches Played
    while (1) {
        printf("Matches Played: ");
        if (scanf("%d", &players[found].matches_played) == 1 && players[found].matches_played >= 0) break;
        printf("Invalid input. Please enter a valid non-negative integer.\n");
        while (getchar() != '\n'); // Clear input buffer
    }

    // Get Goals
    while (1) {
        printf("Goals: ");
        if (scanf("%d", &players[found].goals) == 1 && players[found].goals >= 0) break;
        printf("Invalid input. Please enter a valid non-negative integer.\n");
        while (getchar() != '\n'); // Clear input buffer
    }

    // Get Assists
    while (1) {
        printf("Assists: ");
        if (scanf("%d", &players[found].assists) == 1 && players[found].assists >= 0) break;
        printf("Invalid input. Please enter a valid non-negative integer.\n");
        while (getchar() != '\n'); // Clear input buffer
    }

    // Get Minutes Played
    while (1) {
        printf("Minutes Played: ");
        if (scanf("%d", &players[found].minutes_played) == 1 && players[found].minutes_played >= 0) break;
        printf("Invalid input. Please enter a valid non-negative integer.\n");
        while (getchar() != '\n'); // Clear input buffer
    }

    // Get xG
    while (1) {
        printf("xG: ");
        if (scanf("%f", &players[found].xG) == 1 && players[found].xG >= 0) break;
        printf("Invalid input. Please enter a valid non-negative float.\n");
        while (getchar() != '\n'); // Clear input buffer
    }



    // Get Ratings
    while (1) {
        printf("Ratings: ");
        if (scanf("%f", &players[found].ratings) == 1 && players[found].ratings >= 0 && players[found].ratings <= 10) break;
        printf("Invalid input. Please enter a valid float between 0 and 10.\n");
        while (getchar() != '\n'); // Clear input buffer
    }

    // Update the CSV file
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: Couldn't open file to update.\n");
        return;
    }

    // Write updated data back to the file
     qsort(players, *count, sizeof(Player), compareByRatings);
    fprintf(file, "Country,League,Club,Name,Matches Played,Goals,Assists,Minutes Played,xG,Position,Ratings\n");
    for (int i = 0; i < *count; i++) {
        fprintf(file, "%s,%s,%s,%s,%d,%d,%d,%d,%.2f,%s,%.2f\n",
            players[i].country, players[i].league, players[i].club, players[i].name,
            players[i].matches_played, players[i].goals, players[i].assists,
            players[i].minutes_played, players[i].xG, players[i].position, players[i].ratings);
    }

    fclose(file);
    printf("Player updated successfully and CSV file updated.\n");
}