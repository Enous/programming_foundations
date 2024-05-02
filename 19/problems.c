#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "problems.h"
#include "matrix.h"
#include "string_.h"

typedef struct wares
{
    char name[MAX_STR_SIZE];
    int unit_cost;
    int count;
    int total_cost;
} wares;

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

        int order = strtol(token, NULL, 10);

        token = strtok(NULL, " ");

        int* arr = malloc(sizeof(int) * order * order);
        int i = 0;
        arr[i++] = order;

        while (token)
        {
            arr[i] = strtol(token, NULL, 10);
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


/* решает выражение из 2-3 операндов
   и записывает в конец данного файла результат */
void fsolve(FILE* f, char* fname)
{
    f = fopen(fname, "r");

    char buffer[MAX_STR_SIZE];
    float nums[MAX_SIZE];
    char operators[MAX_SIZE];

    fgets(buffer, sizeof(buffer), f);

    int i, j;
    i = j = 0;

    char* token = strtok(buffer, " ");

    while (token)
    {
        if (*token == '+' || !strcmp(token, "-") ||
            *token == '*' || *token == '/')
            operators[j++] = *token;
        else
            nums[i++] = atof(token);

        token = strtok(NULL, " ");
    }

    fclose(f);

    float res = 0;

    if (i == 0)
    {
        f = fopen(fname, "w");
        fprintf(f, "");
        fclose(f);
        return;
    }

    if (j == 1)
    {
        if (operators[0] == '+')
            res = nums[0] + nums[1];
        else if (operators[0] == '-')
            res = nums[0] - nums[1];
        else if (operators[0] == '*')
            res = nums[0] * nums[1];
        else if (operators[0] == '/')
            res = nums[0] / nums[1];
    }
    else if (j == 2)
    {
        if (operators[0] == '+')
        {
            if (operators[1] == '*')
                res = nums[0] + nums[1] * nums[2];
            else if (operators[1] == '/')
                res = nums[0] + nums[1] / nums[2];
            else if (operators[0] == '+')
                res = nums[0] + nums[1] + nums[2];
            else
                res = nums[0] + nums[1] - nums[2];
        }
        else if (operators[0] == '-')
        {
            if (operators[1] == '*')
                res = nums[0] - nums[1] * nums[2];
            else if (operators[1] == '/')
                res = nums[0] - nums[1] / nums[2];
            else if (operators[0] == '+')
                res = nums[0] - nums[1] + nums[2];
            else
                res = nums[0] - nums[1] - nums[2];
        }
        else if (operators[0] == '*')
        {
            if (operators[1] == '*')
                res = nums[0] * nums[1] * nums[2];
            else if (operators[1] == '/')
                res = nums[0] * nums[1] / nums[2];
            else if (operators[0] == '+')
                res = nums[0] * nums[1] + nums[2];
            else
                res = nums[0] * nums[1] - nums[2];
        }
        else if (operators[0] == '/')
        {
            if (operators[1] == '*')
                res = nums[0] / nums[1] * nums[2];
            else if (operators[1] == '/')
                res = nums[0] / nums[1] / nums[2];
            else if (operators[0] == '+')
                res = nums[0] / nums[1] + nums[2];
            else
                res = nums[0] / nums[1] - nums[2];
        }
    }

    f = fopen(fname, "a");

    fprintf(f, "%.2g", res);

    fclose(f);
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
    f = fopen(fname, "rb");

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
        {
            *(buffer_ptr - 1) = '\n';
            *buffer_ptr = '\0';
        }
        else if (*buffer_ptr != '\0')
            *buffer_ptr = '\0';

        strcpy(res[j++], buffer);

        memset(buffer, 0, sizeof(buffer));
    }

    fclose(f);

    f = fopen(fname, "wb");

    if (j == 0)
        fwrite("", 0, 0, f);
    else
    {
        for (int k = 0; k < j; k++)
            fwrite(res[k], sizeof(char), strlen(res[k]), f);
    }

    fclose(f);
}


/* транспонирует матрицу в файле, если она не симметрична */
void ftransposeIfNonSymmetric(FILE* f, char* fname)
{
    f = fopen(fname, "rb");

    char buffer[MAX_STR_SIZE];
    char str_arr[MAX_SIZE][MAX_STR_SIZE];

    int j = 0;

    while (fgets(buffer, sizeof(buffer), f))
    {
        char* token = strtok(buffer, " ");

        char* chr_order = token;
        char* chr_order_ptr = chr_order;

        int order = strtol(token, NULL, 10);;

        token = strtok(NULL, " ");

        int* mx_arr = malloc(sizeof(int) * order * order);
        int i = 0;
        mx_arr[i++] = order;

        while (token)
        {
            mx_arr[i] = strtol(token, NULL, 10);
            token = strtok(NULL, " ");
            i++;
        }

        matrix mx = createMatrixFromArray(mx_arr + 1, order, order);

        if (!isSymmetricMatrix(&mx))
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

        chr_order_ptr = chr_order + strlen(chr_order);
        *(chr_order_ptr++) = '\n';
        *chr_order_ptr = '\0';

        strcpy(str_arr[j++], chr_order);

        *buffer = '\0';
    }

    fclose(f);

    f = fopen(fname, "wb");

    if (j == 0)
        fwrite("", 0, 0, f);
    else
    {
        for (int k = 0; k < j; k++)
            fwrite(str_arr[k], sizeof(char), strlen(str_arr[k]), f);
    }

    fclose(f);
}


