#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <time.h>
#include <setjmp.h>
#include <unistd.h>

// #include <sys/types.h>
// #include <sys/stat.h>
#include <fcntl.h>

#define BUFSIZE 256

const char *files[] = {
        "애국가",
        "별_헤는_밤",
        "님의_침묵",
        "향수",
        "test"
};
const char *utilites[] = {
    "기록 파일 초기화하기",
    "랭킹표 확인"
};

struct time_struct {
    time_t t;
    char buf[BUFSIZE];
    struct tm* lt;
};

struct buf_set {
    char line[BUFSIZE];
    char user_input[BUFSIZE];
    wchar_t line_wstr[BUFSIZE];
    wchar_t user_wstr[BUFSIZE];
};

void login(char**, int, char *, char *);
FILE* choose_file(char**);
void remove_record();
void show_record();
void pre_processing(struct buf_set*, int*, int*);
struct time_struct time_check();
void comp_string(int , int , wchar_t* , wchar_t* , int* , int *, int *, int *);
void show_stat(FILE *, char *, char *, int , int , int , int );
void copy_buf(char *, char *, int , int );
void free_buf(char *, int , int );
int comp_two(char *, char *);
// void exit_process();

jmp_buf jump_buf;
char ID[BUFSIZE], PASSWORD[BUFSIZ];

