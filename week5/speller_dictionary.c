// Implements a dictionary's functionality

#include <stdbool.h>
#include "dictionary.h"
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 17575;

// Hash table
node *table[N];

unsigned int word_count = 0;
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //hash the word
    unsigned int hashed_value =hash(word);
    node *hashed_word = table[hashed_value];

    while (hashed_word != NULL) {
        if (strcasecmp(hashed_word->word, word) == 0){
            return true;
        }
        hashed_word=hashed_word->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // unsigned int first =  toupper(word[0]) - 'A';
    // unsigned int second =  toupper(word[1]) - 'A';
    // unsigned int third =  toupper(word[2]) - 'A';
    // printf("%i,%i,%i",first,second,third);
    // int final = (676*first) + (26*second) + third;
    // return final;
    int hash_value = 0;

    if(strlen(word) <= 1)                                       // if there's only one word calculate that word, store to element after apostrophe
    {
        hash_value = ((677 * (toupper(word[0]) - 'A')) + 1);
        return hash_value;
    }
    else if(strlen(word) <= 2)                                  // if there's two word calculate that two word, store to element after apostrophe
    {
        hash_value = (677 * (toupper(word[0]) - 'A')) + (27 * (toupper(word[1]) - 'A')) + 1;
        return hash_value;
    }
    else
    {
        hash_value = (677 * (toupper(word[0]) - 'A')) + (27 * (toupper(word[1]) - 'A')) + (toupper(word[2]) - 'A') + 1;
        return hash_value;
    }
    // return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *fptr;
    if((fptr = fopen(dictionary,"r")) == NULL){
        printf("Error! opening file");

       // Program exits if the file pointer returns NULL.
       exit(1);
    }
    // Read each word in the file
    char dictword[LENGTH + 1];
    while(fscanf(fptr,"%s", dictword) != EOF){
        //Creating a node for hash table
        node *n = malloc(sizeof(node));
        if (n == NULL){
            printf("Error!");

            return false;
        }
        strcpy(n->word, dictword);
        unsigned int hash_value = hash(dictword);
        n->next = table[hash_value];
        table[hash_value] = n;
        word_count++;
    }
        // Add each word to the hash table

    // Close the dictionary file
    fclose(fptr);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for(int i = 0; i < N; i ++){
        node *cursor = table[i];
        while(cursor){
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        if (i == N - 1 && cursor == NULL)
        {
            return true;
        }
    }
    return false;
}