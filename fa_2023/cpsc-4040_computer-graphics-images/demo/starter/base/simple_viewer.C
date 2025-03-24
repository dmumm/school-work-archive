
#include <vector>
#include <string>
#include "StarterViewer.h"
#include <iostream>

#include <OpenImageIO/imageio.h> // from video
using namespace OIIO; // from video

using namespace starter;


// from video:
void read_image()
{
   std::string filename = "100_0093.jpeg";
   std::cout << "\n\n\n" << filename << std::endl;
   auto inp = ImageInput::open(filename);
   if(! inp) {
      return;
   }
   const ImageSpec &spec = inp->spec();
   int xres = spec.width;
   int yres = spec.height;
   int channels = spec.nchannels;
   std::vector<unsigned char> pixels(xres * yres * channels);
   inp->read_image(TypeDesc::UINT8, &pixels[0]);
   inp->close();
};

int main( int argc, char** argv )
{
   read_image();
   StarterViewer* viewer = CreateViewer();

   std::vector<std::string> args;

   for(int i=0;i<argc;i++)
   {
      std::string s(argv[i]);
      args.push_back(s);
   }
   viewer->Init(args);

   viewer->MainLoop();

}
