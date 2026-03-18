#include <iostream>

    int main()
{
        int num;

        std::cout << "정수를 입력하시오: ";
        std::cin >> num;

        double sum = 0.0;          //소수를 저장하는 자료형인 double을 이용해 sum이라는 변수를 만듦, 실수 시작을 위해 0.0으로 초기값을 설정

        for(int i =0; i <= num; ++i){           //임의의 변수 i가 0부터 입력한 정수와 같아 질 때까지 i가 1씩 증가
            if(i % 2 ==0)                       //i를 2로 나눴을때 0일 경우
            {
                sum += 1.0 / (2*i+1);           //짝수일 경우에
            }
            else
            {
                sum -= 1.0 / (2*i+1);           //홀수 일 겅우에
            }
        }

        std::cout << 4 * sum << std::endl;      //문제에 주어진 식 앞에 4가 곱해져 있고, 이 값을 출력하면 std::endl가 실행됨

        return 0;
    }