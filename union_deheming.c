#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void kontrolbit(int *kod, int lengh)
{
    int i = 0, summ = 0, errorpos = 0;
    while(i < lengh)
    {
        if((i+1 == 1)||(i+1 == 2)||(i+1 == 4)||(i+1 == 8)||(i+1 == 16)||(i+1 == 32)||(i+1 == 64))
        {
            int start = i;
            while(start < lengh)
            {
                for(int g = 0; g < i + 1; g++)
                {
                    if((start+g != i)&&(start+g < lengh))
                        summ = summ + kod[start+g];
                }
                start = start + i + i + 2;
            }
            if(kod[i] != summ%2)
            {
                errorpos = errorpos + i;
            }
            summ = 0;
        }
        i++;
    }
    if(errorpos != 0)
    {
        if(kod[errorpos] == 0)
            kod[errorpos] = 1;
        else
            kod[errorpos] = 0;
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

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s input.hmng output.file [8/12/16/32/64]\n", argv[0]);
        return 0;
    }
    FILE *f = fopen(argv[1], "rb");
    FILE *t = fopen(argv[2], "w+b");
    int byte[8];
    printf("coded: %s\n", argv[1]);
    printf("file: %s\n", argv[2]);
    int c = 8;
    if (argc > 3) c = atoi(argv[3]);
    printf("decoding length: %d\n\n", c);
    if(c == 8)
    {
        int x, kod[12], g = 0;
        while(fgetc(f) != EOF)
        {
            fseek(f, -1, SEEK_CUR);
            x = fgetc(f);
            tobit(x, byte);
            for(int i = 0; i < 8; i++)
            {
                if((i != 0)&&(i != 1))
                    kod[g++] = byte[i];
            }
            if(g == 12)
            {
                kontrolbit(kod, 12);
                g = 0;
                for(int i = 0; i < 12; i++)
                {
                    if((i+1 != 1)&&(i+1 != 2)&&(i+1 != 4)&&(i+1 != 8))
                    {
                        byte[g++] = kod[i];
                    }
                }
                fputc(todec(byte), t);
                g = 0;
            }
        }
    }
    else if(c == 12)
    {
        int tmp[4], x, kod[17], g = 0, flag = 0, schet = 0;
        while(fgetc(f) != EOF)
        {
            fseek(f, -1, SEEK_CUR);
            x = fgetc(f);
            tobit(x, byte);
            kod[g] = byte[7];
            g++;
            if(g == 17)
            {
                g = 0;
                kontrolbit(kod, 17);
                g = 0;
                if(flag == 1) //костыль
                {
                    for(int i = 0; i < 4; i++)
                    {
                        byte[g++] = tmp[i];
                    }
                    flag = 0;
                }
                for(int i = 0; i < 17; i++)
                {
                    if((i+1 != 1)&&(i+1 != 2)&&(i+1 != 4)&&(i+1 != 8)&&(i+1 != 16)&&(i+1 != 32)&&(i+1 != 64))
                        byte[g++] = kod[i];
                    if(g == 8)
                    {
                        fputc(todec(byte), t);
                        g = 0;
                        if((flag == 0)&&(schet%2 == 0)) //костыль 2
                        {
                            for(int i = 12; i < 17; i++)
                            {
                                if(i+1 != 16)
                                {
                                    tmp[g++] = kod[i];
                                }
                            }
                            flag = 1;
                        }
                        g = 0;
                    }
                }
                g = 0;
            }
            schet++; //костыль 3
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
                if(i != 0)
                    kod[g++] = byte[i];
            }
            if(g == 21)
            {
                kontrolbit(kod, 21);
                g = 0;
                for(int i = 0; i < 21; i++)
                {
                    if((i+1 != 1)&&(i+1 != 2)&&(i+1 != 4)&&(i+1 != 8)&&(i+1 != 16)&&(i+1 != 32)&&(i+1 != 64))
                        byte[g++] = kod[i];
                    if(g == 8)
                    {
                        fputc(todec(byte), t);
                        g = 0;
                    }
                }
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
                if((i == 6)||(i == 7))
                    kod[g++] = byte[i];
            }
            if(g == 38)
            {
                kontrolbit(kod, 38);
                g = 0;
                for(int i = 0; i < 38; i++)
                {
                    if((i+1 != 1)&&(i+1 != 2)&&(i+1 != 4)&&(i+1 != 8)&&(i+1 != 16)&&(i+1 != 32)&&(i+1 != 64))
                        byte[g++] = kod[i];
                    if(g == 8)
                    {
                        fputc(todec(byte), t);
                        g = 0;
                    }
                }
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
                if(i == 7)
                    kod[g++] = byte[i];
            }
            if(g == 71)
            {
                kontrolbit(kod, 71);
                g = 0;
                for(int i = 0; i < 71; i++)
                {
                    if((i+1 != 1)&&(i+1 != 2)&&(i+1 != 4)&&(i+1 != 8)&&(i+1 != 16)&&(i+1 != 32)&&(i+1 != 64))
                        byte[g++] = kod[i];
                    if(g == 8)
                    {
                        fputc(todec(byte), t);
                        g = 0;
                    }
                }
            }
        }
    }
    else
    {
        printf("Error: bad decoding length %d, maybe 8/12/16/32/64\n\n", c);
    }
    fclose(f);
    fclose(t);
    return 0;
}
