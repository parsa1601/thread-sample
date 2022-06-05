#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <time.h>


void thread1(int *arg);
void thread2(int *arg);
void thread3(int *arg);
void thread4(int *arg);

void checking();


char input_file[20][150];
char line[150];
int numberOfLines = 0;
int numberOfWords = 0;
char word[100][20];


char th1input[25][100];
int th1ct = 0;
int th1line[25];


char th2input[25][100];
int th2ct = 0;
int th2line[25];


char th3input[25][100];
int th3ct = 0;
int th3line[25];


char th4input[25][100];
int th4ct = 0;
int th4line[25];


pthread_mutex_t mtx;
sem_t sem;

clock_t clockSet;
clock_t clockEnd;

FILE *output_file;


int main()
{
    FILE *test_case;
    FILE *search_input;

    clockSet = clock();

    test_case = fopen("testInput.txt", "r");
    search_input = fopen("searchInput.txt" , "r");

    ///////////
    while(fgets(line,150, test_case)){
        strcpy(input_file[numberOfLines],line);
        numberOfLines++;
    }

    for(int j = 0 ; j < numberOfLines ; j++){
        // printf("%s", input_file[j]);
    }
    ///////////


    ///////////
    while(fgets(line,150, search_input)){
        strcpy(word[numberOfWords],line);
        numberOfWords++;
    }

    for(int j = 0 ; j < numberOfWords ; j++){
        // printf("%s", word[j]);
    }
    // printf("N - words: %d\n", numberOfWords);
    ///////////


    ///////////
    int counter = 0;
    for (int i = 0; i < numberOfLines; ++i)
    {
    	char* token = strtok(input_file[i], " ");
	// printf("###################\n");
	while (token != NULL) {
		char *newline = strchr( token, '\n' );
		if ( newline )
		  *newline = 0;
		
		if(counter % 4 == 0){
    		counter++;
    		strcpy(th1input[th1ct],token);
    		th1line[th1ct] = i;
    		th1ct++;
    		token = strtok(NULL, " ");
    	}
    	else if(counter % 4 == 1){
    		counter++;
    		strcpy(th2input[th2ct],token);
    		th2line[th2ct] = i;
    		th2ct++;
    		token = strtok(NULL, " ");
    	}
    	else if(counter % 4 == 2){
    		counter++;
    		strcpy(th3input[th3ct],token);
    		th3line[th3ct] = i;
    		th3ct++;
    		token = strtok(NULL, " ");
    	}
    	else if(counter % 4 == 3){
    		counter++;
    		strcpy(th4input[th4ct],token);
    		th4line[th4ct] = i;
    		th4ct++;
    		token = strtok(NULL, " ");
    	}		
	}
	// printf("###################\n");
    }


    ///////////
    /*
    printf("******bache1\n");
    for (int i = 0; i < th1ct; i++)
    {
    	printf("%s\n",th1input[i]);
    }
    printf("******bache2\n");
    for (int i = 0; i < th2ct; i++)
    {
    	printf("%s\n",th2input[i]);
    }
    printf("******bache3\n");
    for (int i = 0; i < th3ct; i++)
    {
    	printf("%s\n",th3input[i]);
    }
    printf("******bache4\n");
    for (int i = 0; i < th4ct; i++)
    {
    	printf("%s\n",th4input[i]);
    }
    printf("*************\n");
    */
    ///////////




    fclose(test_case);
    fclose(search_input);
    // printf("%d \n", numberOfLines);

    checking();
    ///////////
    pthread_t tid1, tid2, tid3, tid4;

    pthread_mutex_init(&mtx, NULL);
    sem_init(&sem,0,1);

    pthread_create(&tid1, NULL, &thread1, NULL);
    pthread_create(&tid2, NULL, &thread2, NULL);
    pthread_create(&tid3, NULL, &thread3, NULL);
    pthread_create(&tid4, NULL, &thread4, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);
    ///////////

    return 0;
}