void fileFormSportsTeam(FILE* f, char* fname, int n)
{
    f = fopen(fname, "rb");

    char buffer[MAX_STR_SIZE];
    str_matrix res = getMemStrMatrix(MAX_SIZE, MAX_STR_SIZE);
    int scores[MAX_SIZE];

    int i = 0;

    if (fgets(buffer, sizeof(buffer), f))
    {
        strcpy(res.values[i], buffer);

        Word w;
        getWordStartingFromEnd(buffer, getEndOfString(buffer), &w);

        char str_score[MAX_STR_SIZE];
        w.end++;
        wordToStr(w, str_score);

        int score = atoi(str_score);
        scores[i++] = score;

        *str_score = '\0';
        *buffer = '\0';

        while (fgets(buffer, sizeof(buffer), f))
        {
            strcpy(res.values[i], buffer);

            Word w_score;
            getWordStartingFromEnd(buffer, getEndOfString(buffer), &w_score);

            w_score.end++;
            wordToStr(w_score, str_score);

            score = atoi(str_score);
            scores[i] = score;
            int temp = scores[i];
            int j = i;

            scores[j] = temp;

            while (j > 0 && scores[j - 1] < temp)
            {
                scores[j] = scores[j - 1];
                swapStrings(res, j, j - 1);
                j--;
            }

            scores[j] = temp;
            i++;

            *str_score = '\0';
            *buffer = '\0';
        }
    }

    fclose(f);

    f = fopen(fname, "wb");

    if (i == 0)
    {
        fwrite("", 0, 0, f);
        fclose(f);
        return;
    }

    int count = n > i ? i : n;

    for (int k = 0; k < count; k++)
        fwrite(res.values[k], sizeof(char), strlen(res.values[k]), f);

    fclose(f);
}


void fwares(FILE* f, char* fname, FILE* g, char* gname)
{
    f = fopen(fname, "rb");

    char buffer[MAX_STR_SIZE];
    wares wares_arr[MAX_SIZE];

    int j = 0;

    while (fgets(buffer, sizeof(buffer), f))
    {
        Word w;
        char* buffer_ptr = buffer;

        wares ware;

        int i = 0;

        while (getWord(buffer_ptr, &w) || i < WARES_FIELDS_COUNT)
        {
            char str[MAX_STR_SIZE];
            wordToStr(w, str);

            if (i == 0)
                strcpy(ware.name, str);
            else if (i == 1)
                ware.unit_cost = strtol(str, NULL, 10);
            else if (i == 2)
                ware.count = strtol(str, NULL, 10);
            else if (i == 3)
                ware.total_cost = strtol(str, NULL, 10);

            i++;
            buffer_ptr = w.end;
        }

        wares_arr[j++] = ware;

        *buffer = '\0';
    }

    fclose(f);

    if (j == 0)
    {
        f = fopen(fname, "wb");
        fwrite("", 0, 0, f);
        fclose(f);
        return;
    }

    g = fopen(gname, "rb");

    while (fgets(buffer, sizeof(buffer), g))
    {
        char* buffer_ptr = buffer;

        Word w;
        getWord(buffer_ptr, &w);

        char name[MAX_STR_SIZE];
        wordToStr(w, name);

        for (int i = 0; i < j; i++)
        {
            if (!strcmp(name, wares_arr[i].name))
            {
                buffer_ptr = w.end;

                Word w_count;
                getWord(buffer_ptr, &w_count);

                char str_count[MAX_STR_SIZE];
                wordToStr(w_count, str_count);

                int count = strtol(str_count, NULL, 10);

                wares_arr[i].count -= count;
                wares_arr[i].total_cost = wares_arr[i].unit_cost * wares_arr[i].count;

                break;
            }
        }

        *buffer = '\0';
    }

    fclose(g);

    f = fopen(fname, "wb");

    for (int k = 0; k < j; k++)
    {
        if (wares_arr[k].count > 0)
        {
            char unit_cost[MAX_STR_SIZE];
            itoa(wares_arr[k].unit_cost, unit_cost, 10);

            char count[MAX_STR_SIZE];
            itoa(wares_arr[k].count, count, 10);

            char total_cost[MAX_STR_SIZE];
            itoa(wares_arr[k].total_cost, total_cost, 10);

            fwrite(wares_arr[k].name, sizeof(char), strlen(wares_arr[k].name), f);
            fwrite(" ", sizeof(char), 1, f);

            fwrite(unit_cost, sizeof(char), strlen(unit_cost), f);
            fwrite(" ", sizeof(char), 1, f);

            fwrite(count, sizeof(char), strlen(count), f);
            fwrite(" ", sizeof(char), 1, f);

            fwrite(total_cost, sizeof(char), strlen(total_cost), f);
            fwrite("\n", sizeof(char), 1, f);
        }
    }

    fclose(f);
}
