#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#ifndef REAL
#define F r += ft_printf
#else
#define F r += printf
#endif

size_t ft_strlen(char *s)
{
	size_t len;
	len=0;
	while(s[len])
	len++;
	return(len);
}

int ft_counter(long long num,int base_len)
{
	int ct=1;
	while(num>=base_len||num<=-base_len)
	{
		num=num/base_len;
		ct++;
	}
	return(ct);
}

void ft_putnum(long long num,int base_len,char *base)
{
	if(num>=base_len)
		ft_putnum(num/base_len,base_len,base);
	write(1,&base[num%base_len],1);
}

int	ft_printf(char *format, ...)
{
	va_list lst;
	char *s,*base;
	long num;
	int pos = 0,ct = 0,neg = 0,zero = 0,space = 0,width = 0,p_range = 0,pocision = 0,ret = 0,base_len = 0;
	va_start(lst,format);
	while(format[pos])
	{
		if(format[pos]=='%')
		{
			pos++;
			ct = 0,neg = 0,space = 0,width = 0, p_range = 0,pocision = 0,zero = 0;
			while(format[pos]>='0'&&format[pos]<='9')
			{
				width = width * 10 + (format[pos] - 48);
				pos++;
			}
			if(format[pos]=='.')
			{
				pos++;
				pocision = 1;
				while(format[pos]>='0'&&format[pos]<='9')
				{
				p_range = p_range * 10 +(format[pos] - 48);
				pos++;
				}
			}
			if(format[pos]=='s')
			{
				s = va_arg(lst,char *);
				if(!s)
				s = "(null)";
				ct = ft_strlen(s);
			}
			else if(format[pos]=='x')
			{
				num = va_arg(lst,unsigned int);
				base = "0123456789abcdef";
				base_len = 16;
				ct = ft_counter(num,base_len);
			}
                        else if(format[pos]=='d')
                        {
                                num = va_arg(lst,int);
                                base = "0123456789";
                                base_len = 10;
                                ct = ft_counter(num,base_len);
				if(num < 0)
				{
				num=-num;
				neg=1;
				}
                        }
			if(pocision && p_range > ct && format[pos] != 's')
			zero = p_range - ct;
			if(pocision && p_range < ct && format[pos] == 's')
			ct = p_range;
                        if(pocision && !p_range && (format[pos] == 's' || !num))
			ct = 0;
			space = width - zero - ct - neg;
			while(space-->0)
			{
				write(1," ",1);
				ret++;
			}
                        if(neg)
                        {
				write(1,"-",1);
				ret++;
                        }
                        while(zero-->0)
                        {
				write(1,"0",1);
				ret++;
                        }
			if(format[pos]=='s')
				write(1,s,ct);
			else if(ct)
				ft_putnum(num,base_len,base);
			ret += ct;
			pos++;
		}
		else
		{
		write(1,&format[pos],1);
		pos++;
		ret++;
		}
		
	}
return(ret);
}

int main ()
{
    printf("----> Mio\n");
    printf("\n%d\n", ft_printf("holala %d %s %x", -12, "42\0", 13));
    printf("----> Original\n");
    printf("\n%d\n", printf("holala %d %s %x", -12, "42\0", 13));
    return(0);
}
