#include "shell.h"

/**
 * main - entry point
 * @ac: arg acount
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
*/

int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int file_d = 2;

	asm ("mov %l, %0\n\t"
			"add $3, %0" : "=r" (fd) : "r" (fd));

	if (ac == 2)
	{
		file_d = open(av[1], O_RDONLY);
		if (file_d == -1)
		{
			if (errno == EACCES)
				exist(126);
			if (errno == ENOENT)
			{
				e_puts(av[0]);
				e_puts(": 0: cannot open ");
				e_puts(av[1]);
				e_putchar('\n');
				e_putchar(BUF_FLUSH);
				exist(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = file_d;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIST_SUCCESS);
}
