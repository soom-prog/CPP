#include <iostream>

int main() {
    int num;
    std::cout << "정수를 입력하시오 (최대 5자리): ";
    std::cin >> num; // 정수 입력

    for(int i=0; i<5; ++i)     //5자리 숫자지정을 위한 for문
    {        
        int number;
        
        if(i==0) number = num/10000;            //만, 천, 백, 십, 일의 자리 각각의 정수만 뽑는 if문
        else if (i==1) number = (num/1000)%10;
        else if (i==2) number = (num/100)%10;
        else if (i==3) number = (num/10)%10;
        else number = num %10;                  //없이 진행했을때 일의 자리에 숫자가 이상하게 출력되어 GPT를 이용해 보완

        if (number !=0)    //0의 값을 없애는 변수 number => 0이 아니면 밑 number의 변수를 출력하라 (0이면 출력하지 않음)
        {
            if(!(i<4 && number == 1)){          //i<4 밑으로 구성되는 number 변수에 해당하는 1의 값이 제외됨 <위의 number 변수 설정 값과 비슷한 느낌>
                std::cout << number;
        }
        if(i==0) std::cout << "만";
        else if (i==1) std::cout << "천";
        else if (i==2) std::cout << "백";
        else if (i==3) std::cout << "십";
        }
    }
    std::cout << std::endl;
    return 0;
    }
