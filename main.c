#include <stdio.h>

int		ft_printf(const char *format, ...);

int		main(void)
{
	char *f = NULL;
	ft_printf("%.5p\n", 0);
	printf("%.5p\n", 0);
	return (0);
}
