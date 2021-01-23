#include <conio.h>   // needed for _getch() call at end of main()
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> // needed for _getch() call at end of main()

#define SUITS 4
#define FACES 13
#define CARDS 52
#define HAND_SIZE 5
#define HANDS_IN_DECK 10
#define NUMBER_OF_HANDS_PLAYED 10000000  //Currently set to 10 million
#define NUMB_HANDS_STR "10 million" //Currently set to 10 million
#define TRUE 1
#define FALSE 0
#define NEXT4 4

// prototypes of functions supplied
void deal(const unsigned int wDeck[], const char* wFace[], //display all cards in deck
    const char* wSuit[]);
void dealNextHand(unsigned int wDeck[], unsigned int hand[]); //deal out next hand from the deck
int isFourOfAKind(const unsigned int hand[]);  // return true if hand contains four of a kind and false otherwise

// prototypes of functions you must implement
void swap(unsigned int* const, unsigned int* const); //swap the two cards pointed to by the 2 pointers
void shuffle(unsigned int wDeck[]); //shuffle deck
int isPair(const unsigned int hand[]);  // return true if hand contains a pair and false otherwise
int isTwoPair(const unsigned int hand[]);  // return true if hand contains a two pair and false otherwise
int isThreeOfAKind(const unsigned int hand[]);  // return true if hand contains three of a kind and false otherwise
int isStraight(const unsigned int hand[]);  // return true if hand is a straight and false otherwise
int isFlush(const unsigned int hand[]);  // return true if hand is a flush and false otherwise
int isFullHouse(const unsigned int hand[]);  // return true if hand is a full house and false otherwise
int isRoyalFlush(const unsigned int head[]); // return true if hand is a royal flush and false otherwise

int main(void)
{
    // define and initialize deck array
    unsigned int deck[CARDS];

    // initialize deck with values 0 to CARDS-1
    // value / 13 caluclates suit #     { "Hearts", "Diamonds", "Clubs", "Spades" };
    // value % 13 calculates face card  {Ace, 2, 3, ... 10, Jack, Queen, King}
    for (size_t card = 0; card < CARDS; ++card)
    {
        deck[card] = card;
    }

    srand((unsigned int)time(NULL)); // seed random-number generator

    // initialize suit array                       
    const char* suit[SUITS] =
    { "Hearts", "Diamonds", "Clubs", "Spades" };

    // initialize face array                   
    const char* face[FACES] =
    { "Ace", "Deuce", "Three", "Four",
     "Five", "Six", "Seven", "Eight",
     "Nine", "Ten", "Jack", "Queen", "King" };

    /*
    shuffle(deck);  // uncomment after completing the implementation 
                    // of the swap() and shuffle() functions
    */
    shuffle(deck);
    deal(deck, face, suit); // display the deck unshuffled

    unsigned int hand[HAND_SIZE]; // will contain the cards in the hand.

    //Define and initialize variables used to count each type of hand
    unsigned int pairCount = 0;
    unsigned int twoPairCount = 0;
    unsigned int threeOfAKindCount = 0;
    unsigned int straightCount = 0;
    unsigned int flushCount = 0;
    unsigned int fullHouseCount = 0;
    unsigned int fourOfAKindCount = 0;
    unsigned int straightFlushCount = 0; //NOTE: This count includes both straight flushes and royal flushes.
    unsigned int royalFlushCount = 0;
    // Shuffle the deck for the first time
    // After this, we shuffle deck every time we do not have enough undealth cards 
    // for a complete hand which will be every 10 deals assuming five card hands
    shuffle(deck);

    // Deal out NUMBER_OF_HANDS_PLAYED hands
    for (size_t hands = 1; hands < NUMBER_OF_HANDS_PLAYED; ++hands)
    {
        dealNextHand(deck, hand); // Deal out next 5 cards from the deck into the array hand

        // Does hand have a pair?
        if (isPair(hand))
        {
            ++pairCount;  // Yes, increment pair count
        }

        // Does hand have two pair?
        if (isTwoPair(hand))
        {
            ++twoPairCount;
        }

        // Does hand have three of a kind?
        if (isThreeOfAKind(hand))
        {
            ++threeOfAKindCount;
        }

        // Does hand have a straight?
        if (isStraight(hand))
        {
            // Check if also a flush
            if (isFlush(hand) & !isRoyalFlush(hand))
            {
                ++straightFlushCount; //both straight and flush
            }
            else
            {
                ++straightCount; // nope, just a straight
            }
        }

        // Does hand have a flush?
        else if (isFlush(hand)) //not a straight, how about a flush?
        {
            ++flushCount;
        }

        // Does hand have a full house?
        if (isFullHouse(hand))
        {
            ++fullHouseCount;
        }

        // Does hand have four of a kind?
        if (isFourOfAKind(hand))
        {
            ++fourOfAKindCount;
        }

        // Does hand have royal flush?
        if (isRoyalFlush(hand))
        {
            ++royalFlushCount;
        }
    }

    printf("\nA pair occurred %d times in "NUMB_HANDS_STR" hands, which means the probability of a pair is %.2f % c", pairCount, pairCount * 100.0 / NUMBER_OF_HANDS_PLAYED, '%');
    printf("\nTwo pair occurred %d times in "NUMB_HANDS_STR" hands, which means the probability of two pair is %.2f %c", twoPairCount, twoPairCount * 100.0 / NUMBER_OF_HANDS_PLAYED, '%');
    printf("\nThree of a kind occurred %d times in "NUMB_HANDS_STR" hands, which means the probability of three of a kind is %.2f %c", threeOfAKindCount, threeOfAKindCount * 100.0 / NUMBER_OF_HANDS_PLAYED, '%');
    printf("\nA straight occurred %d times in "NUMB_HANDS_STR" hands, which means the probability of a straight is %.3f %c", straightCount, straightCount * 100.0 / NUMBER_OF_HANDS_PLAYED, '%');
    printf("\nA flush occurred %d times in "NUMB_HANDS_STR" hands, which means the probability of a flush is %.3f %c", flushCount, flushCount * 100.0 / NUMBER_OF_HANDS_PLAYED, '%');
    printf("\nA full house occurred %d times in "NUMB_HANDS_STR" hands, which means the probability of a full house is %.4f %c", fullHouseCount, fullHouseCount * 100.0 / NUMBER_OF_HANDS_PLAYED, '%');
    printf("\nFour of a kind occurred %d times in "NUMB_HANDS_STR" hands, which means the probability of four of a kind is %.4f %c", fourOfAKindCount, fourOfAKindCount * 100.0 / NUMBER_OF_HANDS_PLAYED, '%');
    printf("\nStraight flush occurred %d times in "NUMB_HANDS_STR" hands, which means the probability of a straight flush is %.5f %c", straightFlushCount, straightFlushCount * 100.0 / NUMBER_OF_HANDS_PLAYED, '%');
    printf("\nRoyal flush occurred %d times in "NUMB_HANDS_STR" hands, which means the probability of a royal flush is %.5f %c", royalFlushCount, royalFlushCount * 100.0 / NUMBER_OF_HANDS_PLAYED, '%');
    puts("");

    _getch();
}

