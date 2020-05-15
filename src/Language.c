/**
 * @file language.c
 * @brief This file enable to have different language for the game.
 * For each language a new file must be create and redeclare in it all message corresponding to the id
 *
 * @author Brisset J.
 */

#ifndef language
#define language

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __Win32
# include "utils\\LinkedList.c"
#else
# include "utils/LinkedList.c"
#endif

#ifdef __Win32
# define LANG_DIRECTORY "resources\\lang\\"
#else
# define LANG_DIRECTORY "ressources/lang/"
#endif
#define LANG_FILE_EXTENTION "lang"
#define DEFAULT_LANG "en_us"

#define TRANSLATION_LENGHT 256

/**
 * @struct Translation
 * @brief This structure represente a traduction
 */
typedef struct {
    char id[TRANSLATION_LENGHT];            /*<id of the message >*/
    char message[TRANSLATION_LENGHT];       /*<translated message >*/
} Translation;

/**
 * @def Data
 * @brief A LinkedList tha contain as value a pointer to a Translation struct
 */
Cell * Data = NULL;


/**
 * @fn int unloadLanguage()
 * @brief Unregister all translation
 */
int unloadLanguage() {

    //FREE ALL MALLOC
    foreach(i, Data) {
        free(i->value);
    }
    freeAll(Data);

    Data = NULL; //reset header
    return 0;
}

/**
 * @fn int loadLanguage(const char * lang)
 * @brief This function register all message of the specified lang in Data 
 *
 * @param lang is the language to load (i.e. "en_us" for american translation)
 */
int loadLanguage(const char * lang) {

    if (Data != NULL) unloadLanguage();

    char fileName[256] = "";
    sprintf(fileName, "%s%s.%s", LANG_DIRECTORY, lang, LANG_FILE_EXTENTION);
    FILE* stream = fopen(fileName, "r");

    if (stream == NULL && lang == DEFAULT_LANG) { //DEFAULT LANG FILE DOES NOT EXIST
        //log(SEVERE, "No default lang file found ! (%s)", DEFAULT_LANG);
        Data = NULL;
        return -1;
    }
    if (stream == NULL) { // FILE NOT FOUND
        loadLanguage(DEFAULT_LANG);
        //log(WARN, "No %s file found! Loaded %s lang", fileName, DEFAULT_LANG);
        return -1;
    }

    char buffer[1024] = "";
    while (fgets(buffer, sizeof(buffer), stream) != NULL) { //READING FILE
        if ( !strcmp(buffer, "\n") || buffer[0] == '#') continue;
        Translation * translate = malloc( sizeof(Translation) );

        char id[256], message[256];
        sscanf(buffer, "%s = %s", id, message);

        sprintf(translate->id, id);
        sprintf(translate->message, message);

        addValue(&Data, translate);
    }

    fclose(stream);
    return 0;
}

/**
 * @fn char * getTranslatedText(const char * id)
 * @brief This function give the translation of the message in the current language
 *
 * @char id is the id of the message to translate (i.e. "game.title" )
 *
 * @return the translated message as string
 */
char * getTranslatedText(char * id) {
    foreach(i, Data) {
        if (!strcmp( ((Translation*)i->value)->id, id ) ) return ((Translation *)i->value)->message;
    }
    return id;
}

/**
 * @fn int printfTranslationList()
 * @brief print all translation registered
 * @deprecated intend for debug uses
 */
int printfTranslationList() {
    foreach(i, Data) {
        printf("%s : %s\n", ((Translation*)i->value)->id, ((Translation*)i->value)->message);
    }
    printf("\n");

    return 0;
}
#endif 