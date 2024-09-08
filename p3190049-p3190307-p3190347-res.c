#include <pthread.h>  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <C:\Users\30697\Desktop\p3190049-p3190307-p3190347-res\p3190049-p3190307-p3190347-res.h> //exo balei thn dieyuynhsh ston diko m upologisth,ua prepei na allajei gia na trexei



int **board;
int kostos=0;
int count;
unsigned int seed;
double callwait=0;
double cashwait=0;
double fulltime=0;
pthread_mutex_t lockcalls;
pthread_cond_t  condcalls;
pthread_mutex_t lockcash;
pthread_cond_t  condcash;
pthread_mutex_t mutexboard;
pthread_mutex_t mutexCount;
pthread_mutex_t mutexkostos;
pthread_mutex_t printing;
pthread_mutex_t calltime;
pthread_mutex_t cashtime;
pthread_mutex_t fltime;
/**
 * H synartisi pou tha kaleitai apo ta threads kai tha kanei olh thn sunallagh
*/




void *action(void *threadId) {
	struct timespec scall;
    struct timespec fcall;
    struct timespec scash;
    struct timespec fcash;   
    struct timespec start;
    struct timespec finish;
	int print=2;;
	int zone;
	int plithos=0;
	int *tid = (int *)threadId;
	srand(seed* *tid);
	clock_gettime(CLOCK_REALTIME, &scall);
	clock_gettime(CLOCK_REALTIME, &start);
	int tempzone = rand_r(&seed)% 100+1 ;
	int x= PzoneA*100;
	if(1<=tempzone&&tempzone<=x){ //an gurisei to 2 pame sto zone a
		zone = 2;
	}
	else if(x<tempzone&& tempzone <= 100){
		zone= 1;  // allios b
	}
	
	
	while(plithos==0){
		plithos =rand_r(&seed)% (Nseatlow+Nseathigh);
			
	}
	
	
    int rc;
    	
	rc = pthread_mutex_lock(&lockcalls);	
    while (Ntel == 0) {
        rc = pthread_cond_wait(&condcalls, &lockcalls);
    }
	clock_gettime(CLOCK_REALTIME, &fcall);
    Ntel--;
    rc = pthread_mutex_unlock(&lockcalls);    
	rc = pthread_mutex_lock(&mutexboard);

	//////

	int counter=0;
	int breaking =0;
	int i1,j1,k1;
	int tempTheseis[10]={100,100,100,100,100,100,100,100,100,100}; //se ayton ton pinaka kanoume copy tis suntetagmenes ton ueseon poy 
	int tempcount=0;						  						//kleisane oi thlefonites etsi oste ama akyrouei h plhrvmh na tis kanoume pali 0
	if(zone==2){													//to 100 to ebala giati einai ena moumero to opoio den exei sxesh me ton pinaka kai ua bohuhsei sto check

		for(i1=0;i1<NzoneA;i1++){
		if(breaking){
			break;
		}	
		counter=0;
			for( j1 = 0;j1<10;j1++){
				if(board[i1][j1]==0){
					counter++;
					if(counter==plithos){
						print=1;
						for(k1 =j1;k1!=(j1-plithos);k1--){
						  	board[i1][k1]=1;
						  	tempTheseis[tempcount]=i1;
						  	tempcount++;
						  	tempTheseis[tempcount]=k1;      //edo kanei store tis suntetagmenes ton theseon ston prosorino pinaka
						  	tempcount++;
						  }	
						 breaking = 1;
					}	
				}
				else{
					counter =0;
				}	
			}		
		}	
	}
	else{
		for(i1=10;i1<NzoneB+10;i1++){
		if(breaking){
			break;
		}	
		counter=0;
			for(j1 = 0;j1<10;j1++){
				if(board[i1][j1]==0){
					counter++;
					if(counter==plithos){
						print =1;
						for( k1 =j1;k1!=(j1-plithos);k1--){
						  	board[i1][k1]=1;
						  	tempTheseis[tempcount]=i1;
						  	tempcount++;
						  	tempTheseis[tempcount]=k1;
						  	tempcount++;
						  }	
						 breaking = 1;
					}	
				}
				else{
					counter =0;
				}	
			}		
		}
	}	
	
	int seatsearch = tseatlow + ( rand_r(&seed) % (tseathigh-tseatlow+1));
	  
	sleep(seatsearch);
	
	
	/////////////
	rc = pthread_mutex_lock(&lockcalls);
	//printf("o pelaths %d eksipiretithike epitixos apo ton thlefonhth! \n", *tid);
    Ntel++;
    rc = pthread_cond_signal(&condcalls);
    rc = pthread_mutex_unlock(&lockcalls);	
	rc = pthread_mutex_unlock(&mutexboard);	
	
	
	clock_gettime(CLOCK_REALTIME, &scash);	
		int verify;
		int check= rand_r(&seed)%100+1;
		int z= Pcardsucces*100;
		if(1<=check&& check<=z){ //an gurisei to 2 tote ginetai h sunallagh
		verify = 2;
	}
	else{
		verify = 1;  // allios oxi
	}

	int paytime;
    paytime =tcashlow + rand_r(&seed)%(tcashhigh-tcashlow+1);                  
    sleep(paytime);
    
	rc = pthread_mutex_lock(&lockcash);	
    while (Ncash == 0) {
        //printf("H pelaths %d den brike diathesimo tamia. waiting...\n", *tid);
        rc = pthread_cond_wait(&condcash, &lockcash);
    }
    //printf("o pelaths %d brhke tamia \n",*tid);
    clock_gettime(CLOCK_REALTIME, &fcash);
    Ncash--;

    rc = pthread_mutex_unlock(&lockcash);
	int payment;

        
	if(verify== 2&& print==1&&tempTheseis[1]<30){
		rc = pthread_mutex_lock(&mutexkostos);
		if(zone==2){
		kostos +=plithos*CzoneA;
		payment=plithos*CzoneA;
		}
		else{
			kostos += plithos*CzoneB;
			payment	=plithos*CzoneB;;	
		}
		
		rc = pthread_mutex_unlock(&mutexkostos);
		
	}
	else if(verify== 1&& print==1){
		int p;
		rc = pthread_mutex_lock(&mutexboard);
		for(p=0;p<10;p+=2){
			if(tempTheseis[p]!=100){
				board[tempTheseis[p]][tempTheseis[p+1]]=0;  //gurnaei tis theseis piso
			}
			else{
				break;
			}
		}
		rc = pthread_mutex_unlock(&mutexboard);
		print =3;
	}
	
	
	rc = pthread_mutex_lock(&lockcash);
	//printf("o pelaths %d eksipiretithike epitixos apo ton tameia! \n", *tid);
    Ncash++;
    rc = pthread_cond_signal(&condcash);
    rc = pthread_mutex_unlock(&lockcash);
    
    
    
    rc = pthread_mutex_lock(&printing);
    
    	if(print==1){
	    	succes++;
	    	int t1,t2,t3,t4,t5;
		    t1=(tempTheseis[1]+1);
		    t2=(tempTheseis[3]+1);
		    t3=(tempTheseis[5]+1);
		    t4=(tempTheseis[7]+1);
		    t5=(tempTheseis[9]+1);
		    if(plithos==5){
		    	printf("h krathsh oloklhrouhke epityxos,oi theseis sas einai sthn zonh <%d>,seira <%d>,arithmoi< %d,%d,%d,%d,%d >,kai to kostos tis sunallaghs einai < %d >\n",zone,tempTheseis[0]+1,t5,t4,t3,t2,t1,payment);

			}
			else if(plithos==4){
				printf("h krathsh oloklhrouhke epityxos,oi theseis sas einai sthn zonh <%d>,seira <%d>,arithmoi< %d,%d,%d,%d>,kai to kostos tis sunallaghs einai < %d >\n",zone,tempTheseis[0]+1,t4,t3,t2,t1,payment);
	
			}
			else if(plithos==3){
				printf("h krathsh oloklhrouhke epityxos,oi theseis sas einai sthn zonh <%d>,seira <%d>,arithmoi<%d,%d,%d>,kai to kostos tis sunallaghs einai < %d >\n",zone,tempTheseis[0]+1,t3,t2,t1,payment);
	
			}
			else if(plithos==2){
				printf("h krathsh oloklhrouhke epityxos,oi theseis sas einai sthn zonh <%d>,seira <%d>,arithmoi<%d,%d>,kai to kostos tis sunallaghs einai < %d >\n",zone,tempTheseis[0]+1,t2,t1,payment);
	
			}
			else{
				printf("h krathsh oloklhrouhke epityxos,oi theseis sas einai sthn zonh <%d>,seira <%d>,arithmoi<%d>,kai to kostos tis sunallaghs einai < %d >\n",zone,tempTheseis[0]+1,t1,payment);		
			}

		}
		else if(print==2){
			seatserror++;
			printf("h krathsh apetuxe giati den breuhkan katallhles theseis\n");
		}
		else{
			carderror++;
			printf("h krathsh apetuxe giati h sunallagh me thn pistotikh karta den egine dekth\n");
		}
		
	rc = pthread_mutex_unlock(&printing);
	clock_gettime(CLOCK_REALTIME, &finish);
		
    rc = pthread_mutex_lock(&calltime);
    callwait=fcall.tv_sec-scall.tv_sec;
    rc = pthread_mutex_unlock(&calltime);
    
    rc = pthread_mutex_lock(&cashtime);
    cashwait+= fcash.tv_sec-scash.tv_sec;
    rc = pthread_mutex_unlock(&cashtime);
    
    rc = pthread_mutex_lock(&fltime);
    fulltime+= finish.tv_sec-start.tv_sec;
    rc = pthread_mutex_unlock(&fltime);
	pthread_exit(threadId);
}

