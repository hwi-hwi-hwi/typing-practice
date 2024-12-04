#include <stdio.h>
#include <stdlib.h>

int main(){
    // 파일 이름들을 배열로 저장
    const char *files[] = {
        "typing_sentences/애국가.txt",
        "typing_sentences/별_헤는_밤.txt",
        "typing_sentences/님의_침묵.txt",
        "typing_sentences/향수.txt"
    };
    // 파일 개수
    int num_files = sizeof(files) / sizeof(files[0]);

    // 파일 목록 출력
    printf("파일 목록:\n");
    int i;
    for(i = 0; i < num_files; i++){
    	
        printf("%d. %s\n", i + 1, files[i]);
    }

    // 사용자로부터 파일 선택
    int choice;
    printf("열고 싶은 파일의 번호를 입력하세요: ");
    scanf("%d", &choice);

    // 입력 값이 유효한지 확인
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

    // 파일 내용 읽어서 출력
    char line[256];
    
    while(fgets(line, sizeof(line), file)){
        printf("%s", line);
    }

    fclose(file);  // 파일 닫기
    
    return 0;
}
