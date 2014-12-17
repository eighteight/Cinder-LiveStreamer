#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/qtime/QuickTime.h"
#include "CinderLiveStreamer.h"
#define DEFAULT_STREAM "http://www.ustream.tv/channel/live-iss-stream"
using namespace ci;
using namespace ci::app;
using namespace std;

class _TBOX_PREFIX_App : public AppNative {
public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    void resize() override;
    
private:
    string getStreamUrl(string _link);
    
    qtime::MovieSurfaceRef	mMovieRef;
    SurfaceRef				mSurfaceRef;
    int mWidth, mHeight;
    string mStream;
};

void _TBOX_PREFIX_App::resize(){
    mWidth = getWindowWidth();
    mHeight= getWindowHeight();
}

void _TBOX_PREFIX_App::setup()
{
    string mStream = CinderLiveStreamer::getStreamUrl("http://www.ustream.tv/channel/live-iss-stream");
    if (mStream != "ERROR") {
        mMovieRef = cinder::qtime::MovieSurface::create( Url(mStream) );
    }
    mWidth = getWindowWidth();
    mHeight= getWindowHeight();
    getWindow()->setTitle( "Cinder LiveStreamer: " + (mStream == "ERROR" ? mStream : DEFAULT_STREAM));
    
}

void _TBOX_PREFIX_App::mouseDown( MouseEvent event )
{
}

void _TBOX_PREFIX_App::update()
{
    if (mMovieRef->checkNewFrame())
        mSurfaceRef = mMovieRef->getSurface();
}

void _TBOX_PREFIX_App::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    
    if (mSurfaceRef){
        gl::draw(gl::Texture::create(*mSurfaceRef), Rectf(0,0,mWidth,mHeight));
    }
}

CINDER_APP_NATIVE( _TBOX_PREFIX_App, RendererGl )
