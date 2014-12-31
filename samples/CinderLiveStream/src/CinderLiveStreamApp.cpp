#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/qtime/QuickTime.h"
#include "CinderLiveStreamer.h"

#define DEFAULT_STREAM "http://www.ustream.tv/channel/live-iss-stream"
using namespace ci;
using namespace ci::app;
using namespace std;

class CinderLiveStreamApp : public AppNative {
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

};

void CinderLiveStreamApp::resize(){
    mWidth = getWindowWidth();
    mHeight= getWindowHeight();
}

void CinderLiveStreamApp::setup()
{
    string mUrl = "http://www.ustream.tv/channel/iss-hdev-payload";
    
    string mStream = CinderLiveStreamer::getStreamUrl(mUrl);
    if (mStream != "ERROR") {
        mMovieRef = cinder::qtime::MovieSurface::create( Url(mStream) );
        mMovieRef->play();
    }
    mWidth = getWindowWidth();
    mHeight= getWindowHeight();
    getWindow()->setTitle( "Cinder LiveStreamer: " + (mStream == "ERROR" ? mStream : mUrl));

}

void CinderLiveStreamApp::mouseDown( MouseEvent event )
{
}

void CinderLiveStreamApp::update()
{
    if (mMovieRef->checkNewFrame())
        mSurfaceRef = mMovieRef->getSurface();
}

void CinderLiveStreamApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    
    if (mSurfaceRef){
        gl::draw(gl::Texture::create(*mSurfaceRef), Rectf(0,0,mWidth,mHeight));
    }
}

CINDER_APP_NATIVE( CinderLiveStreamApp, RendererGl )
