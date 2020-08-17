
/** @file VedioStreamZMQ/main.cpp
 *  @brief 
 *         This code of ZMQ server
 *   
 *  
 *  @author Rekulapalli Karthikeya
 *  @bug No bugs
 */

#include <czmq.h>
#include "zwssock.h" 
#include <math.h>
#include <bits/stdc++.h> 
#include "matbase.hpp"

std::string stringcon(const char *s)
{
     std::string str(s);
   
     return str;

}
int strintoint(std::string x)
{
std::istringstream iss (x);
  int number;
  iss >> number;
  return (number/8192);


}
int main() 
{ 
   
        /*creating socket */
        zwssock_t *sock;

       /*socket type is router*/
	sock = zwssock_new_router();

       /*URL String*/
        std::string url = "tcp://127.0.0.1:8000";
  
        char *con = new char[url.length() + 1];
       
        strcpy(con, url.c_str());
  
       /*Bining Your socket to URL*/
	zwssock_bind(sock, con);


       /*Message Pointer*/
        zmsg_t* msg;


       /*this is request ID from HTML */
        zframe_t *id;



while(!zsys_interrupted){
          


        msg = zwssock_recv(sock);
    	id = zmsg_pop(msg);
        std::string string1(zmsg_popstr(msg));
        int x=strintoint(string1)+1;
        std::string recv="";
        int i=0;
        #pragma omp parallel num_threads(x)
        {
          
          #pragma omp critical 
          recv=recv+stringcon(zmsg_popstr(msg));
          
        }  

        cv::Mat frame=Base2Mat(recv);
        zmsg_destroy(&msg);
        std::string base=Mat2Base64(frame);
        char *cstr = new char[base.length() + 1];
        strcpy(cstr, base.c_str());
        msg = zmsg_new();
        zmsg_push(msg, id);
	    zmsg_addstr(msg,cstr);
       
	    int rc = zwssock_send(sock, &msg);
		
        if (rc != 0)
        {zmsg_destroy(&msg);}
          
        delete [] cstr;


      
 }

	    

  zwssock_destroy(&sock);
  
  delete [] con;

    return 0; 
} 
