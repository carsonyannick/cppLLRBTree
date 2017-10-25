#include "LLRBTree.h"
#include <iostream> 
#include <signal.h>
#include <unistd.h> // unlink()

#include "socket.h"

using namespace std;

const char* socket_name_ = "/tmp/cppLLRBT-socket";
Server * initalize();
void setUpSignalHandler();
void onExit(int);

int main()
{

    LLRBTree<int,int> tree;

    Server * server = initalize();

    while(1)
    {
        while(server->Accept() > 0)
        {
            Server::request request_;
            /* server->Listen(request_); */
            while(server->Listen(request_))
            {
                char * command = request_.command;
                int & arg = request_.argument;

                if (strcmp("add   ",command) == 0)
                {
                 cout << "inside add if" << endl;
                 tree.Insert(arg, 11);
                }
                else if (strcmp(command,"search") == 0)
                {
                 cout << "inside search if" << endl;
                 /* tree.Search(); */
                }
                else if (strcmp(command,"delete") == 0)
                {
                 cout << "inside delete if" << endl;
                 tree.Delete(arg);
                }
                else if (strcmp(command,"draw  ") == 0)
                {
                 cout << "inside draw if" << endl;
                 server->Reply(tree.Draw());
                }
                else 
                {
                 cerr << "invalid option"<< endl;
                 onExit(0);
                 exit (33);
                }
            }
        }
    }
}

Server* initalize() 
{
    setUpSignalHandler();
    Server * server = new Server(socket_name_);
    return server;
}

void setUpSignalHandler()
{
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = onExit;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
}

void onExit(int) 
{
    unlink(socket_name_);
    exit(2);
}
