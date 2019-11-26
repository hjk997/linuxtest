#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{   
	char c;
	char sentence[50], input[50];
	time_t start_time, finish_time;
	int O_TA = 0;   //오타횟수
	int num_typing=0;
	double time_gap;
      
	strcpy(sentence, "As a man sows so he shall reap.");
   
	printf("* 타자 연습 프로그램 * \n y 를 입력하면 시작합니다. ");
	scanf("%s", &c);

	if(c == 'y' || c == 'Y')   //타자 프로그램 시작.
	{
		time(&start_time);
		printf("시간 측정을 시작합니다. 다음 문장을 입력하세요.\n");
		printf(sentence);
		printf("\n");
      
		//사용자에게 문자열을 입력받는다.      
		scanf(" %[^\n]", &input);
		time(&finish_time);

		for(int i = 0 ; i < strlen(input) ; i++)
		{
			if(sentence[i] != input[i])   //오타발생
				O_TA++;
			//글자 수 세기
			if((sentence[i] == input[i]) && input[i] != NULL)
				num_typing ++;
		}
		//결과출력
		printf("\n오타 수: %d\n", O_TA);
		time_gap = difftime(finish_time, start_time);
		time_gap = (num_typing / time_gap)*60;
		printf("평균 분당 타자수: %lf\n", time_gap);

	}   
	else             //이상한 문자 입력. 타자프로그램 종료
	{
		printf("Wrong letter. Exit the program.\n");
		exit(1);
	}
   
	return 0;
}
