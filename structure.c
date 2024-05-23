/*
    LEGENDA DOS COMENTARIOS
    WIP = Codigo que falta
    temporario = o nome ja diz
*/


/*

    Nomes: Arthur Koichi Nakao e Paulo Sergio Campos de Lima
    Curso: Ciência da computação
    Ano: 2º ano

    Objetivo
    Criar um editor de texto
    Deve incluir as funções:
    Salvamento de texto
    Seletor de arquivo
    Movimentar o ponteiro de texto com as setas(deslocamento de 1), page up e page down(deslocamento do tamanho da pagina(aparentemente))
    Escrita em "tempo real"
    Remocao em "tempo real"
    Indicador escrito de onde está o cursor de texto(tipo o do bloco de notas)(acho que ele tinha falado isso)

    Entrada
    Input do tipo char do usuario

    Saida
    Display do texto escrito
    Menu de arquivos(ou comandos)

*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "structure.h"

//definicao dos tipos


//funcoes de iniciacao
void initializeString(STRING *string)
{
    string = (STRING*)malloc(sizeof(STRING));
    string->size = 0;
    string->last = NULL;
    string->first = NULL;
}

void initializeLine(LINE *line)
{
    line->number = 1;
    line->next = NULL;
    line->previous = NULL;
    line->text = (STRING*)malloc(sizeof(STRING));
    line->text->size = 0;
    line->text->last = NULL;
    line->text->first = NULL;

}

void initializeCursor(CURSOR *cursor,LINE *line)
{
    cursor->line = line;
    cursor->character = NULL;
}

void initializeDescritor(DESCRITOR *descritor,LINE *line)
{
    descritor->size = 1;
    descritor->first = line;
    descritor->last = line;
}

//funcoes de insercao

void insertLineCursor(CURSOR *cursor,DESCRITOR *descritor)
{
    //Nao sei como manter o valor da linha (tipo linha 1, linha 2 e etc) certo.

    LINE *new_line = (LINE*)malloc(sizeof(LINE));
    initializeLine(new_line);

    //confere se o cursor esta antes do primeiro caractere
    if(cursor->character == NULL)
    {
        //confere se a linha do cursor for a primeira
        if(descritor->first == cursor->line)
        {
            descritor->first = new_line;
            new_line->next = cursor->line;
            cursor->line->previous = new_line;
        }
        //a linha do cursor nao e a primeira
        else
        {
            cursor->line->previous->next = new_line;
            new_line->previous = cursor->line->previous;
            new_line->next = cursor->line;
            cursor->line->previous = new_line;
        }
    }
    //confere se o cursor esta no ultimo caractere
    else if(cursor->line->text->last == cursor->character)
    {
        //confere se a linha do cursor for a ultima
        if(descritor->last == cursor->line)
        {
            descritor->last = new_line;
        }
        new_line->previous = cursor->line;
        cursor->line->next = new_line;
        cursor->line = new_line;
        cursor->character = NULL;
    }
    //o cursor esta entre caracteres
    else
    {
        new_line->previous = cursor->line;
        cursor->line->next = new_line;
        new_line->text->first = cursor->character->next;
        cursor->character->next->previous = NULL;
        cursor->character->next = NULL;
        //Acha o ultimo caractere
        unsigned int aux = 0;
        for(CHARACTER *pointer = cursor->line->text->first; pointer != NULL; pointer = pointer->next) aux++;
        new_line->text->last = cursor->character;
        new_line->text->size = aux;
        cursor->line = new_line;
        cursor->character = NULL;
    }
}

void insertCharacterCursor(CURSOR *cursor,char value)
{
    //WIP falta a parte de conferir o numero maximo de caracteres pos insercao, para quebrar a linha
    CHARACTER *new_character = (CHARACTER*)malloc(sizeof(CHARACTER));
    new_character->value = value;
    new_character->next = NULL;
    new_character->previous = NULL;

    //confere se a linha está vazia
    if(cursor->line->text->first == NULL)
    {
        cursor->line->text->first = new_character;
        cursor->line->text->last = new_character;
    }
    //confere se o cursor esta antes do primeiro caractere
    else if(cursor->character == NULL)
    {
        cursor->line->text->first->previous = new_character;
        new_character->next = cursor->line->text->first;
        cursor->line->text->first = new_character;
    }
    //confere se o cursor esta no ultimo caractere
    else if(cursor->line->text->last == cursor->character)
    {
        cursor->character->next = new_character;
        new_character->previous = cursor->character;
        cursor->character = new_character;
        cursor->line->text->last = new_character;
    }
    //insere entre caracteres
    else
    {
        new_character->next = cursor->character->next;
        new_character->previous = cursor->character;
        cursor->character->next->previous = new_character;
        cursor->character->next = new_character;
    }
    cursor->character = new_character;
    cursor->line->text->size = cursor->line->text->size + 1;
}

//funcoes de remocao
void removeCharacter(CURSOR *cursor)
{
    if(cursor->line->text->first == NULL) return;//WIP Remove line
    if(cursor->line->text->last == cursor->character)
    {
        CHARACTER *aux = cursor->character;
        cursor->character = cursor->character->previous;
        if(cursor->character != NULL)cursor->character->next = NULL;
        if(cursor->line->text->first == cursor->line->text->last)
        {
            cursor->line->text->first = NULL;
            cursor->line->text->last = NULL;
        }
        else
        {
            cursor->line->text->last = cursor->character;
        }
        free(aux);
    }
}

//funcoes de movimento
void moveLeft(CURSOR *cursor)
{
    if(cursor->character != NULL)cursor->character = cursor->character->previous;
}

void moveRight(CURSOR *cursor)
{
    if(cursor->character->next != NULL)cursor->character = cursor->character->next;
}

void printCursorLine(CURSOR *cursor)
{
    LINE *line = cursor->line;
    printf("Cursor line: ");
    for(CHARACTER *pointer = line->text->first; pointer != NULL; pointer = pointer->next)
    {
        printf("%c",pointer->value);
    }
    printf("\n");
}

void printLine(LINE *line)
{
    printf("Line: ");
    for(CHARACTER *pointer = line->text->first; pointer != NULL; pointer = pointer->next)
    {
        printf("%c",pointer->value);
    }
    printf("\n");
}

void printAll(DESCRITOR descritor)
{
    for(LINE *line = descritor.first; line != NULL; line = line->next)
    {
        printLine(line);
    }
}