// Display all of the cards in the deck
void deal(const unsigned int wDeck[], const char* wFace[],
    const char* wSuit[])
{
    // deal each of the cards
    for (size_t card = 0; card < CARDS; ++card) {
        size_t suit = wDeck[card] / 13;
        size_t face = wDeck[card] % 13;
        printf("%5s of %-8s%c", wFace[face], wSuit[suit],
            card % 4 == 3 ? '\n' : '\t'); // 4-column format 
    }
}

// Deal out the next HAND_SIZE cards into the array hand[]
// If not enough undealt cards left in wDeck, shuffle wDeck and 
//    start dealing from beginning of the wDeck again.
void dealNextHand(unsigned int wDeck[], unsigned int hand[])
{
    static unsigned int currentCard = 0; //remembers which is the next card to be dealt.

    // Shuffle deck and start from beginning of deck if not enough cards left for whole hand
    if ((currentCard + HAND_SIZE) >= CARDS)
    {
        shuffle(wDeck);
        currentCard = 0;
    }

    // Deal out HAND_SIZE cards from wDeck into the hand array
    for (size_t card = 0; card < HAND_SIZE; ++card)
    {
        hand[card] = wDeck[currentCard++];
    }
}

// Returns true if hand contains four of kind and false otherwise
int isFourOfAKind(const unsigned int hand[])
{
    unsigned int faceCnt[FACES] = { 0 };

    // Calculate the frequency of each face card in the hand
    for (size_t card = 0; card < HAND_SIZE; ++card)
    {
        ++faceCnt[hand[card] % 13];
    }

    // Iterate through all of the frequency counts to find out if 
    //     any of them occurred 4 times in the hand
    for (size_t face = 0; face < FACES; ++face)
    {
        if (faceCnt[face] == 4)
        {
            return TRUE; // Yes!!! Return true.
        }
    }

    return FALSE; //Nope ;-(
}

