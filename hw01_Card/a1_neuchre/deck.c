#include <stdio.h>
#include <stdlib.h>

#include "neuchre.h"

#define PRINT_DEBUG 1

// Put your deck functions in here

//----------------------------------------
// Deck functions
//----------------------------------------
// Implement these functions in deck.c.
// Creates the deck to be used for NEUchre.
// Assume that the value of cards are:
// Nine=9; Ten=10; Jack=11; and so on, up to Ace=14.

// Creates the deck, initializing any fields necessary.
// Returns a pointer to the deck, which has been allocated on the heap.
Deck* CreateDeck() {
    Deck* newDeck = (Deck*)malloc(sizeof(Deck));
    newDeck->top_card = -1;
    return newDeck;
}

// Adds a card to the top of the deck.
// Returns a pointer to the deck.
// Changed the pass in argument.
Deck* PushCardToDeck(Card* card, Deck* currDeck) {
    if (currDeck->top_card < (kNumCardsInDeck - 1)) {
        currDeck->cards[++currDeck->top_card] = card;
    } else {
        printf("Deck is full!!\n");
    }
    return currDeck;
}

// Shows the top card, but does not remove it from the stack.
// Returns a pointer to the top card.
// If the deck is empty, return NULL.
Card* PeekAtTopCard(Deck* deck) {
    if ((deck->top_card >= 0) && (deck->top_card < kNumCardsInDeck)) {
        return deck->cards[deck->top_card];
    }
    return NULL;
}

// Removes the top card from the deck and returns it.
// The card should NOT be freed at this point; it is the
// responsibility of the caller to free the card at the
// appropriate time.
// Returns a pointer to the top card in the deck.
// If the deck is empty, return NULL.
Card* PopCardFromDeck(Deck* deck) {
    if (deck->top_card >= 0) {
        Card *tempCard = deck->cards[deck->top_card];
        deck->cards[deck->top_card] = NULL;
        deck->top_card--;
        return tempCard;
    }
    return NULL;
}

// Determines if the deck is empty.
// Returns 1 if the Deck is empty, 0 otherwise.
int IsDeckEmpty(Deck* deck) {
    if (deck->top_card >= 0) return 0;
    else
        return 1;
}

// Destroys the deck, freeing any memory allocated
// for this deck (the cards and the deck).
// DestroyDeck should call DestroyCard on all of the
// cards in the deck.
void DestroyDeck(Deck* deck) {
    int i;
    for (i = deck->top_card; i >= 0; i--) {
        DestroyCard(PopCardFromDeck(deck));
    }
    free(deck);
}

// Create a Deck for this game, and add any
// needed cards to the deck.
// Return a pointer to the deck to be used for the game
Deck* PopulateDeck() {
    Deck *deck = CreateDeck();
    Suit s = HEARTS;
    Name n = NINE;
    Card* tempCard;

    for (s = HEARTS; s <= DIAMONDS; s++) {
        for (n = NINE; n <= ACE; n++) {
            tempCard = CreateCard(s, n);
            PushCardToDeck(tempCard, deck);
        }
    }
    return deck;
}

// Shuffle the deck.
// Put them in a random order.
void Shuffle(Deck *deck) {
    srand(SHUFFLE_RAND);
    int i;
    for (i = 0; i < kNumCardsInDeck; i++) {
        int randCard = rand() % kNumCardsInDeck;
        SwapCards(deck->cards[i], deck->cards[randCard]);
    }
}

// sending in address of two cards
// to swap the cards in the card array in the deck
void SwapCards(Card* cardOne, Card* cardTwo) {
    Card temp = *cardOne;
    *cardOne = *cardTwo;
    *cardTwo = temp;
}
