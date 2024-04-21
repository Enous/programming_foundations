#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <memory.h>

#include "string_.h"

/* возвращает кол-во символов в строке, не считая нуль-символ */
size_t get_strlen(const char* start)
{
    char* end = start;

    while (*end != '\0')
        end++;

    return end - start;
}


/* возвращает указатель на первый элемент с кодом chr,
   расположенном на ленте памяти между адресами start и end,
   не включая end */
char* find(char* start, char* end, int code)
{
    while (start != end && *start != code)
        start++;

    return start;
}


/* возвращает указатель на первый символ, отличный от пробельного,
   расположенный на ленте памяти между адресами start и end,
   не включая end */
char* findNonSpaceChr(char* start)
{
    while (isspace(*start) && *start != '\0')
        start++;

    return start;
}


/* возвращает указатель на первый пробельный символ,
   расположенный на ленте памяти между адресами start и end,
   не включая end */
char* findSpaceChr(char* start)
{
    while (!isspace(*start) && *start != '\0')
        start++;

    return start;
}


/* возвращает указатель на последний символ, отличный от пробельного,
   расположенный на ленте памяти между адресами start и end,
   не включая start */
char* findLastNonSpaceChr(char* end, const char* start)
{
    while (end != start )
    {
        end--;

        if (!isspace(*end) && *end != '\0')
            break;
    }

    return end;
}


/* возвращает указатель на последний пробельный символ,
   расположенный на ленте памяти между адресами start и end,
   не включая start */
char* findLastSpaceChr(char* end, const char* start)
{
    while (!isspace(*(end - 1)) && end != start)
        end--;

    return end;
}


int strcmp(const char* lhs, const char* rhs)
{
    while (*lhs && *lhs == *rhs)
        lhs++, rhs++;

    return *lhs - *rhs;
}


/* записывает по адресу destination фрагмент памяти,
   начиная с адреса source_start до source_end;
   возвращает указатель на следующий свободный фрагмент памяти в
   destination */
char* copy(const char* source_start, const char* source_end, char* destination)
{
    size_t len = source_end - source_start;

    memcpy(destination, source_start, sizeof(char) * len);

    return destination + sizeof(char) * len;
}


/* возвращает 1, если латинская буква прописная, и 0 в противном случае */
int is_lowercase(int chr)
{
    return chr >= 0x61 && chr <= 0x7a;
}


/* записывает по адресу destination элементы из фрагмента памяти,
   начиная с source_start и заканчивая source_end,
   удовлетворяющие функции-предикату;
   возвращает указатель на следующий свободный для записи фрагмент в памяти */
char* copyBasedOnCondition(char* source_start, const char* source_end, char* destination, int (*condition)(int))
{
    while (*source_start != *source_end)
    {
        if (condition(*(source_start)))
        {
            memcpy(destination, source_start, sizeof(char));
            destination++;
        }

        source_start++;
    }

    return destination;
}


/* записывает по адресу destination элементы из фрагмента памяти,
   начиная с source_end и заканчивая source_start,
   удовлетворяющие функции-предикату;
   возвращает указатель на следующий свободный для записи фрагмент в памяти */
char* copyReversedBasedOnCondition(char* source_end, const char* source_start,
                    char* destination, int (*condition)(int))
{
    while (*source_end != *source_start)
    {
        if (condition(*(source_end)))
        {
            memcpy(destination, source_end, sizeof(char));
            destination++;
        }

        source_end--;
    }

    return destination;
}


/* возвращает указатель на последний символ в строке */
char* getEndOfString(char* s)
{
    while (*s != '\0')
        s++;

    return s;
}


/* сокращает количество пробелов между словами
   данного предложения до одного */
void removeExtraSpaces(char* s)
{
    char* endSource = getEndOfString(s);
    int curr_space_count = 0;
    char *destination = s;
    char* destination_end = destination;

    while (*s != *endSource)
    {
        if (*s == ' ')
            curr_space_count++;
        else
        {
            if (curr_space_count >= 1)
            {
                *destination_end = ' ';
                destination_end++;
                curr_space_count = 0;
            }

            *destination_end = *s;
            destination_end++;
        }

        s++;
    }

    if (curr_space_count >= 1)
    {
        *destination_end = ' ';
        destination_end++;
        curr_space_count = 0;
    }

    *destination_end = '\0';
}


int getWord(char* start, Word* word)
{
    word->beginning = findNonSpaceChr(start);

    if (*word->beginning == '\0')
        return 0;

    word->end = findSpaceChr(word->beginning);

    return 1;
}


/* переносит цифры каждого слова были в конец слова
   без изменения порядка следования их в слове, а буквы – в начало */
void moveDigitsToWordEnd(Word word)
{
    char stringBuffer[MAX_STRING_SIZE + 1];

    char* endStringBuffer = copy(word.beginning, word.end,
                                 stringBuffer);

    char* letters_moved_to_end_w = copyBasedOnCondition(stringBuffer,
                                             endStringBuffer,
                                      word.beginning, isalpha);

    copyBasedOnCondition(stringBuffer, endStringBuffer,
                         letters_moved_to_end_w, isdigit);
}


/* заменяет каждую цифру в строке соответствующим ей числом пробелов */
void replaceDigitsWithDigitNumOfSpaces(char* s)
{
    size_t len = get_strlen(s);

    char stringBuffer[MAX_STRING_SIZE];

    char* endStringBuffer0 = copy(s, s + len,
                                 stringBuffer);

    char* read_ptr = stringBuffer;

    while (read_ptr != endStringBuffer0)
    {
        if (isdigit(*read_ptr))
        {
            size_t total_spaces = *read_ptr - '0';

            for (size_t i = 0; i < total_spaces; i++)
            {
                *s = ' ';
                s++;
            }
        }
        else
        {
            memcpy(s, read_ptr, sizeof(char));
            s++;
        }

        read_ptr++;
    }

    *s = '\0';
}


