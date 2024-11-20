#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Enum for difficulty levels
typedef enum {
    EASY = 1,
    MEDIUM,
    HARD
} DifficultyLevel;

// Struct to represent player data
typedef struct {
    int health;
    int armor;
    int points;
    int usedBatarang;
    DifficultyLevel difficulty;
} Player;

// Struct to represent a riddle
typedef struct {
    char question[256];
    char answer[50];
} Riddle;

// Global player variable
Player player;
Riddle riddles[3]; // Array of riddles for the current difficulty level
int currentRiddle = 0;

// Functions
void displayHeader();
void displayInstructions();
void menu();
void startMission();
void riddle();
void upgrades();
void checkStatus();
void gameOver();
void saveGame();
void loadGame();
void setDifficulty();
void initializeRiddles();
void printPlayerStatus(const Player *p);

int main() {
    displayHeader();
    displayInstructions();
    printf("Welcome to Batman vs The Riddler!\n");
    setDifficulty();
    initializeRiddles();  // Initialize riddles based on difficulty
    printf("\nGame initialized! Here's your starting status:\n");
    printPlayerStatus(&player);
    menu();
    return 0;
}

// Function to display the ASCII art header
void displayHeader() {
    printf("========================================\n");
    printf("       BATMAN VS THE RIDDLER\n");
    printf("========================================\n");
    printf("          _==/          i     i          \\==_\n");
    printf("        /XX/            |\\-\"\"\"-/|            \\XX\\\n");
    printf("      /XXXX\\            |       |            /XXXX\\\n");
    printf("    /XXXXXX\\_         _|  (o)  |_         _/XXXXXX\\\n");
    printf("   /XXXXXXXX\\       /  |       |  \\       /XXXXXXXX\\\n");
    printf("  /XXXXXXXXXX\\     /   |  \\_/  |   \\     /XXXXXXXXXX\\\n");
    printf(" /XXXXXXXXXXXX\\   /    |       |    \\   /XXXXXXXXXXXX\\\n");
    printf("(XXXXXXXXXXXXXX|   \\    \\_____/    /   |XXXXXXXXXXXXXX)\n");
    printf("XXXXXXXXXXXXXXXX|   \\             /    |XXXXXXXXXXXXXXX\n");
    printf("XXXXXXXXXXXXXXXXX\\   \\           /    /XXXXXXXXXXXXXXX\n");
    printf("XXXXXXXXXXXXXXXXXX\\   \\         /    /XXXXXXXXXXXXXXXX\n");
    printf("\n");
}

// Function to display game instructions
void displayInstructions() {
    printf("Game Instructions:\n");
    printf("1. Select a difficulty level to start the game.\n");
    printf("2. Solve riddles to earn points. Each correct answer gives you +10 points, while wrong answers deduct -5 points.\n");
    printf("3. Use your points to upgrade your stats.\n");
    printf("4. Save and load your progress anytime.\n");
    printf("5. The game ends if your health reaches 0 or you complete all difficulty levels.\n");
    printf("\nLet's begin your mission, Batman!\n");
}

// Display player status
void printPlayerStatus(const Player *p) {
    printf("\nCurrent Status:\n");
    printf("Health: %d\n", p->health);
    printf("Armor: %d\n", p->armor);
    printf("Points: %d\n", p->points);
    printf("Batarang Used: %d\n", p->usedBatarang);
}

// Initialize riddles array based on difficulty level
void initializeRiddles() {
    if (player.difficulty == EASY) {
        strcpy(riddles[0].question, "What has to be broken before you can use it?");
        strcpy(riddles[0].answer, "egg");

        strcpy(riddles[1].question, "I’m tall when I’m young, and I’m short when I’m old. What am I?");
        strcpy(riddles[1].answer, "candle");

        strcpy(riddles[2].question, "What month of the year has 28 days?");
        strcpy(riddles[2].answer, "all");

    } else if (player.difficulty == MEDIUM) {
        strcpy(riddles[0].question, "What is full of holes but still holds water?");
        strcpy(riddles[0].answer, "sponge");

        strcpy(riddles[1].question, "What question can you never answer yes to?");
        strcpy(riddles[1].answer, "are you asleep");

        strcpy(riddles[2].question, "What goes up but never comes down?");
        strcpy(riddles[2].answer, "age");

    } else if (player.difficulty == HARD) {
        strcpy(riddles[0].question, "The more you take, the more you leave behind. What am I?");
        strcpy(riddles[0].answer, "footsteps");

        strcpy(riddles[1].question, "What has many keys but can’t open a single lock?");
        strcpy(riddles[1].answer, "piano");

        strcpy(riddles[2].question, "What has cities, but no houses; forests, but no trees; and rivers, but no water?");
        strcpy(riddles[2].answer, "map");
    }
}

