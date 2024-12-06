#include <stdio.h>
#include <string.h>
#include <time.h>    // Ÿ�̸� ��� ���� �߰�

int main() {
    const char* files[] = {
        "typing_sentences/�ֱ���.txt",
        "typing_sentences/��_���_��.txt",
        "typing_sentences/����_ħ��.txt",
        "typing_sentences/���.txt"
    };
    int num_files = sizeof(files) / sizeof(files[0]);
    printf("Ÿ�� ���� ���� ���:\n");
    int i;
    for (i = 0; i < num_files; i++) {
        printf("%d. %s\n", i + 1, files[i]);
    }

    int choice;
    printf("Ÿ�� ������ �ϰ� ���� ������ ��ȣ�� �Է��ϼ���: ");
    scanf("%d", &choice);
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    if (choice < 1 || choice > num_files) {
        printf("�߸��� �����Դϴ�.\n");
        return 1;
    }

    FILE* file = fopen(files[choice - 1], "r");
    if (file == NULL) {
        perror("������ �� �� �����ϴ�.");
        return 1;
    }

    char line[256];
    char user_input[256];
    int total_characters = 0;
    int incorrect_characters = 0;

    // ���� �ð��� ���� �ð����� ����
    time_t start_timestamp = time(NULL);
    struct tm* start_time = localtime(&start_timestamp);
    printf("\n���� �ð�: %d�� %d�� %d��\n",
        start_time->tm_hour,
        start_time->tm_min,
        start_time->tm_sec);

    // Ÿ�̸� ����
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

    // ���� �ð� ����
    time_t end_timestamp = time(NULL);
    struct tm* end_time = localtime(&end_timestamp);
    clock_t end_clock = clock();

    // �ð� ���
    double time_taken = (double)(end_clock - start_clock) / CLOCKS_PER_SEC;
    double accuracy = 100.0 * (total_characters - incorrect_characters) / total_characters;
    double typing_speed = (total_characters / 2.0) / (time_taken / 60.0);

    printf("\n���� �ð�: %d�� %d�� %d��\n",
        end_time->tm_hour,
        end_time->tm_min,
        end_time->tm_sec);
    printf("\n�� �ɸ� �ð�: %.2f��\n", time_taken);
    printf("Ÿ��: %.2fŸ/��\n", typing_speed);
    printf("��Ȯ��: %.2f%%\n", accuracy);

    return 0;
}