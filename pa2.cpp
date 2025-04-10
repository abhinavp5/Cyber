#include <iostream>
#include <string>
#include <random>
#include <cmath>
#include <vector>

using namespace std;

/*
Function that returns the modular exponentiation of base^exp mod mod
*/
long long modPow(long long base, long long exp, long long mod) {
    __int128 result = 1;
    __int128 b = base % mod;

    while (exp > 0) {
        if (exp & 1) {
            result = (result * b) % mod;
        }
        b = (b * b) % mod;
        exp >>= 1;
    }

    return (long long)result;
}


/*
Function that returns the modular inverse of a and m
*/
long long modInverse(long long a, long long m){
    long long m0 = m, y = 0, x = 1;
    if (m == 1) return 0;
    while (a > 1){
        long long q = a / m;
        long long t = m;
        m = a % m, a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    return (x % m0 + m0) % m0; 
}

/*
Function that generates a random Prime Number betwee 0 and 1000000)
*/
long long generate_prime(){
    //seeding random number
    random_device rd;
    mt19937 gen(rd());  // using the Mersenne Twister Engine to Produce unbiased Random Numbers
    uniform_int_distribution<> distrib(1, 999999);//generate num in range inclusive
    bool isPrime = false;
    int firstPrimes [7] = {2,3,5,7,11,13,17};
    
    while (!isPrime){
        //1. generating a random number
        long long prime = distrib(gen);

        //2. checking w/ the first 7 primes
        bool divisible = false;
        for (int pn : firstPrimes){
            if (prime % pn == 0 && prime != pn){
                divisible = true;
                break;
            }
        }
        
        if (divisible) {
            continue; // Try another number if divisible by any of the first primes
        }

        //3. Miler Rabin 
        long long temp = prime-1; 
        long long k = 1; 
        while ((temp / (1LL << k)) <= prime && temp % (1LL << k) == 0) {
            k++;
        }
        k--;
        long long m = temp / (1LL << k);

        //choosing a value for a between 1 and n
        long long a = 2; 

        long long b0 = modPow(a, m, prime); // Using modPow instead of pow for modular exponentiation
        
        //checking for primality
        if(b0 == prime-1 || b0 == 1){
            isPrime = true;
            return prime;
        }
        //reaching here means the number failed the primality test
        
    }
    
    // should never reach here
    return -1;
}


/*
Encryption functino: return Ciphertext
*/

vector<long long> encrypt(string msg, long long e, long long n) {
    vector<long long> cipherText;
    //iterating through message
    for (char c: msg){
        long long aValue = static_cast<int>(c); //casting char to int
        long long encrypt = modPow(aValue, e, n); // aValue^e mod n
        cipherText.push_back(encrypt);
    }

    return cipherText;
}


string decrypt(vector<long long> cipherText, long long d, long long n ){
    string res;
    for (long long c : cipherText) {
        long long decipheredAscii = modPow(c, d, n);
        
        // Append only printable characters
        if (decipheredAscii >= 32 && decipheredAscii <= 126) {
            res += static_cast<char>(decipheredAscii);
        } else {
            res += '*'; // Placeholder for invalid characters
        }
    }
    return res;
}


int main(){
    string M;
    cout << "Enter a Message: ";
    getline(cin, M);

    //RSA values of Algorithm
    long long p = generate_prime();
    long long q = generate_prime();
    long long n = p*q;
    long long r = (p-1) * (q-1);  //phi or to
    long long e = 65537; //predefined encryption exponenet
    long long d = modInverse(e, r); //private key --> d = e^-1 mod r

    cout << "p:" << p << endl;
    cout << "q:" << q << endl; 
    cout << "e:" << e << endl; 
    cout << "d:" << d << endl; 

    //encrypting the message
    vector<long long> cipherText = encrypt(M, e, n);

    //printing the encrypted message
    cout << "Ciphertext: [";
    for (int i = 0; i< cipherText.size();i++){
        cout << cipherText[i];
        if (i != cipherText.size()-1){
            cout << ", ";
        }
    }
    cout << "]" << endl;// for the final value

    string decipheredText  = decrypt(cipherText, d, n); 

    cout<< "Decrypted message: " << decipheredText << endl;

}
