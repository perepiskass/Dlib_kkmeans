#include <iostream>

#include <dlib/clustering.h>
#include <dlib/rand.h>

#include "3dwindow.h"

size_t checkArg(int argc,char** argv);

int main(int argc, char *argv[]) 
{
  try
  {
    auto center_count = checkArg(argc,argv);

    kcentroid<kernel_type> kc(kernel_type(0.1),0.01, 8);
    kkmeans<kernel_type> test(kc);

    std::vector<sample_type> samples;
    std::vector<sample_type> initial_centers;

    sample_type m;

    dlib::rand rnd;

    string str;
    while(getline(cin, str))
    {
      auto delim = str.find_first_of(';');
      m(0) = stod(str.substr(0, delim++));
      m(1) = stod(str.substr(delim, str.length()));
      samples.push_back(m);
    }

    test.set_number_of_centers(center_count);
    pick_initial_centers(center_count, initial_centers, samples, test.get_kernel());
    test.train(samples,initial_centers);

    for (unsigned long i = 0; i < samples.size(); ++i)
    {
      cout <<samples[i](0) << ';' << samples[i](1) << ';' << test(samples[i]) << endl;
    }
    std::vector<unsigned long> assignments = spectral_cluster(kernel_type(0.1), samples, center_count);

    show_window(samples,test);
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  return 0;
}



