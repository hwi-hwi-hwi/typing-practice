#include <stdio.h>
#include <string.h>

int main(){
    // 파일 이름들 배열로 저장
    const char *files[] = {
        "typing_sentences/애국가.txt",
        "typing_sentences/별_헤는_밤.txt",
        "typing_sentences/님의_침묵.txt",
        "typing_sentences/향수.txt"
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

    char line[256];
    char user_input[256];
    int total_characters = 0;
    int incorrect_characters = 0;

    // 타이머 시작
    // start_time();

    while(fgets(line, sizeof(line), file)){
        
        printf("%s", line);

        // 사용자 입력 받기
        fgets(user_input, sizeof(user_input), stdin);

        // '\n' 문자 제거
        user_input[strcspn(user_input, "\n")] = 0;

        // 틀린 글자 수 계산
        // incorrect_characters += ;
        total_characters += strlen(line);
    }

    fclose(file);  // 파일 닫기

    // 타이머 종료
    // double time_taken = end_time();

    // 통계 계산

    // 통계 출력
    // printf("\n총 걸린 시간: %.2f초\n", time_taken);
    // printf("타수: ");
    // printf("오타율: ");

    return 0;
}
