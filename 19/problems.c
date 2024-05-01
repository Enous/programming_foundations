#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "problems.h"
#include "matrix.h"
#include "string_.h"

/* транспонирует матрицу в файле */
void ftranspose(FILE* f, char* fname)
{
    f = fopen(fname, "r");

    char buffer[MAX_STR_SIZE];
    char str_arr[MAX_SIZE][MAX_STR_SIZE];

    int j = 0;

    while (fgets(buffer, sizeof(buffer), f))
    {
        char* token = strtok(buffer, " ");

        char* chr_order = token;
        char* chr_order_ptr = chr_order;

        int order = atoi(token);

        token = strtok(NULL, " ");

        int* arr = malloc(sizeof(int) * order * order);
        int i = 0;
        arr[i++] = order;

        while (token)
        {
            arr[i] = atoi(token);
            token = strtok(NULL, " ");
            i++;
        }

        matrix mx = createMatrixFromArray(arr + 1, order, order);
        transposeMatrix(&mx);

        int shift = 0;

        while (order > 0)
        {
            order /= 10;
            shift++;
        }

        chr_order_ptr += sizeof(char) * shift;
        *(chr_order_ptr++) = ' ';
        *chr_order_ptr = '\0';

        int str_size;

        char* res = matrixIntoCharArr(mx, &str_size);
        strcat(chr_order, res);

        strcpy(str_arr[j++], chr_order);

        *buffer = '\0';
    }

    fclose(f);

    f = fopen(fname, "w");

    if (j == 0)
        fprintf(f, "%s", "");
    else
    {
        for (int k = 0; k < j; k++)
        {
            if (k < j - 1)
                fprintf(f, "%s\n", str_arr[k]);
            else
                fprintf(f, "%s", str_arr[k]);
        }
    }

    fclose(f);
}


/* представляет каждое вещественное число в файле
   в форме с плавающей точкой */
void fileFixedToFloating(FILE* f, char* fname)
{
    f = fopen(fname, "r");

    char buffer[MAX_STR_SIZE];
    double res_arr[MAX_SIZE];

    int j = 0;

    while (fgets(buffer, sizeof(buffer), f))
    {
        res_arr[j++] = ceil(atof(buffer) * 100) / 100;

        *buffer = '\0';
    }

    fclose(f);

    f = fopen(fname, "w");

    if (j == 0)
        fprintf(f, "%s", "");
    else
    {
        for (int k = 0; k < j; k++)
        {
            if (k < j - 1)
                fprintf(f, "%.2f\n", res_arr[k]);
            else
                fprintf(f, "%.2f", res_arr[k]);
        }
    }

    fclose(f);
}


/* решает выражение из 2-3 операндов, находящееся в файле,
   и записывает в конец данного файла результат */
void fsolve(FILE* f, char* fname)
{
    f = fopen(fname, "r");

    char buffer[MAX_STR_SIZE];
    double nums[MAX_SIZE];

    int j = 0;
    char operator;
    float res = 0;

    char* token = strtok(buffer, " ");

    while (token)
    {
        if (isdigit(*buffer) && (operator == '*' || operator == '/'))
            nums[j++] = *buffer - '0';
        else if (*buffer == '+' || *buffer == '-')
        {
            operator = *buffer;
        }
        else if (*buffer == '*' || *buffer == '/')
        {

        }

        token = strtok(NULL, " ");
    }
}


/* сохраняет в файле только те слова,
   которые содержат данную последовательность символов */
