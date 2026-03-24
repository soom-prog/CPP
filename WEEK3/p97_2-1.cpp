#include <iostream>

int main()
{   int num
    std::cout << "정수를 입력하시오 (최대 5자리): ";
    std::cin >> num;    //정수 입력

    for(int i=0; i<5; ++i)
    {
        int number;
        if(i==0) number = num/10000;            //만, 천, 백, 십, 일의 자리 각각의 정수만 뽑는 if문
        else if (i==1) number = (num/1000)%10;
        else if (i==2) number = (num/100)%10;
        else if (i==3) number = (num/10)%10;
        else number = num %10;                  //없이 진행했을때 일의 자리에 숫자가 이상하게 출력되어 GPT를 이용해 보완 이렇게 해야 마지막 일의 자리 숫자가 정확하게 출력

        std::cout << number;

        if(i==0) std::cout << "만";
        else if (i==1) std::cout << "천";
        else if (i==2) std::cout << "백";
        else if (i==3) std::cout << "십";
    }
    std::cout << std::endl;
}
