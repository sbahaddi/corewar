/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhourba <akhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 21:57:42 by akhourba          #+#    #+#             */
/*   Updated: 2019/05/02 17:57:11 by akhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdarg.h>

typedef struct	s_flags
{
	int hash;
	int zero;
	int plus;
	int prcsn;
	int minif;
	int minus;
	int space;
}				t_flags;
typedef struct	s_sum
{
	int		i;
	int		j;
	int		sm;

}				t_sum;
typedef struct	s_mu
{
	int i;
	int j;
	int sm;
	int k;
	int l1;
	int l2;

}				t_mu;

typedef struct	s_pow
{
	char	*res;
	int		i;
	char	*tmp;
	char	*x;
}				t_pow;

typedef struct	s_mantissa
{
	char	*res;
	char	*sum;
	char	*multi;
	int		nbrbit;
}				t_mantissa;

typedef struct	s_flt
{
	char	*str;
	char	*bf;
	char	*pown;
	char	*mnts;
	int		p;
}				t_flt;

# define I(nbr)  (nbr - '0')
# define C(nbr) (nbr % 10) + '0'
# define R(nbr) nbr < 9 ? nbr+1 : 0
# define ABS(x) (x < 0 ? x*-1 : x )
# define H(c) ( c != 'c' && TL(c,'f'))
# define TL(c,f) (ft_tolower(c) != f)
# define ATL(c) (TL(c,'c') && TL(c,'f') && TL(c,'s'))

int				ft_printf(const char *restrict format, ...);
int				ft_intlength(long int nbr);
int				ft_intlengh(long long int nbr, int base);
char			ft_searchflag(char *f);
char			*ft_c(char *f, char c, va_list args);
int				ft_indextoskip(char *f);
char			*ft_s(char *f, va_list args, char c);
int				ft_searchonsize(char *f, char c, int isfloat);
char			*ft_di(char *f, va_list args, char c);
int				ft_search_zmps(char *cmdf, char c, int zmp);
char			*ft_itoa_base(long long int x, int bsnbr);
int				ft_glolbal(char *f, va_list args);
char			*ft_globaldi(char *f, va_list args, char c);
char			*ft_globalfe(char *f, va_list args, char c);
char			*ft_strfillwith(t_flags flgs, int len, char *nbr);
void			ft_searchall(char *f, char c, t_flags *ret, va_list args);
char			*ft_strjoindi(t_flags flgs, char *str);
char			*ft_fe(char *f, va_list args, char c, int precision);
int				ft_fintlengh(long double nbr, int base);
char			*ft_strdouble(double x, int precision);
char			*ft_strldouble(long double x, int precision);
char			*ft_mantissa_val(char *bf, int one);
char			*ft_uconvert(char *ptr, int size);
char			*ft_multiple(char *n1, char *n2, char *res);
char			*ft_2power(char *nbr, int pow);
int				ft_biaspower(char *m, int start, int nbr);
char			*ft_sumx(char *nbr1, char *nbr2);
char			*ft_snbrnew(size_t size);
void			ft_setfzero(char *str, size_t size);
char			*ft_point(char *nbr, int pos, int x, int s);
char			*ft_pmanager(char *str, char *mnts, int precision, int p);
int				ft_isrd(int a, int b);
char			*ft_special(char *bf, int nbits);
char			*ft_round(char *nbr, int pr, int p, int np);
int				ft_scan(char *nbr, int pos);
char			*ft_roundnbr(char *res, int r, int x);
int				ft_status(char *f, int nbr);
char			*ft_dxp(char *f, va_list args, char c);
char			*ft_globalpx(char *f, va_list args, char c);
char			*ft_dxph(t_flags flgs, char *str, int len, char c);
char			*ft_strfillwithxp(t_flags flgs, int len, char *nbr);
void			ft_strtrasform(char *str, int y);
char			*ft_uitoa_base(unsigned long long int x, int bsnbr);
int				ft_uintlengh(unsigned long long int nbr, unsigned int base);
char			*ft_globaluo(char *f, va_list args, char c);
char			*ft_uo(char *f, va_list args, char c);
char			*ft_percent(char *f, char c, va_list args);
char			*ft_strfillfeg(t_flags flgs, char *nbr);
void			ft_finstr(char *res, int pr, int p, int np);
void			ft_searchall(char *f, char c, t_flags *ret, va_list args);
int				ft_searchnbr(char *f, char c, int precision);
void			ft_printc(char *str, t_flags flgs, char mc);
size_t			ft_fstrlen(char *s, int f);
char			*ft_fstrjoin(char *s1, char *s2);
char			*ft_fstrdup(char *s2, const char *s1);
void			ft_mulfree(char *s1, char *s2);
int				ft_ispecial(char *str, t_flags	*flgs);
char			*ft_widestring(wchar_t *str);
char			*ft_wchar(char *s, int size);
int				ft_wbinary(char *res);
char			*ft_mask(int wnbr);
char			*ft_wsetmask(char *nbr, char *mask);
int				ft_getsizemask(int wnbr);
char			*ft_widechar(wchar_t wc);
char			*ft_wc(t_flags flgs, va_list args);
char			*ft_strfillxp(t_flags flgs, int len, char *nbr);
int				ft_pow(int nb, int power);
#endif