/*
void thread1(int *arg){
    printf("entered %s", word[1]);
    printf("thread1\n");
	for (int i = 0; i < th1ct; ++i)
	    {

	    	for(int j = 0; j < numberOfWords ; j++){
		    	if(strcmp(word[j], th1input[i]) == 0){
		    		printf("aa%s\n", word[j]);
		    		printf("Founded in line %d\n",th1line[i]+1);
		    	}
	  		}
	    }    


    pthread_exit(0);
}

void thread2(int *arg){
    for (int i = 0; i < th2ct; ++i)
    {

    	for(int j = 0; j < numberOfWords ; j++){
	    	if(strcmp(word[j], th2input[i]) == 0){
	    			printf("%s\n", word[j]);
		    		printf("Founded in line %d\n", th2line[i]+1);
		    }
		}
    }

    pthread_exit(0);
}

void thread3(int *arg){
    for (int i = 0; i < th3ct; ++i)
    {

    	for(int j = 0; j < numberOfWords ; j++){
	    	if(strcmp(word[j], th3input[i]) == 0){
	    			printf("%s\n", word[j]);
		    		printf("Founded in line %d\n", th3line[i]+1);
		    }
		}
    }


    pthread_exit(0);
}

void thread4(int *arg){
    for (int i = 0; i < th4ct-1; ++i)
    {
    	for(int j = 0; j < numberOfWords ; j++){
	    	if(strcmp(word[j], th4input[i]) == 0){
	    			printf("%s\n", word[j]);
		    		printf("Founded in line %d\n", th4line[i]+1);
		    }
		}
    }

    pthread_exit(0);
}

*/


void thread1(int *arg){
    for (int i = 0; i < th1ct; ++i)
        {
            for(int j = 0; j < numberOfWords ; j++){
                if(strstr(word[j], th1input[i]) != NULL && strcmp("",th1input[i])!=0 ){
                    sem_wait(&sem);
                    // pthread_mutex_lock(&mtx);

                    printf("%s", th1input[i]);
                    printf(" -- Founded in line %d\n",th1line[i]+1);


                    output_file = fopen("output.txt", "a");
                    clockEnd = clock();
                    double dure = (double) (clockEnd - clockSet) / CLOCKS_PER_SEC;
                    fprintf(output_file, "%s in 1 line %d . duration: %f\n",th1input[i], th1line[i]+1, dure);
                    fclose(output_file);

                    word[j][0] = '#';
                    // char *temp = word[j] + 1;
                    // strcpy(word[j], temp);
                    printf("after change: %s\n",word[j]);
                    // printf("T-after change: %s\n",temp);


                    // pthread_mutex_unlock(&mtx);
                    sem_post(&sem);
                }
            }
        }    


    pthread_exit(0);
}

void thread2(int *arg){
    for (int i = 0; i < th2ct; ++i)
    {
        for(int j = 0; j < numberOfWords ; j++){
                if(strstr(word[j], th2input[i]) != NULL && strcmp("",th2input[i])!=0 ){
                    sem_wait(&sem);
                    // pthread_mutex_lock(&mtx);

                    printf("%s", th2input[i]);
                    printf(" -- Founded in line %d\n",th2line[i]+1);


                    output_file = fopen("output.txt", "a");
                    clockEnd = clock();
                    double dure = (double) (clockEnd - clockSet) / CLOCKS_PER_SEC;
                    fprintf(output_file, "%s in 2 line %d . duration: %f\n",th2input[i], th2line[i]+1, dure);
                    fclose(output_file);

                    // char *temp = word[j] + 1;
                    // strcpy(word[j], temp);
                    word[j][0] = '#';
                    printf("after change: %s\n",word[j]);
                    // printf("T-after change: %s\n",temp);

                    // pthread_mutex_unlock(&mtx);
                    sem_post(&sem);
                }
        }
    }

    pthread_exit(0);
}

