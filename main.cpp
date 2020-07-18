#include <string>
#include "opencv2/opencv.hpp"
#include <iostream> 

#include <czmq.h>

#include "zwssock.h" 
  
//using namspace cv;

static std::string base64Encode(const unsigned char* Data, int DataByte)
{
	 // code table
	const char EncodeTable[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	 	//return value 
	std::string strEncode;
	unsigned char Tmp[4] = { 0 };
	int LineLength = 0;
	for (int i = 0; i < (int)(DataByte / 3); i++)
	{
		Tmp[1] = *Data++;
		Tmp[2] = *Data++;
		Tmp[3] = *Data++;
		strEncode += EncodeTable[Tmp[1] >> 2];
		strEncode += EncodeTable[((Tmp[1] << 4) | (Tmp[2] >> 4)) & 0x3F];
		strEncode += EncodeTable[((Tmp[2] << 2) | (Tmp[3] >> 6)) & 0x3F];
		strEncode += EncodeTable[Tmp[3] & 0x3F];
		if (LineLength += 4, LineLength == 76) { strEncode += "\r\n"; LineLength = 0; }
	}
	 // Encode the remaining data
	int Mod = DataByte % 3;
	if (Mod == 1)
	{
		Tmp[1] = *Data++;
		strEncode += EncodeTable[(Tmp[1] & 0xFC) >> 2];
		strEncode += EncodeTable[((Tmp[1] & 0x03) << 4)];
		strEncode += "==";
	}
	else if (Mod == 2)
	{
		Tmp[1] = *Data++;
		Tmp[2] = *Data++;
		strEncode += EncodeTable[(Tmp[1] & 0xFC) >> 2];
		strEncode += EncodeTable[((Tmp[1] & 0x03) << 4) | ((Tmp[2] & 0xF0) >> 4)];
		strEncode += EncodeTable[((Tmp[2] & 0x0F) << 2)];
		strEncode += "=";
	}
 
 
	return strEncode;
}
static std::string Mat2Base64(const cv::Mat &img)
{
	 
      
       
	std::string img_data;
	std::vector<uchar> vecImg;
	std::vector<int> vecCompression_params;
	//vecCompression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
	vecCompression_params.push_back(90);
	cv::imencode(".png",img, vecImg, vecCompression_params);
	img_data = base64Encode(vecImg.data(), vecImg.size());
        
	return img_data;
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

        /*Opencv Vedio cature*/
        cv::VideoCapture cap(0);

       /*Message Pointer*/
        zmsg_t* msg;


       /*this is request ID from HTML */
        zframe_t *id;

while(!zsys_interrupted){

           cv::Mat frame;
           cap >> frame;
           std::string base=Mat2Base64(frame);
           char *cstr = new char[base.length() + 1];
           strcpy(cstr, base.c_str());

          msg = zwssock_recv(sock);

		id = zmsg_pop(msg);

		while (zmsg_size(msg))
		{
			char * str = zmsg_popstr(msg);

			printf("%s\n", str);

			free(str);
		}

		zmsg_destroy(&msg);

		msg = zmsg_new();
                
		zmsg_push(msg, id);
		zmsg_addstr(msg,cstr);
                
		int rc = zwssock_send(sock, &msg);
		
                 if (rc != 0)
		{zmsg_destroy(&msg);}


 }	    
  
  cap.release();
 
  cv::destroyAllWindows();

  zwssock_destroy(&sock);
  
  delete [] con;

    return 0; 
} 
