#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFSIZE 256

int comp_string(int FGETS_LEN, int STDIN_LEN, wchar_t *FGETS_ARRAY, wchar_t *STDIN_ARRAY);
void show_stat(int total_line, int total_miss, int total_time);

int main(){
    setlocale(LC_ALL, "ko_KR.UTF-8");
    // 파일 이름들 배열로 저장
    const char *files[] = {
        "typing_sentences/애국가.txt",
        "typing_sentences/별_헤는_밤.txt",
        "typing_sentences/님의_침묵.txt",
        "typing_sentences/향수.txt",
        "typing_sentences/test_txt.txt"
    };
    int num_files = sizeof(files) / sizeof(files[0]);

    // 타자 연습 파일 목록 출력
    printf("타자 연습 파일 목록:\n");
    int i;
    for(i = 0; i < num_files; i++){

        printf("%d. %s\n", i + 1, files[i]);
    }

    // 파일 선택
    int choice;
    printf("타자 연습을 하고 싶은 파일의 번호를 입력하세요: ");
    scanf("%d", &choice);

    // 입력 버퍼에 남아 있는 개행 문자 제거
    int ch;
    while((ch = getchar()) != '\n' && ch != EOF);

    if(choice < 1 || choice > num_files){
        printf("잘못된 선택입니다.\n");

        return 1;
    }

    // 선택한 파일 열기
    FILE *file = fopen(files[choice - 1], "r");
    if(file == NULL){
        perror("파일을 열 수 없습니다.");

        return 1;
    }

    char line[BUFSIZE];
    char user_input[BUFSIZE];
    int total_characters = 0;
    int incorrect_characters = 0;

    wchar_t line_wstr[BUFSIZE] = {0};
    wchar_t user_wstr[BUFSIZE] = {0};
    // 타이머 시작
    // start_time();

    while(fgets(line, BUFSIZE, file) != NULL){
        
        printf("%s", line);
        // 사용자 입력 받기
        if(fgets(user_input, BUFSIZE, stdin) == NULL)
            perror("user_input error");

        // '\n' 문자 제거
        line[strcspn(line, "\n")] = '\0';
        user_input[strcspn(user_input, "\n")] = '\0';

        int line_len = mbstowcs(line_wstr, line, sizeof(line_wstr) / sizeof(line_wstr[0]));
        int user_len = mbstowcs(user_wstr, user_input, sizeof(user_wstr) / sizeof(user_wstr[0]));
        int miss_count = comp_string(line_len, user_len, line_wstr, user_wstr);
        // printf("[line_len: %d], [user_len: %d], [miss_count: %d]\n", line_len, user_len, miss_count);
        // 틀린 글자 수 계산
        incorrect_characters += miss_count;

        total_characters += line_len;

    }

    fclose(file);  // 파일 닫기

    // 타이머 종료
    // double time_taken = end_time();

    // 통계 계산
    show_stat(total_characters, incorrect_characters, 100);

    return 0;
}
int comp_string(int FGETS_LEN, int STDIN_LEN, wchar_t *FGETS_ARRAY, wchar_t *STDIN_ARRAY){
    int miss_count = 0;

    int tmp_len = FGETS_LEN;
    if(FGETS_LEN != STDIN_LEN && STDIN_LEN > FGETS_LEN) tmp_len = STDIN_LEN;
    // printf("[FGETS_LEN / tmp_len] : [%d / %d]\n",FGETS_LEN, tmp_len);
    for(int i=0; i < tmp_len; i++){
        // printf("In comp_string: [Line: %lc]\t[User: %lc]\n", FGETS_ARRAY[i], STDIN_ARRAY[i]);
        if(FGETS_ARRAY[i] != STDIN_ARRAY[i]){
            miss_count++;
        }
    }
    
    int result_miss_count = ((miss_count >= FGETS_LEN) ? FGETS_LEN : miss_count); 
    return result_miss_count;
}

void show_stat(int total_line, int total_miss, int total_time){
    char line[BUFSIZE]; 
    FILE* file = fopen("record.txt", "a+t");
    double typing_per_min = (double) total_line * 60 / total_time;
    double typing_speed = typing_per_min / 5;  
    printf("[total_line: %d], [total_miss: %d], [total_time: %d]\n", total_line, total_miss, total_time);
    double accuracy = (1 - ((double) total_miss / total_line))*100;
    printf("=================================RESULT=================================\n");
    printf("%15s|%15s|%15s|%15s|\n", "걸린 시간", "평균 타수", "정확도", "오타율"); 
    printf("%10d |%10.3f |%11.3f |%11.3f |\n", total_time, typing_speed, accuracy, 100-accuracy);
    printf("=================================RECORD=================================\n");
    while(fgets(line, BUFSIZE, file) != NULL){
        printf("%s\n", line);
    }
    fprintf(file, "%10d |%10.3f |%11.3f |%11.3f |\n", total_time, typing_speed, accuracy, 100-accuracy);
}

