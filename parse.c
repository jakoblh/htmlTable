#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define USELESS 1
#define HEAD 2
#define TABLE 3

int main(int argc, char **argv){
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	int mode = USELESS;
	fp = fopen(argv[1], "r");

	while((read = getline(&line, &len, fp)) != -1){
		if(strcmp("<thead>\n", line) == 0){
				mode = HEAD;
		}
		else if(strcmp("</thead>\n", line) == 0){
			printf("\n");
			mode = USELESS;
		}
		else if(strcmp("<tbody>\n", line) == 0){
				mode = TABLE;
		}
		else if(mode == TABLE && strcmp("</tr>\n", line) == 0){
			printf("\n");
		}
		else if(mode != USELESS && strcmp("<tr>\n", line) == 0){

		}
		else if(mode != USELESS){
			int bracket = 0;
			int i = 0;
			while(line[i] != 0){
				if(line[i] == '<')
					bracket++;
				else if(line[i] == '>')
					bracket--;
				else if(bracket == 0 && line[i] != '\n'){
					printf("%c", line[i]);
				}
				i++;
			}
			printf("\t");
		}
	}


	free(line);
}
