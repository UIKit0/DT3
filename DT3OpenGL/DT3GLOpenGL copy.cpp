//==============================================================================
///	
///	File: 			DT2GL.cpp
///	
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "DT2GLOpenGL.hpp"
#include "DT2GLOpenGLResources.hpp"
#include "ConsoleStream.hpp"

//==============================================================================
//==============================================================================

namespace DT2 {

//==============================================================================
//==============================================================================

namespace {

    DTuint gBlending[] = {
        /*DT2GL_BLEND_ZERO*/                GL_ZERO,
        /*DT2GL_BLEND_ONE*/                 GL_ONE,
        /*DT2GL_BLEND_SRC_ALPHA*/           GL_SRC_ALPHA,
        /*DT2GL_BLEND_ONE_MINUS_SRC_ALPHA*/ GL_ONE_MINUS_SRC_ALPHA,
        /*DT2GL_BLEND_DST_ALPHA*/           GL_DST_ALPHA,
        /*DT2GL_BLEND_ONE_MINUS_DST_ALPHA*/ GL_ONE_MINUS_DST_ALPHA,
        /*DT2GL_BLEND_SRC_COLOR*/           GL_SRC_COLOR,
        /*DT2GL_BLEND_DST_COLOR*/           GL_DST_COLOR,
        /*DT2GL_BLEND_ONE_MINUS_SRC_COLOR*/ GL_ONE_MINUS_SRC_COLOR,
        /*DT2GL_BLEND_ONE_MINUS_DST_COLOR*/ GL_ONE_MINUS_DST_COLOR
    };

    DTuint gCulling[] = {
        /*DT2GL_FRONT*/                     GL_FRONT,
        /*DT2GL_BACK*/                      GL_BACK
    };
    
//    DTuint gWrap[] = {
//        /*TEXTURE_WRAP_REPEAT*/			GL_REPEAT,
//        /*TEXTURE_WRAP_CLAMP*/			GL_CLAMP_TO_EDGE
//    };
//
//    DTuint gFilterMode[] = {
//        /*TEXTURE_FILTER_NEAREST*/		GL_NEAREST,
//        /*TEXTURE_FILTER_LINEAR*/		GL_LINEAR,
//        /*TEXTURE_FILTER_MIPMAP_LINEAR*/GL_LINEAR_MIPMAP_LINEAR
//    };
    
	DTuint gComparison[] = {
        /*DT2GL_ALWAYS*/                GL_ALWAYS,
        /*DT2GL_NEVER*/                 GL_NEVER,
        /*DT2GL_EQUAL*/                 GL_EQUAL,
        /*DT2GL_NOTEQUAL*/              GL_NOTEQUAL,
        /*DT2GL_GREATER*/               GL_GREATER,
        /*DT2GL_GEQUAL*/                GL_GEQUAL,
        /*DT2GL_LESS*/                  GL_LESS,
        /*DT2GL_LEQUAL*/                GL_LEQUAL
	};
    
