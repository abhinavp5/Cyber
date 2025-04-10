#include <iostream>
#include <string>
#include <random>
#include<math>
#include <vector>

using namespace std;


/*
Function that generates a random Prime Number betwee 0 and 1000000)
*/
int generate_prime(){
    //seeidng random number
    random_device rd;
    mt19937 gen(rd());  // using the Erse Twister Engine to Produce unbiased Random Numbers
    uniform_int_distribution<> distrib(1, 999999);//genate num in range inclusive
    bool isPrime = false;
    int firstPrimes [7] = {2,3,5,7,11,13,17};
    
    while (!isPrime){
        //1. generating a random number
        int prime = distrib(gen);

        //2. checking w/ the first 7 primes
        for (int pn : firstPrimes){
            if (prime%pn == 0 ){
                continue; //go back upto the top of loop
            }
        }


        //3. Miler Rabin 
        int temp = prime-1; 
        int k =1; 
        while (temp/ pow(2,k) <= prime && temp% pow(2,k) ==0 ){
            k++;
        }
        k--; 
        int m = temp/ pow(2,k);

        //chossing a value for a between 1 and n
        int a = 2; 

        int b0 = pow(2,m) % prime;
        
        //checking for primality
        if(b0 == -1 || b0== 1){
            return prime;
        }
    }

}


/*
Encryption functino: return Ciphertext
*/
vector<int> encrypt(string msg, int e, int n ){
    vector<int> cipherText;
    //iterating through message
    for (char c: msg){
        int aValue = static_cast<int>(c):
        int encrypt = pow(aVlaue, e) %n ; 
        cipherText.push_back(encrypt);
    }

    return cipherText;
}

/*
Decryption Function: return ciphered text
*/
string decrypt(int cipherText, int d, int n ){

}

int main(){
    string M;
    cout << "Enter a Message" << endl;
    cin >> M;


    //RSA values of Algorithm
    int p = generate_prime();
    int q = generater_prime();
    int n = p*q;
    int r = (p-1) * (q-1);  //phi or to
    int e = 65537; //predefined encryption exponenet
    int d = pow(e, -1) % r; //private key

    cout << "p:" << p << endl;
    cout << "q:" << q << endl; 
    cout << "e:" << e << endl; 
    cout << "d:" << d << endl; 

    //encrypting the message
    vector<int> cipherText = encrypt(M, e, n);

    //printing the encrypted message
    cout << "Ciphertext: [";
    for (int i = 0; i< vectorLength(cipherText)-1;i++){
        cout << cipherText[i] << ", ";
    }
    cout<< cipherText[i-1] << "]";// for the final value


    






}
