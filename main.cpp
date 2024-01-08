#include <iostream>
#include <fstream>
#include <string>

using namespace std;
///***********************************************************************
//Matr.-Nr:                     3124035
//Nachname/Surname:             Amini Amir
//Vorname/Given name:           Muhammad Aflah Bin
//Uni-Email:                    muhammad.amir@stud.uni-due.de
//Studiengang/Course of studis: Computer Engineering ISE Software Engineering
//***********************************************************************/
struct Pixel
{
    unsigned int red;
    unsigned int green;
    unsigned int blue;

};
class Image
{
    public:
        Image()
        {

            this->SetmagNum1('P');
            this->SetmagNum2('3');
            this->Setheight(0);
            this->Setwidth(0);
            this->SetmaxColVal(255);
            this->Setpixel(nullptr);
        };

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
                cout<< name << " opened"<< endl;
                file >> magNum1 ;
                file >> magNum2 ;
                file >> width ;
                file >> height ;
                cout<< "read header of file"<< endl;



                for (int i = 0 ; i < 2 ; i++)
                {
                    file.ignore( '\n');
                }

                alloc_raster();

                cout<< "read RGB pixel data row by row.."<< endl;
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


                }
                cout<< "done and " << name << " closed"<< endl;
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
              cout<< fileName << " opened..."<< endl;

              file << magNum1  << magNum2 << endl;
              file << width ;
              file << " " << height << endl;
              file << 255 << endl;
              file << "# end of header" << endl;

              cout<< "write header of file"<< endl;

              cout<< "write RGB pixel data row by row.."<< endl;
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
                cout<< "done and " << fileName << " closed"<< endl;
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
            //mirror vertically
//            for(int i = 0; i < Getwidth() ; i++)
//                for(int j = 0; j < Getheight()/2; j++)
//                  {
//
//                    temp = Getpixel()[j][i];
//                    Getpixel()[j][i] = Getpixel()[Getheight()-1-j][i];
//                    Getpixel()[Getheight()-1-j][i] = temp;
//
//
//
//                  }
            //mirror horizontally
            for(int i = 0; i < Getheight() ; i++)
                for(int j = 0; j < Getwidth()/2; j++)
                  {

                    temp = Getpixel()[i][j];
                    Getpixel()[i][j] = Getpixel()[i][Getwidth()-1-j];
                    Getpixel()[i][Getwidth()-1-j] = temp;
                    //cout << Getpixel()[j][i].red << Getpixel()[j][i].green << Getpixel()[j][i].blue << endl;


                  }

        }

        void sepia()
        {
            for(int i = 0; i < Getheight(); i++)
                    for(int j = 0; j < Getwidth(); j++)
                  {
                      int r,g,b;
                      r = 0.393*Getpixel()[i][j].red + 0.769*Getpixel()[i][j].green + 0.189*Getpixel()[i][j].blue;
                      g = 0.349*Getpixel()[i][j].red + 0.686*Getpixel()[i][j].green + 0.168*Getpixel()[i][j].blue;
                      b = 0.272*Getpixel()[i][j].red + 0.534*Getpixel()[i][j].green + 0.131*Getpixel()[i][j].blue;
                      if(r > 255)
                        Getpixel()[i][j].red = 255;
                      else
                        Getpixel()[i][j].red = r;
                      if(g > 255)
                        Getpixel()[i][j].green = 255;
                      else
                        Getpixel()[i][j].green = g;
                      if(b > 255)
                        Getpixel()[i][j].blue = 255;
                      else
                        Getpixel()[i][j].blue = b;

                  }

        }

        void strip_curtain(const int stripWidth, const int distance, Pixel p)
        {
            for(int i = distance; i < Getwidth(); i+=stripWidth+distance)
                    for(int j = i; j < i + stripWidth; j++)
                        for(int k =0; k < Getheight(); k++ )
                        {
                            Getpixel()[k][j].red = p.red;
                            Getpixel()[k][j].green = p.green;
                            Getpixel()[k][j].blue =  p.blue;
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
                cout<<"allocate " << Getwidth() <<"x"<< Getheight() <<" pixel array on heap..";
                arr = new Pixel*[Getheight()]; // creates a pointer to a pointer of the address of the first array(rows)
                for(unsigned int k =0; k < Getheight(); k++)
                    arr[k] = new Pixel[Getwidth()]; // assign to each of row arrays of Pixel
            }
                cout<<"done"<<endl;


        }
};

int main()
{

    Image *i = new Image();
    int s = -1;
    string filename = "";

    //i->read_ppm("C:/Users/ASUS/Downloads/peppers.ppm");

    while(s!=0){
    cout<< "0 Ende                     / end" << endl;
    cout<< "1 lese .ppm Datei          / read .ppm file" << endl;
    cout<< "2 vertikal spiegeln        / mirror vertically"<<endl;
    cout<< "3 schreibe .ppm Datei      / write .ppm file"<<endl;
    cout<< "4 Sepia Filter(Vergilbung) / strip sepia filter(yellowing)"<<endl;
    cout<< "5 Streifenvorhang          / strip curtain"<<endl;


    cin >> s;

        switch(s){
            case 0 : break;
            case 1 :{
                cout << "please input file name:" ;
                cin >> filename;

                string path = "C:/Users/ASUS/Downloads/" + filename;

                cout << "Reading file....." ;
                i->read_ppm(path);
                cout << "done!" << endl;



                }break;
            case 2 :{


                cout << "Mirroring file....." ;
                i->mirror_vertically();
                cout << "done!" << endl;
                }break;
            case 3 :{
                cout << "please input file name:" ;
                cin >> filename;

                string path = "C:/Users/ASUS/Downloads/" + filename;

                cout << "Writing file....." ;

                i->write_ppm(path);

                cout << "done!" << endl;

                }break;

            case 4 :{
                cout << "start sepia fitler....." ;

                i->sepia();

                cout << "done"<<endl; ;
                break;


            }

            case 5 :{
                Pixel p;
                int w, d;

                cout << "please input width of strips: " << endl;
                cin >> w;

                cout << "please input distance between strips:" << endl;
                cin >> d;

                cout << "please input R G B values: " << endl;
                cin >> p.red >> p.green >> p.blue;

                cout << "start generating strip curtain of width " << w << " and distance " << d << "....." ;
                i->strip_curtain(w,d,p);
                cout << "done"<<endl; ;
                break;
            }

            default:
                cout<< "Incorrect input!" << endl;
        }
    }

    return 0;
}
