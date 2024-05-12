#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "matrix.h"
#include "problems.h"


void assertString(const char *expected, char *got,
                  char const *fileName, char const *funcName,
                  int line)
{
    if (strcmp(expected, got))
    {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%s\"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    }
    else
        fprintf(stderr, "%s - OK\n", funcName);
}


void assert(const int expected, int got,
            char const *fileName, char const *funcName,
            int line)
{
    if (expected != got)
    {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%d\"\n", expected);
        fprintf(stderr, "Got: \"%d\"\n\n", got);
    }
    else
        fprintf(stderr, "%s - OK\n", funcName);
}


void add_to_queue(TreeNode* node, TreeNode** queue, int* queue_size, int* first_element)
{
    queue[*first_element + (*queue_size)++] = node;
}


TreeNode* delete_from_queue(TreeNode** queue, int* queue_size, int* first_element)
{
    TreeNode* first = NULL;

    if (queue_size > 0)
    {
        first = queue[(*first_element)++];
        (*queue_size)--;
    }
    return first;
}


int is_empty(int queue_size)
{
    return queue_size == 0;
}


int getMax(int* arr, int size)
{
    if (size > 0)
    {
        int max_i = 0;
        int max = arr[max_i];

        for (int i = 1; i < size; i++)
        {
            if (max < arr[i])
            {
                max_i = i;
                max = arr[i];
            }
        }

        return max_i;
    }

    return -1;
}


void width(TreeNode *root, TreeNode** queue, int* queue_size, int* first_element)
{
    if (!root)
        return;

    add_to_queue(root, queue, queue_size, first_element);

    while (!is_empty(*queue_size))
    {
        TreeNode *curr = delete_from_queue(queue, queue_size, first_element);
        if (curr)
        {
            printf("%d ", curr->max);

            if (curr->left_child || curr->right_child)
            {
                add_to_queue(curr->left_child, queue, queue_size, first_element);
                add_to_queue(curr->right_child, queue, queue_size, first_element);
            }
        }
        else
            printf("null ");
    }
}


TreeNode* binaryTree(int* nums, int size)
{
    if (size > 0)
    {
        TreeNode* node = malloc(sizeof(TreeNode));

        int max_idx = getMax(nums, size);

        node->max = nums[max_idx];

        if (max_idx > 0)
            node->left_child = binaryTree(nums, max_idx);
        else
            node->left_child = NULL;

        if (size - max_idx > 0)
            node->right_child = binaryTree(nums + max_idx + 1, size - max_idx - 1);
        else
            node->right_child = NULL;

        return node;
    }

    return NULL;
}


void buildTree(int* nums, int size)
{
    TreeNode* root_node = binaryTree(nums, size);

    TreeNode* queue[50];
    int queue_size = 0;
    int first_element = 0;

    width(root_node, queue, &queue_size, &first_element);
}


void matrixAdd(matrix* mx1, int** arr, int arr_size)
{
    for (int i = 0; i < arr_size; i++)
    {
        int r1 = arr[i][0];
        int r2 = arr[i][2];

        int c1 = arr[i][1];
        int c2 = arr[i][3];

        while (r1 <= r2 && c1 <= c2)
        {
            mx1->values[r1][c1] += 1;

            if (c1 + 1 <= c2)
                c1++;
            else
            {
                r1++;
                c1 = arr[i][1];
            }
        }
    }
}


int countLiveCells(matrix mx, int row, int col)
{
    int count = 0;

    int row1, row2, col1, col2;
    row1 = row - 1;
    row2 = row + 1;
    col1 = col - 1;
    col2 = col + 1;

    for (int i = row1; i <= row2; i++)
    {
        if (i < 0)
            continue;

        for (int j = col1; j <= col2; j++)
        {
            if (j < 0 || (i >= mx.rows_count || j >= mx.cols_count) || i == row && j == col)
                continue;

            count += mx.values[i][j];
        }
    }

    return count;
}


