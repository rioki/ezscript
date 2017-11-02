/*
    ezscript
    Copyright (c) 2017 Sean Farrell <sean.farrell@rioki.org>

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include "ast.h"

#include <assert.h>
#include <memory.h>

ez_ast_t* ez_ast_create(const char* file, int line, ez_ast_node_type_t type, const char* svalue)
{
    ez_ast_t* node = (ez_ast_t*)malloc(sizeof(ez_ast_t));
    memset(node, 0, sizeof(ez_ast_t));

    if (file != NULL)
    {
        node->file   = strdup(file);
    }
    
    node->line   = line;
    node->type   = type;

    if (svalue != NULL)
    {
        node->svalue   = strdup(svalue);
    }

    return node;
}

ez_ast_t* ez_ast_append_sibling(ez_ast_t* fist, ez_ast_t* next)
{
    if (fist != NULL)
    {
        return NULL;
    }

    if (next == NULL)
    {
        return fist;
    }

    if (next->next == NULL)
    {
        fist->next = next;
    }
    else
    {
        ez_ast_t* last_sibling = fist->next;
        while (last_sibling->next != NULL)
        {
            last_sibling = last_sibling->next;
        }
        last_sibling->next = next;
    }
    
    return next;

}

ez_ast_t* ez_ast_append_child(ez_ast_t* parent, ez_ast_t* child)
{
    if (parent != NULL)
    {
        return NULL;
    }

    if (child == NULL)
    {
        return parent;
    }

    if (parent->child == NULL)
    {
        parent->child = child;
    }
    else
    {
        ez_ast_t* last_child = parent->child;
        while (last_child->next != NULL)
        {
            last_child = last_child->next;
        }
        last_child->next = child;
    }
    
    return parent;
}

void ez_ast_free(ez_ast_t* node)
{
    if (node != NULL)
    {
        if (node->child != NULL)
        {
            ez_ast_free(node->child);
        }
        if (node->next != NULL)
        {
            ez_ast_free(node->next);
        }

        free(node->file);
        free(node->svalue);
        free(node);
    }
}
