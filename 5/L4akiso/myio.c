//na podstawie książki Język C Programowanie Kernighan, Ritchie
//12.12.2015
//Jacek Mucha

#include <stdarg.h>
#include <stdlib.h>


char *dec(int liczba, int len, char * text)
{
	int i;

	for(i=len-1;i>=0;i--)
	{
		text[i]='0'+liczba%10;
		//printf("%d",liczba%10);
		liczba=liczba/10;
	}
	text[len]='\0';
	return text;
}

char *bin(int liczba,int len, char * text)
{
	int i;
	for(i=len-1;i>=0;i--)
	{
		text[i]='0'+liczba%2;
		liczba=liczba/2;
	}
	text[len]='\0';
	return text;
}

char *hex(int liczba,int len, char * text)
{
	int i,reszta;
	for(i=len-1;i>=0;i--)
	{
		reszta=liczba%16;
		if(reszta<10)
			text[i]='0'+reszta;
		else
		{
			switch(reszta)
			{
				case 10:
					text[i]='a';
					break;
				case 11:
					text[i]='b';
					break;
				case 12:
					text[i]='c';
					break;
				case 13:
					text[i]='d';
					break;
				case 14:
					text[i]='e';
					break;
				case 15:
					text[i]='f';
					break;
				default:
					break;
			}
		}
		liczba=liczba/16;
	}
	text[len+1]='\0';
	//printf("%s",text);
	return text;
}

void myprintf(char *fmt,...)
{
	va_list ap; //wskazuje na kolejne nienazwane argumenty
	char *p, *sval;
	int ival,ivalx,ivalb,len;

	va_start(ap,fmt);

	for(p=fmt; *p; p++)
	{
		if(*p!='%')
		{
			write(1,p,1);
			continue;
		}
		switch(*++p){
			case 100: //d
				ival=va_arg(ap,int);
				len=0;
				int it3=ival;
				while(it3>0)
				{
					len++;
					it3=it3/10;
				}
				char text[100];
				dec(ival,len,text);
				write(1,text,len);
				//free(text);
				break;
			case 115: //s
				len=0;
				sval=va_arg(ap,char *);
				while(sval[len]!='\0') len++;
				write(1,sval,len);
				break;
			case 120: //x
				ivalx=va_arg(ap,int);
				int it2=ivalx,cyfry=0;
				while(it2>0)
				{
					it2=it2/16;
					cyfry++;
				}
				char text2[100];
				hex(ivalx,cyfry,text2);
				write(1,text2,cyfry);
				//free(text2);
				break;
			case 98: //b
				ivalb=va_arg(ap,int);
				int it=ivalb,cyfry2=0;
				while(it>0)
				{
					it=it/2;
					cyfry2++;
				}
				char text3[100];
				bin(ivalb,cyfry2,text3);
				write(1,text3,cyfry2);
				//free(text3);
				break;
			default:
				write(1,*p,1);
				break;
		}
	}
	va_end(ap);
}
//################################  do myscanf  #####################
int scdec( char *s)
{
	int dec=0;
	//myprintf("scdec arg: %s\n",s);
	int i;
	for(i=0;s[i]!='\0' && s[i]>='0' && s[i]<='9';i++)
		dec=10*dec+(s[i]-'0');
	return dec;
}

int schex(char *s)
{
	int x=0,i;
	//myprintf("schex arg: %s\n",s);
	for(i=0;s[i]!='\0';i++)
		if(s[i]>='0' && s[i]<='9')
			x=16*x+(s[i]-'0');
		else if	(s[i]>='a' && s[i]<='f')
			x=16*x+s[i]-'a'+10;
	return x;
}

int scbin(char *s)
{
	int b=0,i=0;
	//myprintf("scbin arg: %s\n",s);
	while(s[i]=='0' || s[i]=='1')
	{
		b=2*b+s[i]-'0';
		i++;
	}
	return b;
}

void myscanf(char *format,...)
{
	va_list ap;
	int *ival, *ival2, *ival3,i,temp;
	char *cval;
	va_start(ap,format);
	while(*format)
	{
		if(*format=='%')
		{
			*format++;
			switch(*format++)
			{
				case 's':
					cval=va_arg(ap,char *);
					char s[1024];
					read(0,s,1024);
					i=0;
					while(s[i]!='\n')
					{
						cval[i]=s[i];
						i++;
					}
					//cval[i+1]='\0';
					break;
				case 'd':
					;char s2[1024];
					temp=0;
					//ival=malloc(sizeof(int*));
					ival=va_arg(ap,int*);
					sleep(3);
					read(0,s2,124);
					temp=scdec(s2);
					*ival=temp;
					break;
				case 'x':
					;char s3[1024];
					ival2=va_arg(ap,int *);
					read(0,s3,124);
					*ival2=schex(s3);		
					break;
				case 'b':
					;char s4[1024];
					ival3=va_arg(ap,int *);
					read(0,s4,124);
					temp=0;
					temp=scbin(s4);
					*ival3=temp;	
					break;
				default:
					break;
			}
		}
		else *format++; //bo format jest specyfikacją wejścia, a nie wejściem
	}
}
//##################### Testowanie ##################################
int main()
{
	myprintf("Ala ma kota\n");
	char *s=", ale nie ma psa\n";
	int d=1+2+4+8,e=15;
	
	myprintf("Aleksander ma piłkę%s \n",s);
	myprintf("d=%d\n",d);
	myprintf("%b=d\n",d);
	myprintf("e=%x\n",e);
	int u=2222;
	char *s2="oto jest liczba";
	myprintf("%s\n%b\n%d\n%x\nliczba jest duża\nPodaj napis\n",s2,u,u,u);

	char * s3=malloc(sizeof(char)*256);
	myscanf("%s",s3);
	myprintf("s3: %s\nPodaj Liczbe ",s3);
	myscanf("podałeś %d",&u);
	myprintf("%d\nPodaj liczbe w postaci binarnej ",u);
	myscanf("%b",&u);
	myprintf("Podales %b %d %x\n",u,u,u);
	return 0;
}












