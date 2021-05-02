#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"

// test1
// volatile int globalCounter = 0;

// void addToCounter(){
//   globalCounter++;
//   printf(1, "counter is: %x\n", globalCounter);
//   exit();
// }

// int
// main(int argc, char *argv[])
// {
//  int tid;
//  void * stack[10];

//  printf(1, "Running testUserCalls:\n");
//  globalCounter++;
//  printf(1, "before cloning counter is: %x\n", globalCounter);

//  int x;
//  for(x=0; x<10; x++){
//    stack[x] = malloc(4096);
//    tid = clone((void *) &addToCounter, (void *) stack[x], 24, (void *) &globalCounter);
//    printf(1, "join tid %d\n", join(tid));
//    printf(1, "user tid: %d\n", tid);
//  }

// //  for(x=0; x<10; x++){
// //  }

// //  sleep(300);
//  globalCounter++;
//  printf(1, "joined\n");

//  printf(1, "The globalCounter should be 12 : and it is = %d\n", globalCounter);
//  exit();
// }

// test2
// int test_1(int *arg) {
//   // fork();
//   // sleep(500);
//   printf(1, "#himani\n");
//   // wait();
//   printf(1, "&\n");
//   exit();
// }

// int thread_function(int *arg) {
//   THREAD t;
//   int arg2[2];
//   arg2[0] = 5;
//   // fork();
//   t = pthread_create((void*)&test_1, arg2, CLONE_THREAD);
//   pthread_join(t);
//   // sleep(200);
//   printf(1, "join ret : %d\n", t.tid);
//   // sleep(200);
//   // printf(1, "hey###\n");
//   // char readstr[20];
//   // read(arg[0], readstr, 5);
//   // printf(1, "varcha ret : %s\n", readstr);
//   // close(arg[0]);
//   // open("README", O_CREATE | O_RDWR);
//   // char readstr[20];
//   // read(f, readstr, 10);
//   // printf(1, "ret : %s\n", readstr);
//   // printf(1, "thread variable : %d\n", arg[0]);
//   exit();
// }

// void simple_clone_test(int flags) {
//   int arg[1];
//   int f = 7;
//   // int f = open("README", O_CREATE | O_RDWR);
//   // char readstr[20];
//   arg[0] = f;
//   THREAD t;
//   t = pthread_create((void*)&thread_function, arg, CLONE_THREAD);
//   pthread_join(t);
//   printf(1, "out\n");
//   // int i = 0;
//   // for(i = 0; i < 16; i++) {
//   //   t = pthread_create((void*)&thread_function, arg, i);
//   //   pthread_join(t);
//   //   // close(f);
//   //   // printf(1, "file : %d pid : %d\n", f, t.tid);
//   //   f = read(3, readstr, 10);
//   //   printf(1, "File desc : %d\n", f);
//   //   printf(1, "khalacha ret : %s\n", readstr);
//   //   readstr[0] = '\0';
//   //   close(3);
//   // }
//   return; 
// }

// int main() {
//   simple_clone_test(24);
//   exit();
// }

// test3
// void test_function1(int fd){
//   printf(1, "T: %d\n", fd);
//   // sleep(500);
//   mkdir("hi");
//   int k = thread_getcwdinum();
//   printf(1, "A : %d\n", k);
//   chdir("hi");
//   k = thread_getcwdinum();
//   printf(1, "B : %d\n", k);
//   wait();
//   exit();
// }

// void test_function(int fd){
//   // printf(1, "%d\n", flags);
//   // int f = open("README", O_CREATE | O_RDWR);
//   // int gid, ppid, tid;
//   // gid = get_pid();
//   // ppid = get_ppid();
//   // tid = get_tid();
//   // thread_kill(gid, tid, 1);
//   // fork();
//   // printf(1, "0");
//   int k = thread_getcwdinum();
//   printf(1, "C : %d\n", k);
//   THREAD t = pthread_create((void *)&test_function1, (void *)fd, fd);
//   pthread_join(t);
//   k = thread_getcwdinum();
//   printf(1, "D : %d\n", k);
//   // printf(1, "1");
//   // printf(1, "2");
  
//   exit();
// }

// int clone_test(int flags){
//   THREAD t;
//   // int fd = 7;
//   // int pid;
//   // char readstr[20];
//   t = pthread_create((void *)&test_function, (void *)flags, flags);
//   // pid = t.tid;
//   pthread_join(t);
//   // pthread_kill(t.tid);
//   int k = thread_getcwdinum();

//   printf(1, "E : %d\n", k);

