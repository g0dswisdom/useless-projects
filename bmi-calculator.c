#include <stdio.h>
#include <stdlib.h>

int main() {
    char weight[200];
    char height[30];
    float _height;
    float _weight;
    float result;

    system("clear");

    printf("Please enter your weight in kilograms: ");
    fgets(weight, sizeof(weight), stdin);

    printf("Please enter your height in meters: ");
    fgets(height, sizeof(height), stdin);

    if (sscanf(height, "%f", &_height) == 1) {
        _weight = atof(weight);
        result = _weight / (_height * _height);
        printf("Your BMI is %f\n", result);
             
    } else {
        printf("Error?");
        exit(1);
    }
}