/**
 * H main synartisi pou tha arxikopoiei ton counter kai ta threads. Tha perimenei
 * tin oloklirwsi twn threads kai tha typwnei tin teliki timi tou counter.
*/
int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("ERROR: the program should take two argument, the number of threads to create and the seed for random numbers!\n");
		exit(-1);
	}
	
	Ncust = atoi(argv[1]);
	seed = atoi(argv[2]);
	int rc;
	pthread_t threads[Ncust];
	int threadIds[Ncust];
	//arxikopoiisi pinaka
	board =(int**) malloc(sizeof(int*)*30);

    if(!board) {
        printf("Adunamia desmeushs mnhmhs");

        exit(0);
    }
	int i;
    for( i = 0; i < 30; i++) {

        board[i] = malloc(sizeof(int)*10);   //arxikopoihsh tou pinaka

        if(!board[i]) {

            printf("Adunamia desmeushs mnhmhs");

            exit(0);

        }

    }
    
    for( i = 0; i < 30; i++) {
		int j;
    	for( j = 0; j < 10; j++) {

        	board[i][j] = 0;
        }
        
    }

	srand(time(NULL));
	//arxikopoiisi twn mutex kai conditions.
	
	rc = pthread_mutex_init(&lockcash, NULL);
	rc = pthread_mutex_init(&lockcalls, NULL);	
	rc = pthread_mutex_init(&mutexkostos, NULL);
	rc = pthread_mutex_init(&mutexboard, NULL);
	rc = pthread_cond_init(&condcalls, NULL);
	rc = pthread_cond_init(&condcash, NULL);
	rc = pthread_mutex_init(&printing,NULL);
	rc = pthread_mutex_init(&calltime,NULL);
	rc = pthread_mutex_init(&cashtime,NULL);
	rc = pthread_mutex_init(&fltime,NULL);
		
	for (i = 0; i < Ncust; i++) {
		threadIds[i] = i + 1;
		//printf("hrue o %dos pelaths\n", threadIds[i]);
    	rc = pthread_create(&threads[i], NULL, action, &threadIds[i]);
    	int calltime =0; 
   		while(calltime==0){
    		calltime =rand()%(treslow+treshigh);
		}
		sleep(calltime);
    	if (rc != 0) {
    		printf("ERROR: return code from pthread_create() is %d\n", rc);
       		exit(-1);
       	}
	}
 
	void *status;
	for (i = 0; i <Ncust; i++) {
		rc = pthread_join(threads[i], &status);
		
		if (rc != 0) {
			printf("ERROR: return code from pthread_join() is %d\n", rc);
			exit(-1);		
		}

		//printf("Main: Thread %d finished with status %d.\n", threadIds[i], *(int *)status);
	}
	  	for( i = 0; i < 30; i++) {
			int j;
        for( j = 0; j < 10; j++) {
		printf("%d",board[i][j]);
            
        }
        printf("\n");
    }
    
    for(i=0;i<30;i++){
    	free(board[i]);
	}
	free(board);
	
    printf("sunolika esoda = %d\nto pososto ton epituxon sunnalagon einai: %.2f%%\nto pososto ton aporipseon kartas: %.2f%%\nto pososto pou den breuikan theseis: %.2f%%\n"
	,kostos,succes/Ncust*100,carderror/Ncust*100,seatserror/Ncust*100);
	printf("o mesos xronos anamonhs einai : %f seconds\n",(callwait+cashwait)/Ncust);
	printf("o mesos sunolikos xronos oloklirosis tis diadikasias einai: %f\n",fulltime/Ncust);
	
	//"katastrofi" tou mutex.
	rc = pthread_mutex_destroy(&printing);
	rc = pthread_mutex_destroy(&mutexboard);		
	rc = pthread_mutex_destroy(&mutexkostos);
	rc = pthread_mutex_destroy(&lockcalls);
	rc = pthread_cond_destroy(&condcalls);
	rc = pthread_cond_destroy(&condcash);\
	rc = pthread_mutex_destroy(&lockcash);
	rc = pthread_mutex_destroy(&calltime);
	rc = pthread_mutex_destroy(&cashtime);
	rc = pthread_mutex_destroy(&fltime);
	return 1;
}
