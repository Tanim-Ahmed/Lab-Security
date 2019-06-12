#include<iostream>
#include <stdlib.h>
//#include <gmpxx>
#include<stdio.h>
#include <gmp.h>
#include<set>
#include <sstream>
#include <string>
#include<cmath>
#include <unistd.h>
#include <fcntl.h>
using namespace std;
void get_random_n_bits(mpz_t r, size_t bits)
{
    size_t size = (size_t) ceilf(bits/8);
    char *buffer = (char*) malloc(sizeof(char)*size);
    int prg = open("/dev/random", O_RDONLY);
    read(prg, buffer, size);
    close(prg);
    mpz_import (r, size,1,sizeof(char), 0,0, buffer);
    free(buffer);
}

mpz_t p,d,E2,generator,R,C1,C2,msg,de_msg,temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8,one,output,t1;
mpz_in()
{

    mpz_init(p);
    mpz_init(d);
    mpz_init(E2);
    mpz_init(generator);

    mpz_init(C1);
    mpz_init(C2);
    mpz_init(msg);
    mpz_init(de_msg);
    mpz_init(temp1);
    mpz_init(temp2);
    mpz_init(temp3);
      mpz_init(temp4);
      mpz_init(temp5);
      mpz_init(temp6);
        mpz_init(temp7);
       mpz_init(temp8);
    mpz_init(one);
    mpz_init(output);
    mpz_init(t1);


}
mpz_clr()
{
    mpz_clear(p);
    mpz_clear(d);
    mpz_clear(E2);
    mpz_clear(generator);

    mpz_clear(C1);
    mpz_clear(C2);
    mpz_clear(msg);
    mpz_clear(de_msg);
    mpz_clear(temp1);
    mpz_clear(temp2);
    mpz_clear(temp3);
    mpz_clear(temp4);
    mpz_clear(temp5);
     mpz_clear(temp6);
      mpz_clear(temp7);
       mpz_clear(temp8);
    mpz_clear(one);

    mpz_clear(output);
    mpz_clear(t1);


}

int prime_num()
{
    mpz_in();
    int PRIMESIZE;
    cout<<"Enter No of bits for P and Q: ";
    cin>>PRIMESIZE;

    char* p_str = new char[PRIMESIZE+1];

    p_str[0] = '1';

    for(int i=1; i<PRIMESIZE; i++)
    {
        p_str[i] = char((rand()%2)+48);

    }
    p_str[PRIMESIZE] = '\0';

    mpz_set_str(p,p_str,2);

    mpz_nextprime(p,p);
    printf("prime number = [%s]\n", mpz_get_str(NULL,10,p));

    do
    {
        get_random_n_bits(generator,mpz_sizeinbase(p,2));
        mpz_nextprime(generator,generator);
    }
    while (mpz_cmp(generator,p)>=0);

    printf("generator number = [%s]\n", mpz_get_str(NULL,10,generator));

    do
    {
        printf("Enter a private number: ");
        char dd[1024];
        cin>>dd;
        mpz_set_ui(d,0);
        mpz_set_str(d,dd,10);
    }
    while(!(mpz_cmp(d, p) < 0) );



    printf("private number = [%s]\n", mpz_get_str(NULL,10,d));
    mpz_set_ui(one,1);

    mpz_powm(E2,generator,d,p);

    do
    {
        printf("Enter a random number: ");
        char RR[1024];
        cin>>RR;
        mpz_set_str(R,RR,10);
    }
    while(!(mpz_cmp(R, p) < 0) );






    mpz_powm(C1,generator,R,p);

    do
    {
        printf ("Enter your msg: ");
        char msg2[1024];
        cin>>msg2;
        mpz_set_str(msg,msg2,10);
    }
    while(!(mpz_cmp(msg, p) < 0) );



    printf("Original Message = [%s]\n", mpz_get_str(NULL,10,msg));

/*
    mpz_powm(temp1,E2,R,p);
    mpz_mul(temp2,msg,temp1);
    mpz_powm(C2,temp2,one,p);
    */
    mpz_mul(temp2,d,temp1);
    mpz_mod(temp2,temp2,p-1);
    mpz_sub(temp3,msg,temp2);
    mpz_mod(temp3,temp3,p-1);
mpz_invert(R,R,one);
mpz_mod(R,R,p-1);
mpz_mul(temp4,temp3,R);
mpz_mod(temp4, temp4, p-1);



mpz_powm(temp5,generator,msg,p);
mpz_powm (temp6, E2,  temp1,one);
mpz_powm (temp7, temp1,temp4,one);
mpz_mul(temp8,temp7,temp6);


 if(mpz_cmp(temp5,temp8))
 {
     cout<<"incorrect"<<endl;
 }
 else
 {
     cout<<"correct"<<endl;
 }





}

int main()
{
    prime_num();




}
