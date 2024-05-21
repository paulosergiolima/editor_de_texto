#include <conio.h>
#include "structure.h"
int main()
{
    LINE lines;
    initializeLine(&lines);

    CURSOR cursor;
    initializeCursor(&cursor,&lines);

    //variaveis temporarias(debug ou placeholder)
    char on = 1;
    char flagLine = 1;

    //varaveis fixas
    char input;
    while(on)
    {
        flagLine = 1;//temporario
        input = getch();
        printf("numero: %d\n",input);
        /*
            dicionario
            Ctrl + s = 19
            Ctrl + backspace = 127
            Ctrl + z = 26 por algum motivo invoca um ? ao contário



            delet = -32 e 83
            insert = -32 e 82
            page up = -32 e 73
            page down = -32 e 81
            home = -32 e 71
            end = -32 e 79




            F1 = 0 e 59
            ...
            F10 = 0 68
            F11 = -32 e -123
            F12 = -32 e -122
            seta para cima = -32 e 72
            seta para baixo = -32 e 80
            seta para esquerda = -32 e 75
            seta para direita = -32 e 77
        */
        switch(input)
        {
            case 8://BackSpace
                removeCharacter(&cursor);
            break;
            case 13://Enter
                printf(" enter");
            break;
            case 0:
                flagLine = 0;//temporario
                input = getch();
                printf("segundo: %d\n",input);
                switch(input)
                {
                    case 59://F1
                        printf("F1\n");
                    break;
                    case 60://F2
                        printf("F2\n");
                    break;
                    case 61://F3
                        printf("F3\n");
                    break;
                    case 62://F4
                        printf("F4\n");
                    break;
                    case 63://F5
                        printf("F5\n");
                    break;
                    case 64://F6
                        printf("F6\n");
                    break;
                    case 65://F7
                        printf("F7\n");
                    break;
                    case 66://F8
                        printf("F8\n");
                    break;
                    case 67://F9
                        printf("F9\n");
                    break;
                    case 68://F10
                        printf("F10\n");
                    break;
                }
            break;
            case -32://"Controle"
                flagLine = 0;//temporario
                input = getch();
                printf("segundo: %d\n",input);
                switch(input)
                {
                    case 72://Up
                        printf("Up\n");
                    break;
                    case 80://Down
                        printf("Down\n");
                    break;
                    case 75://Left
                        moveLeft(&cursor);
                    break;
                    case 77://Right
                        moveRight(&cursor);
                    break;
                    case -123://F11
                        printf("F11\n");
                    break;
                    case -122://F12
                        printf("F12\n");
                    break;
                }
            break;
            default:
                insertCharacterCursor(&cursor,input);
            break;
        }
        if(flagLine)printLine(&cursor);
    }



    return 0;
}


void initializeScreen() {
}
