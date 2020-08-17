#include "matbase.hpp"
std::string base64Encode(const unsigned char* Data, int DataByte)
{


	 // code table
	const char EncodeTable[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; 	
	std::string strEncode;
	unsigned char Tmp[4] = { 0 };
	int LineLength = 0;

   /*
   *#######################################################################
   *
   * #pragma omp for divides loop iterations between the spawned threads
   *
   *#######################################################################
   */

     #pragma omp for 
	for (int i = 0; i < (int)(DataByte / 3); i++)
	{
        
        #pragma omp critical
        {        
		Tmp[1] = *Data++;
		Tmp[2] = *Data++;
		Tmp[3] = *Data++;
		strEncode += EncodeTable[Tmp[1] >> 2];
		strEncode += EncodeTable[((Tmp[1] << 4) | (Tmp[2] >> 4)) & 0x3F];
		strEncode += EncodeTable[((Tmp[2] << 2) | (Tmp[3] >> 6)) & 0x3F];
		strEncode += EncodeTable[Tmp[3] & 0x3F];
        }
		
		if (LineLength += 4, LineLength == 76)
                { 
                    
                    #pragma omp critical
                    strEncode += "\r\n"; LineLength = 0; 
                    
                }
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

std::string base64Decode(const char* Data, int DataByte)
{
	// Decoding table
	const char DecodeTable[] =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		62, // '+'
		0, 0, 0,
		63, // '/'
		52, 53, 54, 55, 56, 57, 58, 59, 60, 61, // '0'-'9'
		0, 0, 0, 0, 0, 0, 0,
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
		13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, // 'A'-'Z'
		0, 0, 0, 0, 0, 0,
		26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
		39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, // 'a'-'z'
	};
	 	//return value 
	std::string strDecode;
	int nValue;

	#pragma omp for
	for(int i = 0;i < DataByte;i++)
	{
              
		if (*Data != '\r' && *Data != '\n')
		{
            #pragma omp critical
		    {
			nValue = DecodeTable[*Data++] << 18;
			nValue += DecodeTable[*Data++] << 12;
			strDecode += (nValue & 0x00FF0000) >> 16;
			if (*Data != '=')
			{
				nValue += DecodeTable[*Data++] << 6;
				strDecode += (nValue & 0x0000FF00) >> 8;
				if (*Data != '=')
				{
					nValue += DecodeTable[*Data++];
					strDecode += nValue & 0x000000FF;
				}
			}
			i += 3;
			}

		}else{ 

		    #pragma omp critical
            Data++;
            
	       }
		

	}
    
	return strDecode;
}
std::string Mat2Base64(const cv::Mat &img)
{
	std::string img_data;
	std::vector<uchar> vecImg;
	std::vector<int> vecCompression_params;
	vecCompression_params.push_back(cv::IMWRITE_JPEG_QUALITY);
	vecCompression_params.push_back(90);
	cv::imencode(".jpeg",img, vecImg, vecCompression_params);
	img_data = base64Encode(vecImg.data(), vecImg.size());
	return img_data;
}
cv::Mat Base2Mat(std::string &base64_data)
{
	cv::Mat img;
	std::string s_mat;
	s_mat = base64Decode(base64_data.data(), base64_data.size());
	std::vector<char> base64_img(s_mat.begin(), s_mat.end());
	img = cv::imdecode(base64_img,cv::IMREAD_GRAYSCALE);
	return img;
}

