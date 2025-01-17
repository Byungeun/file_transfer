#include <unistd.h> 	/* 유닉스 표준(UNIX Standard) 시스템 콜을 위한 헤더 파일 */
#include <fcntl.h>
#include <stdio.h> 	/* perror() 함수 */
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

//int main(int argc, char **argv)
int main(int argc, char* argv[])
{
    int n, in, out;
    char buf[1024];
/*
	printf("argc : %d\n",argc);
	printf("argv[0] : %p\n",argv[0]);
	printf("argv[1] : %p\n",argv[1]);
	printf("argv[2] : %p\n",argv[2]);

	for(int i=0;i<argc;i++)
	{
		printf("argv[%d] : %s\n",i,argv[i]);
		for(int j=0;j<strlen(argv[i]);j++)
		{
			printf("argv[%d][%d] : %c\n",i,j,argv[i][j]);
		}
		puts("\n");
	}
*/
    /* 명령행 인수로 복사할 파일명이 없는 경우에 에러를 출력하고 종료한다. */
    if (argc < 3) {
//        write(2, "Usage : copy file1 file2\n", 25);
        printf("Usage : %s file1 file2\n",argv[0]);
        return 1;
    }

    /* 복사의 원본이 되는 파일을 읽기 모드로 연다. */
    if ((in = open(argv[1], O_RDONLY)) < 0) {
//        perror(argv[1]);
        perror("open()");
        return 2;
    }

    /* 복사할 결과 파일을 쓰기 모드(새로운 파일 생성 | 기존에 파일 내용 지움)로 연다. */
//    if ((out = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH)) < 0) {
    if ((out = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0664)) < 0) {
        perror(argv[2]);
        return 3;
    }

    /* 원본 파일의 내용을 읽어서 복사할 파일에 쓴다. */
//    while ((n = read(in, buf, sizeof(buf))) > 0)
//        write(out, buf, n);

	while(1) {
		n = read(in, buf, sizeof(buf));
		printf(" n : %d\n",n);
		if(n > 0)
			write(out, buf, n);
		else if(n == 0)
			break;
		else
		{		
			perror("read()");
			break;
		}
	}

    /* 열린 파일들을 닫는다. */
    close(out);
    close(in);

    /* 프로그램의 정상 종료 시 0을 반환한다. */
    return 0;
}
