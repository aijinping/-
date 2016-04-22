#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test(char *scrFileUrl, char *destFileUrl);
int hideInfo(char *scrFileUrl, char *destFileUrl, char *str);
void getInfo(char *scrFileUrl, char *destSecretUrl, int n);

void main()
{

/*	char secretInfo[40] = "you are die";
	FILE *inFile;
	FILE *outFile;
	inFile = fopen("D:\\filetest\\timg.bmp", "rb");
	outFile = fopen("D:\\filetest\\timg2.bmp", "wb");
	if(inFile == NULL)
	{
		printf("open file failed\n");
		return;
	}
	
	char c;
	for (;!feof(inFile);)
	{
		c = fgetc(inFile);
		
		fputc(c, outFile);
	}
	
	fclose(outFile);
	fclose(inFile);*/
//	test("D:\\filetest\\24Bit.bmp", "D:\\filetest\\24Bit2.bmp.bmp");
	int n = hideInfo("D:\\filetest\\24Bit.bmp", "D:\\filetest\\24Bit2.bmp", "D:\\filetest\\pic.bmp");
	getInfo("D:\\filetest\\24Bit2.bmp", "D:\\filetest\\pic2.bmp", n);
}

int hideInfo(char *scrFileUrl, char *destFileUrl, char *secretFileUrl)
{
	char *buff = (char*)malloc(1024 * 500);
	FILE *inFile;
	FILE *outFile;
	FILE *secFile;
	inFile = fopen(scrFileUrl, "rb");
	outFile = fopen(destFileUrl, "wb");
	secFile = fopen(secretFileUrl, "rb");
	if(inFile == NULL)
	{
		printf("open srcFile failed\n");
		return 0;
	}
	if(secFile == NULL)
	{
		printf("open secretFile failed\n");
		return 0;
	}
	
	char c;
	int i;
	for (i=0; !feof(secFile);i++)
	{
		buff[i] = getc(secFile);
	}
	int size=i;    //secFile×Ö½ÚÊý

	int j=0;
	int k=0;
	printf("%d", size);
	for (i=0; !feof(inFile);i++)
	{
		c = fgetc(inFile);
		if(i > 64 && j < size)
		{
			c = (c&0xfe) + ((buff[j]>>k)&0x01);
			k++;
			if(k>=8)
			{
				k=0;
				j++;
			}
		}
		fputc(c, outFile);
	}
	
	free(buff);
	fclose(outFile);
	fclose(secFile);
	fclose(inFile);

	return size;
}

void getInfo(char *scrFileUrl, char *destSecretUrl, int n)
{
	char *buff = (char*)malloc(1024 * 500);

	FILE *inFile;
	FILE *outFile;

	inFile = fopen(scrFileUrl, "rb");
	outFile = fopen(destSecretUrl, "wb");

	if(inFile == NULL)
	{
		printf("open srcFile failed\n");
		return;
	}
	
	char c;
	int i;
	int j=0;
	int k=0;
	buff[0]=0;
	for (i=0; !feof(inFile);i++)
	{
		c = fgetc(inFile);
		if(i > 64 && j < n)
		{
//			c = (c&0xfe) + ((buff[j]>>k)&0x01);
			buff[j] = buff[j] + ((c&0x01)<<k);
			k++;
			if(k>=8)
			{
				k=0;
				j++;
				buff[j] = 0;
			}
		}
	}

	for (i=0; i<n; i++)
	{
		fputc(buff[i], outFile);
	}
	
	free(buff);
	fclose(outFile);
	fclose(inFile);
}

void test(char *scrFileUrl, char *destFileUrl)
{
	FILE *inFile;
	FILE *outFile;
	inFile = fopen(scrFileUrl, "rb");
	outFile = fopen(destFileUrl, "wb");
	if(inFile == NULL)
	{
		printf("open srcFile failed\n");
		return;
	}
	
	int i;
	char c;
	char d;
	for (i=0; !feof(inFile); i++)
	{
		c = fgetc(inFile);
		if(i > 64)
			c = c&0xfe+1;
		fputc(c, outFile);
	}

	fclose(outFile);
	fclose(inFile);
}