// Student implements the 8 functions below

// Swap the two unsigned ints pointed to by the pointers card1 and card2
void swap(unsigned int* const card1, unsigned int* const card2)
{
    // Student implements this function
    unsigned int hold;
    hold = *card1;
    *card1 = *card2;
    *card2 = hold;
}

// Shuffle cards in deck
void shuffle(unsigned int wDeck[])
{
    // Student implements this function
    for (int i = 0; i < CARDS; i++)
    {
        swap(&wDeck[i], &wDeck[rand()%CARDS]);
    }
}

// Returns true if hand contains only a pair and false other wise
// NOTE: Will return FALSE if the hand contains any of these hand types as well:
//  1) Hand has 2 pairs
//  2) Hand has 3 of a kind
//  3) Hand is a full house
//  4) Hand has 4 of a kind
int isPair(const unsigned int hand[])
{
    // Student implements this function
    unsigned int faceCnt[FACES] = { 0 };
    unsigned int pairCount = 0;
    unsigned int threeCount = 0;
    unsigned int fourCount = 0;
    // Calculate the frequency of each face card in the hand 
    for (size_t card = 0; card < HAND_SIZE; ++card)
    {
        ++faceCnt[hand[card] % 13];
    }

    // Iterate through all of the frequency counts to find out 
    //  if any of them occured 2 times (a pair) in the hand 
    for (size_t face = 0; face < FACES; ++face)
    {
        switch (faceCnt[face])
        {
        case 2:
            ++pairCount;
            break;
        case 3:
            ++threeCount;
            break;
        case 4:
            ++fourCount;
            break;
        default:
            break;
        }
    }

    // False if there's 2 pairs OR 3 of a kind OR full house OR 4 of a kind
    if (pairCount > 1 || threeCount > 0 || (pairCount == 1 && threeCount == 1) || fourCount > 0 )
    {
        return FALSE;
    }

    return pairCount == 1 ? TRUE : FALSE;// true if exacly one pair

}

// Returns true if hand contains two pairs and false otherwise
// NOTE: Will return FALSE if the hand contains any of these hand types as well:
//  1) Hand has 3 of a kind
//  2) Hand is a full house
//  3) Hand has 4 of a kind
int isTwoPair(const unsigned int hand[])
{
    // Student implements this function
    unsigned int faceCnt[FACES] = { 0 };
    unsigned int pairCount = 0;
    unsigned int threeCount = 0;
    unsigned int fourCount = 0;
    // Calculate the frequency of each face card in the hand 
    for (size_t card = 0; card < HAND_SIZE; ++card)
    {
        ++faceCnt[hand[card] % 13];
    }

    // Iterate through all of the frequency counts to find out 
    //  if any of them occured 2 times (a pair) in the hand 
    // if there's a pair, add one to the pairCount
    for (size_t face = 0; face < FACES; ++face)
    {
        switch (faceCnt[face])
        {
        case 2:
            ++pairCount;
            break;
        case 3:
            ++threeCount;
            break;
        case 4:
            ++fourCount;
            break;
        default:
            break;
        }
    }
    
    //false if there's a 3 of a kind, full hosue or a 4 of a kind 
    if (threeCount > 0 || (threeCount == 1 && pairCount == 1) || fourCount > 0)
    {
        return FALSE;
    }

    return pairCount == 2 ?  TRUE: FALSE;

}

// Returns true if hand contains 3 of a kind and false otherwise
// NOTE: Will return FALSE if the hand contains any of these hand types as well:
//  1) Hand has a full house
//  2) Hand has 4 of a kind
int isThreeOfAKind(const unsigned int hand[])
{
    // Student implements this function
    unsigned int faceCnt[FACES] = { 0 };
    unsigned int pairCount = 0;
    unsigned int threeCount = 0;
    unsigned int fourCount = 0;

    // Calculate the frequency of each face card in the hand 
    for (size_t card = 0; card < HAND_SIZE; ++card)
    {
        ++faceCnt[hand[card] % 13];
    }

    // Iterate through all of the frequency counts to out 
    //  if any of them occured 3 times (3 of a kind) in the hand 
    for (size_t face = 0; face < FACES; ++face)
    {
        switch (faceCnt[face])
        {
        case 2:
            ++pairCount;
            break;
        case 3:
            ++threeCount;
            break;
        case 4:
            ++fourCount;
            break;
        default:
            break;
        }
    }

    // false if there's full house or a 4 of a kind 
    if ((threeCount == 1 && pairCount == 1) || fourCount == 1) {
        return FALSE;
    }

    //true only if there's exactly one 3 of a kind 
    return threeCount == 1 ? TRUE : FALSE;
}

