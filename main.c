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
	ft_printf("%%f 0000042 == |%f|\n", 33.0/*(double)0000042*/);
	ft_printf("%.1f\n", 51651332165.0);
	ft_printf("%.10f\n", 0.0);
	ft_printf("%.15f\n", 0.1);
	ft_printf("%.15Lf\n", 0.000000000005153105l);
	//printf("%.10Lf\n", 123456789012345678901234567890.1234567l);
	/*printf("%u\n", f.parts.exponent);
	printf("%u\n", f.parts.mantisa);
	printf("%u\n", d.parts.exponent);
	printf("%u\n", d.parts.mantisa);*/
	/*while (1)
		ft_printf("^.^/%9lc^.^/", 'E');*/
	/*printf("%.100Lf\n", ld.f);
	ld.f = 151212456416541564165341683416541654165416.3112;
	printf("%Lf\n", ld.f);*/
	return (0);
}
