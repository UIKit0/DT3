//==============================================================================
///	
///	File: Framebuffer.cpp
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "DT3Core/Types/Graphics/Framebuffer.hpp"
#include "DT3Core/System/Factory.hpp"
#include "DT3Core/System/System.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
//==============================================================================

IMPLEMENT_FACTORY_CREATION(Framebuffer)

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

Framebuffer::Framebuffer (void)
{    

}
			
Framebuffer::~Framebuffer (void)
{ 

}

//==============================================================================
//==============================================================================

void Framebuffer::allocate (DTint width, DTint height, DT3GLTextelFormat color_format, DT3GLTextelFormat depth_format, DTuint num_color_targets)
{
    _color_texture.resize(num_color_targets);
    for (DTsize i = 0; i < _color_texture.size(); ++i) {
        _color_texture[i] = System::renderer()->create_texture_2D (width, height, NULL, color_format, false, DT3GL_ACCESS_CPU_NONE | DT3GL_ACCESS_GPU_WRITE);
    }

    _depth_texture = System::renderer()->create_texture_2D (width, height, NULL, depth_format, false, DT3GL_ACCESS_CPU_NONE | DT3GL_ACCESS_GPU_WRITE);

    _framebuffer = System::renderer()->create_framebuffer ();

    for (DTsize i = 0; i < _color_texture.size(); ++i) {
        System::renderer()->attach_framebuffer_color (_framebuffer, _color_texture[i], (DTuint) i);
    }
    
    System::renderer()->attach_framebuffer_depth_stencil (_framebuffer, _depth_texture);

    _rb_color_format = DT3GL_RB_FORMAT_NONE;
    _rb_depth_format = DT3GL_RB_FORMAT_NONE;
    
    _width = width;
    _height = height;
}

void Framebuffer::allocate (DTint width, DTint height, DT3GLTextelFormat color_format, DT3GLRenderBufferFormat depth_format, DTuint num_color_targets)
{
    _color_texture.resize(num_color_targets);
    for (DTsize i = 0; i < _color_texture.size(); ++i) {
        _color_texture[i] = System::renderer()->create_texture_2D (width, height, NULL, color_format, false, DT3GL_ACCESS_CPU_NONE | DT3GL_ACCESS_GPU_WRITE);
    }

    _framebuffer = System::renderer()->create_framebuffer();

    for (DTsize i = 0; i < _color_texture.size(); ++i) {
        System::renderer()->attach_framebuffer_color (_framebuffer, _color_texture[i], (DTuint) i);
    }
    
    if (depth_format != DT3GL_RB_FORMAT_NONE)
        System::renderer()->attach_renderbuffer_depth_stencil (_framebuffer, width, height, depth_format);

    _rb_color_format = DT3GL_RB_FORMAT_NONE;
    _rb_depth_format = depth_format;

    _width = width;
    _height = height;
}
    
void Framebuffer::allocate (DTint width, DTint height, DT3GLRenderBufferFormat color_format, DT3GLTextelFormat depth_format)
{
    _depth_texture = System::renderer()->create_texture_2D (width, height, NULL, depth_format, false, DT3GL_ACCESS_CPU_NONE | DT3GL_ACCESS_GPU_WRITE);

    _framebuffer = System::renderer()->create_framebuffer ();

    System::renderer()->attach_renderbuffer_color (_framebuffer, width, height, color_format);
    System::renderer()->attach_framebuffer_depth_stencil(_framebuffer, _depth_texture);

    _rb_color_format = color_format;
    _rb_depth_format = DT3GL_RB_FORMAT_NONE;

    _width = width;
    _height = height;
}

//==============================================================================
//==============================================================================

std::shared_ptr<DT3GLTexture2DResource>& Framebuffer::color_texture (DTuint color_target_index)
{
    return _color_texture[color_target_index];
}

std::shared_ptr<DT3GLTexture2DResource>& Framebuffer::depth_texture (void)
{
    return _depth_texture;
}

//==============================================================================
//==============================================================================

void Framebuffer::activate (void)
{
    System::renderer()->activate_framebuffer(_framebuffer);
}

//==============================================================================
//==============================================================================

} // DT3

