#include <stdio.h>

int main(void)
{
	int num = 0;
	int count = -1;
	int point[300] = { 0 };
	int case_1 = 0;
	int case_2 = 0;
	int case_3 = 0;
	int case_4 = 0;
	int result = 0;

	scanf("%d", &num);
	if (num > 300) return 0;

	for(int i = 0; i< num; i++) {

		scanf("%d", &point[i]);

		if (point[i] > 10000) return 0;

	}

	//Count 빼기
	num -= 1;

	while (num > count) {
		if (num - count >= 4) { //4칸 or 3칸
			case_1 = point[count + 1]+point[count + 2]+point[count + 4];
			case_2 = point[count + 1]+point[count + 3];
			if (case_1 > case_2) {
				//printf("case1_1\n");
				result += case_1;
				count += 4;
			}
			if (case_1 <= case_2) {
				//printf("case1_1\n");
				result += case_2;
				count += 3;
			}

		}
		else if(num - count == 3) { //3칸
			case_1 = point[count + 2] + point[count + 3];
			case_2 = point[count + 1] + point[count + 3];
		}
		else if (num - count == 2) { //2칸
			//printf("case3\n");
			case_1 = point[count + 2];
			result += case_1;
			count += 2;
		}
		else if (num - count == 1) { //1칸
			//printf("case4\n");
			case_1 = point[count + 1];
			result += case_1;
			count += 1;
		}

	}

	printf("%d", result);

	return 0;
}
