#include <stdio.h>
#include <string.h>
#include <time.h>    // 타이머 기능 위해 추가

int main() {
    const char* files[] = {
        "typing_sentences/애국가.txt",
        "typing_sentences/별_헤는_밤.txt",
        "typing_sentences/님의_침묵.txt",
        "typing_sentences/향수.txt"
    };
    int num_files = sizeof(files) / sizeof(files[0]);
    printf("타자 연습 파일 목록:\n");
    int i;
    for (i = 0; i < num_files; i++) {
        printf("%d. %s\n", i + 1, files[i]);
    }

    int choice;
    printf("타자 연습을 하고 싶은 파일의 번호를 입력하세요: ");
    scanf("%d", &choice);
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    if (choice < 1 || choice > num_files) {
        printf("잘못된 선택입니다.\n");
        return 1;
    }

    FILE* file = fopen(files[choice - 1], "r");
    if (file == NULL) {
        perror("파일을 열 수 없습니다.");
        return 1;
    }

    char line[256];
    char user_input[256];
    int total_characters = 0;
    int incorrect_characters = 0;

    // 시작 시간을 현재 시간으로 저장
    time_t start_timestamp = time(NULL);
    struct tm* start_time = localtime(&start_timestamp);
    printf("\n시작 시간: %d시 %d분 %d초\n",
        start_time->tm_hour,
        start_time->tm_min,
        start_time->tm_sec);

    // 타이머 시작
    clock_t start_clock = clock();

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
        fgets(user_input, sizeof(user_input), stdin);
        user_input[strcspn(user_input, "\n")] = 0;
        line[strcspn(line, "\n")] = 0;

        int min_len = strlen(line) < strlen(user_input) ? strlen(line) : strlen(user_input);
        for (i = 0; i < min_len; i++) {
            if (line[i] != user_input[i]) {
                incorrect_characters++;
            }
        }
        incorrect_characters += abs(strlen(line) - strlen(user_input));
        total_characters += strlen(line);
    }
    fclose(file);

    // 종료 시간 저장
    time_t end_timestamp = time(NULL);
    struct tm* end_time = localtime(&end_timestamp);
    clock_t end_clock = clock();

    // 시간 계산
    double time_taken = (double)(end_clock - start_clock) / CLOCKS_PER_SEC;
    double accuracy = 100.0 * (total_characters - incorrect_characters) / total_characters;
    double typing_speed = (total_characters / 2.0) / (time_taken / 60.0);

    printf("\n종료 시간: %d시 %d분 %d초\n",
        end_time->tm_hour,
        end_time->tm_min,
        end_time->tm_sec);
    printf("\n총 걸린 시간: %.2f초\n", time_taken);
    printf("타수: %.2f타/분\n", typing_speed);
    printf("정확도: %.2f%%\n", accuracy);

    return 0;
}