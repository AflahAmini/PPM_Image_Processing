#ifndef IMAGE_H
#define IMAGE_H
#include <fstream>
#include <string>
#include<iostream>


using namespace std;
struct Pixel
{
    unsigned int red;
    unsigned int green;
    unsigned int blue;

};
class Image
{
    public:
        Image();
        virtual ~Image();

        char GetmagNum1() { return magNum1; }
        void SetmagNum1(char val) { magNum1 = val; }
        char GetmagNum2() { return magNum2; }
        void SetmagNum2(char val) { magNum2 = val; }
        unsigned int Getwidth() { return width; }
        void Setwidth(unsigned int val) { width = val; }
        unsigned int Getheight() { return height; }
        void Setheight(unsigned int val) { height = val; }
        unsigned int GetmaxColVal() { return maxColVal; }
        void SetmaxColVal(unsigned int val) { maxColVal = val; }
        Pixel** Getpixel(){return arr;}
        void Setpixel(Pixel **p){arr = p;}

        void read_ppm(string name)
        {
            ifstream file(name, ios::binary);
            if(file.is_open())
            {
                file >> magNum1 ;
                file >> magNum2 ;
                file >> width ;
                file >> height ;

                for (int i = 0 ; i < 2 ; i++)
                {
                    file.ignore( '\n');
                }

                alloc_raster();

                //TO DO allocate array of pixel
                int val;
                for(int i = 0; i < Getheight(); i++)
                    for(int j = 0; j < Getwidth(); j++)
                {
                    file >> val;
                    Getpixel()[i][j].red = val;

                    file >> val;
                    Getpixel()[i][j].green = val;

                    file >> val;
                    Getpixel()[i][j].blue = val;

                    cout << Getpixel()[i][j].red << Getpixel()[i][j].green << Getpixel()[i][j].blue << endl;
                }
              file.close();

            }
            else
            {
                cout << "Unable to open file!" << endl;
            }

        }

        void write_ppm(string fileName)
        {
            ofstream file(fileName, ios::binary);
            if(file.is_open())
            {
              file << magNum1 << magNum2 << endl;
              file << width ;
              file << height << endl;
              file << 255 << endl;
              file << "# end of header" << endl;

              if(magNum1 == 'P' && magNum2 == '3')
              {
                for(int i = 0; i < Getheight(); i++)
                    for(int j = 0; j < Getwidth(); j++)
                  {
                        file << (int) Getpixel()[i][j].red << ' ';
                        file << (int) Getpixel()[i][j].green << ' ';
                        file << (int) Getpixel()[i][j].blue << '\n';
                  }
                file.close();
              }
              else
              {
                  cout << "Incorrect version, only P3!" << endl;
                  file.close();

              }

            }

        }

        void mirror_vertically()
        {
            Pixel temp;
            temp.red =0;
            temp.green = 0;
            temp.blue = 0;
            cout << Getwidth() << Getheight() << endl;
            for(int i = 0; i < Getwidth() ; i++)
                for(int j = 0; j < Getheight()/2; j++)
                  {
                    temp = Getpixel()[j][i];
                    Getpixel()[j][i] = Getpixel()[Getheight()-1-j][i];
                    Getpixel()[Getheight()-1-j][i] = temp;
                    cout << Getpixel()[j][i].red << Getpixel()[j][i].green << Getpixel()[j][i].blue << endl;
                  }
        }


    protected:

    private:
        char magNum1;
        char magNum2;
        unsigned int width;
        unsigned int height;
        unsigned int maxColVal;
        Pixel **arr;

        void alloc_raster()
        {
            if(Getwidth() > 0 && Getheight() > 0 && Getpixel() == nullptr)
            {

                arr = new Pixel*[Getheight()]; // creates a pointer to a pointer of the address of the first array(rows)
                for(unsigned int k =0; k < Getheight(); k++)
                    arr[k] = new Pixel[Getwidth()]; // assign to each of row arrays of Pixel
            }



        }
};

#endif // IMAGE_H
