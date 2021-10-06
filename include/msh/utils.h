#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

int	utils_exit(int ec, char *err_msg);

int	utils_printerror(char *prog, char *msg);

int	utils_is_number(char *str);

#endif
