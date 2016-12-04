/*Program to play the game blackjack*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define D 52
#define N 100


typedef struct deck
{
    int cards[D];
}Deck;

typedef struct player
{
   char name[N];
   int money;
   int hand[];
}Player;

typedef struct dealer
{
    int money;
    int hand[];
}Dealer;
j

//swaps two cards in the deck
void swap(int *a, int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}

//shuffles all the cards in the deck
void shuffle(int card[], int n)
{
    srand(time(NULL));  //initialises seed randomly

    for(int i=n-1; i>0; i--)
    {
        int j=rand()%(i+1);

        swap(&card[i],&card[j]);
    }
}

//goes through the process of hitting in the game
void hit(int s, int bet,Player *t)
{
    int m;
    //card dealt

    for(m=1; m<4; ++m)
    {
    printf("Would you like to hit again?\n");

        if(m==3 && s<22)
        {
            printf("Player wins as you hit four times without busting");
            t->money=t->money+bet;
            printf("You now have %d pounds", t->money);
        }
    }
     if(s>21)
        {
            printf("You have bust!");
            t->money=t->money-bet;
            printf("You now have %d pounds", t->money);
        }
}

//plays the main part of the game
void play()
{
    int bet, choose;
    int score, dscore;
    Deck *d=NULL;
    Player *one=NULL;

    one=malloc(sizeof *one);
    if(one==NULL)
    {
        fprintf(stderr,"Out of memory\n");
        exit(99);
    }

    d=malloc(sizeof *d);
    if(d==NULL)
    {
        fprintf(stderr,"Out of memory\n");
        exit(99);
    }

    one->money=200;

    printf("Please enter your name.(no spaces)\n");
    scanf("%s",one->name);
    printf("Hello %s\nWelcome to Blackjack.\n",one->name);

    shuffle(d->cards, D);

    printf("You have %d pounds.\n",one->money);
    printf("Please place a bet between 1 and 25 pounds\n");
    scanf("%d", &bet);

    if(bet<1 || bet>25)
    {
        printf("Invalid bet, choose bet within correct range\n");
        scanf("%d", &bet);
    }

    printf("You are betting %d pounds\n", bet);

    score=0;
    dscore=0;

    //dealer deals two cards for them 1 face up, 1 face down
    //dealer deal two cards for each player face up

    if(score==21)
    {
        printf("BLACKJACK,you win 1.5 times your bet automatically!\n");
        one->money=one->money+(1.5*bet);
        printf("You now have %d pounds.\n", one->money);
    }

    else
    {
    if(score<22)
    {

    int answer;

    printf("After seeing your first cards do you want to double your bet?\n"
           "\t 1.Yes\n"
           "\t 2.No\n");
    scanf("%d", &answer);

    switch(answer)
    {
    case 1:
        bet=bet*2;
        printf("Your are now betting %d pounds.\n", bet);
        break;

    case 2:
        printf("Your bet stays the same.");
    }


        printf("\n What would you like to do?\n\n"
                "\t 1.STAY\n"
                "\t 2.HIT\n");
        scanf("%d", &choose);

        switch (choose)
        {
            case 1:
                printf("Your turn has ended");

                break;

            case 2:
                printf("Hit chosen\n");
                hit(score, bet, one);
                break;
        }

        //dealer continues to draw cards until he reaches 21 or over
        if(21-score < 21-dscore)
        {
            printf("%s is closer to 21. Therefore they win the round.\n",one->name);
            one->money=one->money+bet;
            printf("%s now has %d pounds.\n",one->name, one->money);
        }

        if(21-dscore < 21-score)
        {
            printf("Dealer is closer to 21. Therefore they win.\n");
            one->money=one->money-bet;
            printf("%s now has %d pounds.\n",one->name, one->money);
        }

        if(dscore==score)
        {
            printf("There is a tie, therefore the dealer wins.\n");
            one->money=one->money-bet;
            printf("%s now has %d pounds.\n",one->name, one->money);
        }
    }
    }

    if(one->money >= 300)
    {
        printf("Well done %s you have broken the bank and win.\n",one->name);

    }

    if(one->money < 1)
    {
        printf("Bad luck %s you have lost all your money, dealer wins.\n",one->name);

    }

}

int main()
{
 int option;

    printf("BLACKJACK\n\n");



    printf("\n Menu\n\n"
           "\t 1.Play game\n"
           "\t 2.Rules\n"
           "\t 0.Quit\n");
    scanf("%d",&option);

    switch (option)
    {
        case 0:
            printf("Thank you for playing blackjack.");
            return 0;

        case 1:
            play();
            break;


        case 2:
            printf("RULES:\n1. The goal is to get as close to 21 points without going over 21.\n");
            printf("2. All numbered cards are worth the number of points on the card.\n");
            printf("3. All face cards are worth 10 points.\n");
            break;

        default:
            printf("Unknown option: %d\n", option);


    return 0;
}

}
