#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>
// #include <sys/types.h>
// #include <sys/stat.h>
#include <fcntl.h>

#define BUFSIZE 256

<<<<<<< HEAD int comp_string(int FGETS_LEN, int STDIN_LEN, wchar_t *FGETS_ARRAY, wchar_t *STDIN_ARRAY);
void show_stat(int total_line, int total_miss, int total_time);

<<<<<<< HEAD
int main()
{
    == == == =
                 int main()
    {
        setlocale(LC_ALL, "ko_KR.UTF-8");
>>>>>>> origin/main
        // 파일 이름들 배열로 저장
        const char *files[] = {
            "typing_sentences/애국가.txt",
            "typing_sentences/별_헤는_밤.txt",
            "typing_sentences/님의_침묵.txt",
<<<<<<< HEAD
            "typing_sentences/향수.txt"};
        int num_files = sizeof(files) / sizeof(files[0]);

        // 타자 연습 파일 목록 출력

        printf("타자 연습 파일 목록:\n");
        int i;
        for (i = 0; i < num_files; i++)
        {

            == == == =
                         "typing_sentences/향수.txt",
                  "typing_sentences/test_txt.txt"
        };
        int num_files = sizeof(files) / sizeof(files[0]);

        // 타자 연습 파일 목록 출력
        printf("타자 연습 파일 목록:\n");
        int i;
        for (i = 0; i < num_files; i++)
        {
>>>>>>> origin/main
            printf("%d. %s\n", i + 1, files[i]);
        }

        // 파일 선택
        int choice;
        printf("타자 연습을 하고 싶은 파일의 번호를 입력하세요: ");
        scanf("%d", &choice);

        // 입력 버퍼에 남아 있는 개행 문자 제거
        int ch;
<<<<<<< HEAD
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;

        if (choice < 1 || choice > num_files)
        {
            printf("번호를 잘못 입력하였습니다.\n");
            == == == =
                         while ((ch = getchar()) != '\n' && ch != EOF);
>>>>>>> origin/main

            if (choice < 1 || choice > num_files)
            {
                printf("잘못된 선택입니다.\n");
                return 1;
            }

<<<<<<< HEAD
            // 선택한 파일 열기
            FILE *file = fopen(files[choice - 1], "r");
            if (file == NULL)
            {
                perror("파일을 열 수 없습니다.");

                == == == =
                             FILE *file = fopen(files[choice - 1], "r");
                if (file == NULL)
                {
                    perror("파일을 열 수 없습니다.");
>>>>>>> origin/main
                    return 1;
                }
                == == == =
                             struct time_struct
                {
                    time_t t;
                    char buf[BUFSIZE];
                    struct tm *lt;
                };
>>>>>>> origin/main

                struct buf_set
                {
                    char line[BUFSIZE];
                    char user_input[BUFSIZE];
                    wchar_t line_wstr[BUFSIZE];
                    wchar_t user_wstr[BUFSIZE];
                };

<<<<<<< HEAD
<<<<<<< HEAD
                == == == =
                             wchar_t line_wstr[BUFSIZE] = {0};
                wchar_t user_wstr[BUFSIZE] = {0};
>>>>>>> origin/main
                // 타이머 시작
                // start_time();
                // 시작 시간을 현재 시간으로 저장
                time_t start_timestamp = time(NULL);
                struct tm *start_time = localtime(&start_timestamp);
                printf("\n시작 시간: %d시 %d분 %d초\n",
                       start_time->tm_hour,
                       start_time->tm_min,
                       start_time->tm_sec);

<<<<<<< HEAD
                while (fgets(line, sizeof(line), file))
                {

                    == == == =
                                 // 타이머 시작
                        clock_t start_clock = clock();

                    while (fgets(line, sizeof(line), file))
                    {
>>>>>>> origin/main
                        printf("%s", line);
                        // 사용자 입력 받기
                        if (fgets(user_input, BUFSIZE, stdin) == NULL)
                            perror("user_input error");

<<<<<<< HEAD
                        // 사용자 입력 받기
                        fgets(user_input, sizeof(user_input), stdin);

                        // '\n' 문자 제거
                        user_input[strcspn(user_input, "\n")] = 0;

                        // 틀린 글자 수 계산
                        // incorrect_characters += ;
                        total_characters += strlen(line);
                        == == == =
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

>>>>>>> origin/main
                        == == == =
                                     FILE * choose_file();
                        void remove_record();
                        void pre_processing(struct buf_set * buf, int *line_len, int *user_len);
                        struct time_struct time_check();
                        void comp_string(int FGETS_LEN, int STDIN_LEN, wchar_t *FGETS_ARRAY, wchar_t *STDIN_ARRAY, int *count);
                        void show_stat(int total_line, int typing_line, int total_miss, int total_time);
                        void exit_process();

                        int total_correct_characters = 0, total_typing_characters, incorrect_characters = 0;
                        const char *file_name;
                        FILE *file, *save;

                        int main()
                        {
                            setlocale(LC_ALL, "ko_KR.UTF-8");

                            struct buf_set buf = {
                                {0},
                            };
                            struct time_struct start_time, end_time;

                            if ((file = choose_file()) == NULL)
                            {
                                perror("잘못된 파일 선택으로 종료되었습니다.");
                                exit(-1);
>>>>>>> origin/main
                            }

<<<<<<< HEAD
<<<<<<< HEAD
                            fclose(file); // 파일 닫기

                            // 타이머 종료
                            // double time_taken = end_time();

                            // 통계 계산

                            // 통계 출력
                            // printf("\n총 걸린 시간: %.2f초\n", time_taken);
                            // printf("타수: ");
                            // printf("오타율: ");
                            == == == =
                                         // 종료 시간 저장
                                time_t end_timestamp = time(NULL);
                            struct tm *end_time = localtime(&end_timestamp);
                            clock_t end_clock = clock();
                            == == == =
                                         // 타이머 시작
                                start_time = time_check();
>>>>>>> origin/main

                            while (fgets(buf.line, sizeof(buf.line), file))
                            {
                                printf("%s", buf.line);
                                if (fgets(buf.user_input, BUFSIZE, stdin) == NULL)
                                    perror("user_input error");
                                printf("\n");
                                int miss_count = 0, line_len = 0, user_len = 0;
                                pre_processing(&buf, &line_len, &user_len);
                                comp_string(line_len, user_len, buf.line_wstr, buf.user_wstr, &miss_count);
                            }

<<<<<<< HEAD
                            // 통계 계산
                            show_stat(total_characters, incorrect_characters, 100);
>>>>>>> origin/main
                            == == == =
                                         end_time = time_check();
                            show_stat(total_correct_characters, total_typing_characters, incorrect_characters, (end_time.t - start_time.t));
>>>>>>> origin/main

                            if (atexit(exit_process))
                            {
                                perror("on_exit: no fclosed");
                                exit(-1);
                            }
                            return 0;
                        }

                        FILE *choose_file()
                        {
                            // 파일 이름들 배열로 저장
                            const char *files[] = {
                                "애국가",
                                "별_헤는_밤",
                                "님의_침묵",
                                "향수",
                                "test"};
                            const char *utilites[] = {
                                "기록 파일 초기화하기"};
                            int num_files = sizeof(files) / sizeof(files[0]);
                            const int num_utilities = sizeof(utilites) / sizeof(utilites[0]);

                            void (*func[])(void) = {remove_record};
                            int choice;

                            do
                            {
                                printf("========== 타자 연습 파일 목록 ==========\n");
                                int i;
                                for (i = 0; i < num_files; i++)
                                {
                                    printf("%d. %s\n", i + 1, files[i]);
                                }
                                printf("========== 유틸리티 기능 목록  ==========\n");
                                for (int i = 0; i < num_utilities; i++)
                                {
                                    printf("%d. %s\n", i + num_files + 1, utilites[i]);
                                }

                                printf("타자 연습을 하고 싶은 파일의 번호를 입력하세요: ");
                                scanf("%d", &choice);
                                while (getchar() != '\n')
                                    ;

                                if (choice < 1 || choice > num_files + num_utilities)
                                {
                                    printf("잘못된 선택입니다.\n");
                                    return NULL;
                                }
                                else if (choice >= num_files + 1 && choice < num_files + num_utilities + 1)
                                {
                                    func[choice - num_files - 1]();
                                }
                                else
                                {
                                    break;
                                }

                            } while (1);

                            file_name = files[choice - 1];
                            char *tmp_name = (char *)malloc(sizeof(char) * 256);
                            if (tmp_name == NULL)
                            {
                                perror("Memory allocation failed");
                                exit(-1);
                            }
                            sprintf(tmp_name, "%s/%s.%s", "typing_sentences", file_name, "txt");

                            FILE *tmp_file = fopen(tmp_name, "r");
                            if (tmp_file == NULL)
                            {
                                perror("파일을 열 수 없습니다");
                                return NULL;
                            }
                            return tmp_file;
                        }
                        void remove_record()
                        {
                            int fd = open("record.txt", O_TRUNC | O_RDWR);
                            close(fd);
                        }
                        struct time_struct time_check()
                        {
                            struct time_struct time_val;
                            time_val.t = time(NULL);
                            time_val.lt = localtime(&(time_val.t));
                            strftime(time_val.buf, BUFSIZE, "%c\n", time_val.lt);
                            return time_val;
                        }

                        void pre_processing(struct buf_set * buf, int *line_len, int *user_len)
                        {
                            buf->line[strcspn(buf->line, "\n")] = '\0';
                            buf->user_input[strcspn(buf->user_input, "\n")] = '\0';

                            *line_len += mbstowcs(buf->line_wstr, buf->line, sizeof(buf->line_wstr) / sizeof(buf->line_wstr[0]));
                            *user_len += mbstowcs(buf->user_wstr, buf->user_input, sizeof(buf->user_wstr) / sizeof(buf->user_wstr[0]));
                        }

                        void comp_string(int FGETS_LEN, int STDIN_LEN, wchar_t *FGETS_ARRAY, wchar_t *STDIN_ARRAY, int *count)
                        {
                            int miss_count = 0;
                            int tmp_len = (FGETS_LEN > STDIN_LEN) ? FGETS_LEN : STDIN_LEN;

                            int i;
                            for (i = 0; i < tmp_len; i++)
                            {
                                if (FGETS_ARRAY[i] != STDIN_ARRAY[i])
                                {
                                    miss_count++;
                                }
                            }

                            int result_miss_count = ((miss_count >= FGETS_LEN) ? FGETS_LEN : miss_count);

                            incorrect_characters += result_miss_count;
                            total_correct_characters += FGETS_LEN;
                            total_typing_characters += STDIN_LEN;
                            *count += result_miss_count;
                        }

                        void show_stat(int total_line, int typing_line, int total_miss, int total_time)
                        {
                            save = fopen("record.txt", "r+t");
                            char fline[BUFSIZE];

                            double typing_per_min = (double)total_line * 60 / total_time;
                            double typer_per_min = (double)typing_line * 60 / total_time;
                            double typing_speed = typing_per_min / 5;
                            double accuracy = (1 - ((double)total_miss / total_line)) * 100;

                            printf("==================================================== RESULT ====================================================\n\n");
                            printf("| %-10s | %-15s | %-15s | %-10s | %-10s | %-20s |\n",
                                   "걸린 시간", "평균 타수(min)", "타이핑 속도", "정확도", "오타율", "선택한 파일");
                            printf("| %-10d | %-15.3f | %-15.3f | %-10.3f | %-10.3f | %-20s |\n",
                                   total_time, typing_speed, typer_per_min, accuracy, 100 - accuracy, file_name);
                            printf("\n==================================================== RECORD ====================================================\n\n");

                            while (fgets(fline, BUFSIZE, save) != NULL)
                            {
                                printf("%s", fline);
                            }

                            fprintf(save, "| %-10d | %-15.3f | %-15.3f | %-10.3f | %-10.3f | %-20s |\n",
                                    total_time, typing_speed, typer_per_min, accuracy, 100 - accuracy, file_name);
                        }

                        void exit_process()
                        {
                            printf("[atexit]: fclose() start..\n");
                            fclose(file);
                            fclose(save);
                            printf("[atexit]: fclose() end..\n");
                            exit(1);
                        }