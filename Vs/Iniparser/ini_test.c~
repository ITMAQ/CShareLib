/*
 * ini_test.c
 *
 *  Created on: Apr 13, 2018
 *      Author: lgh
 */
#include <stdio.h>
#include <stdlib.h>
#include "iniparser.h"

int main(void)
{
	dictionary *ini;
	int n = 0;
	char *str;

	ini = iniparser_load("/.../test.ini"); //添加test.ini的绝对路径；
	if (ini == NULL)
	{
		fprintf(stderr, "can not open %s", "test.ini");
		exit(EXIT_FAILURE);
	}

	printf("----------------------------------------------\n");
	//iniparser_dump(ini,stderr);    //save ini to stderr

	//    printf("\n%s:\n",iniparser_getsecname(ini,0)); //get section name
	//    printf("%d\n",iniparser_getnsec(ini));
	//    printf("number of keys in a section====== %d\n" ,iniparser_getsecnkeys(ini, "serial port"));

	n = iniparser_getint(ini, "tcp:port", -1);
	printf("port : %d\n", n);

	//    str = iniparser_getstring(ini,"tcp:ip","null");
	//    printf("ip : %s\n",str);
	//
	//    str = iniparser_getstring(ini,"tcp:family","null");
	//    printf("family : %s\n",str);
	//
	//    printf("\n%s:\n",iniparser_getsecname(ini,1));
	//    n = iniparser_getint(ini,"serial port:speed", -1);
	//    printf("speed : %d\n",n);

	iniparser_freedict(ini);
	return 0;
}


