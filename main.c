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
	//printf("^.^/%57lc^.^/\n", (char)0);
	for (int i = 0; i < 100000; i++)
		ft_printf("^.^/%lc^.^/\n", i);
	/*printf("{%f}{%lf}{%Lf}\n", 1444565444646.6465424242242, 1444565444646.6465424242242, 1444565444646.6465424242242l);
	ft_printf("{%f}{%lf}{%Lf}\n", 1444565444646.6465424242242, 1444565444646.6465424242242, 1444565444646.6465424242242l);*/
	return (0);
}
