// Jiapei Li
// Submission date: 20200709

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "neuchre.h"

#define kPrintDebug 1

// Implement the Hand and other functions in here

//----------------------------------------
// Card functions
//----------------------------------------

// Creates a card, initializing the suit and name to that specified.
// Returns a pointer to the new card, which has beel allocated on the heap.
// It is the responsibility of the caller to call destroyCard()
// when it is done with the Card.
Card* CreateCard(Suit suit, Name name) {
    Card* tempCard;
    tempCard = (Card*)malloc(sizeof(Card));
    tempCard->name = name;
    tempCard->suit = suit;
    tempCard->value = -1;
    return tempCard;
}

// Destroys the card, freeing any memory allocated for the card.
void DestroyCard(Card* card) {
    free(card);
}

//----------------------------------------
// Hand functions
//----------------------------------------

// Creates a Hand struct and initializes any necessary fields.
// Returns a pointer to the new Hand, which has been allocated on the heap.
Hand* CreateHand() {
    Hand* newHand = (Hand*)malloc(sizeof(Hand));
    newHand->num_cards_in_hand = 0;
    newHand->first_card = NULL;
    return newHand;
}

// Adds a card to the hand.
void AddCardToHand(Card *card, Hand *hand) {
    if (hand->num_cards_in_hand >= kNumCardsInHand) {
        return;
    }

    hand->num_cards_in_hand++;
    CardNode* newCardNode = (CardNode*)malloc(sizeof(CardNode));

    if (hand->first_card !=NULL) {
        newCardNode->this_card = card;
        newCardNode->next_card = hand->first_card;
        newCardNode->prev_card = NULL;
        hand->first_card->prev_card = newCardNode;
        hand->first_card = newCardNode;
    } else {
        newCardNode->this_card = card;
        newCardNode->next_card = NULL;
        newCardNode->prev_card = NULL;
        hand->first_card = newCardNode;
    }
}

// Removes a card from the hand.
// Does not free the card; it is the responsibility
// of the caller to free the card at the appropriate
// time.
// Returns a pointer to the card that is no longer in the hand.
// Deleting the only node
// Deleting the first node that has other nodes after it
// Deleting the last node that has other nodes preceding it
// Deleting a node in the middle
Card* RemoveCardFromHand(Card *card, Hand *hand) {
    // no element in the hand
    if (hand->num_cards_in_hand == 0) {
        return NULL;
    }

    // For looping through the hand for checking each CardNode
    CardNode* currNode;
    currNode = hand->first_card;
    // For checking which CardNode to be removed,
    // and be called to free its memory
    CardNode* returnNode;
    Card* returnCard;  // For checking returned card

    // remove only card
    if (hand->num_cards_in_hand == 1) {
      returnNode = hand->first_card;  // CardNode to be freed
        hand->first_card = currNode->next_card;
        hand->num_cards_in_hand--;
        returnCard = currNode->this_card;
        free(returnNode);
        return returnCard;
    }

    // remove first card
    if (currNode->this_card == card) {
      returnNode = hand->first_card;  // CardNode to be freed
        hand->first_card = hand->first_card->next_card;
        hand->num_cards_in_hand--;
        hand->first_card->prev_card = NULL;
        returnCard = currNode->this_card;
        free(returnNode);
        return returnCard;
    }

    // remove middle card
    while (currNode->next_card != NULL) {
        if (currNode->this_card == card) {
            returnNode = currNode;  // CardNode to be freed
            currNode->prev_card->next_card = currNode->next_card;
            currNode->next_card->prev_card = currNode->prev_card;
            hand->num_cards_in_hand--;
            returnCard = currNode->this_card;
            free(returnNode);
            return returnCard;
        }
        currNode = currNode->next_card;

        // remove last card
        if ((currNode->next_card == NULL) && (currNode->this_card == card)) {
            returnNode = currNode;  // CardNode to be freed
            currNode->prev_card->next_card = currNode->next_card;
            hand->num_cards_in_hand--;
            returnCard = currNode->this_card;
            free(returnNode);
            return returnCard;
        }
    }

    return NULL;
}

// Determines if there are any cards in the hand.
// Return 1 if the hand is empty; 0 otherwise.
int IsHandEmpty(Hand* hand) {
    if (hand->num_cards_in_hand > 0) {
        return 0;
    }
    return 1;
}

// Destroys the hand, freeing any memory allocated for it.
void DestroyHand(Hand* hand) {
    free(hand);
}

//----------------------------------------
// Game functions
//----------------------------------------

// Given a deck (assume that it is already shuffled),
// take the top card from the deck and alternately give
// it to player 1 and player 2, until they both have
// kNumCardsInHand.
void Deal(Deck *aDeck, Hand *p1hand, Hand *p2hand) {
    int i;
    for (i = 0; i < kNumCardsInHand; i++) {
        Card* temp = PopCardFromDeck(aDeck);
        AddCardToHand(temp, p1hand);
        temp = PopCardFromDeck(aDeck);
        AddCardToHand(temp, p2hand);
    }
}

// Given a lead card, a players hand, and the card the player wants
// to play, is it legal?
// If the player has a card of the same suit as the ledCard, they
// must play a card of the same suit.
// If the player does not have a card of the same suit, they can
// play any card.
// Returns 1 if the move is legal; 0 otherwise.
int IsLegalMove(Hand *hand, Card *lead_card, Card *played_card) {
    // check if there is same suit in the hand
    if (IsHandEmpty(hand)) {
        return 0;
    }

    int mark = FALSE;

    CardNode* currNode;
    currNode = hand->first_card;
    while (currNode->next_card != NULL) {
        if (currNode->this_card->suit == lead_card->suit) {
            mark = TRUE;
        }
        currNode = currNode->next_card;
    }

    if (mark == TRUE) {
        if (played_card->suit == lead_card->suit) return 1;
        return 0;
    }
    return 1;
}

// Given two cards that are played in a hand, which one wins?
// If the suits are the same, the higher card name wins.
// If the suits are not the same, player 1 wins, unless player 2 played trump.
// Returns 1 if the person who led won, 0 if the person who followed won.
int WhoWon(Card *lead_card, Card *followed_card, Suit trump) {
    if (lead_card->suit == followed_card->suit) {
        if (lead_card->name >= followed_card->name) return 1;
        return 0;
    }
    if (lead_card->suit != followed_card->suit) {
        if (followed_card->suit == trump) return 0;
        return 1;
    }
    return 1;
}

// Take all the cards out of a given hand, and put them
// back into the deck.
void ReturnHandToDeck(Hand *hand, Deck *deck) {
    CardNode* currNode = (CardNode*)malloc(sizeof(CardNode));
    currNode = hand->first_card;
    while (currNode->next_card != NULL) {
        PushCardToDeck(currNode->this_card, deck);
        currNode = currNode->next_card;
    }
    PushCardToDeck(currNode->this_card, deck);
    free(currNode);
}

//----------------------------------------
// Challenge functions
//----------------------------------------

// Considering this for a challenge problem.
Card* GetBestMove(Hand *my_hand, Card *led_card, Suit trump) {
    return NULL;
}

// Sort the given hand in descending order of power.
//
// The sort order should be: all cards of the given trump should
// be the "highest", and A high down to 9;
// The other suits can be in random order, but the card values must go
// from high to low.
void SortHand(Hand *hand, Suit trump) {
}

void ShuffleHand(Hand* hand) {
}