void fsaveWordsWithSequence(FILE* f, char* fname, char* sequence)
{
    f = fopen(fname, "r");

    char buffer[MAX_STR_SIZE];
    fgets(buffer, sizeof(buffer), f);
    char* buffer_ptr = buffer;

    char res[MAX_STR_SIZE];
    char* res_ptr = res;

    int sequence_len = strlen(sequence);

    Word w;

    while (getWord(buffer_ptr, &w))
    {
        bool contains_sequence = false;

        char* ptr = w.beginning;

        while (ptr != w.end)
        {
            if (*ptr == *sequence && (w.end - ptr >= sequence_len))
            {
                if (!wordsAreEqual((Word) {ptr, ptr + sequence_len},
                                                  (Word) {sequence, sequence + sequence_len}))
                {
                    contains_sequence = true;
                    break;
                }
            }

            ptr++;
        }

        if (contains_sequence)
        {
            int word_len = w.end - w.beginning;
            memcpy(res_ptr, w.beginning, word_len);
            res_ptr += word_len;
            *res_ptr = ' ';
            res_ptr++;
        }

        buffer_ptr = w.end;
    }

    if (*(res_ptr - 1) == ' ')
        *(res_ptr - 1) = '\0';
    else if (*res_ptr != '\0')
        *res_ptr = '\0';

    fclose(f);

    f = fopen(fname, "w");

    fprintf(f, "%s", res);

    fclose(f);
}


/* преобразовывает файл, оставляя в каждой строке
   только самое длинное слово */
void fsaveOnlyLongestWordInEveryLine(FILE* f, char* fname)
{
    f = fopen(fname, "r");

    char buffer[MAX_STR_SIZE];
    char res[MAX_SIZE][MAX_STR_SIZE];

    int j = 0;

    while (fgets(buffer, sizeof(buffer), f))
    {
        char* buffer_ptr = buffer;

        Word w;
        getWord(buffer_ptr, &w);

        char longest_word[MAX_WORD_LEN];
        wordToStr(w, longest_word);

        int max_len = w.end - w.beginning;

        buffer_ptr = w.end;

        while (getWord(buffer_ptr, &w))
        {
            int w_len = w.end - w.beginning;

            if (w_len > max_len)
            {
                max_len = w_len;
                wordToStr(w, longest_word);
            }

            buffer_ptr = w.end;
        }

        *(longest_word + max_len) = '\0';
        strcpy(res[j++], longest_word);

        *buffer = '\0';
    }

    fclose(f);

    f = fopen(fname, "w");

    if (j == 0)
        fprintf(f, "%s", "");
    else
    {
        for (int k = 0; k < j; k++)
        {
            if (k < j - 1)
                fprintf(f, "%s\n", res[k]);
            else
                fprintf(f, "%s", res[k]);
        }
    }

    fclose(f);
}


/* преобразовывает файл таким образом, чтобы сначала были
   целые положительные числа, а затем отрицательные;
   порядок следования как положительных,
   так и отрицательных чисел сохраняется */
void fsortPosAndNeg(FILE* f, char* fname)
{
    f = fopen(fname, "r");

    char buffer[MAX_STR_SIZE];
    char res[MAX_SIZE][MAX_STR_SIZE];

    int j = 0;

    while (fgets(buffer, sizeof(buffer), f))
    {
        Word w;

        char str[MAX_STR_SIZE];
        strcpy(str, buffer);
        char* str_ptr = str;

        char* buffer_ptr = buffer;

        while (getWord(str_ptr, &w))
        {
            if (*w.beginning != '-')
            {
                strcpy(buffer_ptr, w.beginning);
                buffer_ptr += w.end - w.beginning;
                *buffer_ptr = ' ';
                buffer_ptr++;
            }

            str_ptr = w.end;
        }

        str_ptr = str;

        while (getWord(str_ptr, &w))
        {
            if (*w.beginning == '-')
            {
                strcpy(buffer_ptr, w.beginning);
                buffer_ptr += w.end - w.beginning;
                *buffer_ptr = ' ';
                buffer_ptr++;
            }

            str_ptr = w.end;
        }

        if (*(buffer_ptr - 1) == ' ')
            *(buffer_ptr - 1) = '\0';
        else if (*(buffer_ptr - 1) == ' ' || *buffer_ptr != '\0')
            *buffer_ptr = '\0';

        strcpy(res[j++], buffer);

        *buffer = '\0';
    }

    fclose(f);

    f = fopen(fname, "w");

    if (j == 0)
        fprintf(f, "%s", "");
    else
    {
        for (int k = 0; k < j; k++)
        {
            if (k < j - 1)
                fprintf(f, "%s\n", res[k]);
            else
                fprintf(f, "%s", res[k]);
        }
    }

    fclose(f);
}