//     // chdir("hi");
//   //    k = thread_getcwdinum();
//   // printf(1, "%d\n", k);
//   // printf(1, "PID: %d\n", pid);
//   // fd = read(3, readstr, 10);
//   // printf(1, "File desc: %d\n", fd);
//   // printf(1, "below return: %s", readstr);
//   // close(3);
//   return 0;
// }

// int main() {
//   // int flags;
//   // flags = 0;
//   // int i = 0;
//   // for(; i <= 20; i++){
//     // printf(1, "I: %d\n", i);
//     // if(i != 12)
//     int r = clone_test(CLONE_FS);
//     printf(1, "R: %d\n", r);
//     // clone_test(1);
//     // clone_test(2);
//     // clone_test(4);
//     // clone_test(8);
//     // clone_test(CLONE_FS);
//     // clone_test(31);
//     // close(10);

//   // }
//     // printf(1, "Iadsf: %d\n", i);
//     // mkdir("hi");
//   //   int k = thread_getcwdinum();

//   // printf(1, "%d\n", k);

//   //   // chdir("hi");
//   //    k = thread_getcwdinum();
//   // printf(1, "%d\n", k);
//   exit();
// }

void test_race_fun(void *arg) {
  int *x = (int*)arg;
    for(int i = 0; i < 1000;i++){
        *x += 1;
    }
    exit();
}

void test_race() {
  THREAD t;
  int v = 0;
  for(int i = 0; i < 50; i++){
      t = pthread_create(test_race_fun,(void*)&v, CLONE_VM | CLONE_THREAD);
      pthread_join(t);
  }
  if(v != 50*1000){
      printf(1,"Race Test : Pass\n\n");
  }else{
      printf(1,"Race Test : Pass\n\n");
  }
  return;
} 

int test_clone_var = 0;
void test_clone_fun() {
  test_clone_var = 5;
  exit();
}

void test_clone() {
  THREAD t;
  int args[1];
  args[0] = 7;
  t = pthread_create(test_clone_fun, (void*)args, CLONE_VM | CLONE_THREAD);
  pthread_join(t);
  if(test_clone_var == 5) {
    printf(1, "Clone Test : Pass\n\n");
  } else {
    printf(1, "Clone Test : Fail\n\n");
  }
  return;
}


int test_tkill_var = 0;
void test_tkill_fun() {
  sleep(100);
  test_tkill_var = 7;
  exit();
}

void test_tkill() {
  THREAD t;
  int args[1];
  args[0] = 7;
  t = pthread_create(test_tkill_fun, (void*)args, CLONE_VM | CLONE_THREAD);
  pthread_kill(t.tid);
  if(test_tkill_var == 0) {
    printf(1, "tkill Test : Pass\n\n");
  } else {
    printf(1, "tkill Test : Fail\n\n");
  }
  return;
}

int test_clone_in_thread_var = 8;
void test_clone_in_thread_fun2() {
  test_clone_in_thread_var += 1;
  exit();
}

void test_clone_in_thread_fun1() {
  THREAD t;
  int args[1];
  args[0] = 4;
  test_clone_in_thread_var += 1;
  t = pthread_create(test_clone_in_thread_fun2, (void*)args, CLONE_VM | CLONE_THREAD);
  pthread_join(t);
  test_clone_in_thread_var += 1;
  exit();
}

void test_clone_in_thread() {
  THREAD t;
  int args[1];
  args[0] = 4;
  t = pthread_create(test_clone_in_thread_fun1, (void*)args, CLONE_VM | CLONE_THREAD);
  pthread_join(t);
  if(test_clone_in_thread_var == 11 ) {
    printf(1, "clone in thread Test : Pass\n\n");
  } else {
    printf(1, "clone in thread Test : Fail\n\n");
  }
  return;
}


int no_of_threads = 3;
int r1,c1,r2,c2;
int mat1[100][100];
int mat2[100][100];
int res[100][100];

void test_mat_mul(void *arg) {
  int n = (int)arg;
  //printf("%d\n",r1);
  int start = (n*r1)/no_of_threads;
  int end = ((n+1)*r1)/no_of_threads;

  for(int i = start ; i < end; i++){
      for(int j = 0; j < c2; j++){
          res[i][j] = 0;
          for(int k = 0 ; k < c1; k++){
              res[i][j] += mat1[i][k]*mat2[k][j];
          }
      }
  }
  exit();
}

void test_matrix_mul() {
  THREAD tid[no_of_threads];
  r1 = 1; 
  c1 = 3;
  for(int row = 0; row<r1; row++){
      for(int col = 0; col < c1; col++){
          mat1[row][col] = 5;
      }
  }
  r2 = 3; c2 = 1;
  
  for(int row = 0; row<r2; row++){
      for(int col = 0; col < c2; col++){
          mat2[row][col] = 7;
      }
  }
  
  for(int i = 0; i < no_of_threads; i++){
      tid[i] = pthread_create(test_mat_mul, (void*)i, CLONE_VM);
      
  }
  for(int i = 0; i < no_of_threads; i++){
      pthread_join(tid[i]);
  }
  if(res[0][0] == 105){
    printf(1,"Test matrix multiplaction : Pass\n\n");
  } else {
    printf(1,"Test matrix multiplaction : Fail\n\n");
  }
}

