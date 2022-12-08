#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<string.h>

#define capacity 1000
#define false -1

typedef struct seqstring {
	char *string;
	int length;
}seqstring;

int StrAssign(seqstring& t, char* chars) {
	if (t.string) {
		free(t.string);
	}
	if (t.length != 0) {
		t.length = 0;
	}
	int i = 0, j = 0;
	//t.length = 0;
	for (i = 0; *(chars + i) != '\0'; i++) {
		t.length++;
	}
	if (!i) {
		t.string = NULL;
		t.length = 0;
	}
	else {
		t.string = (char*)malloc(2 * i * sizeof(char));
		if (t.string == NULL) {
			printf("ERROR");
			return false;
		}
		for (j = 0; j < i; j++) {
			t.string[j] = chars[j];
		}
		t.length = i;
	}
	return 0;
}

void getnext(seqstring compare, int next[]) {
	int i, j;
	i = 1;//指向字符串每个字符的下标
	j = 0;
	next[1] = 0;//next[0]放上-1 
	while (i < compare.length) {//没有到达结尾的话 
		if (j == 0 || *(compare.string+i-1) == *(compare.string + j - 1)) {//如果是第一个字符或遇到相同的字符
			++i;
			++j;
			next[i] = j;
		}
		else j = next[j];
	}
}

int kmp(seqstring main, seqstring compare, int next[]) {
	int i, j;
	i = j = 1;
	while (i <= main.length && j <= compare.length) {
		if (j == 0 || *(main.string + i - 1) == *(compare.string +j - 1)) {
			++i; ++j;
		}//进行匹配
		else {
			j = next[j];//如果不匹配，跳转
		}
	}
	if (j > compare.length) return i - compare.length;
	else return -1;
}
int  main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("ERROR_01");
		return 0;
	}
	seqstring main, compare;
	int next[capacity];
	main.string = NULL;
	compare.string = NULL;
	main.length = 0;
	compare.length = 0;
	StrAssign(main, argv[1]);
	StrAssign(compare, argv[2]);
	getnext(compare, next);
	printf("%d", kmp(main, compare, next));
	free(main.string);
	main.string = NULL;
	free(compare.string);
	compare.string = NULL;
	return 0;
}