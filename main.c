#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "structure.h"

//Acho que seria bom fazer uma camera que segue a linha do cursor, no caso a linha do cursor sempre estará no meio (ou um pouco abaixo do meio)

int main()
{
    LINE lines;
    initializeLine(&lines);

    CURSOR cursor;
    initializeCursor(&cursor,&lines);

    DESCRITOR descritor;
    initializeDescritor(&descritor,&lines);

    //variaveis temporarias(debug ou placeholder)
    char on = 1;
    char flagLine = 1;

    //varaveis fixas
    char input;
    while(on)
    {
        flagLine = 1;//temporario
        input = getch();
        //printf("numero: %d\n",input);//temporario
        /*
            dicionario
            Ctrl + s = 19 //salvar
            Ctrl + backspace = 127 //apagar conteudo da linha (opcional)
            Ctrl + z = 26 //desfazer
            Ctrl + r = 18 //refazer
            Ctrl + n = 14 //novo documento
            Ctrl + o = 15 //abrir documento


            delet = -32 e 83
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
            case 15://Abrir Ctrl + O
                flagLine = 0;
                printf("Abrir\n");
            break;
            case 14://Novo Ctrl + N
                flagLine = 0;
                printf("Novo\n");
            break;
            case 18://Refazer Ctrl + R
                flagLine = 0;
                printf("Refazer\n");
            break;
            case 26://Desfazer Ctrl + Z
                flagLine = 0;
                printf("Desfazer\n");
            break;
            case 19://Salvar Ctrl + S temporario usando para printar o documento inteiro
                flagLine = 0;
                printf("Salvar\n");
            break;
            case 8://BackSpace
                removeCharacterCursor(&cursor,&descritor);
            break;
            case 13://Enter
                flagLine = 0;
                insertLineCursor(&cursor,&descritor);
            break;
            case 0:
                flagLine = 0;//temporario
                input = getch();
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
                //flagLine = 0;//temporario
                input = getch();
                //printf("segundo: %d\n",input);//temporario
                switch(input)
                {
                    case 79://End
                        printf("End\n");
                    break;
                    case 71://Home
                        printf("Home\n");
                    break;
                    case 81://Page down
                        printf("Page down\n");
                    break;
                    case 73://Page up
                        printf("Page up\n");
                    break;
                    case 83://Delet
                        printf("Delet\n");
                    break;
                    case 72://Up
                        moveUp(&cursor);
                    break;
                    case 80://Down
                        moveDown(&cursor);
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
        if(flagLine || 1)//temporario
        {
            //system("cls");
            updateLineNumbers(descritor);
            printAll(descritor,&cursor);
        }

    }



    return 0;
}