void test_id_fun(void* arg){
  int tid = gettid();
  int parent_id = getppid();
  int tgid = getpid();
  printf(1, "TID : %d\nParent_ID : %d\nTGID : %d\n\n", tid,parent_id, tgid);
  exit();
}

void test_id(){
  printf(1,"Thread IDs\n");
  THREAD t1;
  t1 = pthread_create(test_id_fun, 0, CLONE_VM);
  pthread_join(t1);
} 

int test_clone_vm_var = 0;
void test_clone_vm_fun() {
  test_clone_vm_var += 1;
  exit();
}

void test_clone_vm() {
  THREAD t1;
  int flag = 0;
  t1 = pthread_create(test_clone_vm_fun, 0, CLONE_THREAD);
  pthread_join(t1);
  if(test_clone_vm_var != 1) {
    flag = 1;
  }
  t1 = pthread_create(test_clone_vm_fun, 0, CLONE_VM | CLONE_THREAD);
  pthread_join(t1);
  if(flag == 1 && test_clone_vm_var == 1) {
    printf(1,"Test CLONE_VM flag : Pass\n\n");
  } else {
    printf(1,"Test CLONE_VM flag : Fail\n\n");
  }
  return;
}


void test_multi_join_fun(void* flags) {
  int var = (int)flags;
  sleep(var);
  exit();
}

void test_multi_join() {
  THREAD t1, t2;
  int ret1, ret2;
  int var1 = 100, var2 = 200;
  t1 = pthread_create(test_multi_join_fun, (void*)var1, CLONE_VM | CLONE_THREAD);
  t2 = pthread_create(test_multi_join_fun, (void*)var2, CLONE_VM | CLONE_THREAD);
  ret1 = pthread_join(t1);
  ret2 = pthread_join(t2);
  if (ret1 == t1.tid && ret2 == t2.tid) {
    printf(1, "Test Join in order : Pass\n\n");
  } else {
    printf(1, "Test Join in order : Fail\n\n");\
  }
}


int test_fork_in_thread_var = 0;
void test_fork_in_thread_fun(void *args) {
  int ret = fork();
  if(ret == 0) {
    test_fork_in_thread_var += 5;
    exit();
  } else {
    wait();
    test_fork_in_thread_var += 10;
  }
  exit();
}

void test_fork_in_thread() {
  THREAD t;
  int var1 = 9;
  // printf()
  t = pthread_create(test_fork_in_thread_fun, (void*)&var1, CLONE_VM | CLONE_THREAD);
  pthread_join(t);
  if(test_fork_in_thread_var == 10) {
    printf(1, "Test fork in thread : Pass\n\n");
  } else {
    printf(1, "Test fork in thread : Fail\n\n");\
  }
}

char test_pass_string_arg_var[5];
void test_pass_string_arg_fun(void* args) {
  char *var1 = (char*)args;
  test_pass_string_arg_var[0] = var1[0];
  exit();
}

void test_pass_string_arg() {
  THREAD t;
  char var1[5] = "hello";
  // printf()
  t = pthread_create(test_pass_string_arg_fun, (void*)var1, CLONE_VM | CLONE_THREAD);
  pthread_join(t);
  if(test_pass_string_arg_var[0] == 'h') {
    printf(1, "Test pass string argument : Pass\n\n");
  } else {
    printf(1, "Test pass string argument : Fail\n\n");
  }
}


int test_join_by_thread_grp_member_var = 0;
void test_join_by_thread_grp_member_fun2(void *args) {
  THREAD *t = (THREAD*)args;
  pthread_join(*t);
  if(test_join_by_thread_grp_member_var == 0) {
    test_join_by_thread_grp_member_var = 5;
  }
  exit();
}

void test_join_by_thread_grp_member_fun1(void *args) {
  sleep(100);
  test_join_by_thread_grp_member_var = 1;
  exit();
}

void test_join_by_thread_grp_member() {
  THREAD t1, t2;
  int tid = 1;
  t1 = pthread_create(test_join_by_thread_grp_member_fun1, (void*)&tid, CLONE_VM | CLONE_THREAD);
  t2 = pthread_create(test_join_by_thread_grp_member_fun2, (void*)&t1, CLONE_VM | CLONE_THREAD);
  pthread_join(t2);
  if(test_join_by_thread_grp_member_var == 1) {
    printf(1, "Test join called by member of thread group : Pass\n\n");
  } else {
    printf(1, "Test join called by member of thread group : Fail\n\n");
  }
}

