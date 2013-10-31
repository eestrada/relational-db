/*
 * Context creation code based on code from:
 * http://www.opengl.org/wiki/Tutorial:_OpenGL_3.0_Context_Creation_(GLX) 
 */

/* Include C standard headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Include C++ standard headers */
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

// TODO: Place X11 and GL in namespaces. This should help distinguish what 
// functions are coming from where (most are clear, but some are pretty 
// ambiguous).

#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>

//#include <GL/glut.h>
//glutInitContextVersion (3, 2);
//glutInitContextFlags (GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);

#define GLX_CONTEXT_MAJOR_VERSION_ARB       0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB       0x2092

// Typedef function
typedef GLXContext (*glXCreateContextAttribsARBProc)
    (Display*, GLXFBConfig, GLXContext, Bool, const int*);
 
static bool ctxErrorOccurred = false;
static int ctxErrorHandler( Display *dpy, XErrorEvent *ev )
{
    ctxErrorOccurred = true;
    return 0;
}

namespace ede
{

bool stringInStringList(std::string str, std::string strlist)
{
    /* String "str" should not have spaces or be empty. */
    if(str.empty() || str.find_first_of(' ') != str.npos)
        {return false;}
 
    std::istringstream extstrm(strlist);
    std::string tmp;

    while(!extstrm.eof())
    {
        extstrm >> tmp;

        if(str == tmp) return true;
    }

    return false; /* String not found.*/
}

Display *initDisplay(void)
{
    // Get the current X display
    Display *display = XOpenDisplay(0);

    if ( !display )
    {
        std::cerr << "Failed to open X display\n" ;
        throw std::runtime_error("Failed to open X display.");
    }
    else
    {
        std::cerr << "Succeeded in opening X display!\n" ;
    }

    return display;
 
}

Window *initWindow(Display *display);
 
int glxInit(Display *display, Window *w, Colormap *cm)
{
  // All settings for new Frame Buffer
  // Get a matching FB config
  static int visual_attribs[] =
    {
      GLX_X_RENDERABLE    , True,
      GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
      GLX_RENDER_TYPE     , GLX_RGBA_BIT,
      GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
      GLX_RED_SIZE        , 8,
      GLX_GREEN_SIZE      , 8,
      GLX_BLUE_SIZE       , 8,
      GLX_ALPHA_SIZE      , 8,
      GLX_DEPTH_SIZE      , 24,
      GLX_STENCIL_SIZE    , 8,
      GLX_DOUBLEBUFFER    , True,
      //GLX_SAMPLE_BUFFERS  , 1,
      //GLX_SAMPLES         , 4,
      None
    };
 
  int glx_major, glx_minor;
 
  // FBConfigs were added in GLX version 1.3.
  if ( !glXQueryVersion( display, &glx_major, &glx_minor ) || 
       ( ( glx_major == 1 ) && ( glx_minor < 3 ) ) || ( glx_major < 1 ) )
  {
    std::cerr << "Invalid GLX version" ;
    throw std::runtime_error("Invalid GLX version");
  }
 
  std::cerr << "Getting matching framebuffer configs\n" ;
  int fbcount;
  GLXFBConfig *fbc = glXChooseFBConfig( display, DefaultScreen( display ), 
                                        visual_attribs, &fbcount );
  if ( !fbc )
  {
    std::cerr << "Failed to retrieve a framebuffer config\n" ;
    throw std::runtime_error("Failed to retrieve a framebuffer config");
  }
  std::cerr << "Found " << fbcount << " matching FB configs.\n";
 
  // Pick the FB config/visual with the most samples per pixel
  std::cerr  << "Getting XVisualInfos\n" ;
  int best_fbc = -1, worst_fbc = -1, best_num_samp = -1, worst_num_samp = 999;
 
  int i;
  for ( i = 0; i < fbcount; i++ )
  {
    XVisualInfo *vi = glXGetVisualFromFBConfig( display, fbc[i] );
    if ( vi )
    {
      int samp_buf, samples;
      glXGetFBConfigAttrib( display, fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf );
      glXGetFBConfigAttrib( display, fbc[i], GLX_SAMPLES       , &samples  );
 
      std::cerr << "  Matching fbconfig "<< i <<", visual ID 0x" << 
        std::hex << vi->visualid << std::dec << ": SAMPLE_BUFFERS = " <<
        samp_buf <<", SAMPLES = "<< samples << "\n";
 
      if ( (best_fbc < 0 || samp_buf) && (samples > best_num_samp) )
        best_fbc = i, best_num_samp = samples;
      if ( worst_fbc < 0 || !samp_buf || samples < worst_num_samp )
        worst_fbc = i, worst_num_samp = samples;
    }
    XFree( vi );
  }
 
  GLXFBConfig bestFbc = fbc[ best_fbc ];
 
  // Be sure to free the FBConfig list allocated by glXChooseFBConfig()
  XFree( fbc );
 
  // Get a visual
  XVisualInfo *vi = glXGetVisualFromFBConfig( display, bestFbc );
  std::cerr << "Chosen visual ID = 0x";
  std::cerr << std::hex << vi->visualid <<  std::dec;
  std::cerr << "\n";
 
  std::cerr << "Creating colormap\n";
  XSetWindowAttributes swa;
  Colormap cmap;
  swa.colormap = cmap = XCreateColormap( display,
                                         RootWindow( display, vi->screen ), 
                                         vi->visual, AllocNone );
  swa.background_pixmap = None ;
  swa.border_pixel      = 0;
  swa.event_mask        = StructureNotifyMask;
 
  std::cerr << "Creating window\n";
  Window win = XCreateWindow( display, RootWindow( display, vi->screen ), 
                              0, 0, 1024, 576, 0, vi->depth, InputOutput, 
                              vi->visual, 
                              CWBorderPixel|CWColormap|CWEventMask, &swa );
  if ( !win )
  {
    std::cerr << "Failed to create window.\n";
    throw std::runtime_error("Failed to create window.");
  }
 
  // Done with the visual info data
  XFree( vi );
 
  XStoreName( display, win, "GL 3.2 Window" );
 
  std::cerr << "Mapping window\n";
  XMapWindow( display, win );
 
  // NOTE: It is not necessary to create or make current to a context before
  // calling glXGetProcAddressARB
  glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
  glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)
           glXGetProcAddressARB( (const GLubyte *) "glXCreateContextAttribsARB" );
 
