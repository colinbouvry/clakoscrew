#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    mOl.setupScreenPerspective();
    string path0 = ofFilePath::getCurrentExeDir() + ofFilePath::addLeadingSlash("divers");
    mListFileIlda.push_back(new ofDirectory(path0));
    mListFileIlda.back()->allowExt("ild");
    mListFileIlda.back()->listDir();
    mAnimation.push_back(Animation());
    string path1 = ofFilePath::getCurrentExeDir() + ofFilePath::addLeadingSlash("suite_lazer_1");
    mListFileIlda.push_back(new ofDirectory(path1));
    mListFileIlda.back()->allowExt("ild");
    mListFileIlda.back()->listDir();
    mAnimation.push_back(Animation());
    string path2 = ofFilePath::getCurrentExeDir() + ofFilePath::addLeadingSlash("suite_lazer_2");
    mListFileIlda.push_back(new ofDirectory(path2));
    mListFileIlda.back()->allowExt("ild");
    mListFileIlda.back()->listDir();
    mAnimation.push_back(Animation());
    string path3 = ofFilePath::getCurrentExeDir() + ofFilePath::addLeadingSlash("dessins");
    mListFileIlda.push_back(new ofDirectory(path3));
    mListFileIlda.back()->allowExt("ild");
    mListFileIlda.back()->listDir();
    mAnimation.push_back(Animation());
    string path4 = ofFilePath::getCurrentExeDir() + ofFilePath::addLeadingSlash("tete");
    mListFileIlda.push_back(new ofDirectory(path4));
    mListFileIlda.back()->allowExt("ild");
    mListFileIlda.back()->listDir();
    mAnimation.push_back(Animation());
    string path5 = ofFilePath::getCurrentExeDir() + ofFilePath::addLeadingSlash("explosion");
    mListFileIlda.push_back(new ofDirectory(path5));
    mListFileIlda.back()->allowExt("ild");
    mListFileIlda.back()->listDir();
    mAnimation.push_back(Animation());
    string path6 = ofFilePath::getCurrentExeDir() + ofFilePath::addLeadingSlash("grenade");
    mListFileIlda.push_back(new ofDirectory(path6));
    mListFileIlda.back()->allowExt("ild");
    mListFileIlda.back()->listDir();
    mAnimation.push_back(Animation());
    string path7 = ofFilePath::getCurrentExeDir() + ofFilePath::addLeadingSlash("couteau");
    mListFileIlda.push_back(new ofDirectory(path7));
    mListFileIlda.back()->allowExt("ild");
    mListFileIlda.back()->listDir();
    mAnimation.push_back(Animation());
    string path8 = ofFilePath::getCurrentExeDir() + ofFilePath::addLeadingSlash("pan");
    mListFileIlda.push_back(new ofDirectory(path8));
    mListFileIlda.back()->allowExt("ild");
    mListFileIlda.back()->listDir();
    mAnimation.push_back(Animation());





    for (int g = 0 ; g < mListFileIlda.size() ; g++)
    {
        for(int i = 0; i < mListFileIlda.at(g)->numFiles(); i++)
        {
            ofLogNotice(mListFileIlda.at(g)->getPath(i));
            try
            {
                mOl.LoadIlda( mListFileIlda.at(g)->getPath(i), mListFileIlda.at(g)->getName(i));
            }
            catch (...)
            {
                ofLogNotice("Can't load ilda file " + mListFileIlda.at(g)->getName(i));
            }

        }
    }

    mOl.initIlda();
    ofSetFrameRate(120);

    mTimeline = ofxCinderTimeline::Timeline::create();
    mTimeline->stepTo(ofGetElapsedTimef());



    //timeline().apply(&mNumIldaAnim, 0, 0 ,0.f);
    //mTimeline->stepTo(ofGetElapsedTimef());
    mNumGroup = -1;
    mNumIlda = 0;
    //timeline().add(bind(&ofApp::playAnim, this, true ), timeline().getCurrentTime() + 6.f* mListFileIlda.at(mNumGroup)->numFiles() );
    playAnim();
}

