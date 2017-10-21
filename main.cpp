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
#include "socket.h"

using namespace std;

const char* socket_name_ = "/tmp/cppLLRBT-socket";
int server_;
/* char* buf_; */

string get_request(int client);
bool send_response(int client, string response);
void handle(int client);
Server * initalize();
int serve();
void setUpSignalHandler();
void onExit(int);

int main()
{

  LLRBTree<int,int> tree;

   /* cout << "test " << *tree.Search(1913); */
 Server * server = initalize();
 /* serve(); */
 
 while(1)
 {
     while(server->Accept())
     {
         string command = server->Listen();

         if (command == "add")
         {
             /* tree.Insert(); */
         }
         else if (command == "search")
         {
             /* tree.Search(); */
         }
         else if (command == "delete")
         {
             /* tree.Delete(); */
         }
         else 
         {
             cerr << "invalid option"<< endl;
             exit (33);
         }

     }
 }

   tree.Draw();
}

Server* initalize() 
{
    setUpSignalHandler();
    Server * server = new Server(socket_name_);
    return server;
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
