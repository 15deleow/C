#include "SnakeGame.h"

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Move(){
    int a;
    int i;

    //game state resets and a new food location is generated until
    //The user hits a move key
    do{
        Food();
        fflush(stdin);

        //Clear the Snake Body
        len = 0;
        for(i = 0; i < 30; i++){
            body[i].x = 0;
            body[i].y = 0;
            
            if(i == length){
                break;
            }
        }

        //Delay the game and draw the game board
        Delay(length);
        Boarder();

        //Handles snake movement based
        //on the current direction of the snake's head
        switch (head.direction)
        {
        case RIGHT:
            Right();
            break;
        case LEFT:
            Left();
            break;
        case DOWN:
            Down();
            break;
        case UP:
            Up();
            break;
        default:
            ExitGame();
        }

    } while( !kbhit() );

    //Wait for user's input 
    //if the escape key is hit, the program exits
    //otherwise it reads another key to change the direction of the snake
    a = getchar();
    if(a == ESCAPE){
        clearScreen();
        exit(EXIT_SUCCESS);
    }

    //If the condition for changing direction is met, handle the bendinf of the snake
    //if the escape key is entered, the program exits
    //if an invalid key is pressed, it produces an alert sound and recursively calls
    //itself to continue the game loop
    key = getch();
    int condition = (key == RIGHT && head.direction != LEFT && head.direction != RIGHT) || 
                    (key == LEFT && head.direction != LEFT && head.direction != RIGHT)  ||
                    (key == UP && head.direction != DOWN && head.direction != UP)  ||
                    (key == DOWN && head.direction != DOWN && head.direction != UP);
    if(condition){
        bend_no++;
        bend[bend_no] = head;
        head.direction = key;

        switch(key){
            case UP: head.y--; break;
            case DOWN: head.y++; break;
            case RIGHT: head.x++; break;
            case LEFT: head.x--; break;
        }

        Move();
    } else if(key == ESCAPE){
        clearScreen();
        exit(EXIT_SUCCESS);
    } else{
        printf("\a");
        Move();
    }
}

// void gotoxy(int x, int y){
//     COORD coord;
//     coord.X = x;
//     coord.Y = y;
//     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
// }

void GotoXY(int x,int y){
    HANDLE a; //Stores the handle to the console window
    COORD b;  //holds the X and Y coordinates

    //FLusht the standard output stream
    fflush(stdout);

    //Set the X and Y coordinates
    b.X = x;
    b.Y = y;

    //Get the handle to the console window
    a = GetStdHandle(STD_OUTPUT_HANDLE);

    //Set the cursor position to the updated X and Y coordinates
    SetConsoleCursorPosition(a,b);
}

void load(){
    //Coordinates for the loading test and animation
    int xOne = 36, yOne = 14;
    int xTwo = 30, yTwo = 15;

    //Display "loading..." text
    GotoXY(xOne,yOne);
    printf("loading...");
    
    //Display loading animation
    GotoXY(xTwo, yTwo);

    for(int r = 1; r <= 20; r++){
        for(int q = 0; q <= 500; q++){
            printf("%c", 177);
        }
    }

    //Wait for user input before continuing
    getch();
}

void record(){
    //Get Player's name
    char playerName[20];
    ReadPlayerName(playerName);

    //Get current time
    time_t mytime;
    mytime = time(NULL);

    //Modify the player's name according to capitalization rules
    char nplname[20];
    for(int j = 0; playerName[j] != '\0'; j++){
        nplname[0] = toupper(playerName[0]);

        if(j > 0 && playerName[j - 1] == ' '){
            nplname[j] = toupper(playerName[j]);
            nplname[j - 1] = playerName[j - 1];
        } else {
            nplname[j] = playerName[j];
        }
    }

    //Append terminator character null
    nplname[strlen(playerName)] = '\0';

    //Get Current score
    int score = Scoreonly();
    WriteToFile(nplname, score);

    //Prompt player if they like to see past scores
    printf("Want to see past records? Press 'y' or 'n': ");
    char input = getch();
    clearScreen();
    if(input = 'y'){
        DisplayRecords();
    }

    return;
}