/* возвращает 0, если w1 и w2 равны,
   отрицательное значение, если w1 располагается до w2 в лексикографическом порядке,
   иначе - положительное значение */
int wordsAreEqual(Word w1, Word w2)
{
    char* start1 = w1.beginning;
    char* start2 = w2.beginning;

    while (start1 != w1.end && start2 != w2.end)
    {
        if (*start1 - *start2 != 0)
            return *start1 - *start2;

        start1++;
        start2++;
    }

    return 0;
}


/* заменяет все вхождения слова 𝑤1 на слово 𝑤2 */
void replace(char* src, char* w1, char* w2)
{
    size_t w1_len = get_strlen(w1);
    size_t w2_len = get_strlen(w2);

    char stringBuffer[MAX_STRING_SIZE + 1];

    Word word1 = {w1, w1 + w1_len};
    Word word2 = {w2, w2 + w2_len};

    char *read_ptr, *rec_ptr;

    if (w1_len >= w2_len)
    {
        read_ptr = src;
        rec_ptr = src;
    }
    else
    {
        copy(src, src + get_strlen(src) + 1, stringBuffer);
        read_ptr = stringBuffer;
        rec_ptr = src;
    }

    char* read_ptr_end = getEndOfString(read_ptr);

    while (read_ptr != read_ptr_end)
    {
        Word w;
        getWord(read_ptr, &w);

        size_t shift = w.beginning - read_ptr;

        memcpy(rec_ptr, read_ptr, sizeof(char) * shift);

        read_ptr += shift;
        rec_ptr += shift;

        size_t shift_read, shift_rec;
        shift_read = shift_rec = w.end - read_ptr;

        if (!wordsAreEqual(w, word1))
        {
                memcpy(rec_ptr, word2.beginning, sizeof(char) * w2_len);
                shift_rec = w2_len;
        }
        else
            memcpy(rec_ptr, read_ptr,sizeof(char) * shift_rec);

        read_ptr += shift_read;
        rec_ptr += shift_rec;
    }

    *rec_ptr = '\0';
}


/* возвращает true, если слова данного предложения расположены в лексикографическом порядке,
   и false в противном случае */
bool wordsAreInLexicographicOrder(char* s)
{
    Word prev_w, curr_w;

    char* start = s;

    if (getWord(start, &prev_w))
    {
        start = prev_w.end;

        while (getWord(start, &curr_w))
        {
            int res = wordsAreEqual(prev_w, curr_w);

            if (res > 0)
                return false;

            start = curr_w.end;
            prev_w = curr_w;
        }
    }

    return true;
}


/* возвращает 1, если слово найдено (начиная с конца строки), и 0 в противном случае */
int getWordStartingFromEnd(char* start, char* end, Word* word)
{
    word->end = findLastNonSpaceChr(end, start);
    word->beginning = findLastSpaceChr(word->end, start);

    if (word->end == word->beginning)
        return 0;

    return 1;
}


/* выводит слова в предложении в обратном порядке */
void printWordsInReverseOrder(char* s)
{
    Word w;

    char *start = s;
    char *end = s + get_strlen(s);

    while (getWordStartingFromEnd(start, end, &w))
    {
        char *w_beginning = w.beginning;

        while (!isspace(*w_beginning) && w_beginning != w.end + 1)
        {
            printf("%c", *w_beginning);
            w_beginning++;
        }

        printf("\n");

        size_t shift = end - w.beginning;
        end -= shift;
    }
}


/* возвращает количество слов-палиндромов в строке */
int countPalindromeWords(char* s)
{
    Word w;

    char *start = s;
    char *end = s + get_strlen(s);

    int count = 0;

    while (getWordStartingFromEnd(start, end, &w))
    {
        char* w_beginning = w.beginning;
        char* w_end = w.end;

        bool is_palindrome = true;

        while (w_beginning <= w_end)
        {
            if (*w_beginning != *w_end)
            {
                is_palindrome = false;
                break;
            }

            w_beginning++;
            w_end--;
        }

        if (is_palindrome)
            count++;

        size_t shift = end - w.beginning;
        end -= shift;
    }

    return count;
}


/* возвращает указатель на строку, в которой чередуются слова данных слов;
   если в одной из строк число слов больше, чем в другой, то оставшиеся
   слова этой строки записываются в конец итоговой строки */
char* mixStrings(char* s1, char* s2)
{
    Word w1, w2;

    size_t str_len = get_strlen(s1) + get_strlen(s2);
    char* s3 = malloc(sizeof(char) * str_len);
    char* ptr = s3;

    bool w1IsFound, w2IsFound;

    char* start1 = s1;
    char* start2 = s2;

    bool turn = false;

    while ((w1IsFound = getWord(start1, &w1)),
            (w2IsFound = getWord(start2, &w2)),
            w1IsFound || w2IsFound)
    {
        size_t len;
        char* src;

        if (w1IsFound && !turn)
        {
            len = w1.end - w1.beginning;
            src = w1.beginning;
        }
        else
        {
            len = w2.end - w2.beginning;
            src = w2.beginning;
        }

        memcpy(ptr, src, sizeof(char) * len);

        src += len;
        ptr += len;

        *ptr = ' ';
        ptr++;

        if (w1IsFound && !turn)
            start1 = w1.end;
        else
            start2 = w2.end;

        if (w1IsFound && w2IsFound)
            turn = !turn;
    }

    if (*(ptr - 1) == ' ')
        *(ptr - 1) = '\0';
    else
        *ptr = '\0';

    return s3;
}