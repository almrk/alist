/*===============================================================================
 *
 * list.h - A very simple header only library for dynamic arrays/lists in C.
 * 
 * LICENSE : MIT License
 *
 * Copyright (c) 2025 almrk
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *===============================================================================*/

/*===============================================================================
 * 
 * How to use:
 *     - Every custom list type must contain at least:
 *         - data (pointer to whatever type you choose)
 *         - size (preferably size_t)
 *         - error (must be a signed integer)
 *     - You may add extra fields to your custom list types, as this library only
 *       interracts with the 3 mentioned above.
 *     - No functions to opearte on the lists have to be written as the library
 *       already covers all those for you using macros. This means that all you
 *       have to do is define the list types you want
 *
 * Example:
 *     typedef struct {
 *         int x;
 *         int y;
 *     } Vector2;
 *
 *     typedef struct {
 *         Vector2* data;
 *         size_t size;
 *         int error;
 *     } Vector2List;
 *
 *     Vector2List v2l = {0};
 *     list_append(v2l, (Vector2){10, 10});
 *     list_deinit(v2l);
 *===============================================================================*/

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

#define LIST_OK 0
#define LIST_BAD_SIZE_ERROR -1
#define LIST_DATA_NULL_ERROR -2 
#define LIST_MALLOC_ERROR -3
#define LIST_REALLOC_ERROR -4

#define list_new_type(T, N) \
    typedef struct {        \
        T* data;            \
        size_t size;        \
        int error;          \
    } N;

#define list_init(L, S)                         \
    do {                                        \
        if (S <= 0) {                           \
            L.error = LIST_BAD_SIZE_ERROR;      \
            break;                              \
        }                                       \
        L.data = malloc(sizeof(L.data[0]) * S); \
        if (L.data == NULL) {                   \
            L.error = LIST_INIT_MALLOC_ERROR;   \
            break;                              \
        }                                       \
        L.size = S;                             \
        L.error = LIST_OK;                      \
    } while (0);

#define list_deinit(L)      \
    do {                    \
        if (L.data == NULL) \
            break;          \
        free(L.data);       \
        L.data = NULL;      \
        L.size = 0;         \
        L.error = LIST_OK;  \
    } while (0);
          
#define list_append(L, V)                                   \
    do {                                                    \
        L.data = realloc(sizeof(L.data[0] * (L.size + 1))); \
        if (L.data == NULL) {                               \
            L.error = LIST_REALLOC_ERROR;                   \
            break;                                          \
        }                                                   \
        L.data[L.size++] = V;                               \
        L.error = LIST_OK;                                  \
    } while (0);

#define list_append_at(L, V, I) 0

#define list_remove(L) 0
#define list_remove_at(L, I) 0

#endif
