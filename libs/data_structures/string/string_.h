#ifndef LIBS_STRING__H
#define LIBS_STRING__H

#define MAX_STRING_SIZE 100

static char stringBuffer[MAX_STRING_SIZE + 1];

typedef struct Word
{
    char *beginning; // позиция начала слова
    char *end; // позиция первого символа после последнего символа слова
} Word;

/* возвращает кол-во символов в строке, не считая нуль-символ */
size_t get_strlen(const char*);

/* возвращает указатель на первый элемент с кодом chr,
   расположенный на ленте памяти между адресами start и end,
   не включая end */
char* find(char*, char*, int);

/* возвращает указатель на первый символ, отличный от пробельного,
   расположенный на ленте памяти между адресами start и end,
   не включая end */
char* findNonSpaceChr(char*);

/* возвращает указатель на первый пробельный символ,
   расположенный на ленте памяти между адресами start и end,
   не включая end */
char* findSpaceChr(char*);

/* возвращает указатель на последний символ, отличный от пробельного,
   расположенный на ленте памяти между адресами start и end,
   не включая start */
char* findLastNonSpaceChr(char*, const char*);

/* возвращает указатель на последний пробельный символ,
   расположенный на ленте памяти между адресами start и end,
   не включая start */
char* findLastSpaceChr(char*, const char*);

int strcmp(const char*, const char*);

int is_lowercase(int);

/* записывает по адресу destination фрагмент памяти,
   начиная с адреса source_start до source_end;
   возвращает указатель на следующий свободный фрагмент памяти в
   destination */
char* copy(const char*, const char*, char*);

/* записывает по адресу destination элементы из фрагмента памяти,
   начиная с source_start и заканчивая source_end,
   удовлетворяющие функции-предикату f;
   возвращает указатель на следующий свободный для записи фрагмент в памяти */
char* copyBasedOnCondition(char*, const char*, char*, int (*)(int));

/* записывает по адресу destination элементы из фрагмента памяти,
   начиная с source_end и заканчивая source_start,
   удовлетворяющие функции-предикату;
   возвращает указатель на следующий свободный для записи фрагмент в памяти */
char* copyReversedBasedOnCondition(char*, const char*,
                                   char*, int (*)(int));

/* возвращает указатель на последний символ в строке */
char* getEndOfString(char*);

/* сокращает количество пробелов между словами
   данного предложения до одного */
void removeExtraSpaces(char*);

int getWord(char*, Word*);

/* переносит цифры каждого слова были в конец слова
   без изменения порядка следования их в слове, а буквы – в начало */
void moveDigitsToWordEnd(Word);

#endif //LIBS_STRING__H
