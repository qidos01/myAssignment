#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define MAX_COLOR_LENGTH 5
#define MAX_NUMBER_OF_BAND 5
#define SEPARATOR '-'
#define COLOR_RANGE 12


char *colors[] = {"bl", "br", "rd","or", "yl", "gr", "bu", "vi","gy", "wh", "gd", "sl" };
float multipliers[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 10, 1, 5, 10};


int acceptInput(char** buffer, size_t* size_copied)
{
    printf("enter a color code\n");
    int result = getline(buffer, size_copied, stdin);
    (*buffer)[strlen(*buffer)-1]='\0';
    printf("what you entered is: %s\n",*buffer);
    return result;
}

int insertInputToBuffer(char* input,char buffer[MAX_COLOR_LENGTH][MAX_NUMBER_OF_BAND])
{
    size_t mLen = strlen(input);
    int position = 0;
    int bufPosition = 0;
    int positionInBuffer = 0;
    char* currentBuff = buffer[bufPosition];
    bool overflown = false;
    while(position < mLen){
        while(input[position] != SEPARATOR && position < mLen){
            if(positionInBuffer < MAX_COLOR_LENGTH-1){
                currentBuff[positionInBuffer++] = input[position];
            }
            position++;
        }
        currentBuff[positionInBuffer] = '\0';
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

int getRealNumbers( int *band, int numberOfBand){
    int limit = numberOfBand-2;
    int finalValue = 0;
    for(int x = 0; x < limit; x++){
        finalValue = band[x] + 10*(finalValue);
    }
    return finalValue;
}

float factorMultiplier(int RealNumber, int multiplier){
    float result; 
    float myPow = pow(10, multiplier);
    result = RealNumber *  myPow;
    return result;
}

float getPercentage(float fullValue, int percentage) {
    float tolerance;
    float percent = (percentage *1.0) / 100.0;
    tolerance = fullValue * percent;
    return tolerance;
}

int main()
{
    char *input = NULL;
    size_t size_copied;
    static char colorBuffer[MAX_NUMBER_OF_BAND][MAX_COLOR_LENGTH];
    static int bandNumbers[MAX_NUMBER_OF_BAND];
    char* currentBuff = colorBuffer[0]; 
    float multiplier;

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
        
        int fullValue = getRealNumbers(bandNumbers,numberOfBandsEntered);
        
        int multiplier = bandNumbers[numberOfBandsEntered-2];
        
        float fullValueWithMultiplier = factorMultiplier(fullValue,multiplier);
        
        int tolerance = bandNumbers[numberOfBandsEntered-1];
        
        float toleranceValue = getPercentage(fullValueWithMultiplier,tolerance);
        
        printf("Resistance value: %.1f ohms\n", fullValueWithMultiplier);
        printf("The tolerance is between %.1f ohms or %.1f ohms",fullValueWithMultiplier+toleranceValue, fullValueWithMultiplier-toleranceValue);
    }
    return 0;
}