// Returns true if hand is a straight and false otherwise
// This function does NOT check if also a flush. That is done in main()

// VERY IMPORTANT: The Ace can be used to create a straight in 2 different ways:
//  Ace, 2, 3, 4, 5 and 
//  10, Jack, Queen, King, Ace
//  You need to check for both uses of the Ace to create a straight
int isStraight(const unsigned int hand[])
{
    // Student implements this function
    unsigned int faceCnt[FACES] = { 0 };
    for (size_t card = 0; card < HAND_SIZE; ++card)
    {
        ++faceCnt[hand[card] % 13];
    }

    for(size_t face = 0; face <FACES - NEXT4; ++face) // we only consider cards from Ace to 9 
    {
        if(face == 0)
        {
            if (faceCnt[face] == 1)
            {   
                // check Ace,2,3,4,5
                int fwdStraight = faceCnt[1] == 1 && faceCnt[2] == 1 && faceCnt[3] == 1 && faceCnt[4] == 1 ? TRUE : FALSE;
                // check 10, J, Q, K, Ace
                int BwdStraight = faceCnt[12] == 1 && faceCnt[11] == 1 && faceCnt[10] == 1 && faceCnt[9] == 1 ? TRUE : FALSE;
                return fwdStraight == TRUE || BwdStraight == TRUE ? TRUE : FALSE;
            }
        }
        else 
        {
            if (faceCnt[face] == 1)
            {
                for (int i = 1; i <= NEXT4; ++i)
                {
                    if (faceCnt[face + i] != 1) {
                        return FALSE;
                    }
                }
                return TRUE; // if the above cases did not return false then straight found.
            }
        }
    }
    return FALSE;
}

// Returns true if hand is a flush and false otherwise
int isFlush(const unsigned int hand[])
{
    // Student implements this function
    unsigned int suitCnt[SUITS] = { 0 };

    // Calculate the frequency of each suit card in the hand
    for (size_t card = 0; card < HAND_SIZE; ++card)
    {
        ++suitCnt[hand[card] / 13];
    }

    // Loop through all of the frequency counts to find out 
    //  if any of them occured 5 times in the hand
    for (size_t suit = 0; suit < SUITS; ++suit)
    {
        if (suitCnt[suit] == 5)
        {
            return TRUE;
        }
    }
    return FALSE;
}

// return true if hand is a full house and false otherwise
int isFullHouse(const unsigned int hand[])
{
    // Student implements this function
    unsigned int faceCnt[FACES] = { 0 };
    unsigned int pairCount = 0;
    unsigned int threeCount = 0;

    // Calculate the frequency of each face card in the hand 
    for (size_t card = 0; card < HAND_SIZE; ++card)
    {
        ++faceCnt[hand[card] % 13];
    }

    // Iterate through all of the frequency counts to out 
    //  if any of them occured 3 times (3 of a kind) in the hand 
    for (size_t face = 0; face < FACES; ++face)
    {   
        switch (faceCnt[face])
        {
            case 2:
                ++pairCount;
                break;
            case 3:
                ++threeCount;
                break;
            default:
                break;
        }
    }

    // true only if there's exactly one pair and one 3 of a kind 
    return pairCount == 1 && threeCount == 1 ? TRUE : FALSE;
}

// return true if hand is a royal flush false otherwise 
int isRoyalFlush(const unsigned int hand[])
{
    // Student implements this function
    unsigned int suitCnt[SUITS] = { 0 };
    unsigned int faceCnt[FACES] = { 0 };

    // Calculate the frequency of each suit card in the hand
    for (size_t card = 0; card < HAND_SIZE; ++card)
    {
        ++suitCnt[hand[card] / 13];
        ++faceCnt[hand[card] % 13];
    }

    // Loop through all of the frequency counts to find out 
    //  if any of them occured 5 times in the hand
    for (size_t suit = 0; suit < SUITS; ++suit)
    {   
        if(suitCnt[suit] == 5)
        {   
            // check if there's an Ace
            if (faceCnt[0] == 1)
            {
                // check 10, J, Q, K, Ace
                return faceCnt[12] == 1 && faceCnt[11] == 1 && faceCnt[10] == 1 && faceCnt[9] == 1 ? TRUE : FALSE;
            }
        }
    }

    return FALSE;
}
