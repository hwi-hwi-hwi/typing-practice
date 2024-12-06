#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <time.h>

#define BUFSIZE 256

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

FILE* choose_file();
void pre_processing(struct buf_set* buf, int* line_len, int* user_len);
struct time_struct time_check();
void comp_string(int FGETS_LEN, int STDIN_LEN, wchar_t* FGETS_ARRAY, wchar_t* STDIN_ARRAY, int* count);
void show_stat(int total_line, int typing_line, int total_miss, int total_time);
void exit_process();

int total_correct_characters = 0, total_typing_characters, incorrect_characters = 0;
const char* file_name;
FILE* file, * save;

int main() {
    setlocale(LC_ALL, "ko_KR.UTF-8");

    struct buf_set buf = {{0}, };
    struct time_struct start_time, end_time;

    if ((file = choose_file()) == NULL) {
        perror("잘못된 파일 선택으로 종료되었습니다.");
        exit(-1);
    }

    // 타이머 시작
    start_time = time_check();

    while (fgets(buf.line, sizeof(buf.line), file)) {
        printf("%s", buf.line);
        if (fgets(buf.user_input, BUFSIZE, stdin) == NULL)
            perror("user_input error");
        printf("\n");
        int miss_count = 0, line_len = 0, user_len = 0;
        pre_processing(&buf, &line_len, &user_len);
        comp_string(line_len, user_len, buf.line_wstr, buf.user_wstr, &miss_count);
    }

    end_time = time_check();
    show_stat(total_correct_characters, total_typing_characters, incorrect_characters, (end_time.t - start_time.t));

    if(atexit(exit_process) ){
        perror("on_exit: no fclosed");
        exit(-1);
    }
    return 0;
}

FILE* choose_file(){
// 파일 이름들 배열로 저장
    const char *files[] = {
        "애국가",
        "별_헤는_밤",
        "님의_침묵",
        "향수",
        "test"
    };
    int num_files = sizeof(files) / sizeof(files[0]);

    printf("타자 연습 파일 목록:\n");
    for (int i = 0; i < num_files; i++) {
        printf("%d. %s\n", i + 1, files[i]);
    }

    int choice;
    printf("타자 연습을 하고 싶은 파일의 번호를 입력하세요: ");
    scanf("%d", &choice);

    while (getchar() != '\n');

    if (choice < 1 || choice > num_files) {
        printf("잘못된 선택입니다.\n");
        return NULL;
    }

    file_name = files[choice - 1];
    char *tmp_name = (char *)malloc(sizeof(char) * 256);
    if(tmp_name == NULL){
        perror("Memory allocation failed");
        exit(-1);
    }
    sprintf(tmp_name, "%s/%s.%s", "typing_sentences", file_name, "txt");

    FILE *tmp_file = fopen(tmp_name, "r");
    if (tmp_file == NULL) {
        perror("파일을 열 수 없습니다");
        return NULL;
    }
    return tmp_file;
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

void comp_string(int FGETS_LEN, int STDIN_LEN, wchar_t* FGETS_ARRAY, wchar_t* STDIN_ARRAY, int* count) {
    int miss_count = 0;
    int tmp_len = (FGETS_LEN > STDIN_LEN) ? FGETS_LEN : STDIN_LEN;

    for (int i = 0; i < tmp_len; i++) {
        if (FGETS_ARRAY[i] != STDIN_ARRAY[i]) {
            miss_count++;
        }
    }

    int result_miss_count = ((miss_count >= FGETS_LEN) ? FGETS_LEN : miss_count);

    incorrect_characters += result_miss_count;
    total_correct_characters += FGETS_LEN;
    total_typing_characters += STDIN_LEN;
    *count += result_miss_count;
}

void show_stat(int total_line, int typing_line, int total_miss, int total_time){
    save = fopen("record.txt", "r+t");
    char fline[BUFSIZE];

    double typing_per_min = (double) total_line * 60 / total_time;
    double typer_per_min = (double) typing_line * 60 / total_time;
    double typing_speed = typing_per_min / 5;
    double accuracy = (1 - ((double) total_miss / total_line))*100;

    printf("==================================================== RESULT ====================================================\n\n");
    printf("|  %-20s|  %-20s|  %-20s|  %-20s|  %-20s|  %-20s\n", "걸린 시간", "평균 타수(min)", "타이핑 속도", "정확도", "오타율", "선택한 파일");
    printf("|  %-16d|  %-16.3f|  %-15.3f|  %-17.3f|  %-17.3f|  %-15s\n", total_time, typing_speed, typer_per_min, accuracy, 100-accuracy, file_name);
    printf("\n==================================================== RECORD ====================================================\n\n");

    while(fgets(fline, BUFSIZE, save) != NULL){
        printf("%s\n", fline);
    }

    fprintf(save, "|  %-16d|  %-16.3f|  %-15.3f|  %-17.3f|  %-17.3f|  %-15s\n",
        total_time, typing_speed, typer_per_min, accuracy, 100 - accuracy, file_name);
}

void exit_process(){
    printf("[atexit]: fclose() start..\n");
    fclose(file);
    fclose(save);
    printf("[atexit]: fclose() end..\n");
    exit(1);

}