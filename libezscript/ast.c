/*
ezscript 
Copyright 2018 Sean Farrell <sean.farrell@rioki.org>

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies 
of the Software, and to permit persons to whom the Software is furnished to do 
so, subject to the following conditions:

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


#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"

ast_node_t* ast_create(ast_type_t type)
{
    ast_node_t* node = (ast_node_t*)malloc(sizeof(ast_node_t));
    if (node == NULL) {
        return NULL;
    }

    node->type   = type;
    node->parent = NULL;
    node->child  = NULL;
    node->next   = NULL;
    node->svalue = NULL;

    return node;
}

ast_node_t* ast_append(ast_node_t* list, ast_node_t* next)
{
    assert(list != NULL);
    assert(next != NULL);

    if (list->next == NULL) 
    {
        list->next = next;
    }
    else
    {
        ast_node_t* n = list->next;
        while (n->next != NULL) 
        {
            n = n->next;
        }
        n->next = next;
    }

    next->parent = list->parent;

    return list;
}

ast_node_t* ast_child(ast_node_t* parent, ast_node_t* child)
{
    assert(parent != NULL);
    assert(child != NULL);

    if (parent->child == NULL)
    {
        parent->child = child;
        child->parent = parent;
    }
    else
    {
        ast_append(parent->child, child);
    }

    return parent;
}

ast_node_t* ast_rchild(ast_node_t* parent, ast_node_t* child)
{
    assert(parent != NULL);
    assert(child != NULL);

    if (parent->child == NULL)
    {
        parent->child = child;
        child->parent = parent;
    }
    else
    {
        ast_rchild(parent->child, child);
    }

    return parent;
}

ast_node_t* ast_single(ast_type_t type, ast_node_t* child)
{
    ast_node_t* node;

    assert(child != NULL);

    node = ast_create(type);

    ast_child(node, child);

    return node;
}

ast_node_t* ast_named_single(ast_type_t type, char* id, ast_node_t* child)
{
    ast_node_t* node;

    assert(id != NULL);
    assert(child != NULL);

    node = ast_single(type, child);
    assert(node != NULL);

    node->svalue = id;

    return node;
}

ast_node_t* ast_join(ast_type_t type, ast_node_t* lhs, ast_node_t* rhs)
{
    ast_node_t* node;

    assert(lhs != NULL);
    assert(rhs != NULL);

    node = ast_create(type);

    ast_child(node, lhs);
    ast_child(node, rhs);

    return node;
}

ast_node_t* ast_leaf(ast_type_t type, char* value)
{
    ast_node_t* node;

    assert(value != NULL);

    node = ast_create(type);
    node->svalue = value;

    return node;
}

void ast_free(ast_node_t* node)
{
    if (node != NULL)
    {
        ast_free(node->next);
        ast_free(node->child);
        free(node->svalue);
        free(node);
    }
}