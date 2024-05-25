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
        new_line->next = cursor->line->next;
        cursor->line->next = new_line;
        cursor->line = new_line;
        cursor->character = NULL;
    }
    //o cursor esta entre caracteres
    else
    {
        new_line->previous = cursor->line;
        new_line->next = cursor->line->next;

        new_line->text->last = cursor->line->text->last;

        cursor->line->next = new_line;

        new_line->text->first = cursor->character->next;
        cursor->character->next->previous = NULL;

        cursor->line->text->last = cursor->character;
        cursor->character->next = NULL;

        //Acha o ultimo caractere
        unsigned int aux = 0;
        for(CHARACTER *pointer = cursor->line->text->first; pointer != NULL; pointer = pointer->next)
        {
            aux++;
        }
        new_line->text->size = aux;//temporario perigoso?
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
void destroyCharacter(CHARACTER *character)
{
    if(character->previous != NULL)
    {
        character->previous->next = character->next;
    }
    if(character->next != NULL)
    {
        character->next->previous = character->previous;
    }
    free(character);
}

void removeCharacterCursor(CURSOR *cursor,DESCRITOR *descritor)
{
    //confere se o cursor esta antes do primeiro caractere
    if(cursor->character == NULL)
    {
        if(cursor->line->previous != NULL)
        {
            //confere se a linha anterior esta vazia
            if(cursor->line->previous->text->first == NULL)
            {
                LINE *aux = cursor->line->previous;

                if(cursor->line->previous->previous != NULL)
                {
                    cursor->line->previous->previous->next = cursor->line;
                }
                cursor->line->previous = cursor->line->previous->previous;

                if(descritor->first == aux)descritor->first = cursor->line;
                free(aux->text);
                free(aux);
            }
            else
            {
                LINE *aux = cursor->line;

                cursor->line->previous->text->size = cursor->line->previous->text->size + cursor->line->text->size;

                cursor->line->previous->next = cursor->line->next;
                if(cursor->line->next != NULL)cursor->line->next->previous = cursor->line->previous;

                cursor->character = cursor->line->previous->text->last;

                cursor->character->next = cursor->line->text->first;
                cursor->line->text->first->previous = cursor->line->previous->text->last;

                cursor->line->previous->text->last = cursor->line->text->last;
                cursor->line = cursor->line->previous;
                aux->text = NULL;
                free(aux->text);
                free(aux);
            }
        }
    }
    //confere se o cursor esta no ultimo caractere
    else if(cursor->line->text->last == cursor->character)
    {
        CHARACTER *aux = cursor->character;
        if(cursor->character->previous != NULL)
        {
            cursor->character = cursor->character->previous;
            cursor->character->next = NULL;
        }
        else
        {
            cursor->character = cursor->character->previous;
            cursor->line->text->first = NULL;
        }
        cursor->line->text->last = cursor->character;
        cursor->line->text->size -= 1;
        free(aux);
    }
    //remove caractere entre caracteres
    else
    {
        CHARACTER *aux = cursor->character;
        cursor->line->text->size -= 1;
        //confere se o caractere anterior ao cursor e nulo ou nao
        if(cursor->character->previous != NULL)
        {
            cursor->character->next->previous = cursor->character->previous;
            cursor->character->previous->next = cursor->character->next;
            cursor->character = cursor->character->previous;
        }
        else
        {
            cursor->character->next->previous = NULL;
            cursor->line->text->first = cursor->character->next;
            cursor->character = NULL;
        }

        free(aux);

    }
}

void deleteCharacterCursor(CURSOR *cursor,DESCRITOR *descritor)
{
    //confere se o cursor esta no ultimo caractere
    if(cursor->line->text->last == cursor->character)
    {
        //confere se a proxima linha existe
        if(cursor->line->next != NULL)
        {
            //confere se a proxima linha esta vazia
            if(cursor->line->next->text->first == NULL)
            {
                //temporario, isso explode no free quando tentamos excluir a ultima linha
                LINE *aux = cursor->line->next;
                if(cursor->line->next->next != NULL)
                {
                    cursor->line->next->next->previous = cursor->line;
                }
                cursor->line->next = cursor->line->next->next;

                if(descritor->last == aux)
                {
                    descritor->last = cursor->line;
                }
                free(aux->text);
                free(aux);
            }
            else
            {

            }
        }
    }
    //confere se o cursor esta antes do primeiro caractere
    else if(cursor->character == NULL)
    {

    }
    //remove caractere entre caracteres
    else
    {

    }
}

//funcoes de movimento
//temporario, nao e assim que funciona no word, mas teria que mudar tudo entao fica assim por enquanto(que talvez vire permanente)
unsigned int getCursorPosition(CURSOR *cursor)
{
    unsigned int result = 0;
    for(CHARACTER *pointer = cursor->line->text->first; pointer != NULL && pointer != cursor->character; pointer = pointer->next) result++;
    return result;
}

void moveUp(CURSOR *cursor)
{
    unsigned int position = getCursorPosition(cursor);
    if(cursor->line->previous != NULL)
    {
        cursor->line = cursor->line->previous;
        if(cursor->character != NULL)cursor->character = cursor->line->text->first;
        //conferir se a linha nao e vazia
        if(cursor->line->text->first != cursor->line->text->last)
        {
            for(unsigned int i = 0; i < position && cursor->character != NULL; i++)
            {
                if(cursor->character->next == NULL)break;
                cursor->character = cursor->character->next;
            }
        }
        else
        {
            cursor->character = NULL;
        }

    }
}

void moveDown(CURSOR *cursor)
{
    unsigned int position = getCursorPosition(cursor);
    if(cursor->line->next != NULL)
    {
        cursor->line = cursor->line->next;
        if(cursor->character != NULL)cursor->character = cursor->line->text->first;
        //conferir se a linha nao e vazia
        if(cursor->line->text->first != cursor->line->text->last)
        {
            for(unsigned int i = 0; i < position && cursor->character != NULL; i++)
            {
                if(cursor->character->next == NULL)break;
                cursor->character = cursor->character->next;
            }
        }
        else
        {
            cursor->character = NULL;
        }

    }
}

void moveLeft(CURSOR *cursor)
{
    //confere se o cursor esta antes do primeiro caractere
    if(cursor->character == NULL && cursor->line->previous != NULL)
    {
        cursor->line = cursor->line->previous;
        cursor->character = cursor->line->text->last;
    }
    else if(cursor->character != NULL)cursor->character = cursor->character->previous;
}

void moveRight(CURSOR *cursor)
{
    //confere se o cursor esta antes do primeiro caractere
    if(cursor->character == NULL)
    {
        if(cursor->line->text->first != NULL)
        {
            cursor->character = cursor->line->text->first;
        }
        else if(cursor->line->next != NULL)
        {
            cursor->line = cursor->line->next;
        }
    }
    //confere se o cursor esta entre caracteres
    else if(cursor->character->next != NULL)
    {
        cursor->character = cursor->character->next;
    }
    //o cursor esta no ultimo caractere e ha outra linha
    else if(cursor->line->next != NULL)
    {
        cursor->character = NULL;
        cursor->line = cursor->line->next;
    }
}

//outros
void updateLineNumbers(DESCRITOR descritor)//espero que seja temporario
{
    unsigned int number = 1;
    for(LINE *line = descritor.first; line != NULL; line = line->next)
    {
        line->number = number;
        number++;
    }
}

void printCursorLine(CURSOR *cursor)
{
    LINE *line = cursor->line;
    printf("%u:",cursor->line->number);//temporario
    if(cursor->character == NULL)printf("|");
    for(CHARACTER *pointer = line->text->first; pointer != NULL; pointer = pointer->next)
    {
        printf("%c",pointer->value);
        if(cursor->character == pointer)printf("|");
    }
    printf("   size:%u\n",line->text->size);
}

void printLine(LINE *line)
{
    printf("%u:",line->number);//temporario
    for(CHARACTER *pointer = line->text->first; pointer != NULL; pointer = pointer->next)
    {
        printf("%c",pointer->value);
    }
    printf("   size:%u\n",line->text->size);
}

void printAll(DESCRITOR descritor,CURSOR *cursor)
{
    printf("Lines:\n");
    printf("First: %u Last: %u\n",descritor.first->number,descritor.last->number);
    for(LINE *line = descritor.first; line != NULL; line = line->next)
    {
        if(line == cursor->line)
        {
            printCursorLine(cursor);
        }
        else
        {
            printLine(line);
        }
    }
}