	DTuint gStencilOp[] = {
        /*DT2GL_STENCILOP_KEEP*/        GL_KEEP,
        /*DT2GL_STENCILOP_ZERO*/        GL_ZERO,
        /*DT2GL_STENCILOP_REPLACE*/     GL_REPLACE,
        /*DT2GL_STENCILOP_INCR*/        GL_INCR,
        /*DT2GL_STENCILOP_DECR*/        GL_DECR,
        /*DT2GL_STENCILOP_INCR_WRAP*/   GL_INCR_WRAP,
        /*DT2GL_STENCILOP_DECR_WRAP*/   GL_DECR_WRAP,
        /*DT2GL_STENCILOP_INVERT*/      GL_INVERT
	};
    
}

//==============================================================================
// _____             _   _        _____ _                  _ _
//|  __ \           | | | |      / ____| |                (_) |
//| |  | | ___ _ __ | |_| |__   | (___ | |_ ___ _ __   ___ _| |
//| |  | |/ _ \ '_ \| __| '_ \   \___ \| __/ _ \ '_ \ / __| | |
//| |__| |  __/ |_) | |_| | | |  ____) | ||  __/ | | | (__| | |
//|_____/ \___| .__/ \__|_| |_| |_____/ \__\___|_| |_|\___|_|_|
//            | |
//            |_|
//==============================================================================

void DT2GLOpenGL::create_depth_stencil_state      (std::shared_ptr<DT3GLDepthStencilResource> &res, const DT3GLDepthStencilState &state, DTuint flags = DT3GL_ACCESS_CPU_NONE | DT3GL_ACCESS_GPU_READ);
{
    // Build resource
    DT2GLOpenGLDepthStencilResource *r = new DT2GLOpenGLDepthStencilResource();
    res = SmartPtr<DT2GLDepthStencilResource>(r);

    r->flags = flags;
    
    append(makeLatentCall(this, &DT2GLOpenGL::createDepthStencilStateImpl, res, state, flags));
}

void DT2GLOpenGL::createDepthStencilStateImpl (SmartPtr<DT2GLDepthStencilResource> &res, const DT2GLDepthStencilState &state, DTuint flags)
{
    // Do nothing
}

//==============================================================================
//==============================================================================

void DT2GLOpenGL::updateDepthStencilState (SmartPtr<DT2GLDepthStencilResource> res, const DT2GLDepthStencilState &state)
{
    append(makeLatentCall(this, &DT2GLOpenGL::updateDepthStencilStateImpl, res, state));
}

void DT2GLOpenGL::updateDepthStencilStateImpl (SmartPtr<DT2GLDepthStencilResource> res, const DT2GLDepthStencilState &state)
{
    DT2GLOpenGLDepthStencilResource *r = static_cast<DT2GLOpenGLDepthStencilResource*>(res.get());
    r->state = state;
}

//==============================================================================
//==============================================================================

void DT2GLOpenGL::activateDepthStencilState (SmartPtr<DT2GLDepthStencilResource> res)
{
    append(makeLatentCall(this, &DT2GLOpenGL::activateDepthStencilStateImpl, res));
}

void DT2GLOpenGL::activateDepthStencilStateImpl (SmartPtr<DT2GLDepthStencilResource> res)
{
    DT2GLOpenGLDepthStencilResource *r = static_cast<DT2GLOpenGLDepthStencilResource*>(res.get());

    // Depth
    if (r->state.depth_enable)          ::glEnable(GL_DEPTH_TEST);
    else                                ::glDisable(GL_DEPTH_TEST);

    if (r->state.depth_write_mask)      ::glDepthMask(GL_TRUE);
    else                                ::glDepthMask(GL_FALSE);

    ::glDepthFunc(gComparison[r->state.depth_func]);

    // Stencil
    if (r->state.stencil_enable)        ::glEnable(GL_STENCIL_TEST);
    else                                ::glDisable(GL_STENCIL_TEST);

    ::glStencilMask(r->state.stencil_write_mask);

    ::glStencilOpSeparate(  GL_FRONT,
                            gStencilOp[r->state.front_face_stencil_fail_op],
                            gStencilOp[r->state.front_face_stencil_depth_fail_op],
                            gStencilOp[r->state.front_face_stencil_pass_op]);


    ::glStencilFuncSeparate(GL_FRONT,
                            gComparison[r->state.front_face_stencil_func],
                            _stencil_ref,
                            r->state.stencil_read_mask);

    ::glStencilOpSeparate(  GL_BACK,
                            gStencilOp[r->state.back_face_stencil_fail_op],
                            gStencilOp[r->state.back_face_stencil_depth_fail_op],
                            gStencilOp[r->state.back_face_stencil_pass_op]);


    ::glStencilFuncSeparate(GL_BACK,
                            gComparison[r->state.back_face_stencil_func],
                            _stencil_ref,
                            r->state.stencil_read_mask);

}

void DT2GLOpenGL::setStencilRef (DTuint ref)
{
    append(makeLatentCall(this, &DT2GLOpenGL::setStencilRefImpl, ref));
}

void DT2GLOpenGL::setStencilRefImpl (DTuint ref)
{
    _stencil_ref = ref;
}

//==============================================================================
// ____  _                _
//|  _ \| |              | |
//| |_) | | ___ _ __   __| |
//|  _ <| |/ _ \ '_ \ / _` |
//| |_) | |  __/ | | | (_| |
//|____/|_|\___|_| |_|\__,_|
//==============================================================================

void DT2GLOpenGL::createBlendState (SmartPtr<DT2GLBlendResource> &res, const DT2GLBlendState &state, DTuint flags)
{
    // Build resource
    DT2GLOpenGLBlendResource *r = new DT2GLOpenGLBlendResource();
    res = SmartPtr<DT2GLBlendResource>(r);

    r->flags = flags;
    
    append(makeLatentCall(this, &DT2GLOpenGL::createBlendStateImpl, res, state, flags));
}

void DT2GLOpenGL::createBlendStateImpl (SmartPtr<DT2GLBlendResource> &res, const DT2GLBlendState &state, DTuint flags)
{
    // Do nothing
}

//==============================================================================
//==============================================================================

void DT2GLOpenGL::updateBlendState (SmartPtr<DT2GLBlendResource> res, const DT2GLBlendState &state)
{
    append(makeLatentCall(this, &DT2GLOpenGL::updateBlendStateImpl, res, state));
}

void DT2GLOpenGL::updateBlendStateImpl (SmartPtr<DT2GLBlendResource> res, const DT2GLBlendState &state)
{
    DT2GLOpenGLBlendResource *r = static_cast<DT2GLOpenGLBlendResource*>(res.get());
    r->state = state;
}

//==============================================================================
//==============================================================================

void DT2GLOpenGL::activateBlendState (SmartPtr<DT2GLBlendResource> res)
{
    append(makeLatentCall(this, &DT2GLOpenGL::activateBlendStateImpl, res));
}

void DT2GLOpenGL::activateBlendStateImpl (SmartPtr<DT2GLBlendResource> res)
{
    DT2GLOpenGLBlendResource *r = static_cast<DT2GLOpenGLBlendResource*>(res.get());

    // Blend
    if (r->state.blend_enable)          ::glEnable(GL_BLEND);
    else                                ::glDisable(GL_BLEND);

    ::glBlendFuncSeparate(  gBlending[r->state.src_blend],
                            gBlending[r->state.dest_blend],
                            gBlending[r->state.src_blend_alpha],
                            gBlending[r->state.dest_blend_alpha]);

    ::glColorMask(  r->state.render_target_write_mask_r,
                    r->state.render_target_write_mask_g,
                    r->state.render_target_write_mask_b,
                    r->state.render_target_write_mask_a);
}

//==============================================================================
// _____           _            _
//|  __ \         | |          (_)
//| |__) |__ _ ___| |_ ___ _ __ _ _______ _ __
//|  _  // _` / __| __/ _ \ '__| |_  / _ \ '__|
//| | \ \ (_| \__ \ ||  __/ |  | |/ /  __/ |
//|_|  \_\__,_|___/\__\___|_|  |_/___\___|_|
//
//==============================================================================

void DT2GLOpenGL::createRasterizerState (SmartPtr<DT2GLRasterizerResource> &res, const DT2GLRasterizerState &state, DTuint flags)
{
    // Build resource
    DT2GLOpenGLRasterizerResource *r = new DT2GLOpenGLRasterizerResource();
    res = SmartPtr<DT2GLRasterizerResource>(r);

    r->flags = flags;
    
    append(makeLatentCall(this, &DT2GLOpenGL::createRasterizerStateImpl, res, state, flags));
}

void DT2GLOpenGL::createRasterizerStateImpl (SmartPtr<DT2GLRasterizerResource> &res, const DT2GLRasterizerState &state, DTuint flags)
{
    // Do nothing
}

//==============================================================================
//==============================================================================

void DT2GLOpenGL::updateRasterizerState (SmartPtr<DT2GLRasterizerResource> res, const DT2GLRasterizerState &state)
{
    append(makeLatentCall(this, &DT2GLOpenGL::updateRasterizerStateImpl, res, state));
}

void DT2GLOpenGL::updateRasterizerStateImpl (SmartPtr<DT2GLRasterizerResource> res, const DT2GLRasterizerState &state)
{
    DT2GLOpenGLRasterizerResource *r = static_cast<DT2GLOpenGLRasterizerResource*>(res.get());
    r->state = state;
}

//==============================================================================
//==============================================================================

void DT2GLOpenGL::activateRasterizerState (SmartPtr<DT2GLRasterizerResource> res)
{
    append(makeLatentCall(this, &DT2GLOpenGL::activateRasterizerStateImpl, res));
}
    
void DT2GLOpenGL::activateRasterizerStateImpl (SmartPtr<DT2GLRasterizerResource> res)
{
    DT2GLOpenGLRasterizerResource *r = static_cast<DT2GLOpenGLRasterizerResource*>(res.get());

    // Culling
    ::glCullFace(gCulling[r->state.cull_mode]);

    // TODO Depth bias
    //::glPolygonOffset(factor, units)

    // Scissor
    if (r->state.scissor_enable)    ::glEnable(GL_SCISSOR_TEST);
    else                            ::glDisable(GL_SCISSOR_TEST);
}

//==============================================================================
//  _____                       _
// / ____|                     | |
//| (___   __ _ _ __ ___  _ __ | | ___ _ __
// \___ \ / _` | '_ ` _ \| '_ \| |/ _ \ '__|
// ____) | (_| | | | | | | |_) | |  __/ |
//|_____/ \__,_|_| |_| |_| .__/|_|\___|_|
//                       | |
//                       |_|
//==============================================================================

void DT2GLOpenGL::createSamplerState (SmartPtr<DT2GLSamplerResource> &res, const DT2GLSamplerState &state, DTuint flags)
{
    // Build resource
    DT2GLOpenGLSamplerResource *r = new DT2GLOpenGLSamplerResource();
    res = SmartPtr<DT2GLSamplerResource>(r);

    r->flags = flags;
    
    append(makeLatentCall(this, &DT2GLOpenGL::createSamplerStateImpl, res, state, flags));
}

void DT2GLOpenGL::createSamplerStateImpl (SmartPtr<DT2GLSamplerResource> &res, const DT2GLSamplerState &state, DTuint flags)
{
    // Do nothing
}

//==============================================================================
//==============================================================================

void DT2GLOpenGL::updateSamplerState (SmartPtr<DT2GLSamplerResource> res, const DT2GLSamplerState &state)
{
    append(makeLatentCall(this, &DT2GLOpenGL::updateSamplerStateImpl, res, state));
}

void DT2GLOpenGL::updateSamplerStateImpl (SmartPtr<DT2GLSamplerResource> res, const DT2GLSamplerState &state)
{
    DT2GLOpenGLSamplerResource *r = static_cast<DT2GLOpenGLSamplerResource*>(res.get());
    r->state = state;
}

//==============================================================================
// _______        _                    ___  _____
//|__   __|      | |                  |__ \|  __ \
//   | | _____  _| |_ _   _ _ __ ___     ) | |  | |
//   | |/ _ \ \/ / __| | | | '__/ _ \   / /| |  | |
//   | |  __/>  <| |_| |_| | | |  __/  / /_| |__| |
//   |_|\___/_/\_\\__|\__,_|_|  \___| |____|_____/
//==============================================================================

void DT2GLOpenGL::createTexture2D (SmartPtr<DT2GLTexture2DResource> &res, DTint width, DTint height, SmartPtr<ArrayBlock<DTubyte> > textels, DTGLTextelFormat format, DTboolean mipmapped, DTuint flags)
{
    // Build resource
    DT2GLOpenGLTexture2DResource *r = new DT2GLOpenGLTexture2DResource();
    res = SmartPtr<DT2GLTexture2DResource>(r);

    r->flags = flags;
    
    append(makeLatentCall(this, &DT2GLOpenGL::createTexture2DImpl, res, width, height, textels, format, mipmapped, flags));
}

void DT2GLOpenGL::createTexture2DImpl (SmartPtr<DT2GLTexture2DResource> &res, DTint width, DTint height, SmartPtr<ArrayBlock<DTubyte> > textels, DTGLTextelFormat format, DTboolean mipmapped, DTuint flags)
{
    GLint save_tex;
    ::glGetIntegerv(GL_TEXTURE_BINDING_2D, &save_tex);

    DT2GLOpenGLTexture2DResource *r = static_cast<DT2GLOpenGLTexture2DResource*>(res.get());

    r->format = format;
    r->mipmapped = mipmapped;

    ::glGenTextures(1,&r->name);
    
    GLvoid *buffer = textels->getBuffer();
    DTsize size = textels->size();
    
    if (size == 0)
        buffer = NULL;

    // Create OpenGL2 Texture
    ::glBindTexture(GL_TEXTURE_2D, r->name);          //	bind the texture
    
    ::glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    // Build texture based on the format
    switch (r->format) {
    
        case DT2GL_FORMAT_RGBA:
            ::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
            break;
        case DT2GL_FORMAT_BGRA:
            ::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRAM, GL_UNSIGNED_BYTE, buffer);
            break;
        case DT2GL_FORMAT_RGBA_5551:
            ::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, buffer);
            break;
        case DT2GL_FORMAT_RGBA_4444:
            ::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, buffer);
            break;
        case DT2GL_FORMAT_RGB_565:
            ::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, buffer);
            break;
        case DT2GL_FORMAT_LUM_8:
            ::glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, width, height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, buffer);
            break;
        case DT2GL_FORMAT_RGB:
            ::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
            break;
        case DT2GL_FORMAT_DEPTH_16:
            ::glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16M, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, NULL);
            break;
        case DT2GL_FORMAT_DEPTH_24:
            ::glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24M, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, NULL);
            break;

