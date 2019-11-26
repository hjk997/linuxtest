#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEMKEY (key_t)0111
#define SHMSIZE 1024
#define SHMKEY (key_t)0111
#define BUFSIZE 256

void ioshm (int src, int semid, void *shmaddr, int i);
void p (int semid);
void v (int semid);

int main(int argc, char* argv[]) {
	//공유 메모리 
	int shmid, len; 
	void *shmaddr;
	// 파일 기술자 
	int src, dst; 

	int flags = O_RDWR | O_CREAT | O_TRUNC;
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	// 세마포어
	int semid, i; 
	union semun {
		int value;
		struct semid_ds *buf;
		unsigned short int *array;
	} arg;

	// 특정 키에 대한 세마포어 ID 획득
	if ((semid = semget(SEMKEY, 1, IPC_CREAT | 0666)) == -1) {
		perror ("semget failed");
		exit (1);
	}

	// 세마포어 초기값을 1로 세팅  
	arg.value = 1;
	if (semctl(semid, 0, SETVAL, arg) == -1) {
		perror ("semctl failed");
		exit (1);
	}

	// 특정 키와 영역 크기에 대한 공유 메모리 ID 획득
	if ((shmid = shmget(SHMKEY, SHMSIZE,IPC_CREAT|0666)) == -1) {
		perror ("shmget failed");
		exit (1);
	}
	
	// 공유 메모리 영역을 프로세스 주소공간에 붙임 
	if ((shmaddr = shmat(shmid, NULL, 0)) == (void *)-1) {
		perror ("shmat failed");
		exit (1);
	}

	if( argc < 3 ){
		perror("Not enough argument");
		exit(1);
	}

	if( (src=open(argv[1], O_RDONLY)) == -1) {
		perror("cannot open file");
		exit(1);
	}
	
	if( (dst=open(argv[2], flags, mode)) == -1) {
		perror("cannot open file");
		exit(1);
	}
	
	/////////////////////// create process /////////////////////////
	for (i = 0; i < 2; i++) {
		if (!fork()){
			if( i==0 ){
				ioshm(src, semid, shmaddr, i);
			}else if( i==1 ){
				ioshm(dst, semid, shmaddr, i);
			}
		}
	}
	/////////////////////// create process /////////////////////////
	sleep(15);
	// 공유 메모리 영역을 주소 공간에서 분리 
	if (shmdt(shmaddr) == -1) {
		perror ("shmdt failed");
		exit (1);
	}

	// 공유 메모리 영역 해제  
	if (shmctl(shmid, IPC_RMID, 0) == -1) {
		perror ("shmctl failed");
		exit (1);
	}

	// 세마포어 해제  
	if (semctl(semid, 0, IPC_RMID, arg) == -1) {
		perror ("semctl failed");
		exit (1);
	}
	return 0;
}

void ioshm (int src, int semid, void *shmaddr, int i){
	srand((unsigned int) getpid());
	char buf[BUFSIZE];
	int n=1;

	p(semid); // 세마포어 획득 

	if(i == 0){
		while((n = read(src, buf, BUFSIZE-1)) > 0) 
			strcpy((char *)shmaddr, buf);
		}
 	else if (i == 1) {
		while(write(src, (char*)shmaddr, strlen((char*)shmaddr)) == 0) {}
		}
			//strcpy((char *)shmaddr, buf);

	sleep(rand()%5);
	v(semid); // 세마포어 해제
	printf("%d: complete\n", i);
	exit(0);
}

void p (int semid){
	struct sembuf pbuf;
	pbuf.sem_num = 0;
	pbuf.sem_op = -1;
	pbuf.sem_flg = SEM_UNDO;
	if (semop (semid, &pbuf, 1) == -1) {
		perror ("semop failed");
		exit (1);
	}
}

void v (int semid){
	struct sembuf vbuf;
	vbuf.sem_num = 0;
	vbuf.sem_op = 1;
	vbuf.sem_flg = SEM_UNDO;
	if (semop (semid, &vbuf, 1) == -1) {
		perror ("semop failed");
		exit (1);
	}
}


