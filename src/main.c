#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define IDX(row, col,cols) levenshtein_matrix[(row) * ((cols) + 1) + (col)]

#define OK             0
#define ERR_MALLOC     1
#define ERR_FIRST_STR  2
#define ERR_SECOND_STR 3

#define MSG_OK         "Все хорошо!\n"
#define MSG_MALLOC     "Ошибка в выделении памяти!\n"
#define MSG_FIRST_STR  "Первая строка была не иницилизированна!\n"
#define MSG_SECOND_STR "Вторая строка была не иницилизированна!\n"
#define MSG_UNDEFINED  "Неизвестная ошибка!\n"

#define MAX_CHARS 256

size_t length_str(const char* str)
{
	const char* ptr = str;
	while(*ptr) {
		++ptr;
	}
	return (size_t)(ptr-str);
}

uint8_t char_differ(const char S_1,
	                      const char S_2)
{
	return S_1 == S_2 ? 0 : 1;
}

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
uint32_t levenshtein_distance(const char *str1,
	                            const char* str2)
{
	uint32_t result = 0;
	uint8_t status = OK;

	const size_t rows = length_str(str1);
	const size_t cols = length_str(str2);

	uint32_t* levenshtein_matrix = malloc((rows + 1) * (cols + 1) * sizeof(uint32_t));
	status = (levenshtein_matrix == NULL) ? ERR_MALLOC
		                                    : OK;

	if(status == OK) {
		for(size_t row = 0; row <= rows; row++) {
			IDX(row,0,cols) = (uint32_t)(row);
		}
		for(size_t col = 0; col <= cols; col++) {
			IDX(0,col,cols) = (uint32_t)(col);
		}

		for(size_t row = 1; row <= rows; row++) {
			for(size_t col = 1; col <= cols; col++) {
				const uint8_t equal = char_differ(str1[row - 1],str2[col-1]);

				uint32_t add = IDX(row - 1, col, cols) + 1;
				uint32_t delete = IDX(row,col - 1,cols) + 1;
				uint32_t change = IDX(row - 1, col - 1,cols) + equal;

				uint32_t min = delete;
				if(add < min) { min = add;}
				if(change < min) {min = change;}

				IDX(row,col,cols) = min;
			}
		}
		result = IDX(rows,cols,cols);
	} else {
		printf(MSG_MALLOC);
	}
	free(levenshtein_matrix);
	return result;
}

uint8_t read_two_lines(char* str1,size_t size_str1,
	                     char* str2,size_t size_str2)
{
	uint8_t status = OK;
	
	printf("Введите первую строку: ");
	if(fgets(str1,size_str1,stdin) == NULL) {
		status = ERR_FIRST_STR;
	} else {
		printf("Введите вторую строку: ");
		if((fgets(str2,size_str2,stdin) == NULL)) {
			status = ERR_SECOND_STR;
		}
	}

	if(status == OK) {
		str1[strcspn(str1,"\n")] = '\0';
		str2[strcspn(str2,"\n")] = '\0';
	}
	
	return status;
}

int main()
{
	uint8_t status = OK;

	char str1[MAX_CHARS];
	char str2[MAX_CHARS];

	status = read_two_lines(str1,sizeof(str1),
		                     str2,sizeof(str2));

	switch(status) {
		case OK: {
			uint32_t dis = levenshtein_distance(str1,str2);
			printf("Разница:%u\n",dis);
			break;
		}
		case ERR_FIRST_STR: {
			printf(MSG_FIRST_STR);
			break;
		}
		case ERR_SECOND_STR: {
			printf(MSG_SECOND_STR);
			break;
		}
		default:
			printf(MSG_UNDEFINED);
	}


	return 0;
}