matrix gameOfLife(matrix mx)
{
    matrix res_mx = getMemMatrix(mx.rows_count, mx.cols_count);

    for (int i = 0; i < mx.rows_count; i++)
    {
        for (int j = 0; j < mx.cols_count; j++)
        {
            int total_live_neighbour_cells = countLiveCells(mx, i, j);
            int cell_state = mx.values[i][j];

            if (cell_state)
            {
                if (total_live_neighbour_cells < 2 || total_live_neighbour_cells > 3)
                    res_mx.values[i][j] = 0;
                else
                    res_mx.values[i][j] = 1;
            }
            else
            {
                if (total_live_neighbour_cells == 3)
                    res_mx.values[i][j] = 1;
                else
                    res_mx.values[i][j] = 0;
            }
        }
    }

    return res_mx;
}


int cmpfunc(const void* a, const void* b)
{
    int v1 = *(int*) a;
    int v2 = *(int*) b;

    if (v1 < v2)
        return -1;

    if (v1 == v2)
        return 0;

    return 1;
}


int getArrMedian(matrix mx, int row, int col, int arr_size)
{
    int arr[arr_size * arr_size];

    int shift = floor(arr_size / 2);
    int row1 = row - shift;
    int row2 = row + shift;
    int col1 = col - shift;
    int col2 = col + shift;

    int curr_size = 0;

    for (int i = row1; i <= row2; i++)
    {
        for (int j = col1; j <= col2; j++)
            arr[curr_size++] = mx.values[i][j];
    }

    qsort(arr, curr_size, sizeof(int), cmpfunc);

    return arr[(int) floor(curr_size / 2)];
}


void medianFilter(matrix* mx, int window_size)
{
    if (window_size > mx->rows_count || window_size > mx->cols_count)
        return;

    int shift = floor(window_size / 2);
    int r_border = mx->rows_count - shift;
    int c_border = mx->cols_count - shift;

    for (int i = shift; i < r_border; i++)
    {
        for (int j = shift; j < c_border; j++)
            mx->values[i][j] = getArrMedian(*mx, i, j, window_size);
    }
}


void shuffleStr(char* s, int* indices, int size)
{
    char* s_copy = malloc(sizeof(char) * size);
    memcpy(s_copy, s, size);

    for (int i = 0; i < size; i++)
        s[i] = s_copy[indices[i]];

    free(s_copy);
}


int submatricesThatContainOnlyDigit1(matrix mx)
{
    int total_elems = mx.rows_count * mx.cols_count;

    for (int i = 0; i < mx.rows_count; i++)
    {
        for (int j = mx.cols_count - 2; j >= 0; j--)
        {
            if (mx.values[i][j] == 1)
                mx.values[i][j] += mx.values[i][j + 1];
        }
    }

    int count = 0;

    for (int i = 0; i < mx.rows_count; i++)
    {
        for (int j = 0; j < mx.cols_count; j++)
        {
            int min = mx.values[i][j];

            for (int k = j; k < mx.rows_count; k++)
            {
                if (mx.values[k][j] == 0)
                    break;

                min = min < mx.values[k][j] ? min : mx.values[k][j];
                count += min;
            }
        }
    }

    return count;
}


bool checkKey(map* arr, size_t size, char* key, int value)
{
    for (size_t i = 0; i < size; i++)
    {
        if (!strcmp(arr[i].key, key))
        {
            arr[i].value += value;
            return true;
        }
    }

    return false;
}


char* tok(char* s1, char* s2)
{
    while (*s1 != *s2 && *s1 != '\0')
        s1++;

    if (*s1 == *s2)
        s1++;

    return s1;
}


