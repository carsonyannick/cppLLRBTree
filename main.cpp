/* #include <sys/socket.h> */
#include <netinet/in.h>
#include "LLRBTree.h"
/* #include <stdio.h> */
#include <iostream> 
/* #include <stdlib.h> */
/* #include <sys/types.h> */
#include <string.h>
/* #include <unistd.h> */
#include <signal.h>
#include <unistd.h> // unlink()

/* #include <signal.h> */
/* #include <stdlib.h> */
/* #include <stdio.h> */
#include <sys/un.h>

using namespace std;

const char* socket_name_ = "/tmp/cppLLRBT-socket";
int server_;
/* char* buf_; */

string get_request(int client);
bool send_response(int client, string response);
void handle(int client);
void initalize();
int serve();
void setUpSignalHandler();
void onExit(int);


int main()
{

   LLRBTree<int,int> tree;

   tree.Insert(33, 54);
   tree.Insert(23, 45);
   tree.Insert(113, 45);
   tree.Insert(78, 45);
   tree.Insert(7, 45);

   tree.Insert(423, 425);
   tree.Insert(1413, 45);
   tree.Insert(478, 45);
   tree.Insert(74, 45);

   tree.Insert(4323, 45);
   tree.Insert(1913, 41115);
   tree.Insert(4278, 45);
   tree.Insert(724, 45);

   tree.Insert(3323, 45);
   tree.Insert(9913, 45);
   tree.Insert(2278, 45);
   tree.Insert(2724, 45);

   /* cout << "test " << *tree.Search(1913); */
 initalize();
 serve();

   /* tree.Insert(1, 45); */
   /* tree.Insert(2, 45); */
   /* tree.Insert(3, 45); */
   /* tree.Insert(4, 45); */
   /* tree.Insert(5, 45); */
   /* tree.Insert(6, 45); */
   /* tree.Insert(7, 45); */
   /* tree.Insert(10, 45); */
   /* /1* 5c1e6fd6b6b0dbc1038dfe81193f4b3c *1/ */

   tree.Draw();
}

void initalize() 
{
    setUpSignalHandler();
    struct sockaddr_un server_addr;

    // setup socket address structure
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path,socket_name_,sizeof(server_addr.sun_path) - 1);

    // create socket
    server_ = socket(PF_UNIX,SOCK_STREAM,0);
    if (!server_) 
    {
        perror("socket");
        exit(-1);
    }

    // call bind to associate the socket with the UNIX file system
    if (bind(server_,(const struct sockaddr *)&server_addr,sizeof(server_addr)) < 0) 
    {
        perror("bind");
        exit(-1);
    }

      // convert the socket to listen for incoming connections
    if (listen(server_,SOMAXCONN) < 0) 
    {
        perror("listen");
        exit(-1);
    }
}

int serve()
{
    // setup client
    int client;
    struct sockaddr_in client_addr;
    socklen_t clientlen = sizeof(client_addr);

      // accept clients
    while ((client = accept(server_,(struct sockaddr *)&client_addr,&clientlen)) > 0) 
    {
        handle(client);
    }
    /* close_socket(); */
}

void handle(int client) 
{
    // loop to handle all requests
    while (1) 
    {
        // get a request
        string request = get_request(client);
        cout << "got request :" << request << endl;
        // break if client is done or an error occurred
        if (request.empty())
            break;
        // send response
        bool success = send_response(client,request);
        // break if an error occurred
        if (not success)
            break;
    }
    /* close(client); */
}

string get_request(int client)
{
    char buf_[1025];
    string request = "";
    // read until we get a newline
    while (request.find("\n") == string::npos) 
    {
        int nread = recv(client,buf_,1024,0);
        if (nread < 0) 
        {
            if (errno == EINTR)
            {
                // the socket call was interrupted -- try again
                continue;
            }
            else
            {
                // an error occurred, so break out
                return "";
            }
        } 
        else if (nread == 0) 
        {
            // the socket is closed
            return "";
        }
        // be sure to use append in case we have binary data
        request.append(buf_,nread);
    }
    // a better server would cut off anything after the newline and
    // save it in a cache
    return request;
}

void setUpSignalHandler()
{
    // setup handler for Control-C so we can properly unlink the UNIX
    // socket when that occurs
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = onExit;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
}


void onExit(int) {
    unlink(socket_name_);
}

bool send_response(int client, string response) 
{
    // prepare to send response
    const char* ptr = response.c_str();
    int nleft = response.length();
    int nwritten;
    // loop to be sure it is all sent
    while (nleft) 
    {
        if ((nwritten = send(client, ptr, nleft, 0)) < 0) 
        {
            if (errno == EINTR) 
            {
                // the socket call was interrupted -- try again
                continue;
            } 
            else 
            {
                // an error occurred, so break out
                perror("write");
                return false;
            }
        } 
        else if (nwritten == 0) 
        {
            // the socket is closed
            return false;
        }
        nleft -= nwritten;
        ptr += nwritten;
    }
    return true;
}
