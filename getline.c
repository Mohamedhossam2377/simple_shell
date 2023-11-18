#include "shell.h"

/**
 * input_buffer - buffers commands
 * 
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buffer(info_t *info, char **buf, size_t *len)
{
	ssize_t re = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigint_Handler);
#if USE_GETLINE
		re = get_line(buf, &len_p, stdin);
#else
		re = get_line(info, buf, &len_p);
#endif
		if (re > 0)
		{
			if ((*buf)[re - 1] == '\n')
			{
				(*buf)[re - 1] = '\0';
				re--;
			}
			info->linecount_flag = 1;
			rem_comment(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = re;
				info->cmd_buf = buf;
			}
		}
	}
	return (re);
}

/**
 * get_input - gets a line minus the newline
 * 
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t re = 0;
	char **buf_p = &(info->arg), *pt;

	put_char(BUF_FLUSH);
	re = input_buffer(info, &buf, &len);
	if (re == -1)
		return (-1);
	if (len)
	{
		j = i;
		pt = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = pt;
		return (str_len(pt));
	}

	*buf_p = buf;
	return (re);
}

/**
 * read_buf - reads a buffer
 * 
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: re
 */
ssize_t read_buffer(info_t *info, char *buf, size_t *i)
{
	ssize_t re = 0;

	if (*i)
		return (0);
	re = read(info->readfd, buf, READ_BUF_SIZE);
	if (re >= 0)
		*i = re;
	return (re);
}

/**
 * get_line - gets the next line of input from STDIN
 * 
 * @info: parameter struct
 * @ptr: address of pointer to buffer
 * @length: size of preallocated ptr
 *
 * Return: s
 */
int get_line(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t re = 0, s = 0;
	char *pt = NULL, *new_p = NULL, *ch;

	pt = *ptr;
	if (pt && length)
		s = *length;
	if (i == len)
		i = len = 0;

	re = read_buffer(info, buf, &len);
	if (re == -1 || (re == 0 && len == 0))
		return (-1);

	ch = str_chr(buf + i, '\n');
	k = ch ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(pt, s, s ? s + k : k + 1);
	if (!new_p)
		return (pt ? free(pt), -1 : -1);

	if (s)
		str_ncat(new_p, buf + i, k - i);
	else
		str_ncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	pt = new_p;

	if (length)
		*length = s;
	*ptr = pt;
	return (s);
}

/**
 * sigint_Handler - blocks ctrl-C
 * 
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigint_Handler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	put_char(BUF_FLUSH);
}
