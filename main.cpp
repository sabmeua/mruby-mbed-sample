#include <string>

#include "mbed.h"
#include "SDFileSystem.h"
#include "EthernetInterface.h"
#include "htmlcontent.h"
#include "cmd.h"

#define RBFILE "/sd/test.rb"
#define ENABLE_DHCP

SDFileSystem sd(P8_5, P8_6, P8_3, P8_4, "sd");

Serial pc(USBTX, USBRX);
char i_buff[1024*3];
char o_buff[1024*3];

int mruby_argc = 2;
char *mruby_argv[] = {
    "mruby",
    RBFILE
};

int getRequestBody(char *request, char *buff, int *size)
{
    string req(request);
    int sp = req.find("Content-Length", 0);
    int ep = req.find("\r\n", sp);
    int len = 0;
    sscanf(req.substr(sp, ep-sp).c_str(), "Content-Length: %d", &len);

    sp = req.find("\r\n\r\n", 0) + 4;
    string body = req.substr(sp, len);
    *size = len;
    sprintf(buff, body.c_str());
}

int writeScriptFile(char *buff, int size)
{
    int i;
    FILE *f = fopen(RBFILE, "w");
 
    for (i=0; i < size; i++) {
        fprintf(f, "%c", buff[i]);
    }

    fclose(f);
}

int main() {
    EthernetInterface eth0;

    printf("Init network interface...\n");
#ifdef ENABLE_DHCP
    eth0.init();
#else
    eth0.init("192.168.1.100", "255.255.255.0", "192.168.1.1");
#endif
    eth0.connect();
    printf("IP Address: %s\n", eth0.getIPAddress());
    printf("done!\n\n");
 
    TCPSocketServer server;
    TCPSocketConnection conn;
    server.bind(80);
    server.listen();
     
    while (true) {
        server.accept(conn);
        conn.receive(i_buff, sizeof(i_buff));
        
        if (i_buff[0] == 'P') {
            int size;
            getRequestBody(i_buff, o_buff, &size);
            writeScriptFile(o_buff, size);
            cmd_mruby(mruby_argc, mruby_argv);
        } else {
            sprintf(o_buff, EDITPAGE);        
        }
        
        conn.send(o_buff, sizeof(EDITPAGE));
        conn.close();
    }
 
    server.close();
    eth0.disconnect();
}
