#include <stdio.h>

typedef union
{
	double	f;
	struct 
	{
		unsigned long int	mantisa : 52;
		unsigned int		exponent : 11;
		unsigned int		sign : 1;
	}			parts;
}				t_double;

int		ft_printf(const char *format, ...);

# include <stddef.h>
int		main(void)
{
	t_double d;

	d.f = 15.3112;
	ft_printf("{%05.*d}", -15, 42);
	printf("{%05.*d}", -15, 42);
	return (0);
}
