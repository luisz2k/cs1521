#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

#define LARGEST_NUM 10
//
// Store an arbitray length Binary Coded Decimal number.
// bcd points to an array of size n_bcd
// Each array element contains 1 decimal digit.
// Digits are stored in reverse order.
//
// For example if 42 is stored then
// n_bcd == 2
// bcd[0] == 0x02
// bcd[1] == 0x04
//

typedef struct big_bcd {
    unsigned char *bcd;
    int n_bcd;
} big_bcd_t;


big_bcd_t *bcd_add(big_bcd_t *x, big_bcd_t *y);
void bcd_print(big_bcd_t *number);
void bcd_free(big_bcd_t *number);
big_bcd_t *bcd_from_string(char *string);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number> <number>\n", argv[0]);
        exit(1);
    }

    big_bcd_t *left = bcd_from_string(argv[1]);
    big_bcd_t *right = bcd_from_string(argv[2]);

    big_bcd_t *result = bcd_add(left, right);

    bcd_print(result);
    printf("\n");

    bcd_free(left);
    bcd_free(right);
    bcd_free(result);

    return 0;
}


// DO NOT CHANGE THE CODE ABOVE HERE



big_bcd_t *bcd_add(big_bcd_t *x, big_bcd_t *y) {

    int largest_num = ((x->n_bcd >= y->n_bcd) ? (x->n_bcd) : (y->n_bcd));

    big_bcd_t *sum = malloc(sizeof(*sum));
    sum->n_bcd = largest_num;
    sum->bcd = calloc(largest_num, sizeof(char*));

    for(int i = 0; i < largest_num; i++){
        if(i >= x->n_bcd){
            sum->bcd[i] = y->bcd[i];
        } else if(i >= y->n_bcd){
            sum->bcd[i] = x->bcd[i];
        } else {
            sum->bcd[i] = x->bcd[i] + y->bcd[i];
        }
        
    }
    for(int i = 0 ; i < largest_num - 1; i++){
        //printf("%d\n", sum->bcd[i]);
        if(sum->bcd[i] >= LARGEST_NUM){
            int holder = sum->bcd[i];
            while(holder >= 0){
                holder = holder - LARGEST_NUM;
                sum->bcd[i+1] = sum->bcd[i+1] + 1;
            }
            holder = holder + LARGEST_NUM;
            sum->bcd[i+1] = sum->bcd[i+1] - 1;
            sum->bcd[i] = holder;
        }
    }
    if(sum->bcd[largest_num-1] > LARGEST_NUM){
        sum->bcd = realloc(sum->bcd, largest_num+1);
        sum->n_bcd++;
        if(sum->bcd[largest_num - 1] >= LARGEST_NUM){
            int holder = sum->bcd[largest_num-1];
            while(holder >= 0){
                holder = holder - LARGEST_NUM;
                sum->bcd[largest_num] = sum->bcd[largest_num] + 1;
            }
            holder = holder + LARGEST_NUM;
            sum->bcd[largest_num] = sum->bcd[largest_num] - 1;
            sum->bcd[largest_num-1] = holder;
        }
    }
    return sum;
}


// DO NOT CHANGE THE CODE BELOW HERE


// print a big_bcd_t number
void bcd_print(big_bcd_t *number) {
    // if you get an error here your bcd_add is returning an invalid big_bcd_t
    assert(number->n_bcd > 0);
    for (int i = number->n_bcd - 1; i >= 0; i--) {
        putchar(number->bcd[i] + '0');
    }
}

// free storage for big_bcd_t number
void bcd_free(big_bcd_t *number) {
    // if you get an error here your bcd_add is returning an invalid big_bcd_t
    // or it is calling free for the numbers it is given
    free(number->bcd);
    free(number);
}

// convert a string to a big_bcd_t number
big_bcd_t *bcd_from_string(char *string) {
    big_bcd_t *number = malloc(sizeof *number);
    assert(number);

    int n_digits = strlen(string);
    assert(n_digits);
    number->n_bcd = n_digits;

    number->bcd = malloc(n_digits * sizeof number->bcd[0]);
    assert(number->bcd);

    for (int i = 0; i < n_digits; i++) {
        int digit = string[n_digits - i - 1];
        assert(isdigit(digit));
        number->bcd[i] = digit - '0';
    }

    return number;
}
