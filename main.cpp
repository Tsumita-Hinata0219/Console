#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cmath>


void CalcForce(float level)
{
    float ans = 0.2f * float(std::pow(1.2f, level));
    //std::cout << ans << std::endl;
    printf("%.3f\n", ans);
}

int main(void) {

    CalcForce(0);
    CalcForce(1);
    CalcForce(2);
    CalcForce(3);
    CalcForce(4);
    CalcForce(5);

    return 0;
}