// Display main menu options
void menu() {
    int choice;
    do {
        printf("\nMain Menu:\n");
        printf("1. Start Mission\n");
        printf("2. Upgrade Stats\n");
        printf("3. Check Status\n");
        printf("4. Save Game\n");
        printf("5. Load Game\n");
        printf("6. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                startMission();
                break;
            case 2:
                upgrades();
                break;
            case 3:
                checkStatus();
                break;
            case 4:
                saveGame();
                break;
            case 5:
                loadGame();
                break;
            case 6:
                printf("Exiting game. Thanks for playing!\n");
                break;
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    } while (choice != 6 && player.health > 0);
}

// Set game difficulty
void setDifficulty() {
    int choice;
    printf("Choose Difficulty Level:\n");
    printf("1. Easy\n2. Medium\n3. Hard\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    player.difficulty = (DifficultyLevel)choice;

    // Set health and armor based on difficulty
    switch (player.difficulty) {
        case EASY:
            player.health = 150;
            player.armor = 50;
            break;
        case MEDIUM:
            player.health = 100;
            player.armor = 30;
            break;
        case HARD:
            player.health = 80;
            player.armor = 10;
            break;
        default:
            printf("Invalid choice. Setting difficulty to Medium.\n");
            player.difficulty = MEDIUM;
            player.health = 100;
            player.armor = 30;
    }
    player.points = 0;
    printf("Difficulty set. Health: %d, Armor: %d\n", player.health, player.armor);
}

// Start a mission with multiple riddles
void startMission() {
    printf("\nStarting a mission...\n");
    currentRiddle = 0;

    while (currentRiddle < 3 && player.health > 0) {
        riddle();
        if (player.health <= 0) {
            gameOver();
            return;
        }
        currentRiddle++;
    }

    if (currentRiddle >= 3) {
        printf("Congratulations! You've completed the mission for this difficulty level.\n");
        
        // Ask if they want to proceed to the next level
        if (player.difficulty < HARD) {
            char choice;
            printf("Do you want to continue to the next difficulty level? (y/n): ");
            scanf(" %c", &choice);

            if (choice == 'y' || choice == 'Y') {
                saveGame();
                player.difficulty += 1;  // Advance to the next level
                initializeRiddles();     // Reinitialize riddles for the new difficulty
                startMission();          // Start the next mission
            }
        } else {
            printf("You have completed all difficulty levels. Well done!\n");
        }
    }
}

// Present a riddle to the player with retries and point deductions
void riddle() {
    char answer[50];
    int correct = 0;

    while (!correct && player.health > 0) {
        printf("Riddle: %s\n", riddles[currentRiddle].question);
        scanf("%s", answer);
        if (strcmp(answer, riddles[currentRiddle].answer) == 0) {
            printf("Correct! You've earned 10 points.\n");
            player.points += 10;
            correct = 1;
        } else {
            printf("Incorrect! You lost 5 points.\n");
            player.points -= 5;
        }
    }
}

// Allow player to upgrade stats
void upgrades() {
    int choice;
    if (player.points < 10) {
        printf("Not enough points to upgrade. Earn more by completing missions.\n");
        return;
    }

    printf("\nChoose an upgrade:\n");
    printf("1. Increase Health (10 points)\n");
    printf("2. Increase Armor (10 points)\n");
    printf("Your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        player.health += 10;
        player.points -= 10;
        printf("Health increased! Current health: %d\n", player.health);
    } else if (choice == 2) {
        player.armor += 10;
        player.points -= 10;
        printf("Armor increased! Current armor: %d\n", player.armor);
    } else {
        printf("Invalid choice.\n");
    }
}

// Check the current status of the player
void checkStatus() {
    printPlayerStatus(&player);
}

// Game over function
void gameOver() {
    printf("\nGame Over! Batman has been defeated by The Riddler.\n");
    printPlayerStatus(&player);
    exit(0);
}

// Save game state to a file
void saveGame() {
    FILE *file = fopen("savegame.txt", "w");
    if (file == NULL) {
        printf("Error saving game.\n");
        return;
    }
    fprintf(file, "%d %d %d %d %d\n", player.health, player.armor, player.points, player.usedBatarang, player.difficulty);
    fclose(file);
    printf("Game saved successfully.\n");
}

// Load game state from a file
void loadGame() {
    FILE *file = fopen("savegame.txt", "r");
    if (file == NULL) {
        printf("No saved game found.\n");
        return;
    }
    fscanf(file, "%d %d %d %d %d", &player.health, &player.armor, &player.points, &player.usedBatarang, (int*)&player.difficulty);
    fclose(file);
    printf("Game loaded successfully. Health: %d, Armor: %d, Points: %d\n", player.health, player.armor, player.points);
}
