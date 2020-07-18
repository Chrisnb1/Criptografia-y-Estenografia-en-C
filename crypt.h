#ifndef CRYPTH
#define CRYPTH
#include<stdio.h>
#include<math.h>

int gcd(int a, int h);
double *Encryption();
void Decryption(double *cifrado);

//Arreglo con el msj cifrado
double cifrado[7];

// Returns gcd of a and b
int gcd(int a, int h)
{
    int temp;
    while (1)
    {
        temp = a%h;
        if (temp == 0)
          return h;
        a = h;
        h = temp;
    }
}

// Code to demonstrate RSA algorithm
double *Encryption(){
    int i;
    double msg[7] = {6,0,13,3,0,11,5};
    double *msgC;
    // Two random prime numbers
    double p = 3;
    double q = 7;
    // First part of public key:
    double n = p*q;
    // Finding other part of public key.
    // e stands for encrypt
    double e = 2;
    double phi = (p-1)*(q-1);
    while (e < phi)
    {
        // e must be co-prime to phi and
        // smaller than phi.
        if (gcd(e, phi)==1)
            break;
        else
            e++;
    }
    // Private key (d stands for decrypt)
    // choosing d such that it satisfies
    // d*e = 1 + k * totient
    int k = 2;  // A constant value
    double d = (1 + (k*phi))/e;
    // Encryption c = (msg ^ e) % n
    for(i=0; i<(sizeof(msg)/sizeof(msg[0])); i++)
    {
        double c = pow(msg[i], e);
        c = fmod(c, n);        
        printf("\nEncrypted data = %lf", c);
        cifrado[i] = c;
    }
    msgC = cifrado;
    return msgC; 
}

void Decryption(double *cifrado){
    int i;
    // Two random prime numbers
    double p = 3;
    double q = 7;

    // First part of public key:
    double n = p*q;

    // Finding other part of public key.
    // e stands for encrypt
    double e = 2;
    double phi = (p-1)*(q-1);
    while (e < phi)
    {
        // e must be co-prime to phi and
        // smaller than phi.
        if (gcd(e, phi)==1)
            break;
        else
            e++;
    }

    // Private key (d stands for decrypt)
    // choosing d such that it satisfies
    // d*e = 1 + k * totient
    int k = 2;  // A constant value
    double d = (1 + (k*phi))/e;

    // Decryption m = (c ^ d) % n
    for(i=0; i<7; i++)
    {
        double m = pow(cifrado[i], d);
        m = fmod(m, n);
        printf("\nOriginal Message Sent = %lf", m);
    } 
    
}

#endif
