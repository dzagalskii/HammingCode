#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int todec(int *byte);
void invert(int *byte);
void tobit(int x, int *byte);
void kontrolbit(int *kod, int lengh);

int main()
{
	FILE *f = fopen("C:/laba/1.txt", "rb"); //файл
	FILE *t = fopen("C:/laba/2.txt", "w+b"); //закодированный файл
	int byte[8];
	printf("file: C:/laba/1.txt\n");
	printf("coded file: C:/laba/2.txt\n\n");
	printf("8 - any length of text\n12 - (length of text)%%3 = 0\n16 - (length of text)%%2 = 0\n32 - (length of text)%%4 = 0\n64 - (length of text)%%8 = 0\n\n");
	printf("select encoding length 8/12/16/32/64: ");
	int c;
	scanf("%d", &c);
	if(c == 8)
	{
		int x, kod[12];
		while(fgetc(f) != EOF)
		{
			fseek(f, -1, SEEK_CUR);
			x = fgetc(f);
			tobit(x, byte);
			int g = 0;
			for(int i = 0; i < 12; i++)
			{
				if((i != 0)&&(i != 1)&&(i != 3)&&(i != 7))
					kod[i] = byte[g++];
				else
					kod[i] = 2;
			}
			kontrolbit(kod, 12);
			g = 0;
			while(g < 12)
			{
				for(int i = 0; i < 8; i++)
				{
					if((i == 0)||(i == 1))
						byte[i] = 0;
					else
						byte[i] = kod[g++];
				}
				fputc(todec(byte), t);
			}
		}
	}
	else if(c == 12)
	{
		int x, kod[17], g = 0, flag = 0;
		while(fgetc(f) != EOF)
		{
			if(flag == 0)
			{
				fseek(f, -1, SEEK_CUR);
				x = fgetc(f);
				tobit(x, byte);
				for(int i = 0; i < 8; i++)
				{
					if((g != 0)&&(g != 1)&&(g != 3)&&(g != 7)&&(g != 15)&&(g != 31)&&(g != 63))
						kod[g++] = byte[i];
					else
					{
						kod[g] = 2;
						g++;
						i--;
					}
				}
				x = fgetc(f);
				tobit(x, byte);
				for(int i = 0; i < 4; i++)
				{
					if((g != 0)&&(g != 1)&&(g != 3)&&(g != 7)&&(g != 15)&&(g != 31)&&(g != 63))
						kod[g++] = byte[i];
					else
					{
						kod[g] = 2;
						g++;
						i--;
					}
				}	
				fseek(f, -1, SEEK_CUR);
				flag = 1;
			}
			else if(flag == 1)
			{
				fseek(f, -1, SEEK_CUR);
				x = fgetc(f);
				tobit(x, byte);
				for(int i = 4; i < 8; i++)
				{
					if((g != 0)&&(g != 1)&&(g != 3)&&(g != 7)&&(g != 15)&&(g != 31)&&(g != 63))
						kod[g++] = byte[i];
					else
					{
						kod[g] = 2;
						g++;
						i--;
					}
				}
				x = fgetc(f);
				tobit(x, byte);
				for(int i = 0; i < 8; i++)
				{
					if((g != 0)&&(g != 1)&&(g != 3)&&(g != 7)&&(g != 15)&&(g != 31)&&(g != 63))
						kod[g++] = byte[i];
					else
					{
						kod[g] = 2;
						g++;
						i--;
					}
				}
				flag = 0;
			}
			if(g == 17)
			{
				kontrolbit(kod, 17);
				g = 0;
				while(g < 17)
				{
					for(int i = 0; i < 8; i++)
					{
						if(i != 7)
							byte[i] = 0;
						else
							byte[i] = kod[g++];
					}
					fputc(todec(byte), t);
				}
				g = 0;
			}
		}
	}
	else if(c == 16)
	{
		int x, kod[21], g = 0;
		while(fgetc(f) != EOF)
		{
			fseek(f, -1, SEEK_CUR);
			x = fgetc(f);
			tobit(x, byte);
			for(int i = 0; i < 8; i++)
			{
				if((g != 0)&&(g != 1)&&(g != 3)&&(g != 7)&&(g != 15)&&(g != 31)&&(g != 63))
					kod[g++] = byte[i];
				else
				{
					kod[g] = 2;
					g++;
					i--;
				}
			}
			if(g == 21)
			{
				kontrolbit(kod, 21);
				g = 0;
				while(g < 21)
				{
					for(int i = 0; i < 8; i++)
					{
						if(i == 0)
							byte[i] = 0;
						else
							byte[i] = kod[g++];
					}
					fputc(todec(byte), t);
				}
				g = 0;
			}
		}
	}
	else if(c == 32)
	{
		int x, kod[38], g = 0;
		while(fgetc(f) != EOF)
		{
			fseek(f, -1, SEEK_CUR);
			x = fgetc(f);
			tobit(x, byte);
			for(int i = 0; i < 8; i++)
			{
				if((g != 0)&&(g != 1)&&(g != 3)&&(g != 7)&&(g != 15)&&(g != 31)&&(g != 63))
					kod[g++] = byte[i];
				else
				{
					kod[g] = 2;
					g++;
					i--;
				}
			}
			if(g == 38)
			{
				kontrolbit(kod, 38);
				g = 0;
				while(g < 38)
				{
					for(int i = 0; i < 8; i++)
					{
						if((i != 6)&&(i != 7))
							byte[i] = 0;
						else
							byte[i] = kod[g++];
					}
					fputc(todec(byte), t);
				}
				g = 0;
			}
		}
	}
	else if(c == 64)
	{
		int x, kod[71], g = 0;
		while(fgetc(f) != EOF)
		{
			fseek(f, -1, SEEK_CUR);
			x = fgetc(f);
			tobit(x, byte);
			for(int i = 0; i < 8; i++)
			{
				if((g != 0)&&(g != 1)&&(g != 3)&&(g != 7)&&(g != 15)&&(g != 31)&&(g != 63))
					kod[g++] = byte[i];
				else
				{
					kod[g] = 2;
					g++;
					i--;
				}
			}
			if(g == 71)
			{
				kontrolbit(kod, 71);
				g = 0;
				while(g < 71)
				{
					for(int i = 0; i < 8; i++)
					{
						if(i != 7)
							byte[i] = 0;
						else
							byte[i] = kod[g++];
					}
					fputc(todec(byte), t);
				}
				g = 0;
			}
		}
	}
	fclose(f);
	fclose(t);
	printf("COMPLETE!");
	getchar();getchar();
	return 0;
}

void kontrolbit(int *kod, int lengh)
{
	int i = 0, summ = 0;
	while(i < lengh)
	{
		if((i+1 == 1)||(i+1 == 2)||(i+1 == 4)||(i+1 == 8)||(i+1 == 16)||(i+1 == 32)||(i+1 == 64))
		{
			int start = i;
			while(start < lengh)
			{
				for(int g = 0; g < i + 1; g++)
				{
					if((kod[start+g] != 2)&&(start+g < lengh))
						summ = summ + kod[start+g];
				}
				start = start + i + i + 2;
			}
			kod[i] = summ%2;
			summ = 0;
		}
		i++;
	}
}

void tobit(int x, int *byte)
{
	for(int i = 0; i < 8; i++)
	{
		byte[i] = x%2;
		x = x/2;
	}
	invert(byte);
}

void invert(int *byte)
{
	int tmp[8], g = 0;
	for(int i = 7; i > -1; i--)
		tmp[g++] = byte[i];
	for(int i = 0; i < 8; i++)
		byte[i] = tmp[i];
}

int todec(int *byte)
{
	int x = 0, st = 7;
	for(int i = 0; i < 8; i++)
	{
		x = x + byte[i]*pow(2, st);
		st--;
	}
	return x;
}