int main() {
    setlocale(LC_ALL, "ko_KR.UTF-8");

    volatile int flag = 0;
    struct buf_set buf = {{0}, };
    struct time_struct start_time, end_time;

    int total_correct_characters=0, total_typing_characters=0, incorrect_characters=0;
    char *file_name; volatile char user_name[BUFSIZE];
    FILE *file, *save;

    if((flag=setjmp(jump_buf)) != 0){
        if(flag==100 || flag==101) { // 100: 일치하지 않는 ID, 101: 일치하지 않는 PW
            system("clear");
            printf("<------------- [ErrorCode: %d] ID 또는 PW가 일치하지 않아 처음으로 되돌아갑니다 ------------->\n", flag); 
            flag=0;
            free_buf(ID, 0, BUFSIZE); free_buf(ID, 0, BUFSIZE);
            // printf("초기화된 변수들: [ID:%s], [PASSWORD:%s], [Flag:%d]", ID, PASSWORD, flag);
            
        }
        else if(flag==110) { // 110: 계정 생성 시, 중복 ID 존재.
            system("clear");
            printf("<------------- [ErrorCode: %d]계정 생성시에 중복되는 ID가 존재하여 처음으로 되돌아갑니다. ------------->\n", flag);
            flag=0;
            free_buf(ID, 0, BUFSIZE); free_buf(ID, 0, BUFSIZE);
            // printf("초기화된 변수들: [ID:%s], [PASSWORD:%s], [Flag:%d]", ID, PASSWORD, flag);
            
        }
        else if(flag==200){ // 200: 계정 생성 시, ID 중복 확인하러 longjmp
            // printf("200 flag 점프: [ID:%s], [PASSWORD:%s], [Flag:%d]", ID, PASSWORD, flag);
        }
        else if(flag==201){ // 201: 중복 검색 성공 후, 복귀 요청 시그널
            system("clear");
            printf("<------------- 중복되는 아이디가 없으므로 계정 생성 후 로그인합니다. ------------->\n!");
            // printf("200 flag 점프: [ID:%s], [PASSWORD:%s], [Flag:%d]", ID, PASSWORD, flag);
            flag=202; // 계정 중복 검색 성공 시그널.
        }
        
    }
    login(&user_name, flag, ID, PASSWORD);
    if ((file = choose_file(&file_name)) == NULL) {
        perror("잘못된 파일 선택으로 종료되었습니다.");
        exit(-1);
    }
    printf("file_name: %s\n", file_name);
    // 타이머 시작
    start_time = time_check();

    while (fgets(buf.line, sizeof(buf.line), file)) {
        printf("%s", buf.line);
        if (fgets(buf.user_input, BUFSIZE, stdin) == NULL)
            perror("user_input error");
        printf("\n");
        int miss_count = 0, line_len = 0, user_len = 0;
        pre_processing(&buf, &line_len, &user_len);
        comp_string(line_len, user_len, buf.line_wstr, buf.user_wstr, &miss_count, &incorrect_characters, &total_correct_characters, &total_typing_characters);
    }

    end_time = time_check();
    printf("[ID:%s], [PW:%s], [user_name:%s]", ID, PASSWORD, user_name);
    show_stat(save, file_name, ID, total_correct_characters, total_typing_characters, incorrect_characters, (end_time.t - start_time.t));
    fclose(file);
 
    return 0;
}
void login(char **user_name, int flag, char *ID, char *PASSWORD){
    int choice;

    if(flag==200) choice=1;
    else if(flag==202) choice=2;// 200 to choice 1, 202 to choice 2
    else{
        printf("===============================================\n");
        printf("1. 로그인\n");
        printf("2. 계정 생성\n");
        printf("===============================================\n");

        scanf("%d", &choice);
        // while (getchar() != '\n');
    }

    if (choice < 1 || choice > 2) {
        printf("잘못된 선택입니다.\n");
        exit(-1);
    }
    else if(choice==1){
        FILE *login_file = fopen("password.txt", "r");
        char buf[BUFSIZE];
        free_buf(buf, 0, BUFSIZE);
        // char typing_id[BUFSIZE], typing_password[BUFSIZE];
        int no_id=1;

        if(flag==0){
            printf("ID를 입력하시오. [한글과 , 기호는 사용불가.]\n");
            scanf("%s", ID);  
            printf("PW를 입력하시오. [한글과 , 기호는 사용불가.]\n");
            scanf("%s", PASSWORD);
            printf("로그인 초기입력 [ID:%s], [PASSWORD:%s]\n", ID, PASSWORD); 
        }
        else if(flag==200){ // todo
            
        }
        else{
            perror("Unkown flag 2");
            exit(-1);
        }

        while(fgets(buf, BUFSIZE, login_file) != 0){
            char temp_id_cmp[BUFSIZE], temp_pw_cmp[BUFSIZE];
            free_buf(temp_id_cmp, 0, BUFSIZE); free_buf(temp_pw_cmp, 0, BUFSIZE);
            
            char *seperator;
            int i;
            for(i=0; i<strlen(buf); i++){
                if(buf[i]==',') {
                    seperator = buf+i;
                    printf("[%c] 발견\n", buf[i]);    
                    break;
                }
            }
            buf[strlen(buf)-1]==0;
            
            copy_buf(temp_id_cmp, buf, 0, seperator-buf);
            copy_buf(temp_pw_cmp, buf, (seperator-buf)+1, strlen(buf)-1);
            printf("파일에서 가져온 [ID:%s], [PASSWORD:%s]\n", temp_id_cmp, temp_pw_cmp);
            
            printf("ID에도 \\n이 포함되어있을까? %d==%d\n", strlen(ID), strlen(temp_id_cmp));
            printf("PW에도 \\n이 포함되어있을까? %d==%d\n", strlen(PASSWORD), strlen(temp_pw_cmp));
            if(comp_two(ID, temp_id_cmp)){
                no_id = 0;
                

                if(flag==200) longjmp(jump_buf, 110);
                
                
                
                if(comp_two(PASSWORD, temp_pw_cmp) == 0){
                    longjmp(jump_buf, 101);
                }
                
                system("clear");
                printf("로그인 성공! [login: %s], [password: %s]\n", ID, PASSWORD);
                break;
            }
            free_buf(temp_id_cmp, 0, seperator-buf-1);
            free_buf(temp_pw_cmp, (seperator-buf)+1, strlen(buf)-1);
        }
        if(no_id && flag==0){
            longjmp(jump_buf, 100);
        }
        else if(no_id && flag==200){
            longjmp(jump_buf, 201); // 계정 생성 시 중복되는 아이디가 없음.
        }
        fclose(login_file);
    }
    else if(choice==2){
        FILE *login_file = fopen("password.txt", "a+");

        //TODO: login에 중복되는 ID가 있는지.
        if(flag==0){
            printf("생성할 ID를 입력하시오. [한글과 , 기호는 사용불가.]\n");
            scanf("%s", ID); 
            printf("생성할 PW를 입력하시오. [한글과 , 기호는 사용불가.]\n");
            scanf("%s", PASSWORD); 
            printf("계정 생성: 입력한 [ID:%s], [PASSWORD:%s]\n", ID, PASSWORD);
            longjmp(jump_buf, 200);
        }
        else if(flag==202) {
            fprintf(login_file, "%s,%s\n", ID, PASSWORD);
        }
        else printf("Unknown Flag\n");
        
        fclose(login_file);
    }
}
FILE* choose_file(char **file_name){
    int num_files = sizeof(files) / sizeof(files[0]);
    const int num_utilities = sizeof(utilites) / sizeof(utilites[0]);

    void (*func[])(void) = {remove_record, show_record};
    int choice;

    do {
        printf("========== 타자 연습 파일 목록 ==========\n");
        for (int i = 0; i < num_files; i++) {
            printf("%d. %s\n", i + 1, files[i]);
        }
        printf("========== 유틸리티 기능 목록  ==========\n");
        for (int i = 0; i< num_utilities; i++){
            printf("%d. %s\n", i + num_files + 1, utilites[i]);
        }
        
        printf("타자 연습을 하고 싶은 파일의 번호를 입력하세요: ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        if (choice < 1 || choice > num_files + num_utilities) {
            printf("잘못된 선택입니다.\n");
            return NULL;
        }
        else if(choice >= num_files+1 && choice < num_files + num_utilities+1){
            func[choice - num_files - 1]();
        }
        else {break;}
        
    } while(1);

    *file_name = files[choice-1];
    // file_name = files[choice-1];
    char *tmp_name = (char *)malloc(sizeof(char) * 256);
    if(tmp_name == NULL){
        perror("Memory allocation failed");
        exit(-1);
    }
    sprintf(tmp_name, "%s/%s.%s", "typing_sentences", files[choice - 1], "txt");
    FILE *tmp_file = fopen(tmp_name, "r");
    if (tmp_file == NULL) {
        perror("파일을 열 수 없습니다");
        return NULL;
    }
    return tmp_file;
}
void remove_record(){
    int fd = open("record.txt", O_TRUNC | O_RDWR);
    close(fd);
}
void show_record(){
    int fd;
    char show[BUFSIZE*10];
    if((fd=open("record.txt", O_RDONLY))<0){
        perror("오류발생");
        exit(-1);
    }
    read(fd, show, BUFSIZE*10);
    puts(show);
    close(fd);

}
struct time_struct time_check() {
    struct time_struct time_val;
    time_val.t = time(NULL);
    time_val.lt = localtime(&(time_val.t));
    strftime(time_val.buf, BUFSIZE, "%c\n", time_val.lt);
    return time_val;
}

