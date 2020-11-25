#include <iostream>
#include <vector>
#include <fstream> 

// set appropriate path for data
#define TRAIN_IMAGE "./data/train-images.idx3-ubyte"
#define TRAIN_LABEL "./data/train-labels.idx1-ubyte"
#define TEST_IMAGE "./data/t10k-images.idx3-ubyte"
#define TEST_LABEL "./data/t10k-labels.idx1-ubyte" 

using namespace std;
int ReverseInt (int i)
{
    unsigned char ch1, ch2, ch3, ch4;
    ch1=i&255;
    ch2=(i>>8)&255;
    ch3=(i>>16)&255;
    ch4=(i>>24)&255;
    return((int)ch1<<24)+((int)ch2<<16)+((int)ch3<<8)+ch4;
}

void ReadMNIST(int NumberOfImages, int DataOfAnImage ,double ** arr)
{
    //arr.resize(NumberOfImages,vector<double>(DataOfAnImage));
    ifstream file (TRAIN_IMAGE ,ios::binary);
    if (file.is_open())
    {
        int magic_number=0;
        int number_of_images=0;
        int n_rows=0;
        int n_cols=0;
        file.read((char*)&magic_number,sizeof(magic_number));
        magic_number= ReverseInt(magic_number);
        file.read((char*)&number_of_images,sizeof(number_of_images));
        number_of_images= ReverseInt(number_of_images);
        file.read((char*)&n_rows,sizeof(n_rows));
        n_rows= ReverseInt(n_rows);
        file.read((char*)&n_cols,sizeof(n_cols));
        n_cols= ReverseInt(n_cols);
        printf("%d, %d , %d ,%d \n" , magic_number, number_of_images,  n_rows , n_cols );
        for(int i=0;i<number_of_images;++i)
        {
            for(int r=0;r<n_rows;++r)
            {
                for(int c=0;c<n_cols;++c)
                {
                    unsigned char temp=0;
                    file.read((char*)&temp,sizeof(temp));
                    arr[i][(n_rows*r)+c]= (double)temp/255.0;
                    //printf("%f", (double)temp);
                }
            }
        }
    }
}
 
void ReadMNISTTest(int NumberOfImages, int DataOfAnImage ,double ** arr)
{
    //arr.resize(NumberOfImages,vector<double>(DataOfAnImage));
    ifstream file (TEST_IMAGE ,ios::binary);
    if (file.is_open())
    {
        int magic_number=0;
        int number_of_images=0;
        int n_rows=0;
        int n_cols=0;
        file.read((char*)&magic_number,sizeof(magic_number));
        magic_number= ReverseInt(magic_number);
        file.read((char*)&number_of_images,sizeof(number_of_images));
        number_of_images= ReverseInt(number_of_images);
        file.read((char*)&n_rows,sizeof(n_rows));
        n_rows= ReverseInt(n_rows);
        file.read((char*)&n_cols,sizeof(n_cols));
        n_cols= ReverseInt(n_cols);
        printf("%d, %d , %d ,%d \n" , magic_number, number_of_images,  n_rows , n_cols );
        for(int i=0;i<number_of_images;++i)
        {
            for(int r=0;r<n_rows;++r)
            {
                for(int c=0;c<n_cols;++c)
                {
                    unsigned char temp=0;
                    file.read((char*)&temp,sizeof(temp));
                    arr[i][(n_rows*r)+c]= (double)temp/255.0;
                    //printf("%f \n", arr[i][(n_rows*r)+c]);
                }
            }
        }
    }
} 

void ReadMNISTTestlabel(int NumberOfImages, int DataOfAnImage ,int ** arr)
{
    //arr.resize(NumberOfImages,vector<double>(DataOfAnImage));
    ifstream file (TEST_LABEL ,ios::binary);
    if (file.is_open())
    {
        int magic_number=0;
        int number_of_images=0;
        int n_rows=0;
        int n_cols=0;
        file.read((char*)&magic_number,sizeof(magic_number));
        magic_number= ReverseInt(magic_number);
        file.read((char*)&number_of_images,sizeof(number_of_images));
        number_of_images= ReverseInt(number_of_images);
        file.read((char*)&n_rows,sizeof(n_rows));
        n_rows= ReverseInt(n_rows);
        file.read((char*)&n_cols,sizeof(n_cols));
        n_cols= ReverseInt(n_cols);
        printf("%d, %d , %d ,%d \n" , magic_number, number_of_images,  n_rows , n_cols );
        for(int i=0;i<number_of_images;++i)
        {
            unsigned char temp=0;
            file.read((char*)&temp,sizeof(temp));
            for(int r=0;r<10;++r)
            {
                if(r == (int)temp){
                    arr[i][r] = 1; 
                }
                else{
                    arr[i][r] = 0; 
                }
            }
        } 
    }
} 


void ReadMNISTTrainlabel(int NumberOfImages, int DataOfAnImage ,int ** arr)
{
    //arr.resize(NumberOfImages,vector<double>(DataOfAnImage));
    ifstream file (TRAIN_LABEL ,ios::binary);
    if (file.is_open())
    {
        int magic_number=0;
        int number_of_images=0;
        int n_rows=0;
        int n_cols=0;
        file.read((char*)&magic_number,sizeof(magic_number));
        magic_number= ReverseInt(magic_number);
        file.read((char*)&number_of_images,sizeof(number_of_images));
        number_of_images= ReverseInt(number_of_images);
        file.read((char*)&n_rows,sizeof(n_rows));
        n_rows= ReverseInt(n_rows);
        file.read((char*)&n_cols,sizeof(n_cols));
        n_cols= ReverseInt(n_cols);
        printf("%d, %d , %d ,%d \n" , magic_number, number_of_images,  n_rows , n_cols );
        for(int i=0;i<number_of_images;++i)
        {
            unsigned char temp=0;
            file.read((char*)&temp,sizeof(temp));
            for(int r=0;r<10;++r)
            {
                if(r == (int)temp){
                    arr[i][r] = 1; 
                }
                else{
                    arr[i][r] = 0; 
                }
            }
        } 
    }
}  