void Delay(long double k){
    long double i;
    Score();
    for(i=0; i<=(10000000); i++);
}

void Food(){
    //If the location of the snakes head overlaps the location of food
    if(head.x == food.x && head.y == food.y){

        //Increase length of snake
        length++;
        time_t a;

        //Update time
        a = time(0);
        srand(a);

        //Generate new random coordinates for the food within the game bounds
        food.x = rand() % 70;
        if(food.x <= 10){
            food.x += 11;
        }

        food.y = rand() % 30;
        if(food.y <= 10){
            food.y += 11;
        }
    }else if(food.x == 0){
        //Initialize the food for the first time
        food.x = rand() % 70;
        if(food.x <= 10){
            food.x += 11;
        }

        food.y = rand() % 30;
        if(food.y <= 10){
            food.y += 11;
        }
    }
}

int Score(){
    int score;

    GotoXY(20, 8);
    score = length - 5;
    printf("SCORE : %d", (length - 5));
    score = length - 5;
    GotoXY(50, 8);
    printf("Life : %d", life);
    return score;
}

void ReadPlayerName(char *plname){
    printf("Enter your name: ");
    scanf("%[^\n]", plname);
    while(getchar() != '\n');
}

void WriteToFile(const char *nplname, int score){
    //Open file and error check
    FILE * info = fopen(FILENAME, "a+");
    if(info == NULL){
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    //Write player info and record to file
    fprintf(info, "Player Name: %s\n", nplname);

    time_t mytime;
    mytime = time(NULL);
    fprintf(info, "Played Date: %s\n", ctime(&mytime));

    fprintf(info, "Score: %d\n", score);

    for(int i = 0; i <= 50; i++){
        fprintf(info, "%c", '_');
    }

    fprintf(info, "\n");

    //Close file
    fclose(info);
}

void DisplayRecords(){
    FILE * info = fopen(FILENAME, "r");
    if(info == NULL){
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char c;
    while( (c = getc(info)) != EOF){
        putchar(c);
    }
}

void Print(){
    printf("\tWelcome to the mini Snake game.(press any key to continue)\n");
    getch();
    clearScreen();
    printf("\tGame instructions:\n");
    printf("\n-> Use arrow keys to move the snake.\n\n-> You will be provided foods at the several coordinates of the screen which you have to eat. Everytime you eat a food the length of the snake will be increased by 1 element and thus the score.\n\n-> Here you are provided with three lives. Your life will decrease as you hit the wall or snake's body.\n\n-> YOu can pause the game in its middle by pressing any key. To continue the paused game press any other key once again\n\n-> If you want to exit press esc. \n");
    printf("\n\nPress any key to play game...");
    if(getch() == ESCAPE){
        exit(0);
    }
}

void Bend(){
    int i, j, diff;

    //Iterate through the bend array in reverse order
    for(i = bend_no; i >= 0 && len < length; i--){
        //Check if going in horizontal direction
        if(bend[i].x == bend[i - 1].x){
            //Calculate the difference between the y-coordinates
            //of the current bend and the previous bend
            diff = bend[i].y - bend[i - 1].y;

            if(diff < 0){
                //Going Left, print snake going left
                for(j = 1; j <= (-diff); j++){
                    body[len].x = bend[i].x;
                    body[len].y = bend[i].y + j;

                    GotoXY(body[len].x, body[len].y);
                    printf("*");
                    len++;
                    if(len == length){
                        break;
                    }
                }
            } else if(diff > 0){
                //Going right, print snake going right
                for(j = 1; j <= diff; j++){
                    body[len].x = bend[i].x;
                    body[len].y = bend[i].y - j;

                    GotoXY(body[len].x, body[len].y);
                    printf("*");
                    len++;
                    if(len == length){
                        break;
                    }
                }
            } 
        //Check if going in the vertical direction
        } else if(bend[i].y == bend[i - 1].y) {
            //Calculate the difference between the x-coordinates
            //of the current bend and the previous bend
            diff = bend[i].x - bend[i - 1].x;
            if(diff < 0){
                //Going Down, print snake going down
                for(j = 1; j <= (-diff) && len < length; j++){
                    body[len].x = bend[i].x + j;
                    body[len].y = bend[i].y;
                    GotoXY(body[len].x, body[len].y);
                    printf("*");
                    if(len == length){
                        break;
                    }
                }
            } else if (diff > 0){
                //Going Up, print snake going up
                for(j = 1; j <= diff && len < length; j++){
                    body[len].x = bend[i].x - j;
                    body[len].y = bend[i].y;
                    GotoXY(body[len].x, body[len].y);
                    printf("*");
                    if(len == length){
                        break;
                    }
                }
            }
        }
    }
}

void Boarder()
{
    clearScreen();
    int i;
    GotoXY(food.x,food.y);   /*displaying food*/
    printf("F");
    for(i=10; i<71; i++)
    {
        GotoXY(i,10);
        printf("!");
        GotoXY(i,30);
        printf("!");
    }
    for(i=10; i<31; i++)
    {
        GotoXY(10,i);
        printf("!");
        GotoXY(70,i);
        printf("!");
    }
}

void Down(){
    //Loop to print the snake body as it moves down 
    for(int i = 0; i <= (head.y-bend[bend_no].y) && len < length; i++){
        //Moves cursor to print snake body
        GotoXY(head.x, head.y-i);

        //Print the head or body segment based on the length
        if(len == 0){
            printf("v");
        }else{
            printf("*");
        }

        // Updates the body coordinates and length
        body[len].x = head.x;
        body[len].y = head.y;
        len++;
    }

    // Perform any necessary bend logic
    Bend();

    //Move the head down if no key is pressed
    if(!kbhit){
        head.y++;
    }
}

void Left(){
    //Move the snake's body to the left
    for(int i = 0; i <= (bend[bend_no].x - head.x) && len < length; i++){
        GotoXY((head.x + i), head.y);

        if(len == 0){
            //Display the snake head facing left
            printf("<");
        } else{
            //Display the snake body segment
            printf("*");
        }

        body[len].x == head.x + i;
        body[len].y == head.y;
        len++;
    }

    //Bend the snake's body
    Bend();

    // If no key is pressed, move the snake's head to the left
    if(!kbhit()) head.x--;
}

void Up(){
    //Handle snake going up, while still in bounds
    for(int i = 0; i <= (bend[bend_no].y - head.y) && len < length; i++){
        body[len].x = head.x - i;
        body[len].y = head.y;

        GotoXY(body[len].x, body[len].y);

        if(len == 0){
            printf(">");
        } else{
            printf("*");
        }
    }

    //Bend snake
    Bend();

    //Keep heading up while no input from user
    if(!kbhit()){
        head.x++;
    }
}

void Right(){
    //Handle snake going right, while still in bounds
    for(int i = 0; i <= (head.x - bend[bend_no].x) && len < length; i++){
        body[len].x = head.x - i;
        body[len].y = head.y;

        GotoXY(body[len].x, body[len].y);

        if(len == 0){
            printf(">");
        } else{
            printf("*");
        }
    }

    //Bend snake
    Bend();

    //Keep heading right while no input from user
    if(!kbhit()){
        head.x++;
    }
}

void ExitGame(){
    int check = 0;

    //Check if the head touches its own body
    //Needs minimum 4 elements to touch its own body
    for(int i = 4; i < length; i++){
        if(body[0].x == body[i].x && body[0].y == body[i].y){
            //Increase as the coordinates of head is equal to any other body coordinates
            check++;
        }

        //Exit loop if reached end of the snake or if check is non-zero
        if(i == length || check != 0){
            break;
        }
    }

    // Check if the head is out of bounds or has touched its own body
    if(head.x <= 10 || head.x >= 70 || head.y <= 10 || head.y >= 30 || check != 0){
        life--;

        //If lives remain, reset the game state and continue
        if(life >= 0){
            head.x=25;
            head.y=20;
            bend_no=0;
            head.direction=RIGHT;
            Move();
        }else{
            //If all lives are exhausted, display a message and exit the
            clearScreen();
            printf("All lives completed\nBetter Luck Next Time!!!\nPress an key to quit the game\n");
            record();
            exit(EXIT_SUCCESS);
        }
    }
}

int Scoreonly(){
    int score = Score();
    clearScreen();
    return score;
}