int test_clone_file_parent_to_thread_var = 0;
void test_clone_file_parent_to_thread_fun(void* args) {
  int *fd = (int*)args;
  char readstr[20];
  int ret = read(*fd, readstr, 5);
  if(ret != -1) {
    test_clone_file_parent_to_thread_var = 1;
  }
  exit();
}

void test_clone_file_parent_to_thread() {
  THREAD t;
  int fd = open("README", O_RDONLY);
  t = pthread_create(test_clone_file_parent_to_thread_fun, (void*)&fd, CLONE_VM | CLONE_FILES);
  pthread_join(t);
  close(fd);
  if(test_clone_file_parent_to_thread_var == 1) {
    printf(1, "Test on CLONE_FILE set parent ofile changes reflect to thread : Pass\n\n");
  } else {
    printf(1, "Test on CLONE_FILE set parent ofile changes reflect to thread : Fail\n\n");
  }
}


void test_clone_file_thread_to_parent_fun(void *args) {
  int *ret_fd = (int*)args;
  int fd = open("README", O_RDONLY);
  *ret_fd = fd;
  exit();
}

void test_clone_file_thread_to_parent() {
  THREAD t;
  int fd;
  t = pthread_create(test_clone_file_thread_to_parent_fun, (void*)&fd,CLONE_VM | CLONE_FILES);
  pthread_join(t);
  char readstr[20];
  int ret = read(fd, readstr, 5);
  close(fd);
  if(ret != 1) {
    printf(1, "Test on CLONE_FILE set thread ofile changes reflect to parent : Pass\n\n");
  } else {
    printf(1, "Test on CLONE_FILE set thread ofile changes reflect to parent : Fail\n\n");
  }
}

void test_clone_fs_fun(void *args) {
  int *k = (int*)args;
  mkdir("new_dir");
  chdir("new_dir");
  *k = thread_getcwdinum();
  exit();
}

void test_clone_fs() {
  int k;
  int kthread;
  THREAD t = pthread_create((void *)&test_clone_fs_fun, (void *)&kthread, CLONE_FS);
  pthread_join(t);
  k = thread_getcwdinum();
  if(k != kthread) {
    printf(1, "Test on CLONE_FS set change of dir from thread relfected in parents : Pass\n\n");
  } else {
    printf(1, "Test on CLONE_FS set change of dir from thread relfected in parents : Fail\n\n");
  }
}

void test_clone_thread_fun(void *args) {
  int *pid = (int*)args;
  *pid = get_pid();
  exit();
}

void test_clone_thread() {
  int pid;
  THREAD t = pthread_create((void *)&test_clone_thread_fun, (void *)&pid, CLONE_VM | CLONE_THREAD);
  pthread_join(t);
  int cur_pid = get_pid();
  if(pid == cur_pid) {
    printf(1, "Test on CLONE_THREAD set thread it put in the same thread group : Pass\n\n");
  } else {
    printf(1, "Test on CLONE_THREAD set thread it put in the same thread group : Fail\n\n");
  }
}

void test_clone_parent_fun(void* args) {
  int *pid = (int*)args;
  *pid = getppid();
  exit();
}

void test_clone_parent() {
  int pid;
  THREAD t = pthread_create((void *)&test_clone_parent_fun, (void *)&pid, CLONE_VM | CLONE_PARENT);
  pthread_join(t);
  int cur_pid = getppid();
  if(pid == cur_pid) {
    printf(1, "Test on CLONE_PARENT set then parent is parent's parent : Pass\n\n");
  } else {
    printf(1, "Test on CLONE_PARENT set then parent is parent's parent : Fail\n\n");
  }
}

void test_stress_fun(void*args) {
  sleep(100);
  exit();
}

void test_stress() {
  for(int i = 0;;i++) {
    THREAD t = pthread_create((void *)&test_stress_fun, 0, 0);
    if(t.tid == -1) {
      break;
    }
    // pthread_join(t);
    printf(1, "%d\n", i);
  }
}

int main() {
  test_clone();
  test_tkill();
  test_race();
  test_pass_string_arg();
  test_matrix_mul();
  test_id();
  test_multi_join();
  test_fork_in_thread();
  test_clone_in_thread();
  test_join_by_thread_grp_member();
  test_clone_vm();
  test_clone_file_parent_to_thread();
  test_clone_file_thread_to_parent();
  test_clone_fs();
  test_clone_thread();
  test_clone_parent();
  test_stress();
  exit();
}