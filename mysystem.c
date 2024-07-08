/*
 *  mysystem.c : system 関数のクローン
 */

#include <stdio.h>
#include <stdlib.h>    // exit, system のため
#include <unistd.h>    // fork, execXX のため
#include <sys/wait.h>  // wait のため
#include "mysystem.h"  // インタフェース

// system関数のクローン
int mysystem(char *command) {
  int status;
  int pid ;

  if((pid = fork()) < 0){ //fork失敗
  return -1;
  }

  if(command == NULL){ //NULLポインタの場合
    return 1;
  }

  if(pid != 0){
    //親プロセス
    while(wait(&status) != pid);
  }else{
    //子プロセス
    execl("/bin/sh","sh","-c",command,NULL);
    perror("/bin/sh");
    exit(127);
  }

  return status;
}

/* 実行例
% make
cc -Wall -std=c99 -o mysysmain mysysmain.c  mysystem.c
% ./mysysmain
使い方 : ./mysysmain コマンド文字列
% ./mysysmain pwd    
mysystem:
/Users/higashiyuinin/OneDrive - 独立行政法人 国立高等専門学校機構/Syspro2/kadai10-i21higasi
retval = 00000000
system:
/Users/higashiyuinin/OneDrive - 独立行政法人 国立高等専門学校機構/Syspro2/kadai10-i21higasi
retval = 00000000
% ./mysysmain ls
mysystem:
Makefile        README.md       README.pdf      mysysmain       mysysmain.c     mysystem.c      mysystem.h
retval = 00000000
system:
Makefile        README.md       README.pdf      mysysmain       mysysmain.c     mysystem.c      mysystem.h
retval = 00000000
% ./mysysmain ls -l
使い方 : ./mysysmain コマンド文字列
% ./mysysmain "ls -l"
mysystem:
total 616
-rw-r--r--  1 higashiyuinin  staff     143  7  4 09:54 Makefile
-rw-r--r--  1 higashiyuinin  staff    2795  7  4 09:54 README.md
-rw-r--r--  1 higashiyuinin  staff  238232  7  4 09:54 README.pdf
-rwxr-xr-x  1 higashiyuinin  staff   50358  7  8 22:00 mysysmain
-rw-r--r--  1 higashiyuinin  staff     925  7  4 09:54 mysysmain.c
-rw-r--r--  1 higashiyuinin  staff     734  7  8 22:00 mysystem.c
-rw-r--r--  1 higashiyuinin  staff      90  7  4 09:54 mysystem.h
retval = 00000000
system:
total 616
-rw-r--r--  1 higashiyuinin  staff     143  7  4 09:54 Makefile
-rw-r--r--  1 higashiyuinin  staff    2795  7  4 09:54 README.md
-rw-r--r--  1 higashiyuinin  staff  238232  7  4 09:54 README.pdf
-rwxr-xr-x  1 higashiyuinin  staff   50358  7  8 22:00 mysysmain
-rw-r--r--  1 higashiyuinin  staff     925  7  4 09:54 mysysmain.c
-rw-r--r--  1 higashiyuinin  staff     734  7  8 22:00 mysystem.c
-rw-r--r--  1 higashiyuinin  staff      90  7  4 09:54 mysystem.h
retval = 00000000
*/


