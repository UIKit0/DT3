//==============================================================================
///	
///	File: main.cpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include <stdlib.h>
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>

#include "Image.hpp"

//==============================================================================
//==============================================================================

void remove_alpha (Image &image)
{
	for (int y = 0; y < image.height(); ++y) {
		for (int x = 0; x < image.width(); ++x) {
			Image::Pixel p = image.pixel(x,y);
            p.a = 255;
			image.set_pixel(x, y, p);
		}
	}
}

//==============================================================================
//==============================================================================

void expand_alpha (Image &image)
{
    Image old_image(image);
    Image temp_image;
    
    bool modified = true;
    while (modified) {
        modified = false;
        temp_image = image;
    
        for (int y = 0; y < temp_image.height(); ++y) {
            for (int x = 0; x < temp_image.width(); ++x) {
            
                Image::Pixel p = temp_image.pixel(x,y);
                                
                if (p.a > 0)
                    continue;
                                
                int x_min = x - 1;
                int x_max = x + 1;
                int y_min = y - 1;
                int y_max = y + 1;
                
                if (x_min < 0)                          x_min = 0;
                if (x_max > temp_image.width()-1)     x_max = temp_image.width()-1;
                if (y_min < 0)                          y_min = 0;
                if (y_max > temp_image.height()-1)    y_max = temp_image.height()-1;

                int r_sum = 0;
                int g_sum = 0;
                int b_sum = 0;
                int num = 0;
                
                for (int yy = y_min; yy <= y_max; ++yy) {
                    for (int xx = x_min; xx <= x_max; ++xx) {
                        p = temp_image.pixel(xx,yy);
                        
                        if (p.a > 0) {
                            r_sum += p.r;
                            g_sum += p.g;
                            b_sum += p.b;
                            num += 1;
                        }
                    
                    }
                }
                
                if (num > 0) {
                    p.r = r_sum / num;
                    p.g = g_sum / num;
                    p.b = b_sum / num;
                    p.a = 255;
                    image.set_pixel(x, y, p);
                    
                    modified = true;
                }
            }
        }
    }
    
    // Replace alpha
    for (int y = 0; y < temp_image.height(); ++y) {
        for (int x = 0; x < temp_image.width(); ++x) {
            Image::Pixel p_rgb = image.pixel(x,y);
            Image::Pixel p_a = old_image.pixel(x,y);
            
            p_rgb.a = p_a.a;
            
            image.set_pixel(x, y, p_rgb);            
        }
    }

}

//==============================================================================
//==============================================================================

void fill_alpha_black (Image &image)
{
	for (int y = 0; y < image.height(); ++y) {
		for (int x = 0; x < image.width(); ++x) {
			Image::Pixel p = image.pixel(x,y);
            if (p.a == 0) {
                p.r = 0;
                p.g = 0;
                p.b = 0;
            }
			image.set_pixel(x, y, p);
		}
	}

}

//==============================================================================
//==============================================================================

void bump_to_normal (Image &image, float strength, bool wrap)
{
    Image old_image(image);

	for (int y = 0; y < image.height(); ++y) {
		for (int x = 0; x < image.width(); ++x) {
			float x00,x10,x20,x01,x11,x21,x02,x12,x22;

            //  x00,x10,x20
            //  x01,x11,x21
            //  x02,x12,x22
    
            if (wrap) {
                x00 = old_image.pixel_wrapped(x-1,  y-1).r / 255.0F;
                x10 = old_image.pixel_wrapped(x,    y-1).r / 255.0F;
                x20 = old_image.pixel_wrapped(x+1,  y-1).r / 255.0F;
                x01 = old_image.pixel_wrapped(x-1,  y).r / 255.0F;
                x11 = old_image.pixel_wrapped(x,    y).r / 255.0F;
                x21 = old_image.pixel_wrapped(x+1,  y).r / 255.0F;
                x02 = old_image.pixel_wrapped(x-1,  y+1).r / 255.0F;
                x12 = old_image.pixel_wrapped(x,    y+1).r / 255.0F;
                x22 = old_image.pixel_wrapped(x+1,  y+1).r / 255.0F;
            } else {
                x00 = old_image.pixel_clamped(x-1,  y-1).r / 255.0F;
                x10 = old_image.pixel_clamped(x,    y-1).r / 255.0F;
                x20 = old_image.pixel_clamped(x+1,  y-1).r / 255.0F;
                x01 = old_image.pixel_clamped(x-1,  y).r / 255.0F;
                x11 = old_image.pixel_clamped(x,    y).r / 255.0F;
                x21 = old_image.pixel_clamped(x+1,  y).r / 255.0F;
                x02 = old_image.pixel_clamped(x-1,  y+1).r / 255.0F;
                x12 = old_image.pixel_clamped(x,    y+1).r / 255.0F;
                x22 = old_image.pixel_clamped(x+1,  y+1).r / 255.0F;
            }

            // sobel filter
            float dx = -(x20 + 2.0F * x21 + x22) + (x00 + 2.0F * x01 + x02);
            float dy = (x02 + 2.0F * x12 + x22) - (x00 + 2.0F * x10 + x20);
            float dz = 1.0 / strength;

            float length = std::sqrt(dx*dx + dy*dy + dz*dz);

            dx /= length;
            dy /= length;
            dz /= length;

            Image::Pixel p;
            p.r = (dx * 0.5F + 0.5F) * 255;
            p.g = (dy * 0.5F + 0.5F) * 255;
            p.b = (dz * 0.5F + 0.5F) * 255;
            p.a = old_image.pixel(x, y).a;

			image.set_pixel(x, y, p);
		}
	}

}

//==============================================================================
//==============================================================================

int main (int argc, char * const argv[])
{
	if (argc < 3) {
		std::cout << "Usage: " << argv[0] << " [-remove_alpha] [-expand_alpha] [-fill_alpha_black] [-bump_to_normal strength wrap]outfile infile" << std::endl;
		exit(1);
	}
        
    std::string outfile_path = argv[argc-2];
    std::string infile_path = argv[argc-1];
    
    Image image;
    image.load(infile_path);
    
    for (int i = 1; i < argc-2; ++i) {
        std::string arg = argv[i];
    
        if (arg == "-remove_alpha")      
            remove_alpha(image);

        if (arg == "-expand_alpha")      
            expand_alpha(image);

        if (arg == "-fill_alpha_black")  
            fill_alpha_black(image);

        if (arg == "-bump_to_normal") {
            std::stringstream strength_str(argv[++i]);
            std::stringstream wrap_str(argv[++i]);

            float strength;
            bool wrap;

            strength_str >> strength;
            wrap_str >> wrap;

            bump_to_normal(image, strength, wrap);
        }
    }
    
    image.save(outfile_path);
	
    return 0;
}

