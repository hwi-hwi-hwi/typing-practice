#include <stdio.h>
#include <stdlib.h>

int* comp_string(int FGETS_LEN, int STDIN_LEN, char *FGETS_ARRAY, char *STDIN_ARRAY);

int main(int argc, char *argv){

}

int* comp_string(int FGETS_LEN, int STDIN_LEN, char *FGETS_ARRAY, char *STDIN_ARRAY){
    int miss_count = 0;

    int tmp_len = FGETS_LEN;
    if(FGETS_LEN != STDIN_LEN && STDIN_LEN > FGETS_LEN) tmp_len = STDIN_LEN;

    for(int i=0; i < tmp_len; i++){
        if(FGETS_ARRAY[i] != STDIN_ARRAY[i]){
            miss_count++;
        }
    }
    // Array of [miss_count], [match_score] 
    int array[] = { miss_count, ((miss_count >= FGETS_LEN) ? 0 : miss_count)}; 
    return array;
}    