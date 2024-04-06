#ifndef LIBS_STRING__H
#define LIBS_STRING__H

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

int strcmp(const char* lhs, const char* rhs);

#endif //LIBS_STRING__H