#if DT2_OS == DT2_IOS || DT2_OS == DT2_ANDROID
        case DT2GL_FORMAT_PVR2_RGBA:
            ::glCompressedTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG, width, height, 0, compressed_size, buffer);
            break;
        case DT2GL_FORMAT_PVR4_RGBA:
            ::glCompressedTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG, width, height, 0, compressed_size, buffer);
            break;
        case DT2GL_FORMAT_PVR2_RGB:
            ::glCompressedTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG, width, height, 0, compressed_size, buffer);
            break;
        case DT2GL_FORMAT_PVR4_RGB:
            ::glCompressedTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG, width, height, 0, compressed_size, buffer);
            break;
#endif

        default:
            Assert(0);

    }
    
	if (r->mipmapped) {
		::glGenerateMipmapM(GL_TEXTURE_2D);   // establish a mipmap chain for the texture
	}

	::glBindTexture(GL_TEXTURE_2D, save_tex);
}

//==============================================================================
//==============================================================================

void DT2GLOpenGL::updateTexture2D (SmartPtr<DT2GLTexture2DResource> res, DTint x, DTint y, DTint width, DTint height, SmartPtr<ArrayBlock<DTubyte> > textels)
{
    append(makeLatentCall(this, &DT2GLOpenGL::updateTexture2DImpl, res, x, y, width, height, textels));
}

void DT2GLOpenGL::updateTexture2DImpl (SmartPtr<DT2GLTexture2DResource> res, DTint x, DTint y, DTint width, DTint height, SmartPtr<ArrayBlock<DTubyte> > textels)
{
    GLint save_tex;
    ::glGetIntegerv(GL_TEXTURE_BINDING_2D, &save_tex);

    DT2GLOpenGLTexture2DResource *r = static_cast<DT2GLOpenGLTexture2DResource*>(res.get());

    GLvoid *buffer = textels->getBuffer();

    // Create OpenGLES2 Texture
    ::glBindTexture(GL_TEXTURE_2D, r->name);          //	bind the texture
    
    ::glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	   
    // Build texture based on the format
    switch (r->format) {

        case DT2GL_FORMAT_RGBA:
            ::glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
            break;
        case DT2GL_FORMAT_BGRA:
            ::glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_BGRAM, GL_UNSIGNED_BYTE, buffer);
            break;
        case DT2GL_FORMAT_RGBA_5551:
            ::glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, buffer);
            break;
        case DT2GL_FORMAT_RGBA_4444:
            ::glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, buffer);
            break;
        case DT2GL_FORMAT_RGB_565:
            ::glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, buffer);
            break;
        case DT2GL_FORMAT_LUM_8:
            ::glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_LUMINANCE, GL_UNSIGNED_BYTE, buffer);
            break;
        case DT2GL_FORMAT_RGB:
            ::glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer);
            break;
        case DT2GL_FORMAT_DEPTH_16:
            Assert(0);
            break;
        case DT2GL_FORMAT_DEPTH_24:
            Assert(0);
            break;
#if DT2_OS == DT2_IOS || DT2_OS == DT2_ANDROID
        case DT2GL_FORMAT_PVR2_RGBA:
            Assert(0);
            break;
        case DT2GL_FORMAT_PVR4_RGBA:
            Assert(0);
            break;
        case DT2GL_FORMAT_PVR2_RGB:
            Assert(0);
            break;
        case DT2GL_FORMAT_PVR4_RGB:
            Assert(0);
            break;
#endif

        default:
            Assert(0);

    }

	if (r->mipmapped) {
		::glGenerateMipmapM(GL_TEXTURE_2D);   // establish a mipmap chain for the texture
	}

	::glBindTexture(GL_TEXTURE_2D, save_tex);
}

//==============================================================================
// _______        _                    ____  _____
//|__   __|      | |                  |___ \|  __ \
//   | | _____  _| |_ _   _ _ __ ___    __) | |  | |
//   | |/ _ \ \/ / __| | | | '__/ _ \  |__ <| |  | |
//   | |  __/>  <| |_| |_| | | |  __/  ___) | |__| |
//   |_|\___/_/\_\\__|\__,_|_|  \___| |____/|_____/
//==============================================================================

void DT2GLOpenGL::createTexture3D (SmartPtr<DT2GLTexture3DResource> &res, DTint width, DTint height, DTint depth, SmartPtr<ArrayBlock<DTubyte> > textels, DTGLTextelFormat format, DTboolean mipmapped, DTuint flags)
{
    // Build resource
    DT2GLOpenGLTexture3DResource *r = new DT2GLOpenGLTexture3DResource();
    res = SmartPtr<DT2GLTexture3DResource>(r);

    r->flags = flags;
    
    append(makeLatentCall(this, &DT2GLOpenGL::createTexture3DImpl, res, width, height, depth, textels, format, mipmapped, flags));
}