void pre_processing(struct buf_set* buf, int* line_len, int* user_len) {
    buf->line[strcspn(buf->line, "\n")] = '\0';
    buf->user_input[strcspn(buf->user_input, "\n")] = '\0';

    *line_len += mbstowcs(buf->line_wstr, buf->line, sizeof(buf->line_wstr) / sizeof(buf->line_wstr[0]));
    *user_len += mbstowcs(buf->user_wstr, buf->user_input, sizeof(buf->user_wstr) / sizeof(buf->user_wstr[0]));
}

void comp_string(int FGETS_LEN, int STDIN_LEN, wchar_t* FGETS_ARRAY, wchar_t* STDIN_ARRAY, int* count, int *ic, int *tcc, int *ttc) {
    int miss_count = 0;
    int tmp_len = (FGETS_LEN > STDIN_LEN) ? FGETS_LEN : STDIN_LEN;

    for (int i = 0; i < tmp_len; i++) {
        if (FGETS_ARRAY[i] != STDIN_ARRAY[i]) {
            miss_count++;
        }
    }

    int result_miss_count = ((miss_count >= FGETS_LEN) ? FGETS_LEN : miss_count);

    *ic += result_miss_count;  // incorrect_characters
    *tcc += FGETS_LEN;  // total_correct_characters
    *ttc += STDIN_LEN;  // total_typing_characters
    *count += result_miss_count;
}

void show_stat(FILE *save, char *file_name, char *username, int total_line, int typing_line, int total_miss, int total_time){
    save = fopen("record.txt", "r+t");
    char fline[BUFSIZE];

    double typing_per_min = (double) total_line * 60 / total_time;
    double typer_per_min = (double) typing_line * 60 / total_time;
    double typing_speed = typing_per_min / 5;
    double accuracy = (1 - ((double) total_miss / total_line))*100;

    printf("==================================================== RESULT ====================================================\n\n");
    printf("|  %-20s|  %-20s|  %-20s|  %-20s|  %-20s|  %-20s|  %-20s\n", "걸린 시간", "평균 타수(min)", "타이핑 속도", "정확도", "오타율", "선택한 파일", "계정 ID");
    printf("|  %-16d|  %-16.3f|  %-15.3f|  %-17.3f|  %-17.3f|  %-15s|  %-15s\n", total_time, typing_speed, typer_per_min, accuracy, 100-accuracy, file_name, username);
    printf("\n==================================================== RECORD ====================================================\n\n");
    
    while(fgets(fline, BUFSIZE, save) != NULL){
        printf("%s\n", fline);
    }

    fprintf(save, "|  %-16d|  %-16.3f|  %-15.3f|  %-17.3f|  %-17.3f|  %-15s|  %-15s\n",
        total_time, typing_speed, typer_per_min, accuracy, 100 - accuracy, file_name, username);
    fclose(save);
}
int comp_two(char *one, char *two){
    
    if(strlen(one) != strlen(two)) return 0;
    for(int i=0; i<strlen(two); i++){
        // printf("%c//%c\n", one[i], two[i]);
        if (one[i]!=two[i]) return 0;
    
    }
    return 1;
}
void copy_buf(char *dest, char *source, int start_index, int end_index){
    int i;
    for(i=0; i<(end_index-start_index); i++){
        dest[i] = source[start_index+i];
        if(dest[i]=='\n'){
            printf("실제로 buf안 \\n도 받음.\n");
        }
    }
    printf("copy_buf: [dest:%s]\n", dest);
}
void free_buf(char *dest, int start_index, int end_index){
    int i;
    for(i=0; i<(end_index-start_index); i++){
        dest[i]=0;
    }
    printf("free_buf: [dest:%s]\n", dest);
}
