#include <stdio.h>
/*
int main(void) {
    char *str = "abc123\n";

    for (char *c = str; *c != '\0'; c++) {
        putchar(*c);
    }

    return 0;
}
*/
int main(void) {
	for (char *str = "abc123\n"; *str != '\0'; str++) {
		putchar(*str);
	}
	
	return 0;
}
