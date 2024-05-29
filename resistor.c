#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_COLOR_LENGTH 5
#define MAX_NUMBER_OF_BAND 5
#define SEPARATOR '-'
#define COLOR_RANGE 10
#define MULTIPLIER_RANGE 1000000
char *singleColor = "bl";


char *colors[] = {"bl", "br", "rd","or", "yl", "gr", "bu", "vi","gy", "wh" };



int acceptInput(char** buffer, size_t* size_copied)
{
    printf("entered a color code\n");
    int result = getline(buffer, size_copied, stdin);
    printf("what you entered is: %s and the size is:%lu\n",*buffer,strlen(*buffer));
    (*buffer)[strlen(*buffer)-1]='\0';
    printf("what you entered is: %s and the size is:%lu\n",*buffer,strlen(*buffer));
    return result;
}

int insertInputToBuffer(char* input,char buffer[MAX_COLOR_LENGTH][MAX_NUMBER_OF_BAND])
{
    size_t mLen = strlen(input);
    printf("about to insertInputToBuffer, input lenght is: %d\n",mLen);
    int position = 0;
    int bufPosition = 0;
    int positionInBuffer = 0;
    char* currentBuff = buffer[bufPosition];
    printf("current buff is: %p\n",currentBuff);
    printf("current buff is: %p\n",buffer[0]);
    bool overflown = false;
    while(position < mLen){
        printf("in while loop, position is: %d, mlen is: %d\n",position,mLen);
        while(input[position] != SEPARATOR && position < mLen){
            if(positionInBuffer < MAX_COLOR_LENGTH-1){
                currentBuff[positionInBuffer++] = input[position];
            }
            position++;
        }
        printf("separator found\n");
        currentBuff[positionInBuffer] = '\0';
        printf("found string %s\n",currentBuff);
        currentBuff = buffer[++bufPosition];
        positionInBuffer = 0;
        position++;
    }
}

int getColorNumberFromString(char *colorString)
{
    int colorNumber = -1;
    for (int k = 0; k < COLOR_RANGE; k++)
    {
        if (strcmp(colorString, colors[k]) == 0)
        {
            colorNumber = k;
        }
    }
    return colorNumber;
}

int getcolormultiplier()
{
    int multiplier = -1;
    for (int m = 0; m <10000; m++ );
    int multiplying;
}

int main()
{
    char *input = NULL;
    size_t size_copied;
    static char colorBuffer[MAX_NUMBER_OF_BAND][MAX_COLOR_LENGTH];
    static int bandNumbers[MAX_NUMBER_OF_BAND];
    char* currentBuff = colorBuffer[0];
    printf("current buff is: %p\n",currentBuff);
    int numberOfBandsEntered = 0;
    while (1)
    {
        int result = acceptInput(&input,&size_copied);
        if(result < 0){
            exit(1);
        }
        result = insertInputToBuffer(input,colorBuffer);
        if(result < 0){
            exit(1);
        }
        for(int x=0;x<MAX_NUMBER_OF_BAND;x++)
        {
            if(strlen(colorBuffer[x]) > 0){
                numberOfBandsEntered++;
            }
            printf("color %d is: %s\n",x,colorBuffer[x]);
        }
        printf("number of bands entered is: %d\n",numberOfBandsEntered);
        bool conversionSuccessful = true;
        for(int j=0;j<numberOfBandsEntered;j++){
            bandNumbers[j] = getColorNumberFromString(colorBuffer[j]);
            printf("band number %d is: %d\n",j,bandNumbers[j]);
            if(bandNumbers[j]< 0){
                conversionSuccessful = false;
                break;
            }
            
        }
        if(!conversionSuccessful){
            continue;
        }

        // int color_number = -1;
        // for (int k = 0; k < 3; k++)
        // {
        //     if (strcmp(input, colors[k]) == 0)
        //     {
        //         color_number = k;
        //     }
        // }
        // if (color_number < 0)
        // {
        //     printf("color not found\n");
        // }
        // else
        // {
        //     printf("color number is: %d\n", color_number);
        // }
    }
}