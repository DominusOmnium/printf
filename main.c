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

int		main(void)
{
	t_double d;

	d.f = 15.3112;
	//ft_printf("%f\n", 11.0);
	/*printf("%u\n", f.parts.exponent);
	printf("%u\n", f.parts.mantisa);
	printf("%u\n", d.parts.exponent);
	printf("%u\n", d.parts.mantisa);*/
	while (1)
		ft_printf("^.^/%9lc^.^/", 'E');
	/*printf("%.100Lf\n", ld.f);
	ld.f = 151212456416541564165341683416541654165416.3112;
	printf("%Lf\n", ld.f);*/
	return (0);
}
