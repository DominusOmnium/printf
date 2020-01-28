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
	//printf("^.^/%57lc^.^/\n", (char)0);
	for ( double i = 0.2134345123; i < 1000; i += 0.001)
		printf("%.20f\n", i);
	/*ft_printf("%.35f\n",  989.624434495810419321060180664063);
	printf("%.35f\n",  989.624434495810419321060180664063);*/
	//printf("%C\n", L'☕');
	//printf("%015s\n", "+qwe");
	/*printf("{%f}{%lf}{%Lf}\n", 1444565444646.6465424242242, 1444565444646.6465424242242, 1444565444646.6465424242242l);
	ft_printf("{%f}{%lf}{%Lf}\n", 1444565444646.6465424242242, 1444565444646.6465424242242, 1444565444646.6465424242242l);*/
	return (0);
}
