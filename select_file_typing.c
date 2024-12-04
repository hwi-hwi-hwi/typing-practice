#include <stdio.h>
#include <stdlib.h>

int main(){
    // ���� �̸����� �迭�� ����
    const char *files[] = {
        "typing_sentences/�ֱ���.txt",
        "typing_sentences/��_���_��.txt",
        "typing_sentences/����_ħ��.txt",
        "typing_sentences/���.txt"
    };
    // ���� ����
    int num_files = sizeof(files) / sizeof(files[0]);

    // ���� ��� ���
    printf("���� ���:\n");
    int i;
    for(i = 0; i < num_files; i++){
    	
        printf("%d. %s\n", i + 1, files[i]);
    }

    // ����ڷκ��� ���� ����
    int choice;
    printf("���� ���� ������ ��ȣ�� �Է��ϼ���: ");
    scanf("%d", &choice);

    // �Է� ���� ��ȿ���� Ȯ��
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

    // ���� ���� �о ���
    char line[256];
    
    while(fgets(line, sizeof(line), file)){
        printf("%s", line);
    }

    fclose(file);  // ���� �ݱ�
    
    return 0;
}
