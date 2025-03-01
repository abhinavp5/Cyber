#include <iostream>
#include <string>
#include <ctime>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;



static void scan(const string& target, int start, int end);
static bool port_is_open(const string& address, int port);
void timeout_handler(int signum);

int main() {

    string address;
    int port_start;
    int port_end;

    cout << "Enter a target to scan: " << flush;
    cin >> address;

    cout << "Please enter the range of ports you want to scan\n" << flush;
    cout << "Enter a start port: " << flush;
    
    // Validate that input is an integer
    while (!(cin >> port_start)) {
        cout << "Enter a valid Port Number: " << flush;
    }

    cout << "Enter an end port: " << flush;
    
    // Validate that input is an integer
    while (!(cin >> port_end)) {
        cout << "Enter a valid Port Number: " << flush;
    }
    // Call scan function
    scan(address, port_start, port_end);
    return 0;
}


//event-handler for timeout
void timeout_handler(int signum){
    cout<< "Target Scan Time Out, Prorgam Shutting Down...";
    exit(1);
}

static void scan(const string& target, int start, int end) {
    //timeout handler
    signal(SIGALRM, timeout_handler);
    alarm(3);//trigger syscall if the progams scans for too long

    //getting the timestamp
    time_t timestamp;
    time(&timestamp);
    cout << "Scanning started at: " <<  ctime(&timestamp);

    //stucutres to store ip address (server) along with port
    struct sockaddr_in addr;
    struct sockaddr_in target_addr;
    int sock =0 ; 
    memset(&target_addr, '0', sizeof(target_addr));//sets target addr to all 0s
    target_addr.sin_family = AF_INET;

    //binary conversoin of ip address
    if (inet_pton(AF_INET, target.c_str(), &target_addr.sin_addr) <= 0) {
        cout << "Error while convering to binary" << endl;
    }

    for (int i = start; i <= end; ++i) {

        target_addr.sin_port = htons(i);
        //attempting to setup a new socket
        int sock = socket(AF_INET, SOCK_STREAM,0);
        if (sock == -1){
            cerr << "Failed to create socket";
            continue; 
        }
        
        //attempting to connect
        if(connect(sock, (struct sockaddr*)&target_addr, sizeof(target_addr)) < 0 ){
            cout <<"Port " << i << " closed" << endl;
        } else{
            cout << "Port " << i << " open" << endl;
        }

        close(sock);
    }
    cout << "Port Scanning Completed" << endl;
}

