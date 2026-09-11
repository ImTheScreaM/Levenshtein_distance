#include <stdio.h>

void insert_latter() {}

void delete_latter() {}

void change_latter() {}
/*
	D(i,j) = 
	{
		0,
		i, -> строка
		j, -> столбец
		min{ D(i,j-1) + 1,
				 D(i-1,j) + 1,
				 D(i-1,j-1) + m(S_1[i],S_2[j]) -> (Если символы S_1 == S_2 ? m(0) : m(1))
			 }
	}
	В конце самая нижняя правая строчка будет результатом Расстояния Левенштейна;
	 | |К|О|Т|Ы|
	 |0|1|2|3|4|
	K|1|0|1|2|3|
	О|2|1|0|1|2|
	Т|3|2|1|0|[1]| <- 1 Будет ресстояние Левенштайна


	
 */
int length_levenshtein() {return 0;}

int main()
{
	printf("hello");
	return 0;
}
