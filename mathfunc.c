#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

static char* doMath(char** inp){
	//first element is function name
	//second and third elements are args
	char* toReturn = (char*)malloc(sizeof(char)*2048);

	if(strcmp("add", inp[0]) == 0){
		double a = strtod(inp[1], NULL);
		double b = strtod(inp[2], NULL);	
		double c = a + b;
		sprintf(toReturn, "%f\n", c);
	}else if(strcmp("sub", inp[0]) == 0){
		double a = strtod(inp[1], NULL);
		double b = strtod(inp[2], NULL);	
		double c = a - b;
		sprintf(toReturn, "%f\n", c);
	}else if(strcmp("mul", inp[0]) == 0){
		double a = strtod(inp[1], NULL);
		double b = strtod(inp[2], NULL);	
		double c = a * b;
		sprintf(toReturn, "%f\n", c);
	}else if(strcmp("div", inp[0]) == 0){
		double a = strtod(inp[1], NULL);
		double b = strtod(inp[2], NULL);
		
		if(b==0){
			sprintf(toReturn, "Trying to divide by zero\n");
			return toReturn;
		}
		double c = a / b;
		sprintf(toReturn, "%f\n", c);
	}else if(strcmp("exp", inp[0]) == 0){
		double a = strtod(inp[1], NULL);
		double b = strtod(inp[2], NULL);	
		double c = pow(a,b);
		sprintf(toReturn, "%f\n", c);
	}else if(strcmp("factor", inp[0]) == 0){
				int ch;
		for(ch=0;ch<strlen(inp[1]);ch++){
			if(isdigit(inp[1][ch]) == 0){
				sprintf(toReturn, "Factor requires an integer input\n");
				return toReturn;
			}
		}
		int a = atoi(inp[1]);
		

		while (a%2 == 0){
			char* addPart =  (char*)malloc(sizeof(char)*2048);
//			printf("%d ", 2);
			sprintf(addPart, "%d\n", 2);
			strcat(toReturn,addPart);
			a = a/2;
			free(addPart);
		}
	
		int i;
	
		for (i = 3; i <= sqrt(a); i = i+2){
			char* addPart =  (char*)malloc(sizeof(char)*2048);
			while (a%i == 0){
//				printf("%d ", i);
				sprintf(addPart, "%d\n", i);
				strcat(toReturn,addPart);
				a = a/i;
			}
			free(addPart);
		}
	 
		if (a > 2){
//			printf ("%d ", a);
			char* addPart =  (char*)malloc(sizeof(char)*2048);
			sprintf(addPart, "%d\n", a);
			strcat(toReturn,addPart);
			free(addPart);
		}		
		
		//sprintf(toReturn, "%d\n", a);
	}else if(strcmp("fib", inp[0]) == 0){
		int ch;
		for(ch=0;ch<strlen(inp[1]);ch++){
			if(isdigit(inp[1][ch]) == 0){
				sprintf(toReturn, "Fib requires an integer input\n");
				return toReturn;
			}
		}

		long unsigned int n = atoi(inp[1]);
		long unsigned int a = 0, b = 1, c, i;
		if( n == 0){
			sprintf(toReturn, "%d\n", 0);
			return toReturn;
		}
		char* addPart =  (char*)malloc(sizeof(char)*2048);
		sprintf(addPart, "%d\n", 0);
		strcat(toReturn,addPart);
		free(addPart);


		if(n==1){
			a = 1;
			//sprintf(toReturn, "%d\n", 1);

			char* addPart =  (char*)malloc(sizeof(char)*2048);
			sprintf(addPart, "%lu\n", a);
			strcat(toReturn,addPart);
			free(addPart);


			return toReturn;
		}
		strcat(toReturn,"1\n");
		
		for (i = 2; i <= n; i++){
			c = a + b;
			//printf(" %d ", c);
			if(c<b || c <a){
				//overflow
				strcat(toReturn, "Overflow - input too large\n");
				return toReturn;
			}else{
				char* addPart =  (char*)malloc(sizeof(char)*2048);
				sprintf(addPart, "%lu\n", c);
				strcat(toReturn,addPart);
				free(addPart);

			}
			a = b;
			b = c;
		}
	
		/*char* addPart =  (char*)malloc(sizeof(char)*2048);
		sprintf(addPart, "%d\n", b);
		strcat(toReturn,addPart);
		free(addPart);
*/

		//sprintf(toReturn, "%d\n", b);
	}

	return toReturn;
}

int main(){
	printf("\n\n");

	char *inps[3];
	inps[0]="factor";
	inps[1]="5.4";
	inps[2]="1";
	
	char* outp = doMath(inps);

	printf("outp: %s", outp);	
	return 0;
}