void thread3(int *arg){
    for (int i = 0; i < th3ct; ++i)
    {
        for(int j = 0; j < numberOfWords ; j++){
                if(strstr(word[j], th3input[i]) != NULL && strcmp("",th3input[i])!=0 ){
                    sem_wait(&sem);
                    // pthread_mutex_lock(&mtx);

                    printf("%s", th3input[i]);
                    printf(" -- Founded in line %d\n",th3line[i]+1);

                    output_file = fopen("output.txt", "a");
                    clockEnd = clock();
                    double dure = (double) (clockEnd - clockSet) / CLOCKS_PER_SEC;
                    fprintf(output_file, "%s in 3 line %d . duration: %f\n",th3input[i], th3line[i]+1, dure);
                    fclose(output_file);

                    // char *temp = word[j] + 1;
                    // strcpy(word[j], temp);
                    word[j][0] = '#';
                    printf("after change: %s\n",word[j]);
                    // printf("T-after change: %s\n",temp);

                    // pthread_mutex_unlock(&mtx);
                    sem_post(&sem);
                }
        }
    }


    pthread_exit(0);
}

void thread4(int *arg){
    for (int i = 0; i < th4ct-1; ++i)
    {
        for(int j = 0; j < numberOfWords ; j++){
                if(strstr(word[j], th4input[i]) != NULL && strcmp("",th4input[i])!=0 ){
                    sem_wait(&sem);
                    // pthread_mutex_lock(&mtx);

                    printf("%s", th4input[i]);
                    printf(" -- Founded in line %d\n",th4line[i]+1);


                    output_file = fopen("output.txt", "a");
                    clockEnd = clock();
                    double dure = (double) (clockEnd - clockSet) / CLOCKS_PER_SEC;
                    fprintf(output_file, "%s in 4 line %d . duration: %f\n",th4input[i], th4line[i]+1, dure);
                    fclose(output_file);

                    // char *temp = word[j] + 1;
                    // strcpy(word[j], temp);
                    word[j][0] = '#';
                    printf("after change: %s\n",word[j]);
                    // printf("T-after change: %s\n",temp);

                    // pthread_mutex_unlock(&mtx);
                    sem_post(&sem);
                }
        }
    }

    pthread_exit(0);
}



void checking(){
    //1,2
    for (int i = 0; i < th1ct; ++i)
    {
        /* code */
        for (int j = 0 ; j < th2ct ; j++){
            if (strcmp(th1input[i] , th2input[j]) == 0){
                if (th1line[i] < th2line[j]) th2line[j] = th1line[i];
                else th1line[i] = th2line[j];
            }
        }
    }
    //1,3
    for (int i = 0; i < th1ct; ++i)
    {
        /* code */
        for (int j = 0 ; j < th3ct ; j++){
            if (strcmp(th1input[i] , th3input[j]) == 0){
                if (th1line[i] < th3line[j]) th3line[j] = th1line[i];
                else th1line[i] = th3line[j];
            }
        }
    }
    //1,4
    for (int i = 0; i < th1ct; ++i)
    {
        /* code */
        for (int j = 0 ; j < th4ct ; j++){
            if (strcmp(th1input[i] , th4input[j]) == 0){
                if (th1line[i] < th4line[j]) th4line[j] = th1line[i];
                else th1line[i] = th4line[j];
            }
        }
    }
    //2,4
    for (int i = 0; i < th4ct; ++i)
    {
        /* code */
        for (int j = 0 ; j < th2ct ; j++){
            if (strcmp(th4input[i] , th2input[j]) == 0){
                if (th4line[i] < th2line[j]) th2line[j] = th4line[i];
                else th4line[i] = th2line[j];
            }
        }
    }
    //2,3
    for (int i = 0; i < th3ct; ++i)
    {
        /* code */
        for (int j = 0 ; j < th2ct ; j++){
            if (strcmp(th3input[i] , th2input[j]) == 0){
                if (th3line[i] < th2line[j]) th2line[j] = th3line[i];
                else th3line[i] = th2line[j];
            }
        }
    }
    //3,4
    for (int i = 0; i < th3ct; ++i)
    {
        /* code */
        for (int j = 0 ; j < th4ct ; j++){
            if (strcmp(th3input[i] , th4input[j]) == 0){
                if (th3line[i] < th4line[j]) th4line[j] = th3line[i];
                else th3line[i] = th4line[j];
            }
        }
    }
    printf("Check Done!\n");
}