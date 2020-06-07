#pragma once

#include <dlib/gui_widgets.h>
#include <dlib/image_transforms.h>
#include <cmath>

#include <vector>

using namespace std;
using namespace dlib;

using sample_type = matrix<double,2,1>;
using kernel_type = radial_basis_kernel<sample_type>;

/**
 * @brief Функция создания окна с отображением точек в трехмерном пространстве.
 * @param samples - вектор точек для отрисовки.
 * @param test - экземпляр натренерованного алгоритма кластеризации, для определения принадлежности точки к одному из кластеров.
 */
void show_window(std::vector<sample_type>& samples,kkmeans<kernel_type>& test)
{
    std::vector<perspective_window::overlay_dot> points;
    for(size_t i = 0; i < samples.size();++i)
    {
        /// Get a point on a 3d
        dlib::vector<double> val(samples[i](0),samples[i](1),1);
        /// Pick a color based on type point
        rgb_pixel color = colormap_jet(test(samples[i]),0,test.number_of_centers()-1);
        /// And add the point to the list of points we will display
        points.push_back(perspective_window::overlay_dot(val, color));
    }

    perspective_window win;
    win.set_title("perspective_window 3D vizualization");
    win.add_overlay(points);
    win.wait_until_closed();
}