void DT2GLOpenGL::createTexture3DImpl (SmartPtr<DT2GLTexture3DResource> &res, DTint width, DTint height, DTint depth, SmartPtr<ArrayBlock<DTubyte> > textels, DTGLTextelFormat format, DTboolean mipmapped, DTuint flags)
{
    GLint save_tex;
    ::glGetIntegerv(GL_TEXTURE_BINDING_3D, &save_tex);

    DT2GLOpenGLTexture3DResource *r = static_cast<DT2GLOpenGLTexture3DResource*>(res.get());

    r->format = format;
    r->mipmapped = mipmapped;

    ::glGenTextures(1,&r->name);
    
    GLvoid *buffer = textels->getBuffer();
    DTsize size = textels->size();
    
    if (size == 0)
        buffer = NULL;

    // Create OpenGL2 Texture
    ::glBindTexture(GL_TEXTURE_3D, r->name);          //	bind the texture
    
    ::glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    switch (r->format) {
    
        case DT2GL_FORMAT_RGBA:
            ::glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, width, height, depth, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);  
            break;
        case DT2GL_FORMAT_BGRA:
            ::glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, width, height, depth, 0, GL_BGRAM, GL_UNSIGNED_BYTE, buffer);
            break;
        case DT2GL_FORMAT_RGBA_5551:
            ::glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, width, height, depth, 0, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, buffer);
            break;
        case DT2GL_FORMAT_RGBA_4444:
            ::glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, width, height, depth, 0, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, buffer);
            break;
        case DT2GL_FORMAT_RGB_565:
            ::glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB, width, height, depth, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, buffer);
            break;
        case DT2GL_FORMAT_LUM_8:
            ::glTexImage3D(GL_TEXTURE_3D, 0, GL_LUMINANCE, width, height, depth, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, buffer);
            break;
        case DT2GL_FORMAT_RGB:
            ::glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB, width, height, depth, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
            break;
        case DT2GL_FORMAT_DEPTH_16:
            Assert(0);
            break;
        case DT2GL_FORMAT_DEPTH_24:
            Assert(0);
            break;
    #if DT2_OS == DT2_IOS || DT2_OS == DT2_ANDROID
        case DT2GL_FORMAT_PVR2_RGBA:
            Assert(0);
            break;
        case DT2GL_FORMAT_PVR4_RGBA:
            Assert(0);
            break;
        case DT2GL_FORMAT_PVR2_RGB:
            Assert(0);
            break;
        case DT2GL_FORMAT_PVR4_RGB:
            Assert(0);
            break;
    #endif

        default:
            Assert(0);
    }

	if (r->mipmapped) {
		::glGenerateMipmapM(GL_TEXTURE_3D);   // establish a mipmap chain for the texture
	}
    
	::glBindTexture(GL_TEXTURE_3D, save_tex);
}

//==============================================================================
//==============================================================================

void DT2GLOpenGL::updateTexture3D (SmartPtr<DT2GLTexture3DResource> res, DTint x, DTint y, DTint z, DTint width, DTint height, DTint depth, SmartPtr<ArrayBlock<DTubyte> > textels)
{
    append(makeLatentCall(this, &DT2GLOpenGL::updateTexture3DImpl, res, x, y, z, width, height, depth, textels));
}

