#include <stdio.h>
#include <string.h>

int main(){
    // ���� �̸��� �迭�� ����
    const char *files[] = {
        "typing_sentences/�ֱ���.txt",
        "typing_sentences/��_���_��.txt",
        "typing_sentences/����_ħ��.txt",
        "typing_sentences/���.txt"
    };
    int num_files = sizeof(files) / sizeof(files[0]);

    // Ÿ�� ���� ���� ��� ���
    printf("Ÿ�� ���� ���� ���:\n");
    int i;
    for(i = 0; i < num_files; i++){

        printf("%d. %s\n", i + 1, files[i]);
    }

    // ���� ����
    int choice;
    printf("Ÿ�� ������ �ϰ� ���� ������ ��ȣ�� �Է��ϼ���: ");
    scanf("%d", &choice);

    // �Է� ���ۿ� ���� �ִ� ���� ���� ����
    int ch;
    while((ch = getchar()) != '\n' && ch != EOF);

    if(choice < 1 || choice > num_files){
        printf("�߸��� �����Դϴ�.\n");

        return 1;
    }

    // ������ ���� ����
    FILE *file = fopen(files[choice - 1], "r");
    if(file == NULL){
        perror("������ �� �� �����ϴ�.");

        return 1;
    }

    char line[256];
    char user_input[256];
    int total_characters = 0;
    int incorrect_characters = 0;

    // Ÿ�̸� ����
    // start_time();

    while(fgets(line, sizeof(line), file)){
        
        printf("%s", line);

        // ����� �Է� �ޱ�
        fgets(user_input, sizeof(user_input), stdin);

        // '\n' ���� ����
        user_input[strcspn(user_input, "\n")] = 0;

        // Ʋ�� ���� �� ���
        // incorrect_characters += ;
        total_characters += strlen(line);
    }

    fclose(file);  // ���� �ݱ�

    // Ÿ�̸� ����
    // double time_taken = end_time();

    // ��� ���

    // ��� ���
    // printf("\n�� �ɸ� �ð�: %.2f��\n", time_taken);
    // printf("Ÿ��: ");
    // printf("��Ÿ��: ");

    return 0;
}
