#include "carbon/types.h"
#include "carbon/mem.h"
#include <stdint.h>
#include <stddef.h>

static size_t	nbr_len(int nbr)
{
	size_t	len;

	len = 0;
	if (nbr < 0)
	{
		len++;
		nbr *= -1;
	}
	if (nbr < 10)
		len++;
	else
	{
		len += nbr_len(nbr / 10);
		len += nbr_len(nbr % 10);
	}
	return (len);
}

static void	str_cat_char(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	str[i] = c;
	str[i + 1] = '\0';
}

static void	nbr_parse(int nbr, char *str)
{
	if (nbr < 0)
	{
		str_cat_char(str, '-');
		nbr *= -1;
	}
	if (nbr < 10)
		str_cat_char(str, '0' + nbr);
	else
	{
		nbr_parse(nbr / 10, str);
		nbr_parse(nbr % 10, str);
	}
}

char	*types_int2str(int nbr)
{
	char	*str;

	str = mem_calloc(sizeof(char) * (nbr_len(nbr) + 1));
	if (str == NULL)
		return (NULL);
	nbr_parse(nbr, str);
	return (str);
}
