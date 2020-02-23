#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define USELESS 1
#define HEAD 2
#define TABLE 3

int print_table(char *file, char *delim){
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	int mode = USELESS;
	fp = fopen(file, "r");

	if(fp == NULL){
		return -1;
	}

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
		else if(strcmp("</tbody>\n", line) == 0){
			free(line);
			return 0;
		}
		else if(mode != USELESS && strcmp("</tr>\n", line) == 0){
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
			printf(delim);
		}
	}

	free(line);
	return 0;
}

int parse_arguments(int argc, char **argv, char **file, char **delim){
	if(argc <= 1){
		return -1;
	}

	for(int i = 0; i < argc; i++){
		if(argv[i][0] == '-'){

			//delimiter
			if(argv[i][1] == 'd'){
				if(argv[i][2] == 0){
					if(i + 1 < argc){
						i++;
						(*delim) = argv[i];
						break;
					}
					return -1;
				}
				(*delim) = argv[i] + 2;
			}

		}	
		else{
			(*file) = argv[i];
		}
	}
	if(*delim == NULL){
		*delim = "\t";
	}
	if(*file == NULL)
		return -1;

	return 0;
}

int main(int argc, char **argv){
	char *delim = NULL;
	char *file = NULL;

	if(parse_arguments(argc, argv, &file, &delim)){
		printf("wrong arguments\n");
		return -1;
	}

	if(print_table(file, delim)){
		printf("error printing\n");
		return -1;
	}

	return 0;
}
