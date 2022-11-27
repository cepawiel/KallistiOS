

// #include <stdio.h>
// #include <sys/cdefs.h>

// static int
// kos_putc(char c, FILE *file)
// {
// 	(void) c;
// 	(void) file;
// 	return dbgio_write(c);
// }

// static int
// kos_getc(FILE *file)
// {
// 	(void) file;
// 	return EOF;
// }

// static int
// kos_flush(FILE *file)
// {
// 	(void) file;
// 	return 0;
// }

// FILE __stdio = FDEV_SETUP_STREAM(kos_putc, kos_getc, kos_flush, _FDEV_SETUP_RW);

// FILE *const stdout = &__stdio;
// FILE *const stdin  = &__stdio;
// FILE *const stderr = &__stdio;

// FILE *const __iob[3] = { &__stdio, &__stdio, &__stdio };