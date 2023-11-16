#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM    0
#define CMD_OR      1
#define CMD_AND     2
#define CMD_CHAIN   3

#define CONVERT_LOWERCASE   1
#define CONVERT_UNSIGNED    2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE   ".simple_shell_history"
#define HIST_MAX    4096

extern char **environ;
/**
 * struct liststr - singly linked list
 *
 * @num: number
 * @str: string
 * @next: point to next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contain pseudo-arguments to pass into function
 *
 * @arg: string from getline containing arguments
 * @argv: array of stringd
 * @path: string path
 * @argc: argument count
 * @line_count: error count
 * @err_num: error code for exit
 * @linecount_flag: if on count this line of input
 * @fname: file name
 * @env: local copy of environ
 * @environ: modified copy of environ from LL env
 * @history: history node
 * @alias: alias node
 * @env_changed: on if environ changed
 * @status: return status of last command
 * @cmd_buf: pointer to cmd_buf
 * @cmd_buf_type: CMD_type
 * @readfd: fd from read line input
 * @histcount: history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtin - contain builtin string
 *
 * @type: builtin command flag
 * @func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

int str_len(char *);
int str_cmp(char *, char *);
char *begins_with(const char *, const char *);
char *str_cat(char *, char *);
char *str_cpy(char *, char *);
char *str_dup(const char *);
void _puts(char *);
int put_char(char);
char *str_ncpy(char *, char *, int);
char *str_ncat(char *, char *, int);
char *str_chr(char *, char);
char **str_tow1(char *, char *);
char **str_tow2(char *, char);

char *mem_set(char *, char, unsigned int);
void f_free(char **);
void *_realloc(void *, unsigned int, unsigned int);
int b_free(void **);

int interactive(info_t *);
int is_delimeter(char, char *);
int is_alpha(int);
int _atoi(char *);
int err_atoi(char *);
void prints_error(info_t *, char *);
int prints_d(int, int);
char *conv_num(long int, int, int);
void rem_comment(char *);

list_t *add_node_start(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_str_list(const list_t *);
int del_node_index(list_t **, unsigned int);
void free_list(list_t **);
size_t list_length(const list_t *);
char **list_of_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with_text(list_t *, char *, char);
ssize_t get_node_ind(list_t *, list_t *);

void e_puts(char *);
int e_putchar(char);
int put_fd(char c, int fd);
int puts_fd(char *str, int fd);

void clear_info_init(info_t *);
void set_info_init(info_t *, char **);
void free_info(info_t *, int);

int my_env(info_t *);
char *get_env(info_t *, const char *);
int my_set_env(info_t *);
int my_unset_env(info_t *);
int populate_env_list(info_t *);
char **get_environ(info_t *);
int unset_env(info_t *, char *);
int set_env(info_t *, char *, char *);

char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int re_number_history(info_t *info);

int my_exit(info_t *);
int my_cd(info_t *);
int my_help(info_t *);
int my_history(info_t *);
int unset_alias(info_t *, char *);
int set_alias(info_t *, char *);
int print_alias(list_t *);
int my_alias(info_t *);

int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

ssize_t input_buffer(info_t *, char **, size_t *);
ssize_t get_input(info_t *);
ssize_t read_buffer(info_t *, char *, size_t *);
int get_line(info_t *, char **, size_t *);
void sigint_Handler(__attribute__((unused))int);

int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

int loophsh(char **);

#endif