  GLXContext ctx = 0;
 
  // Install an X error handler so the application won't exit if GL 3.2
  // context allocation fails.
  //
  // Note this error handler is global.  All display connections in all threads
  // of a process use the same error handler, so be sure to guard against other
  // threads issuing X commands while this code is running.
  ctxErrorOccurred = false;
  int (*oldHandler)(Display*, XErrorEvent*) =
      XSetErrorHandler(&ctxErrorHandler);

    const char * exts = glXQueryExtensionsString(display, DefaultScreen(display));
    // Check for the GLX_ARB_create_context extension string and the function.
    // If either is not present, use GLX 1.3 context creation method.
  if ( !ede::stringInStringList("GLX_ARB_create_context", exts) ||
       !glXCreateContextAttribsARB )
  {
    std::cerr <<  "glXCreateContextAttribsARB() not found"
            " ... using old-style GLX context\n" ;
    ctx = glXCreateNewContext( display, bestFbc, GLX_RGBA_TYPE, 0, True );
  }
 
  // If it does, try to get a GL 3.2 context!
  else
  {
    int context_attribs[] =
      {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
        GLX_CONTEXT_MINOR_VERSION_ARB, 2,
        //GLX_CONTEXT_FLAGS_ARB        , GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
        None
      };
 
    std::cerr << "Creating context\n" ;
    ctx = glXCreateContextAttribsARB( display, bestFbc, 0,
                                      True, context_attribs );
 
    // Sync to ensure any errors generated are processed.
    XSync( display, False );
    if ( !ctxErrorOccurred && ctx )
      std::cerr << "Created GL 3.2 context\n" ;
    else
    {
      // Couldn't create GL 3.2 context.  Fall back to old-style 2.x context.
      // When a context version below 3.2 is requested, implementations will
      // return the newest context version compatible with OpenGL versions less
      // than version 3.2.
      // GLX_CONTEXT_MAJOR_VERSION_ARB = 1
      context_attribs[1] = 1;
      // GLX_CONTEXT_MINOR_VERSION_ARB = 0
      context_attribs[3] = 0;
 
      ctxErrorOccurred = false;
 
      std::cerr << "Failed to create GL 3.2 context"
              " ... using old-style GLX context\n" ;
      ctx = glXCreateContextAttribsARB( display, bestFbc, 0, 
                                        True, context_attribs );
    }
  }
 
  // Sync to ensure any errors generated are processed.
  XSync( display, False );
 
  // Restore the original error handler
  XSetErrorHandler( oldHandler );
 
  if ( ctxErrorOccurred || !ctx )
  {
    std::cerr << "Failed to create an OpenGL context\n" ;
    throw std::runtime_error("Failed to create an OpenGL context");
  }
 
  // Verifying that context is a direct context
  if ( ! glXIsDirect ( display, ctx ) )
  {
    std::cerr << "Indirect GLX rendering context obtained\n" ;
  }
  else
  {
    std::cerr << "Direct GLX rendering context obtained\n" ;
  }
 
  std::cerr << "Making context current\n" ;
  glXMakeCurrent( display, win, ctx );

  glClearColor ( 0, 0.5, 1, 1 );
  glClear ( GL_COLOR_BUFFER_BIT );
  glXSwapBuffers ( display, win );
 
  sleep(1);
 
  glClearColor ( 1, 0.5, 0, 1 );
  glClear ( GL_COLOR_BUFFER_BIT );
  glXSwapBuffers ( display, win );
 
  sleep(1);
 
  glXMakeCurrent( display, 0, 0 );
  glXDestroyContext( display, ctx );
 
  XDestroyWindow( display, win );
  XFreeColormap( display, cmap );
  XCloseDisplay( display );

  return 0;
}

}


int main (int argc, char **argv)
{
    Display *display = ede::initDisplay();
    return ede::glxInit(display, NULL, NULL);
}