void ofApp::FinishGroup()
{
    mNumGroup++;
    mNumGroup %= mListFileIlda.size();
}
void ofApp::playAnim()
{
    FinishGroup();
    switch (mNumGroup)
    {
        case 0 :
        case 1 :
        case 2 :
        case 3 :
        {
            timeline().apply(&mAnimation.at(mNumGroup).mScaleAnim, ofVec3f(2.f,2.f,2.f), ofVec3f(1.f,1.f,1.f), 1.f, ofxCinderTimeline::EaseOutQuad());
            timeline().appendTo(&mAnimation.at(mNumGroup).mScaleAnim, ofVec3f(0.8f,0.8f,0.8f), 4.f);
            timeline().appendTo(&mAnimation.at(mNumGroup).mScaleAnim, ofVec3f(0.1f,0.1f,0.1f), 1.f, ofxCinderTimeline::EaseOutQuad());
            timeline().apply(&mAnimation.at(mNumGroup).mNumIldaAnim, 0, 0, 6.f);
            for (int num = 1 ; num < mListFileIlda.at(mNumGroup)->numFiles() ; ++num)
            {
                timeline().appendTo(&mAnimation.at(mNumGroup).mScaleAnim, ofVec3f(2.f,2.f,2.f), ofVec3f(1.f,1.f,1.f), 1.f, ofxCinderTimeline::EaseOutQuad());
                timeline().appendTo(&mAnimation.at(mNumGroup).mScaleAnim, ofVec3f(0.8f,0.8f,0.8f), 4.f);
                timeline().appendTo(&mAnimation.at(mNumGroup).mScaleAnim, ofVec3f(0.1f,0.1f,0.1f), 1.f, ofxCinderTimeline::EaseOutQuad());
                timeline().appendTo(&mAnimation.at(mNumGroup).mNumIldaAnim, num, num, 6.f);
            }

            timeline().apply(&mAnimation.at(mNumGroup).mRotateAnim, ofVec3f(0.f,0.f, 0.f), ofVec3f(0.f, 0.f,0.f), 6.f*mListFileIlda.at(mNumGroup)->numFiles());
            timeline().apply(&mAnimation.at(mNumGroup).mTranslateAnim, ofVec3f(0.f,0.f,0.f), ofVec3f(0.f,0.f,0.f), 6.f*mListFileIlda.at(mNumGroup)->numFiles()).finishFn(bind(&ofApp::playAnim, this));

            break;
        }
        default :
        {
            timeline().apply(&mAnimation.at(mNumGroup).mScaleAnim, ofVec3f(2.f,2.f,2.f), ofVec3f(1.f,1.f,1.f), 1.f, ofxCinderTimeline::EaseOutQuad());
            timeline().appendTo(&mAnimation.at(mNumGroup).mScaleAnim, ofVec3f(0.8f,0.8f,0.8f), 4.f);
            timeline().appendTo(&mAnimation.at(mNumGroup).mScaleAnim, ofVec3f(0.1f,0.1f,0.1f), 1.f, ofxCinderTimeline::EaseOutQuad());

            for (int num = 1 ; num < mListFileIlda.at(mNumGroup)->numFiles() ; ++num)
            {
                timeline().appendTo(&mAnimation.at(mNumGroup).mScaleAnim, ofVec3f(2.f,2.f,2.f), ofVec3f(1.f,1.f,1.f), 1.f, ofxCinderTimeline::EaseOutQuad());
                timeline().appendTo(&mAnimation.at(mNumGroup).mScaleAnim, ofVec3f(0.8f,0.8f,0.8f), 4.f);
                timeline().appendTo(&mAnimation.at(mNumGroup).mScaleAnim, ofVec3f(0.1f,0.1f,0.1f), 1.f, ofxCinderTimeline::EaseOutQuad());
            }
            timeline().apply(&mAnimation.at(mNumGroup).mNumIldaAnim, 0, mListFileIlda.at(mNumGroup)->numFiles(), (float) mListFileIlda.at(mNumGroup)->numFiles() * 0.2f).loop();
            timeline().apply(&mAnimation.at(mNumGroup).mRotateAnim, ofVec3f(0.f,0.f, 0.f), ofVec3f(0.f, 0.f,0.f), 6.f);
            timeline().apply(&mAnimation.at(mNumGroup).mTranslateAnim, ofVec3f(0.f,0.f,0.f), ofVec3f(0.f,0.f,0.f), 6.f).finishFn(bind(&ofApp::playAnim, this));
            break;
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    mTimeline->stepTo(ofGetElapsedTimef());
    switch (mNumGroup)
    {
        case 0 :
        case 1 :
        case 2 :
        case 3 :
        default :
        {
            mNumIlda = mAnimation.at(mNumGroup).mNumIldaAnim.value() % mListFileIlda.at(mNumGroup)->numFiles();
            break;
        }
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
  mOl.loadIdentity();
  mOl.pushMatrix();
  mOl.translate(mAnimation.at(mNumGroup).mTranslateAnim.value());
  mOl.scale(mAnimation.at(mNumGroup).mScaleAnim.value().x, mAnimation.at(mNumGroup).mScaleAnim.value().y);
  mOl.rotate(mAnimation.at(mNumGroup).mRotateAnim.value().x, 1.f, 0.f, 0.f);
  mOl.rotate(mAnimation.at(mNumGroup).mRotateAnim.value().y, 0.f, 1.f, 0.f);
  mOl.rotate(mAnimation.at(mNumGroup).mRotateAnim.value().z, 0.f, 0.f, 1.f);
  if(mListFileIlda.size() > mNumGroup)  mOl.drawIlda(mListFileIlda.at(mNumGroup)->getName(mNumIlda));
  mOl.popMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
