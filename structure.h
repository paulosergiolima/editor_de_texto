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
    unsigned int count;
    STRING *text;
    struct l *next;
    struct l *previous;
}LINE;

typedef struct{
    CHARACTER *character;
    LINE *line;
}CURSOR;

void initializeString(STRING *string);
void initializeLine(LINE *line);
void initializeCursor(CURSOR *cursor,LINE *line);
void insertCharacterCursor(CURSOR *cursor,char value);
void removeCharacter(CURSOR *cursor);
void moveLeft(CURSOR *cursor);
void moveRight(CURSOR *cursor);

#endif // STRUCTURE2_H_INCLUDED