void DT2GLOpenGL::updateTexture3DImpl (SmartPtr<DT2GLTexture3DResource> res, DTint x, DTint y, DTint z, DTint width, DTint height, DTint depth, SmartPtr<ArrayBlock<DTubyte> > textels)
{
    GLint save_tex;
    ::glGetIntegerv(GL_TEXTURE_BINDING_3D, &save_tex);

    DT2GLOpenGLTexture3DResource *r = static_cast<DT2GLOpenGLTexture3DResource*>(res.get());

    GLvoid *buffer = textels->getBuffer();

    // Create OpenGLES2 Texture
    ::glBindTexture(GL_TEXTURE_2D, r->name);          //	bind the texture
    
    ::glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	   
    // Build texture based on the format
    switch (r->format) {

        case DT2GL_FORMAT_RGBA:
            ::glTexSubImage3D(GL_TEXTURE_3D, 0, x, y, z, width, height, depth, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
            break;
        case DT2GL_FORMAT_BGRA:
            ::glTexSubImage3D(GL_TEXTURE_3D, 0, x, y, z, width, height, depth, GL_BGRAM, GL_UNSIGNED_BYTE, buffer);
            break;
        case DT2GL_FORMAT_RGBA_5551:
            ::glTexSubImage3D(GL_TEXTURE_3D, 0, x, y, z, width, height, depth, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, buffer);
            break;
        case DT2GL_FORMAT_RGBA_4444:
            ::glTexSubImage3D(GL_TEXTURE_3D, 0, x, y, z, width, height, depth, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, buffer);
            break;
        case DT2GL_FORMAT_RGB_565:
            ::glTexSubImage3D(GL_TEXTURE_3D, 0, x, y, z, width, height, depth, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, buffer);
            break;
        case DT2GL_FORMAT_LUM_8:
            ::glTexSubImage3D(GL_TEXTURE_3D, 0, x, y, z, width, height, depth, GL_LUMINANCE, GL_UNSIGNED_BYTE, buffer);
            break;
        case DT2GL_FORMAT_RGB:
            ::glTexSubImage3D(GL_TEXTURE_3D, 0, x, y, z, width, height, depth, GL_RGB, GL_UNSIGNED_BYTE, buffer);
            break;
        case DT2GL_FORMAT_DEPTH_16:
            Assert(0);
            break;
        case DT2GL_FORMAT_DEPTH_24:
            Assert(0);
            break;
    #if DT2_OS == DT2_IOS || DT2_OS == DT2_ANDROID
        case DT2GL_FORMAT_PVR2_RGBA:
            Assert(0);
            break;
        case DT2GL_FORMAT_PVR4_RGBA:
            Assert(0);
            break;
        case DT2GL_FORMAT_PVR2_RGB:
            Assert(0);
            break;
        case DT2GL_FORMAT_PVR4_RGB:
            Assert(0);
            break;
    #endif

        default:
            Assert(0);

    }

	if (r->mipmapped) {
		::glGenerateMipmapM(GL_TEXTURE_3D);   // establish a mipmap chain for the texture
	}
    
	::glBindTexture(GL_TEXTURE_3D, save_tex);
}

//==============================================================================
// _______        _                     _____      _
//|__   __|      | |                   / ____|    | |
//   | | _____  _| |_ _   _ _ __ ___  | |    _   _| |__   ___
//   | |/ _ \ \/ / __| | | | '__/ _ \ | |   | | | | '_ \ / _ \
//   | |  __/>  <| |_| |_| | | |  __/ | |___| |_| | |_) |  __/
//   |_|\___/_/\_\\__|\__,_|_|  \___|  \_____\__,_|_.__/ \___|
//==============================================================================

void DT2GLOpenGL::createTextureCube (SmartPtr<DT2GLTextureCubeResource> &res, DTint width, DTint height,
                                            SmartPtr<ArrayBlock<DTubyte> > textels_front,
                                            SmartPtr<ArrayBlock<DTubyte> > textels_back,
                                            SmartPtr<ArrayBlock<DTubyte> > textels_left,
                                            SmartPtr<ArrayBlock<DTubyte> > textels_right,
                                            SmartPtr<ArrayBlock<DTubyte> > textels_top,
                                            SmartPtr<ArrayBlock<DTubyte> > textels_bottom,
                                            DTGLTextelFormat format,
                                            DTboolean mipmapped,
                                            DTuint flags)
{
    // Build resource
    DT2GLOpenGLTextureCubeResource *r = new DT2GLOpenGLTextureCubeResource();
    res = SmartPtr<DT2GLTextureCubeResource>(r);

    r->flags = flags;
    
    append(makeLatentCall(this, &DT2GLOpenGL::createTextureCubeImpl, res, width, height,
            textels_front, textels_back, textels_left, textels_right, textels_top, textels_bottom, format, mipmapped, flags));
}

void DT2GLOpenGL::createTextureCubeImpl (SmartPtr<DT2GLTextureCubeResource> &res, DTint width, DTint height,
                                            SmartPtr<ArrayBlock<DTubyte> > textels_front,
                                            SmartPtr<ArrayBlock<DTubyte> > textels_back,
                                            SmartPtr<ArrayBlock<DTubyte> > textels_left,
                                            SmartPtr<ArrayBlock<DTubyte> > textels_right,
                                            SmartPtr<ArrayBlock<DTubyte> > textels_top,
                                            SmartPtr<ArrayBlock<DTubyte> > textels_bottom,
                                            DTGLTextelFormat format,
                                            DTboolean mipmapped,
                                            DTuint flags)
{
    GLint save_tex;
    ::glGetIntegerv(GL_TEXTURE_BINDING_CUBE_MAP, &save_tex);

    DT2GLOpenGLTextureCubeResource *r = static_cast<DT2GLOpenGLTextureCubeResource*>(res.get());

    r->format = format;
    r->mipmapped = mipmapped;

    ::glGenTextures(1,&r->name);
    
    // Create OpenGL2 Texture
    ::glBindTexture(GL_TEXTURE_CUBE_MAPM, r->name);          //	bind the texture
    
    ::glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    for (DTuint f = 0; f < 6; ++f) {
    
        GLenum face;
        GLvoid *buffer;
        DTsize size;

        switch (f) {
            case 0: face = GL_TEXTURE_CUBE_MAP_POSITIVE_ZM;  buffer = textels_front->getBuffer();   size = textels_front->size();   break;
            case 1: face = GL_TEXTURE_CUBE_MAP_NEGATIVE_ZM;  buffer = textels_back->getBuffer();    size = textels_back->size();    break;
            case 2: face = GL_TEXTURE_CUBE_MAP_POSITIVE_YM;  buffer = textels_top->getBuffer();     size = textels_top->size();     break;
            case 3: face = GL_TEXTURE_CUBE_MAP_NEGATIVE_YM;  buffer = textels_bottom->getBuffer();  size = textels_bottom->size();  break;
            case 4: face = GL_TEXTURE_CUBE_MAP_POSITIVE_XM;  buffer = textels_left->getBuffer();    size = textels_left->size();    break;
            case 5: face = GL_TEXTURE_CUBE_MAP_NEGATIVE_XM;  buffer = textels_right->getBuffer();   size = textels_right->size();   break;
        };
        
        // Check size to make sure there's data
        if (size == 0)
            buffer = NULL;
        
        switch (r->format) {
	    
            case DT2GL_FORMAT_RGBA:
                ::glTexImage2D(face, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
                break;
            case DT2GL_FORMAT_BGRA:
                ::glTexImage2D(face, 0, GL_RGBA, width, height, 0, GL_BGRAM, GL_UNSIGNED_BYTE, buffer);
                break;
            case DT2GL_FORMAT_RGBA_5551:
                ::glTexImage2D(face, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, buffer);
                break;
            case DT2GL_FORMAT_RGBA_4444:
                ::glTexImage2D(face, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, buffer);
                break;
            case DT2GL_FORMAT_RGB_565:
                ::glTexImage2D(face, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, buffer);
                break;
            case DT2GL_FORMAT_LUM_8:
                ::glTexImage2D(face, 0, GL_LUMINANCE, width, height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, buffer);
                break;
            case DT2GL_FORMAT_RGB:
                ::glTexImage2D(face, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
                break;
            default:
                Assert(0);
                break;
        }
        
        if (r->mipmapped) {
            ::glGenerateMipmapM(GL_TEXTURE_CUBE_MAPM);   // establish a mipmap chain for the texture
        }
    
    }

	::glBindTexture(GL_TEXTURE_CUBE_MAP, save_tex);
}

//==============================================================================
//==============================================================================

void DT2GLOpenGL::updateTextureCube (SmartPtr<DT2GLTextureCubeResource> res, DTint x, DTint y, DTint width, DTint height,
                                            SmartPtr<ArrayBlock<DTubyte> > textels_front,
                                            SmartPtr<ArrayBlock<DTubyte> > textels_back,
                                            SmartPtr<ArrayBlock<DTubyte> > textels_left,
                                            SmartPtr<ArrayBlock<DTubyte> > textels_right,
                                            SmartPtr<ArrayBlock<DTubyte> > textels_top,
                                            SmartPtr<ArrayBlock<DTubyte> > textels_bottom)
{
    append(makeLatentCall(this, &DT2GLOpenGL::updateTextureCubeImpl, res, x, y, width, height,
        textels_front, textels_back, textels_left, textels_right, textels_top, textels_bottom));


}

void DT2GLOpenGL::updateTextureCubeImpl (SmartPtr<DT2GLTextureCubeResource> res, DTint x, DTint y, DTint width, DTint height,
                                            SmartPtr<ArrayBlock<DTubyte> > textels_front,
                                            SmartPtr<ArrayBlock<DTubyte> > textels_back,
                                            SmartPtr<ArrayBlock<DTubyte> > textels_left,
                                            SmartPtr<ArrayBlock<DTubyte> > textels_right,
                                            SmartPtr<ArrayBlock<DTubyte> > textels_top,
                                            SmartPtr<ArrayBlock<DTubyte> > textels_bottom)
{
    GLint save_tex;
    ::glGetIntegerv(GL_TEXTURE_BINDING_CUBE_MAP, &save_tex);

    DT2GLOpenGLTextureCubeResource *r = static_cast<DT2GLOpenGLTextureCubeResource*>(res.get());

    // Create OpenGLES2 Texture
    ::glBindTexture(GL_TEXTURE_2D, r->name);          //	bind the texture
    
    ::glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (DTuint f = 0; f < 6; ++f) {
    
        GLenum face;
        GLvoid *buffer;
        DTsize size;
        
        switch (f) {
            case 0: face = GL_TEXTURE_CUBE_MAP_POSITIVE_ZM;  buffer = textels_front->getBuffer();   size = textels_front->size();   break;
            case 1: face = GL_TEXTURE_CUBE_MAP_NEGATIVE_ZM;  buffer = textels_back->getBuffer();    size = textels_back->size();    break;
            case 2: face = GL_TEXTURE_CUBE_MAP_POSITIVE_YM;  buffer = textels_top->getBuffer();     size = textels_top->size();     break;
            case 3: face = GL_TEXTURE_CUBE_MAP_NEGATIVE_YM;  buffer = textels_bottom->getBuffer();  size = textels_bottom->size();  break;
            case 4: face = GL_TEXTURE_CUBE_MAP_POSITIVE_XM;  buffer = textels_left->getBuffer();    size = textels_left->size();    break;
            case 5: face = GL_TEXTURE_CUBE_MAP_NEGATIVE_XM;  buffer = textels_right->getBuffer();   size = textels_right->size();   break;
        };
        
        // Check size to make sure there's data
        if (size == 0)
            continue;
        
        // Build texture based on the format
        switch (r->format) {

            case DT2GL_FORMAT_RGBA:
                ::glTexSubImage2D(face, 0, x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
                break;
            case DT2GL_FORMAT_BGRA:
                ::glTexSubImage2D(face, 0, x, y, width, height, GL_BGRAM, GL_UNSIGNED_BYTE, buffer);
                break;
            case DT2GL_FORMAT_RGBA_5551:
                ::glTexSubImage2D(face, 0, x, y, width, height, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, buffer);
                break;
            case DT2GL_FORMAT_RGBA_4444:
                ::glTexSubImage2D(face, 0, x, y, width, height, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, buffer);
                break;
            case DT2GL_FORMAT_RGB_565:
                ::glTexSubImage2D(face, 0, x, y, width, height, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, buffer);
                break;
            case DT2GL_FORMAT_LUM_8:
                ::glTexSubImage2D(face, 0, x, y, width, height, GL_LUMINANCE, GL_UNSIGNED_BYTE, buffer);
                break;
            case DT2GL_FORMAT_RGB:
                ::glTexSubImage2D(face, 0, x, y, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer);
                break;
            case DT2GL_FORMAT_DEPTH_16:
                Assert(0);
                break;
            case DT2GL_FORMAT_DEPTH_24:
                Assert(0);
                break;
#if DT2_OS == DT2_IOS || DT2_OS == DT2_ANDROID
            case DT2GL_FORMAT_PVR2_RGBA:
                Assert(0);
                break;
            case DT2GL_FORMAT_PVR4_RGBA:
                Assert(0);
                break;
            case DT2GL_FORMAT_PVR2_RGB:
                Assert(0);
                break;
            case DT2GL_FORMAT_PVR4_RGB:
                Assert(0);
                break;
#endif

            default:
                Assert(0);

        }
        
        if (r->mipmapped) {
            ::glGenerateMipmapM(GL_TEXTURE_CUBE_MAPM);   // establish a mipmap chain for the texture
        }
    
    }

	::glBindTexture(GL_TEXTURE_CUBE_MAP, save_tex);
}

//==============================================================================
// ____         __  __
//|  _ \       / _|/ _|
//| |_) |_   _| |_| |_ ___ _ __
//|  _ <| | | |  _|  _/ _ \ '__|
//| |_) | |_| | | | ||  __/ |
//|____/ \__,_|_| |_| \___|_|
//==============================================================================

void DT2GLOpenGL::createBuffer (SmartPtr<DT2GLBufferResource> &res, SmartPtr<ArrayBlock<DTubyte> > buffer_data, DTuint flags)
{
    // Build resource
    DT2GLOpenGLBufferResource *r = new DT2GLOpenGLBufferResource();
    res = SmartPtr<DT2GLBufferResource>(r);

    r->flags = flags;
    
    append(makeLatentCall(this, &DT2GLOpenGL::createBufferImpl, res, buffer_data, flags));
}

void DT2GLOpenGL::createBufferImpl (SmartPtr<DT2GLBufferResource> &res, SmartPtr<ArrayBlock<DTubyte> > buffer_data, DTuint flags)
{
    DT2GLOpenGLBufferResource *r = static_cast<DT2GLOpenGLBufferResource*>(res.get());

    r->flags = flags;

	::glGenBuffers(1,&r->name);
	::glBindBuffer(GL_ARRAY_BUFFER, r->name);
    
    GLvoid *data = buffer_data->getBuffer();
    DTsize size = buffer_data->size();
    
    if (r->flags == DT2GL_ACCESS_CPU_WRITE)
        ::glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr) size, data, GL_DYNAMIC_DRAW);
	else
        ::glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr) size, data, GL_STATIC_DRAW);
		
	::glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//==============================================================================
//==============================================================================

void DT2GLOpenGL::updateBuffer (SmartPtr<DT2GLBufferResource> res, SmartPtr<ArrayBlock<DTubyte> > buffer_data, DTsize buffer_offset)
{
    append(makeLatentCall(this, &DT2GLOpenGL::updateBufferImpl, res, buffer_data, buffer_offset));
}

void DT2GLOpenGL::updateBufferImpl (SmartPtr<DT2GLBufferResource> res, SmartPtr<ArrayBlock<DTubyte> > buffer_data, DTsize buffer_offset)
{
    DT2GLOpenGLBufferResource *r = static_cast<DT2GLOpenGLBufferResource*>(res.get());

	::glBindBuffer(GL_ARRAY_BUFFER, r->name);
    
    GLvoid *data = buffer_data->getBuffer();
    DTsize size = buffer_data->size();

    ::glBufferSubData(GL_ARRAY_BUFFER, (GLsizeiptr) size, buffer_offset, data);
		
	::glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//==============================================================================
//  _____ _               _
// / ____| |             | |
//| (___ | |__   __ _  __| | ___ _ __
// \___ \| '_ \ / _` |/ _` |/ _ \ '__|
// ____) | | | | (_| | (_| |  __/ |
//|_____/|_| |_|\__,_|\__,_|\___|_|
//==============================================================================

void DT2GLOpenGL::createShader (SmartPtr<DT2GLShaderResource> &shader)
{
    // Build resource
    DT2GLOpenGLShaderResource *r = new DT2GLOpenGLShaderResource();
    shader = SmartPtr<DT2GLShaderResource>(r);
    
    append(makeLatentCall(this, &DT2GLOpenGL::createShaderImpl, shader));
}

void DT2GLOpenGL::createShaderImpl (SmartPtr<DT2GLShaderResource> &shader)
{
    DT2GLOpenGLShaderResource *r = static_cast<DT2GLOpenGLShaderResource*>(shader.get());
    
    // Create Program
    r->name = ::glCreateProgram();
}

//==============================================================================
//==============================================================================

void DT2GLOpenGL::linkShader (SmartPtr<DT2GLShaderResource> shader)
{
    append(makeLatentCall(this, &DT2GLOpenGL::linkShaderImpl, shader));
}

void DT2GLOpenGL::linkShaderImpl (SmartPtr<DT2GLShaderResource> shader)
{
    DT2GLOpenGLShaderResource *r = static_cast<DT2GLOpenGLShaderResource*>(shader.get());

    // Link Program
    ::glLinkProgram(r->name);
    
    GLint linked;
    ::glGetProgramiv(r->name, GL_LINK_STATUS, &linked);

    // Check link status
    if (!linked) {
        GLint infoLen = 0;
        
        ::glGetProgramiv(r->name, GL_INFO_LOG_LENGTH, &infoLen);
        
        if (infoLen > 1) {
            DTcharacter *infoLog = new ("OGL Log") DTcharacter[infoLen];
            ::glGetProgramInfoLog(r->name, infoLen, NULL, infoLog);
            
            LOG_MESSAGE << infoLog;
            
            delete[] infoLog;
        } else {
            LOG_MESSAGE << "Program is not linked and there is no error log.";
        }
        
        ::glDeleteProgram(r->name);
        return;	
    }

}

//==============================================================================
//==============================================================================

void DT2GLOpenGL::createVertexShader (SmartPtr<DT2GLVertexShaderResource> &vertex_shader, const String &source)
{
    // Build resource
    DT2GLOpenGLVertexShaderResource *r = new DT2GLOpenGLVertexShaderResource();
    vertex_shader = SmartPtr<DT2GLVertexShaderResource>(r);
    
    append(makeLatentCall(this, &DT2GLOpenGL::createVertexShaderImpl, vertex_shader, source));
}

void DT2GLOpenGL::createVertexShaderImpl (SmartPtr<DT2GLVertexShaderResource> &vertex_shader, const String &source)
{
    DT2GLOpenGLVertexShaderResource *r = static_cast<DT2GLOpenGLVertexShaderResource*>(vertex_shader.get());

	// Create the shader object
	r->name = ::glCreateShader(GL_VERTEX_SHADER);
	if (r->name == 0)
		return;
		
	// load the _shader source
	const DTcharacter *s = source.cStr();
	::glShaderSource(r->name, 1, &s, NULL);
	
	// compile the _shader
	::glCompileShader(r->name);
	
	// Check the compile status
	GLint	compiled;
	::glGetShaderiv(r->name, GL_COMPILE_STATUS, &compiled);
	
	if (!compiled) {
		GLint infoLen = 0;
		
		::glGetShaderiv(r->name, GL_INFO_LOG_LENGTH, &infoLen);
		
		if (infoLen > 1) {
			DTcharacter *infoLog = new ("ShaderLog") DTcharacter[infoLen];
			::glGetShaderInfoLog(r->name, infoLen, NULL, infoLog);
			
			LOG_MESSAGE << infoLog;
			
			delete[] infoLog;
		}
		
		::glDeleteShader(r->name);
		return;
	}
	
}

//==============================================================================
//==============================================================================

void DT2GLOpenGL::createGeometryShader (SmartPtr<DT2GLGeometryShaderResource> &geometry_shader, const String &source)
{
    // Build resource
    DT2GLOpenGLGeometryShaderResource *r = new DT2GLOpenGLGeometryShaderResource();
    geometry_shader = SmartPtr<DT2GLGeometryShaderResource>(r);
    
    append(makeLatentCall(this, &DT2GLOpenGL::createGeometryShaderImpl, geometry_shader, source));
}

void DT2GLOpenGL::createGeometryShaderImpl (SmartPtr<DT2GLGeometryShaderResource> &geometry_shader, const String &source)
{
    DT2GLOpenGLGeometryShaderResource *r = static_cast<DT2GLOpenGLGeometryShaderResource*>(geometry_shader.get());

	// Create the shader object
	r->name = ::glCreateShader(GL_GEOMETRY_SHADER);
	if (r->name == 0)
		return;
		
	// load the _shader source
	const DTcharacter *s = source.cStr();
	::glShaderSource(r->name, 1, &s, NULL);
	
	// compile the _shader
	::glCompileShader(r->name);
	
	// Check the compile status
	GLint	compiled;
	::glGetShaderiv(r->name, GL_COMPILE_STATUS, &compiled);
	
	if (!compiled) {
		GLint infoLen = 0;
		
		::glGetShaderiv(r->name, GL_INFO_LOG_LENGTH, &infoLen);
		
		if (infoLen > 1) {
			DTcharacter *infoLog = new ("ShaderLog") DTcharacter[infoLen];
			::glGetShaderInfoLog(r->name, infoLen, NULL, infoLog);
			
			LOG_MESSAGE << infoLog;
			
			delete[] infoLog;
		}
		
		::glDeleteShader(r->name);
		return;
	}
}

//==============================================================================
//==============================================================================

void DT2GLOpenGL::createFragmentShader (SmartPtr<DT2GLFragmentShaderResource> &fragment_shader, const String &source)
{
    // Build resource
    DT2GLOpenGLFragmentShaderResource *r = new DT2GLOpenGLFragmentShaderResource();
    fragment_shader = SmartPtr<DT2GLFragmentShaderResource>(r);
    
    append(makeLatentCall(this, &DT2GLOpenGL::createFragmentShaderImpl, fragment_shader, source));
}

void DT2GLOpenGL::createFragmentShaderImpl (SmartPtr<DT2GLFragmentShaderResource> &fragment_shader, const String &source)
{
    DT2GLOpenGLFragmentShaderResource *r = static_cast<DT2GLOpenGLFragmentShaderResource*>(fragment_shader.get());

	// Create the shader object
	r->name = ::glCreateShader(GL_FRAGMENT_SHADER);
	if (r->name == 0)
		return;
		
	// load the _shader source
	const DTcharacter *s = source.cStr();
	::glShaderSource(r->name, 1, &s, NULL);
	
	// compile the _shader
	::glCompileShader(r->name);
	
	// Check the compile status
	GLint	compiled;
	::glGetShaderiv(r->name, GL_COMPILE_STATUS, &compiled);
	
	if (!compiled) {
		GLint infoLen = 0;
		
		::glGetShaderiv(r->name, GL_INFO_LOG_LENGTH, &infoLen);
		
		if (infoLen > 1) {
			DTcharacter *infoLog = new ("ShaderLog") DTcharacter[infoLen];
			::glGetShaderInfoLog(r->name, infoLen, NULL, infoLog);
			
			LOG_MESSAGE << infoLog;
			
			delete[] infoLog;
		}
		
		::glDeleteShader(r->name);
		return;
	}
}

//==============================================================================
//==============================================================================

void DT2GLOpenGL::attachVertexShader (SmartPtr<DT2GLShaderResource> shader, SmartPtr<DT2GLVertexShaderResource> vertex_shader)
{
    append(makeLatentCall(this, &DT2GLOpenGL::attachVertexShaderImpl, shader, vertex_shader));
}

void DT2GLOpenGL::attachVertexShaderImpl (SmartPtr<DT2GLShaderResource> shader, SmartPtr<DT2GLVertexShaderResource> vertex_shader)
{
    DT2GLOpenGLShaderResource *rs = static_cast<DT2GLOpenGLShaderResource*>(shader.get());
    DT2GLOpenGLVertexShaderResource *rv = static_cast<DT2GLOpenGLVertexShaderResource*>(vertex_shader.get());

    ::glAttachShader(rs->name, rv->name);
}

//==============================================================================
//==============================================================================

void DT2GLOpenGL::attachGeometryShader (SmartPtr<DT2GLShaderResource> shader, SmartPtr<DT2GLGeometryShaderResource> geometry_shader)
{
    append(makeLatentCall(this, &DT2GLOpenGL::attachGeometryShaderImpl, shader, geometry_shader));
}

void DT2GLOpenGL::attachGeometryShaderImpl (SmartPtr<DT2GLShaderResource> shader, SmartPtr<DT2GLGeometryShaderResource> geometry_shader)
{
    DT2GLOpenGLShaderResource *rs = static_cast<DT2GLOpenGLShaderResource*>(shader.get());
    DT2GLOpenGLGeometryShaderResource *rg = static_cast<DT2GLOpenGLGeometryShaderResource*>(geometry_shader.get());

    ::glAttachShader(rs->name, rg->name);
}

//==============================================================================
//==============================================================================

void DT2GLOpenGL::attachFragmentShader (SmartPtr<DT2GLShaderResource> shader, SmartPtr<DT2GLFragmentShaderResource> fragment_shader)
{
    append(makeLatentCall(this, &DT2GLOpenGL::attachFragmentShaderImpl, shader, fragment_shader));
}

void DT2GLOpenGL::attachFragmentShaderImpl (SmartPtr<DT2GLShaderResource> shader, SmartPtr<DT2GLFragmentShaderResource> fragment_shader)
{
    DT2GLOpenGLShaderResource *rs = static_cast<DT2GLOpenGLShaderResource*>(shader.get());
    DT2GLOpenGLFragmentShaderResource *rf = static_cast<DT2GLOpenGLFragmentShaderResource*>(fragment_shader.get());

    ::glAttachShader(rs->name, rf->name);
}

//==============================================================================
//==============================================================================

void DT2GLOpenGL::activateShader (SmartPtr<DT2GLShaderResource> shader)
{
    append(makeLatentCall(this, &DT2GLOpenGL::activateShaderImpl, shader));
}

void DT2GLOpenGL::activateShaderImpl (SmartPtr<DT2GLShaderResource> shader)
{
    //TODO
}

//==============================================================================
//==============================================================================

void DT2GLOpenGL::activateSampler (DTuint texture_slot, SmartPtr<DT2GLSamplerResource> res)
{
    append(makeLatentCall(this, &DT2GLOpenGL::activateSamplerImpl, texture_slot, res));
}

void DT2GLOpenGL::activateSamplerImpl (DTuint texture_slot, SmartPtr<DT2GLSamplerResource> res)
{
    //TODO
}

//==============================================================================
//==============================================================================

void DT2GLOpenGL::activateTexture2D (DTuint texture_slot, SmartPtr<DT2GLTexture2DResource> res)
{
    append(makeLatentCall(this, &DT2GLOpenGL::activateTexture2DImpl, texture_slot, res));
}

void DT2GLOpenGL::activateTexture2DImpl (DTuint texture_slot, SmartPtr<DT2GLTexture2DResource> res)
{
    //TODO
}

//==============================================================================
//==============================================================================

void DT2GLOpenGL::activateTexture3D (DTuint texture_slot, SmartPtr<DT2GLTexture3DResource> res)
{
    append(makeLatentCall(this, &DT2GLOpenGL::activateTexture3DImpl, texture_slot, res));
}

void DT2GLOpenGL::activateTexture3DImpl (DTuint texture_slot, SmartPtr<DT2GLTexture3DResource> res)
{
    //TODO
}

//==============================================================================
//==============================================================================

void DT2GLOpenGL::activateTextureCube (DTuint texture_slot, SmartPtr<DT2GLTextureCubeResource> res)
{
    append(makeLatentCall(this, &DT2GLOpenGL::activateTextureCubeImpl, texture_slot, res));
}

void DT2GLOpenGL::activateTextureCubeImpl (DTuint texture_slot, SmartPtr<DT2GLTextureCubeResource> res)
{
    //TODO
}

//==============================================================================
//==============================================================================

void DT2GLOpenGL::activateAttributeBuffer (DTuint attribute_slot, SmartPtr<DT2GLBufferResource> res)
{
    append(makeLatentCall(this, &DT2GLOpenGL::activateAttributeBufferImpl, attribute_slot, res));
}

void DT2GLOpenGL::activateAttributeBufferImpl (DTuint attribute_slot, SmartPtr<DT2GLBufferResource> res)
{
    //TODO
}

//==============================================================================
//==============================================================================

void DT2GLOpenGL::activateUniformBuffer (DTuint uniform_slot, SmartPtr<DT2GLUniformResource> res)
{
    append(makeLatentCall(this, &DT2GLOpenGL::activateUniformBufferImpl, uniform_slot, res));
}

void DT2GLOpenGL::activateUniformBufferImpl (DTuint uniform_slot, SmartPtr<DT2GLUniformResource> res)
{
    //TODO
}

//==============================================================================
// _____                     _
//|  __ \                   (_)
//| |  | |_ __ __ ___      ___ _ __   __ _
//| |  | | '__/ _` \ \ /\ / / | '_ \ / _` |
//| |__| | | | (_| |\ V  V /| | | | | (_| |
//|_____/|_|  \__,_| \_/\_/ |_|_| |_|\__, |
//                                    __/ |
//                                   |___/
//==============================================================================
    
void DT2GLOpenGL::drawElements (DT2GLPrimitiveType primitive_type, SmartPtr<DT2GLElementsResource> elements)
{
    append(makeLatentCall(this, &DT2GLOpenGL::drawElementsImpl, primitive_type, elements));
}

void DT2GLOpenGL::drawElementsImpl (DT2GLPrimitiveType primitive_type, SmartPtr<DT2GLElementsResource> elements)
{
    //TODO
}

void DT2GLOpenGL::drawArrays (DT2GLPrimitiveType primitive_type, DTuint num_elements)
{
    append(makeLatentCall(this, &DT2GLOpenGL::drawArraysImpl, primitive_type, num_elements));
}

void DT2GLOpenGL::drawArraysImpl (DT2GLPrimitiveType primitive_type, DTuint num_elements)
{
    //TODO
}

//==============================================================================
// ______                        _            __  __
//|  ____|                      | |          / _|/ _|
//| |__ _ __ __ _ _ __ ___   ___| |__  _   _| |_| |_ ___ _ __
//|  __| '__/ _` | '_ ` _ \ / _ \ '_ \| | | |  _|  _/ _ \ '__|
//| |  | | | (_| | | | | | |  __/ |_) | |_| | | | ||  __/ |
//|_|  |_|  \__,_|_| |_| |_|\___|_.__/ \__,_|_| |_| \___|_|
//==============================================================================

void DT2GLOpenGL::createFramebufferImpl (SmartPtr<DT2GLFramebufferResource> &framebuffer)
{
    DT2GLOpenGLFramebufferResource *r = static_cast<DT2GLOpenGLFramebufferResource*>(framebuffer.get());

	::glGenFramebuffersM(1, &r->name);
    
    r->name_rb_color = 0;
    r->name_rb_depth = 0;
}

void DT2GLOpenGL::attachFramebufferColorImpl (SmartPtr<DT2GLFramebufferResource> framebuffer, SmartPtr<DT2GLTexture2DResource> tex)
{
    GLint save_fb;
    ::glGetIntegerv(GL_FRAMEBUFFER_BINDINGM, &save_fb);

    DT2GLOpenGLFramebufferResource *rfb = static_cast<DT2GLOpenGLFramebufferResource*>(framebuffer.get());
    DT2GLOpenGLTexture2DResource *rt = static_cast<DT2GLOpenGLTexture2DResource*>(tex.get());
    
    ::glBindFramebufferM(GL_FRAMEBUFFERM, rfb->name);
    ::glFramebufferTexture2DM(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0M, GL_TEXTURE_2D, rt->name, 0);

    ::glBindFramebufferM(GL_FRAMEBUFFERM, save_fb);
}

void DT2GLOpenGL::attachFramebufferDepthStencilImpl (SmartPtr<DT2GLFramebufferResource> framebuffer, SmartPtr<DT2GLTexture2DResource> tex)
{
    GLint save_fb;
    ::glGetIntegerv(GL_FRAMEBUFFER_BINDINGM, &save_fb);

    DT2GLOpenGLFramebufferResource *rfb = static_cast<DT2GLOpenGLFramebufferResource*>(framebuffer.get());
    DT2GLOpenGLTexture2DResource *rt = static_cast<DT2GLOpenGLTexture2DResource*>(tex.get());
    
    ::glBindFramebufferM(GL_FRAMEBUFFERM, rfb->name);
    ::glFramebufferTexture2DM(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, rt->name, 0);

    ::glBindFramebufferM(GL_FRAMEBUFFERM, save_fb);
}

void DT2GLOpenGL::attachRenderbufferColorImpl (SmartPtr<DT2GLFramebufferResource> framebuffer, DTint width, DTint height, DTGLTextelFormat format)
{
    GLint save_fb;
    ::glGetIntegerv(GL_FRAMEBUFFER_BINDINGM, &save_fb);

    DT2GLOpenGLFramebufferResource *r = static_cast<DT2GLOpenGLFramebufferResource*>(framebuffer.get());

    GLenum color_fmt = 0;
    switch (format) {
        case DT2GL_FORMAT_RGBA:                 color_fmt = GL_RGBA;    break;
        
        default:
            break;
    }

    if (!r->name_rb_color)
        ::glGenRenderbuffersM(1, &r->name_rb_color);
    
    ::glBindRenderbufferM(GL_RENDERBUFFER, r->name_rb_color);
    ::glRenderbufferStorageM(GL_RENDERBUFFER, color_fmt, width, height);

    ::glBindFramebufferM(GL_FRAMEBUFFERM, r->name);
    ::glFramebufferRenderbufferM(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0M, GL_RENDERBUFFER, r->name_rb_color);

    ::glBindFramebufferM(GL_FRAMEBUFFERM, save_fb);
}

void DT2GLOpenGL::attachRenderbufferDepthStencilImpl (SmartPtr<DT2GLFramebufferResource> framebuffer, DTint width, DTint height, DTGLTextelFormat format)
{
    GLint save_fb;
    ::glGetIntegerv(GL_FRAMEBUFFER_BINDINGM, &save_fb);

    DT2GLOpenGLFramebufferResource *r = static_cast<DT2GLOpenGLFramebufferResource*>(framebuffer.get());

    GLenum depth_fmt = 0;
    switch (format) {
        case DT2GL_FORMAT_DEPTH_16:              depth_fmt = GL_DEPTH_COMPONENT16M;  break;
        case DT2GL_FORMAT_DEPTH_24:              depth_fmt = GL_DEPTH_COMPONENT24M;  break;
        case DT2GL_FORMAT_DEPTH_24_STENCIL_8:    depth_fmt = GL_DEPTH24_STENCIL8M;   break;
        
        default:
            break;
    }
    
    if (!r->name_rb_depth)
        ::glGenRenderbuffersM(1, &r->name_rb_depth);
    
    ::glBindRenderbufferM(GL_RENDERBUFFER, r->name_rb_depth);
    ::glRenderbufferStorageM(GL_RENDERBUFFER, depth_fmt, width, height);        

    if (depth_fmt == DT2GL_FORMAT_DEPTH_24_STENCIL_8) {
        ::glFramebufferRenderbufferM(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, r->name_rb_depth);
        ::glFramebufferRenderbufferM(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, r->name_rb_depth);
    } else {
        ::glFramebufferRenderbufferM(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, r->name_rb_depth);
    }
    
    ::glBindFramebufferM(GL_FRAMEBUFFERM, save_fb);
}

//==============================================================================
//==============================================================================

void DT2GLOpenGL::deferDraw (SmartPtr<LatentCall> c)
{
    append(c);
}

//==============================================================================
//==============================================================================

void DT2GLOpenGL::append (SmartPtr<LatentCall> c)
{
    c->fire();
}

//==============================================================================
//==============================================================================

} // DT2

