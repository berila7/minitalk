#include "./includes/minitalk.h"

// void	handle_signals(int	signal_number)
// {
// 	if (signal_number == SIGUSR1)
// 		printf("Someone waved at me with signal 1!\n");
// 	if (signal_number == SIGUSR2)
// 		printf("Someone waved at me with signal 2!\n");
// }

void	display_bits(char c)
{
	printf("Character '%c' (ASCII: %d) in binary: ", c, c);
	for (int i = 7; i >= 0; i--)
	{
		printf("%d", (c & (1 << i)) ? 1 : 0);
	}
	printf("\n");
}

// void	print_char_as_binary(char c)
// {
// 	int	i;

// 	i = 8;
// 	printf("Character '%c' in binary is: ", c);
// 	while (i--)
// 	{
// 		if (c & (1 << i))
// 			printf("1");
// 		else
// 			printf("0");
// 	}
// 	printf("\n");
// }

// void show_bits(int num)
// {
// 	int i;

// 	i = 8;
//     while (i--)
// 	{
// 		printf("%d", (num >> i) & 1);
// 	}
// 	printf("\n");
// }

int main(void)
{
	int i = 0;
	int x = 1 << 1;
	printf("%d", x);
	return (0);
	char *str = "hello world";
	printf("Let's see how each character is converted:\n\n");
	for (int i = 0; str[i]; i++)
		display_bits(str[i]);
	return (0);
	// unsigned char a = 5; // 00000101 in binary
    // unsigned char b = 3; // 00000011 in binary

    // printf("a: ");
    // show_bits(a);
    
    // printf("b: ");
    // show_bits(b);
    
    // unsigned char result = a | b; // Perform bitwise OR

    // printf("a | b: ");
    // show_bits(result);
    
	// return (0);
	// int num1 = 5;
	// int num2 = 3;

	// printf("Number 1 (5):\t\t");
	// show_bits(num1);
	// printf("Number 2 (3):\t\t");
	// show_bits(num2);
	// printf("Result of 5 & 3:\t");
	// show_bits(num1 & num2);

	// return (0);
	// int number = 1;
	// printf("Original number (1):\t");
	// show_bits(number);
	// printf("Shift left by 1 (1 << 1):\t");
	// show_bits(number << 1);
	// printf("Shift left by 2 (1 << 2):\t");
	// show_bits(number << 2);
	// printf("Shift left by 3 (1 << 3):\t");
	// show_bits(number << 3);
	// return (0);
	// char letter = 'A';
	// print_char_as_binary(letter);
	// return (0);
	// signal(SIGUSR1, handle_signals);
	// signal(SIGUSR2, handle_signals);

	// printf("Process ID: %d\n", getpid());
	// while (1)
	// 	sleep(1);
	// return (0);
}