#include "shell.h"

/**
 * get_history_file - gets the history file
 * 
 * @info: parameter struct
 *
 * Return: allocated string containing history file
 */

char *get_history_file(info_t *info)
{
    char *buff, *dirc;

    dirc = get_env(info, "HOME=");
    if (!dirc)
        return (NULL);
    buff = malloc(sizeof(char) * (str_len(dirc) + str_len(HIST_FILE) + 2));
    if (!buff)
        return (NULL);
    buff[0] = 0;
    str_cpy(buff, dirc);
    str_cat(buff, "/");
    str_cat(buff, HIST_FILE);
    return (buff);
}

/**
 * write_history - it creates a file, or appends to an existing file.
 * 
 * @info: it is the parameter struct.
 *
 * Return: 1 on success. else -1.
 */

int write_history(info_t *info)
{
    ssize_t file_d;
    char *filename = get_history_file(info);
    list_t *node = NULL;

    if (!filename)
        return (-1);

    file_d = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);
    if (file_d == -1)
        return (-1);
    for (node = info->history; node; node = node->next)
    {
        puts_fd(node->str, file_d);
        put_fd('\n', file_d);
    }
    put_fd(BUF_FLUSH, file_d);
    close(file_d);
    return (1);
}

/**
 * read_history - reads history from file
 * 
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */

int read_history(info_t *info)
{
    int i, last = 0, line_count = 0;
    ssize_t file_d, rd_len, f_size = 0;
    struct stat st;
    char *buf = NULL, *filename = get_history_file(info);

    if (!filename)
        return (0);

    file_d = open(filename, O_RDONLY);
    free(filename);
    if (file_d == -1)
        return (0);
    if(!fstat(file_d, &st))
        f_size = st.st_size;
    if (f_size < 2)
        return (0);
    buf = malloc(sizeof(char) * (f_size +1));
    if (!buf)
        return (0);
    rd_len = read(file_d, buf, f_size);
    buf[f_size] = 0;
    if (rd_len <= 0)
        return (free(buf), 0);
    close(file_d);
    for (i = 0; i < f_size; i++)
        if (buf[i] == '\n')
        {
            buf[i] = 0;
            build_history_list(info, buf + last, line_count++);
            last = i + 1;
        }
    if (last != i)
        build_history_list(info, buf + last, line_count++);
    free(buf);
    info->histcount = line_count;
    while (info->histcount-- >= HIST_MAX)
        del_node_index(&(info->history), 0);
    re_number_history(info);
    return (info->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * 
 * @info: structure containing potential arguments. used to maintain
 * @buf: buffer
 * @linecount: the history lincount, histcount
 *
 * Return: 0
 */

int build_history_list(info_t *info, char *buf, int linecount)
{
    list_t *node = NULL;

    if (info->history)
        node = info->history;
    add_node_end(&node, buf, linecount);

    if (!info->history)
        info->history = node;
    return (0);
}

/**
 * re_number_history - renumbers the history linked list after changes
 * 
 * @info: structure containing potential arguments.
 *
 * Return: the new histcount
 */

int re_number_history(info_t *info)
{
    list_t *node = info->history;
    int i = 0;

    while (node)
    {
        node->num = i++;
        node = node->next;
    }
    return (info->histcount = 1);
}
