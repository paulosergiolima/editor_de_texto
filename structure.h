#ifndef STRUCTURE2_H_INCLUDED
#define STRUCTURE2_H_INCLUDED

typedef struct node{
    char value;
    struct node *next;
    struct node *previous;
}CHARACTER;

typedef struct{
    unsigned int size;
    CHARACTER *first;
    CHARACTER *last;
}STRING;

typedef struct l{
    unsigned int number;
    STRING *text;
    struct l *next;
    struct l *previous;
}LINE;

typedef struct{
    CHARACTER *character;
    LINE *line;
}CURSOR;

typedef struct{
    unsigned int size;
    LINE *first;
    LINE *last;
}DESCRITOR;

//inicializar
void initializeString(STRING *string);
void initializeLine(LINE *line);
void initializeCursor(CURSOR *cursor,LINE *line);
void initializeFile(DESCRITOR *descritor);
void initializeDescritor(DESCRITOR *descritor,LINE *line);

//insercao e remocao
void insertLineCursor(CURSOR *cursor,DESCRITOR *descritor);
void insertCharacterCursor(CURSOR *cursor,char value);
void removeCharacter(CURSOR *cursor);

//movimento
void moveLeft(CURSOR *cursor);
void moveRight(CURSOR *cursor);

//outros
void printAll(DESCRITOR descritor);

#endif // STRUCTURE2_H_INCLUDED
