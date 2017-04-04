/*	Jacob Yager
	jcyager
	2/4/2017
	Assignment 4
	
	Question 1:
	a. unsigned int values[SIZE] = {2,4,6,8,10};
	b. unsigned int *vPtr;
	c. for(size_t i = 0; i < SIZE; i++)
	   {
		printf("%u, ", values[i]);
 	   }
	d. vPtr = &array; 
	   vPtr = &array[0];
	e. for(size_t i = 0; i < SIZE; i++)
	   {
		printf("%u, ", *(vPtr + i));
	   }
	f. for(size_t i = 0; i < SIZE; i++)
	   {
		printf("%u, ", *(&values[0] + i));
	   }
	g. for(size_t i = 0; i < SIZE; i++)
	   {
		printf("%u, ", *(vPtr[i]));
	   }
	h. values[4]; *(&values[4]); *vPtr[4]; *(vPtr + 4);
	i. 1002506, the value is 8 
	j. 1002500, the value is 2


	Question 2:
	a. long *lPtr;
	b. lPtr = &value1;
	c. printf("%ld\n", *lPtr);
	d. value2 = *lPtr;
	e. printf("%ld\n", value2);
	f. printf("%p\n", &value1);
	g. printf("%p\n", lPtr); //yes they are the same 


	Question 3
	a. void zero(long bigIntegers[]){	}
	b. void zero(long bigIntegers[]);
	c. int add1AndSum(int oneTooSmall[]){	}
	d. int add1AndSum(int oneTooSmall[]);
*/

// Fig. 7.24: fig07_24.c
// Card shuffling and dealing.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SUITS 4
#define FACES 13
#define CARDS 52

// prototypes
void shuffle(unsigned int wDeck[][FACES]); // shuffling modifies wDeck
void deal(unsigned int wDeck[][FACES], const char *wFace[], 
   const char *wSuit[]); // dealing doesn't modify the arrays

int main(void)
{
   // initialize deck array
   unsigned int deck[SUITS][FACES] = { 0 };

   srand(time(NULL)); // seed random-number generator

   shuffle(deck); // shuffle the deck

   // initialize suit array                       
   const char *suit[SUITS] =            
      {"Hearts", "Diamonds", "Clubs", "Spades"};
   
   // initialize face array                   
   const char *face[FACES] =
      {"Ace", "Deuce", "Three", "Four",         
       "Five", "Six", "Seven", "Eight",         
       "Nine", "Ten", "Jack", "Queen", "King"};

   deal(deck, face, suit); // deal the deck
} 

// shuffle cards in deck
void shuffle(unsigned int wDeck[][FACES])
{
   // for each of the cards, choose slot of deck randomly
   size_t card;	
   for (card = 1; card <= CARDS; ++card) {
      size_t row; // row number
      size_t column; // column number

      // choose new random location until unoccupied slot found
      do {                                                        
         row = rand() % SUITS;                                   
         column = rand() % FACES;                            
      } while(wDeck[row][column] != 0); // end do...while

      // place card number in chosen slot of deck
      wDeck[row][column] = card;
   } 
}

// deal cards in deck
void deal(unsigned int wDeck[][FACES], const char *wFace[],
   const char *wSuit[])
{

   //These are being created to keep track of the hand 
   const char* handFace[6];
   const char* handSuit[6];


   // deal each of the cards
   size_t card;
   size_t column;
   size_t row;
   //changing card <=CARD to <=5 makes deal only deal 5 cards 
   for (card = 1; card <= 5; ++card) {
      // loop through rows of wDeck
      for (row = 0; row < SUITS; ++row) {
         // loop through columns of wDeck for current row
         for (column = 0; column < FACES; ++column) {
            // if slot contains current card, display card
            if (wDeck[row][column] == card) {
               printf("%5s of %-8s%c", wFace[column], wSuit[row],
                  card % 2 == 0 ? '\n' : '\t'); // 2-column format
	
	       //Assign the correct string to the hand (loactions start at 1)	   
	       handFace[card] = wFace[column];
	       handSuit[card] = wSuit[row];
            } 
         } 
      }
   }

   //determine what the hand contains pairs
   int matches = 0;
   for (column = 1; column < 5;column++){
	
	size_t testColumn = column + 1;
        for (; testColumn < 6;testColumn++){
			
		//Compares the face of the column to the rest of the faces
		int stringEqual = strcmp(handFace[column], handFace[testColumn]);
		if (stringEqual == 0){
			
			//increases when match is found			
			matches++;
		}
	}
   }
   //determine if the hand has a flush
   int flush = 0;
   for (column = 1; column < 2;column++){
	
	size_t testColumn = column + 1;
        for (; testColumn < 6;testColumn++){
			
		//Compares the suit of the first card to the rest of the cards
		int stringEqual = strcmp(handSuit[column], handSuit[testColumn]);
		if (stringEqual == 0){
			
			//increases when match is found			
			flush++;
		}
	}
   }	
  
   //determine if the hand has a straight
   int straight = 0;
  
   //this record the order of the cards  
   int position1;
   int position2;

   //compares the first card to the rest 	
   for (column = 1; column < 6;column++){

	//is the card that is being compared with 
	size_t testColumn = column + 1;
        for (; testColumn < 6;testColumn++){
		//determines the location of the initial card and test next card
		int orderTest = 0;	
		for(orderTest; orderTest < 13; orderTest++){
			
		        //finds the position of the first card in wFace
			int stringEqual = strcmp(handFace[column], wFace[orderTest]);
			if (stringEqual == 0){	
				position1 = orderTest;		
			}
			//finds the position of the second card in wFace
			int secondCardPosition = strcmp(handFace[testColumn], wFace[orderTest]);
			if(secondCardPosition == 0){
				position2 = orderTest;
			}
		}
		//determines if the card being tested is dirrectly next to any of the other cards in the hand
		if (position1 - position2 == 1 || position2 - position1 == 1 || ((position1 == 12 &&  position2 == 0) || (position1 == 0 && position2 == 12))){
			straight++;
		}
		//removes the possibility of KQQQ leading to a false straight 
		if (position1 == position2){
			--straight;
		} 
	}
   }      

   //all of these display if the card have any type of pair
   if (matches == 1){
	printf("\n\nYou have one pair.\n");
   }else if (matches == 2){
	printf("\n\nYou have two pairs.\n");
   }else if (matches == 3){  
	printf("\n\nYou have three of a kind.\n");
   }else if (matches ==  6){
	printf("\n\nYou have four of a kind.\n");
   }
   
   //display if there is a flush
   if (flush == 4){
	printf("\n\nYou have a flush.\n");
   }	
   //display if there is a straight
   if (straight == 4){
	printf("\n\nYou have a straight.\n");
   }
}