char** subdomainVisits(char** cpdomains, int size, int* return_size)
{
    map* map_subdomains = malloc(sizeof(map) * MAX_SIZE);
    *return_size = 0;

    char* cpdomain = malloc(sizeof(char) * MAX_STR_SIZE);

    for (int i = 0; i < size; i++)
    {
        strcpy(cpdomain, cpdomains[i]);

        char* token = strtok(cpdomain, " ");
        int total_visits = atoi(token);

        token = strtok(NULL, " ");

        if (!checkKey(map_subdomains, *return_size, token, total_visits))
        {
            strcpy(map_subdomains[*return_size].key, token);
            map_subdomains[*return_size].value = total_visits;
            (*return_size)++;
        }

        token = tok(token, ".");

        while (*token)
        {
            if (!checkKey(map_subdomains, *return_size, token, total_visits))
            {
                strcpy(map_subdomains[*return_size].key, token);
                map_subdomains[*return_size].value = total_visits;
                (*return_size)++;
            }

            token = tok(token, ".");
        }
    }

    char** subdomains = malloc(sizeof(char*) * MAX_SIZE);

    char* elem = malloc(sizeof(char) * MAX_STR_SIZE);

    for (int i = 0; i < *return_size; i++)
    {
        char* elem_ptr = elem;
        itoa(map_subdomains[i].value, elem_ptr, 10);
        elem_ptr += strlen(elem_ptr);
        *(elem_ptr++) = ' ';
        *elem_ptr = '\0';

        strcat(elem_ptr, map_subdomains[i].key);

        subdomains[i] = malloc(sizeof(char) * MAX_STR_SIZE);

        strcpy(subdomains[i], elem);

        *elem = '\0';
    }

    free(elem);
    free(map_subdomains);

    return subdomains;
}



void createFileWithNumsSmallerThanN(FILE* f, char* fname, char* new_fname, int x)
{
    f = fopen(fname, "r");

    char* buffer = malloc(sizeof(char) * MAX_STR_SIZE);
    char** res_arr = malloc(sizeof(char*) * MAX_SIZE);

    int j = 0;

    while (fgets(buffer, MAX_STR_SIZE, f))
    {
        char* tok = strtok(buffer, " ");
        res_arr[j] = malloc(sizeof(char) * MAX_STR_SIZE);
        char* ptr = res_arr[j];

        while (tok)
        {
            int num = atoi(tok);

            if (num < x)
            {
                strcpy(ptr, tok);
                ptr++;
                *ptr = ' ';
                ptr++;
            }

            tok = strtok(NULL, " ");
        }

        if (!res_arr[j])
            *ptr = '\0';
        if (*(ptr - 1) == ' ')
            *(ptr - 1) = '\0';

        j++;
        *buffer = '\0';
    }

    fclose(f);

    free(buffer);

    FILE* new_f = fopen(new_fname, "w");

    if (j == 0)
        fprintf(new_f, "%s", "");
    else
    {
        for (int k = 0; k < j; k++)
        {
            if (k < j - 1)
                fprintf(new_f, "%s\n", res_arr[k]);
            else
                fprintf(new_f, "%s", res_arr[k]);

            free(res_arr[k]);
        }
    }

    fclose(new_f);

    free(res_arr);
}


void outputAns(char dict[MAX_SIZE][MAX_STR_SIZE], int n, query* queries, int q)
{
    int j = 0;

    for (int i = 0; i < q; i++)
    {
        int count = 0;
        bool found = false;

        while (j < n && *dict)
        {
            char* chr = strstr(*dict, queries[i].prefix);

            if (!chr || chr != *dict)
                count = 0;
            else
            {
                if (chr != *dict)
                    continue;

                count++;

                if (count == queries[i].pos)
                {
                    printf("%d\n", j + 1);
                    found = true;
                    break;
                }
            }

            j++;
            dict++;
        }

        if (!found)
            printf("%d\n", -1);
    }
}


char* smallestNum(char* pattern)
{
    int size = strlen(pattern);
    char* smallest_num = malloc(sizeof(char) * (size + 2));

    for(int i = 0; i < size + 1; i++)
        smallest_num[i] = (i + 1) + '0';


    for (int i = 0; i < size; i++)
    {
        int t = i;

        while (t < size && pattern[t] == 'D')
            t++;

        int l = i;
        int r = t;

        while (l < r)
        {
            char temp = smallest_num[l];
            smallest_num[l++] = smallest_num[r];
            smallest_num[r--] = temp;
        }

        if (t != i)
            i = t - 1;
    }

    smallest_num[size + 1] = '\0';

    return smallest_num;
}