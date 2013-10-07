#include "stdafx.h"
#include "apzZSpaceRenderer.h"
#include "apzUtilities.h"
#include "apzBolshoiSystem.h"
#include "apzWaveFrontLoader.h"

using namespace apz;

WFObject *test;

ZSpaceRenderer::ZSpaceRenderer(WINDOW_DATA *tWinData) : Renderer(tWinData){
  m_renderObjects = new RenderGroup();
  m_timer = new zspace::common::Timer();
}

void ZSpaceRenderer::AddObject(RenderObject *tObj) {
  m_renderObjects->Add(tObj);
}

void ZSpaceRenderer::Setup(GLuint x, GLuint y, GLuint width, GLuint height) {

  v_lastPenPush = -1;
  v_isPenActive = -1;


  penScale = 1.0;
  saveScale = 1.0;
  lastPenPush = -1;
  pause = false;

  m_wx = x;
  m_wy = y;
  m_width = width;
  m_height = height;


  // Setup the ZSpace
  zSpaceInitialize();

  if(!initGlew){
    GLenum err = glewInit();
    if(GLEW_OK != err){
      CRITICAL_ERROR("could not init glew");
      exit(EXIT_FAILURE);
    }
    initGlew = true;
  }


  // Setup GL
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND); 
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_PROGRAM_POINT_SIZE);
  glEnable(GL_POINT_SMOOTH);
  glPointSize(1.0);

  // Formulate an initial set of matrices in case zspace fails


  /*  Setup Shader */
  m_shader = new Shader();
  m_shader->CreateFragmentShader(Data("shaders/fragment.glsl"));
  m_shader->CreateVertexShader(  Data("shaders/vertex.glsl"));
  //m_shader->CreateGeometryShader(Data("shaders/geometry.glsl"));
  m_shader->Link();

  


  /*  Setup the interface  */
 // m_animGrp = new SwitchRGOpacity();
 // m_animGrp->SetFadeAmount(0.10);

 // Data *fileData[61];
  // Read file data first

  /*
  for(int i = 80; i <= 140; i++){
    std::string osStr("data/Eris_bin/out_");

    osStr.append(std::to_string(i));
    osStr.append(".bin");

    fileData[i - 80] = new Data(osStr.c_str());
  }

  for(int i = 0; i <= 60; i++){
    int last = i - 1;
    int next = i + 1;

    if(last < 0) last = 60;
    if(next > 60) next = 0;

    ParticleSystem *sPs = new ParticleSystem(*fileData[i]);
    m_animGrp->Add(sPs);
  }



  m_animGrp->Switch(0);
  m_renderObjects->Add(m_animGrp);


  m_animGrpArms = new SwitchRGOpacity();
  m_animGrpArms->SetFadeAmount(0.10);
  for(int i = 0; i <= 140; ++i){
    std::string osStr("data/Eris_body/CMFinalAx_");

    osStr.append(std::to_string(i));
    osStr.append(".bin");

    ParticleSystem *sPs = new ParticleSystem(Data(osStr.c_str()));

    m_animGrpArms->Add(sPs);
  }
  m_animGrpArms->Switch(0);
  m_renderObjects->Add(m_animGrpArms);
  m_matrix.t = 0.0;
  */
   /*
  Data cake("data/optimal-part-73113.bin");

  typedef struct{
	  float x, y, z, m;
	  int type;
  }VERTEX_BOLSHOI;
  
  VERTEX_BOLSHOI *ptr;
  unsigned long len;
  cake.copyAndAllocate((char **)&ptr, &len);
  len /= sizeof(VERTEX_BOLSHOI);
  float largest = 0.0;

  for(int i = 0; i < len; i++){
	  if(abs(ptr[i].x) > largest)
		  largest = abs(ptr[i].x);
	  else if(abs(ptr[i].y) > largest)
		  largest = abs(ptr[i].y);
	  else if(abs(ptr[i].z > largest))
		  largest = abs(ptr[i].z);
  }

  for(int i = 0; i < len; i++){
	  ptr[i].x /= largest;
	  ptr[i].y /= largest;
	  ptr[i].z /= largest;
  }

  m_renderSystem = new TemplateParticleSystem(
	  Data((char *)ptr, len*sizeof(VERTEX_BOLSHOI)), 6,
	  "vertexPosition", TemplateParticleSystem::VEC3,
	  "vertexMass",     TemplateParticleSystem::FLOAT,
	  "vertexType",     TemplateParticleSystem::INT );
  m_renderSystem->EvaluateShaderLocations(*m_shader);

 m_renderObjects->Add(m_renderSystem);
 */
 test = new WFObject("data/test.obj");
 m_renderObjects->Add(test);
}

/*
void ZSpaceRenderer::ReorientCamera() {
glViewport(0, 0, m_width, m_height);
m_matrix.pj = glm::perspective(glm::float_t(45.0), glm::float_t((float)m_width / (float)m_height), glm::float_t(0.01), glm::float_t(2.0));

m_matrix.mv = glm::lookAt(glm::vec3(-0.01, -0.01, -0.01),
glm::vec3(0.0, 0.0, 0.0),
glm::vec3(0.0, 1.0, 0.0));
}
*/

void ZSpaceRenderer::Render() {
  //LARGE_INTEGER ticksPerSecond = m_timer->getFrequencyTicksPerSecond();

  //m_matrix.t += 1000.0/((double)ticksPerSecond.LowPart);

  m_matrix.t += 0.1;
  if(m_matrix.t >= 1.0){
    m_matrix.t = 0.0;
    //m_animGrp->Inc();
    //m_animGrpArms->Inc();
  }

  //m_timer->restart();

  // m_matrix.mv = glm::rotate(m_matrix.mv, glm::float_t(m_matrix.t * 1000), glm::vec3(1.0, 1.0, 1.0));


  //unsigned long currentTime = timeGetTime();
  //unsigned long diffTime =  currentTime - m_lastAnimTime;



 // if (!pause && diffTime > 33){// && (int)m_matrix.t % 20 == 0) {
//    m_animGrp->Inc();
 //   m_animGrpArms->Inc();

//    m_lastAnimTime = currentTime - (diffTime % 33);
//
  //if (v_isPenActive == 2 && lastPenPush != 2) {
  //	pause = (pause) ? false : true;
  //	}



  zSpaceUpdate();
  renderFrame();
}

void ZSpaceRenderer::TrueRender() {

  /*
  glm::mat4 currentMV = m_matrix.mv;

  if(m_pen->getTopButton()){

  float *cake = glm::value_ptr(currentMV);

  for(int i = 0; i < 16; i++) std::cout << cake[i] << " ";
  std::cout << std::endl << " - ";
  currentMV = currentMV * m_pen->getMatrix();
  cake = glm::value_ptr(currentMV);
  for(int i = 0; i < 16; i++) std::cout << cake[i] << " ";
  std::cout << std::endl;
  }
  */

  //float op = 0.1;
  // Flush the render buffers.
  //
  /*
  float scale = 1.0/sqrt(pow(eyePos.x - pointLightPos.x,2) + pow(eyePos.y - pointLightPos.y,2) + pow(eyePos.z - pointLightPos.z,2));
  if (scale < 0.1) scale = 0.1;

  if (v_isPenActive == 0) {
  penScale = scale*saveScale;
  penSavePos = pointLightPos;
  penSaveRot = pointLightRot;
  }
  else {
  saveScale = penScale;
  }


  if (v_isPenActive == 1 && lastPenPush != 1) {
  penScaleSavePos = pointLightPos;
  penScaleSaveRot = pointLightRot;
  }
  else if (v_isPenActive == 1 && lastPenPush == 1) {
  op = sqrt(pow(penScaleSavePos.x - pointLightPos.x,2) + pow(penScaleSavePos.y - pointLightPos.y,2) + pow(penScaleSavePos.z - pointLightPos.z,2));
  op = (op < 0.1) ? 0.1 : op;

  }
  else if (v_isPenActive != 1 && lastPenPush == 1) {
  //writeSubToFile(penScaleSavePos, op);
  }

  lastPenPush = v_isPenActive;
  */



  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  m_shader->Begin();




  m_shader->SetUniform(m_shader->GetUniform("projectionMatrix"), m_matrix.pj);
  if(m_pen->getTopButton()){
    m_shader->SetUniform(m_shader->GetUniform("modelviewMatrix"), m_matrix.mv * m_pen->getMatrix() * m_stereoFrustum->getWorldScale());
  }else{
    m_shader->SetUniform(m_shader->GetUniform("modelviewMatrix"), m_matrix.mv);
  }
  m_shader->SetUniform(m_shader->GetUniform("time"), m_matrix.t);

  //m_shader->SetUniform(m_shader->GetUniform("opacity"), op);
  //  m_shader->SetUniform(m_shader->GetUniform("eyePos"), eyePos);
  //  m_shader->SetUniform(m_shader->GetUniform("penLightMode"), glm::int_t(m_pen->getPenActive()) );
  /// m_shader->SetUniform(m_shader->GetUniform("penLightPos"), pointLightPos);
  // m_shader->SetUniform(m_shader->GetUniform("penLightRot"), pointLightRot);
  //m_shader->SetUniform(m_shader->GetUniform("penMatPos"), penSavePos);
  // m_shader->SetUniform(m_shader->GetUniform("penMatScale"), penScale);
  // m_shader->SetUniform(m_shader->GetUniform("penMatRot"), penSaveRot);

  //renderStylus();


  m_renderObjects->Render(m_matrix, *m_shader);

  m_shader->End();

}

void ZSpaceRenderer::Resize(GLuint width, GLuint height, GLuint x, GLuint y) {
  m_width = width;
  m_height = height;
  m_wx = x;
  m_wy = y;

  zSpaceUpdate();
}

void ZSpaceRenderer::zSpaceInitialize() {

  // zSpace Stereo Initialization.
  m_stereoWindow   = new zspace::stereo::StereoWindow();
  m_stereoViewport = new zspace::stereo::StereoViewport();

  m_stereoWindow->addStereoViewport(m_stereoViewport);
  m_stereoViewport->setUsingWindowSize(true);

  m_stereoFrustum = m_stereoViewport->getStereoFrustum();
  m_stereoFrustum->setInterPupillaryDistance(0.04f);                                                                                                                                                 
  m_stereoFrustum->setFarClip(1.5f);
  m_stereoFrustum->setNearClip(0.01f);
  m_stereoFrustum->setWorldScale(4.0f);
  m_stereoFrustum->setStereoLevel(1.0);

  // Initialize zSpace Left/Right Detection.
  zspace::stereo::StereoLeftRightDetect::initialize(m_stereoWindow, zspace::stereo::StereoLeftRightDetect::WINDOW_TYPE_GL);

  // <SampleCode zSpace Tracker Initialization>
  // zSpace Tracker Initialization.
  m_trackerSystem = new zspace::tracker::TrackerSystem();
  m_pen = new ZSPenObject();
  // </SampleCode zSpace Tracker Initialization>
  m_timer->start();
}

void ZSpaceRenderer::zSpaceUpdate()
{
  // Update zSpace Left/Right Frame Detection.
  zspace::stereo::StereoLeftRightDetect::update();

  // Check if the application window has moved.  If so, update the 
  // StereoWindow's position to reflect the application window's new position.
  int x = this->m_wx;
  int y = this->m_wy;

  if (m_stereoWindow->getX() != x || m_stereoWindow->getY() != y)
    m_stereoWindow->move(x, y);

  // Check if the application window has been resized.  If so, update
  // the zSpace StereoWindow's dimensions to reflect the application 
  // window's new size.
  int width  = this->m_width;
  int height = this->m_height;

  if (m_stereoWindow->getWidth() != width || m_stereoWindow->getHeight() != height)
  {
    m_stereoWindow->resize(width, height);
    glViewport(0, 0, width, height);
  }

  // Update the tracking information.
  m_trackerSystem->captureTargets();

  // <SampleCode zSpace Head TrackerTarget>
  // Grab the latest 6DOF head pose (position and orientation) and pass it off
  // to the zSpace StereoFrustum.  This allows the StereoFrustum to take the head 
  // position/rotation into account when calculating the left and right eye
  // view/projection matrices.
  m_pen->update(m_trackerSystem, m_stereoWindow);


  zspace::tracker::TrackerTarget* headTarget = m_trackerSystem->getDefaultTrackerTarget(zspace::tracker::TrackerTarget::TYPE_HEAD);

  // Check to make sure the head target is not NULL.  If the head target is NULL,
  // this signifies that the default head target cannot be found.
  if (headTarget) {
    zspace::common::Matrix4 headPose;
    headPose = zspace::common::Matrix4::IDENTITY();
    headTarget->getPose(headPose);

    //zspace::common::Vector3 pos;

    //pos = m_stereoFrustum->getEyePosition(zspace::stereo::StereoFrustum::STEREO_EYE_RIGHT);
    //float wscale = m_stereoFrustum->getWorldScale();
    //eyePos.x = pos.x/wscale;
    //eyePos.y = pos.y/wscale;
    //eyePos.z = pos.z/wscale;


    m_stereoFrustum->setHeadPose(headPose);
    m_headTrackingActive = true;
  }else{
    m_headTrackingActive = false;
  }



  /*
  zspace::tracker::TrackerTarget* primaryTarget = m_trackerSystem->getDefaultTrackerTarget(zspace::tracker::TrackerTarget::TYPE_PRIMARY);
  if (primaryTarget) {
  zspace::common::Matrix4 primaryPose      = zspace::common::Matrix4::IDENTITY();
  zspace::common::Matrix4 primaryWorldPose = zspace::common::Matrix4::IDENTITY();

  primaryTarget->getPose(primaryPose);

  zspace::common::Vector3 pos = zspace::common::Vector3::ZERO();
  zspace::common::Vector3 scale = zspace::common::Vector3::ZERO();
  zspace::common::Quaternion ori = zspace::common::Quaternion::ZERO();
  primaryPose.decomposition(pos,scale,ori);


  float wscale = m_stereoFrustum->getWorldScale();
  //pos.y *= wscale;
  //pos.z *= wscale;
  //pos.x *= wscale;
  pos *= wscale;
  scale.x *= wscale;
  scale.y *= wscale;
  scale.z *= wscale;
  //scale *= wscale;
  ori.w *= wscale;
  ori.x *= wscale;
  ori.y *= wscale;
  ori.z *= wscale;

  primaryPose = zspace::common::Matrix4(ori);
  primaryPose.setScale(scale);
  primaryPose.setTrans(pos);


  convertPoseToWorldSpace(primaryPose, primaryWorldPose);

  setStylusTransform(primaryWorldPose);
  }
  */
}



void ZSpaceRenderer::zSpaceShutdown() {
  // Shutdown zSpace Left/Right Frame Detection.
  zspace::stereo::StereoLeftRightDetect::shutdown();

  // Remove references to any zSpace objects that have been allocated.
  if (m_stereoWindow)
    m_stereoWindow->removeReference();

  if (m_stereoViewport)
    m_stereoViewport->removeReference();

  // <SampleCode zSpace Tracker Shutdown>
  if (m_trackerSystem)
    m_trackerSystem->removeReference();

  m_timer->stop();
}
/*
void ZSpaceRenderer::setStylusVisualizationEnabled(bool isStylusEnabled)
{
m_isStylusEnabled = isStylusEnabled;
}


void ZSpaceRenderer::setStylusTransform(const zspace::common::Matrix4& stylusTransform)
{
m_stylusTransform = stylusTransform;
}


void ZSpaceRenderer::setSecondaryVisualizationEnabled(bool isSecondaryEnabled)
{
m_isSecondaryEnabled = isSecondaryEnabled;
}


void ZSpaceRenderer::setSecondaryTransform(const zspace::common::Matrix4& secondaryTransform)
{
m_secondaryTransform = secondaryTransform;
}

int ZSpaceRenderer::isStylusButtonPressed() {
int state = -1;
zspace::tracker::TrackerTarget* primaryTarget = m_trackerSystem->getDefaultTrackerTarget(zspace::tracker::TrackerTarget::TYPE_PRIMARY);
if (primaryTarget) {
// Get the primary tracker target's button capability if it exists.
zspace::tracker::ITrackerButtonCapability* trackerButtonCapability =
(zspace::tracker::ITrackerButtonCapability*)(primaryTarget->getCapability(zspace::tracker::ITrackerCapability::TYPE_BUTTON));

if (!trackerButtonCapability) {
printf("Tracker button capability: Not Found.\n");
return state;
}

// Get the number of buttons associated with the stylus.
unsigned int numButtons = trackerButtonCapability->getNumButtons();

for (unsigned int buttonId = 0; buttonId < numButtons; ++buttonId) {
// Check if the specified button is up or down.
bool isButtonPressed = trackerButtonCapability->isButtonPressed(buttonId);

// Detect any changes in state.
if (isButtonPressed) {
state = buttonId;
}
}
}
return state;
}
*/

void ZSpaceRenderer::renderStylus()
{

  if (m_pen->getPenActive()) {

    glm::mat4 penMatrix = m_pen->getMatrix();


    // Get the x,y,z position of the stylus from the viewing matrix
    float wscale = 1.0/m_stereoFrustum->getWorldScale();

    //pointLightPos.x = -wscale;
    //pointLightPos.y = wscale*(stylusTransformGl[13]/0.5);
    //pointLightPos.x = wscale*(stylusTransformGl[12]/0.5);
    //pointLightPos.z = wscale*(stylusTransformGl[14]/0.5);
    pointLightPos.x = penMatrix[0][0];
    pointLightPos.y = penMatrix[0][1];
    pointLightPos.z = penMatrix[0][2];

    //pointLightPos *= wscale;

    //calcuate the orientation of the pen
    float thetaS = glm::atan(pointLightPos.y,pointLightPos.z);


    //Rotation along x axis -- I think the x axis is up and down on a 2d screen
    float rS = sqrt(pointLightPos.y*pointLightPos.y  + pointLightPos.z*pointLightPos.z);
    //pointLightPos.z = wscale * (rS/* + 0.11*wscale*/)* cos(thetaS);
    //pointLightPos.y = wscale * (rS/* + 0.11*wscale*/) * sin(thetaS);
    //pointLightPos.z -= 0.8;



    //calcuate the orientation of the pen
    float thetaX = glm::atan(penMatrix[2][1],penMatrix[2][2]);
    float c2     = glm::sqrt(penMatrix[0][0]*penMatrix[0][0]  + penMatrix[1][0]*penMatrix[1][0]);
    float thetaY = glm::atan(-penMatrix[2][0],c2);
    float s1     = glm::sin(thetaX);
    float c1     = glm::cos(thetaX);
    float thetaZ = glm::atan(s1*penMatrix[0][2] - c1*penMatrix[0][1], c1*penMatrix[1][1] - s1*penMatrix[1][2]);


    //The pen should now be pointing down the z axis
    pointLightRot.x = thetaX;
    pointLightRot.y = thetaY;
    pointLightRot.z = thetaZ;
    //The pens orientation and position are now available to be passed to Vertex
  }


}

void ZSpaceRenderer::renderFrame() {
  wglMakeCurrent(m_window->m_hDC, m_window->m_hRC);

  /*
  bool pressed = false;
  time(&timer);
  if(v_isPenActive == 0 && v_lastPenPush != v_isPenActive){
  prevTime = timer;
  }
  if(v_isPenActive == 0 && (((unsigned int)(difftime(timer,prevTime)*100))%60) == 0){
  pressed = true;
  }
  v_lastPenPush = v_isPenActive;
  */

  // Orbit the monoscopic camera about the center of the scene.
  //OpenGlScene::rotateScene();

  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Render the scene for each eye.
  renderScene(zspace::stereo::StereoFrustum::STEREO_EYE_LEFT);
  renderScene(zspace::stereo::StereoFrustum::STEREO_EYE_RIGHT);

  // Flush the render buffers.
  SwapBuffers(m_window->m_hDC);
}

void ZSpaceRenderer::renderScene(zspace::stereo::StereoFrustum::StereoEye eye) {
  //glm::mat4 s_proj = m_matrix.pj;
  //glm::mat4 s_mvm  = m_matrix.mv;



  // Set up the view and projection matrices for the specified eye.
  setupViewMatrix(eye);
  setupProjectionMatrix(eye);

  // m_matrix.pj = glm::perspective(45.0f, (float)m_width / (float)m_height, 0.01f, 1.5f);
  //m_matrix.mv = glm::lookAt(glm::vec3(0.0f, 1.0f, 0.1f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

  // Select appropriate back buffer to render to based on the specified eye.
  if (eye == zspace::stereo::StereoFrustum::STEREO_EYE_LEFT)
    glDrawBuffer(GL_BACK_LEFT);
  else if (eye == zspace::stereo::StereoFrustum::STEREO_EYE_RIGHT)
    glDrawBuffer(GL_BACK_RIGHT);

  // Render the scene.
  //OpenGlScene::render();
  TrueRender();

  //m_matrix.pj = s_proj;
  //m_matrix.mv = s_mvm;
}

void ZSpaceRenderer::setupViewMatrix(zspace::stereo::StereoFrustum::StereoEye eye) {

  if(m_headTrackingActive){
    GLfloat viewMatrixGl[16];

    // Get the view matrix from the zSpace StereoFrustum for a specified eye
    // and convert it into OpenGl matrix format.
    zspace::common::Matrix4 viewMatrix = zspace::common::Matrix4::IDENTITY();
    m_stereoFrustum->getViewMatrix(eye, viewMatrix);


    zspace::common::MathConverterGl::convertMatrix4ToMatrixGl(viewMatrix, viewMatrixGl);
    m_matrix.mv = glm::make_mat4(viewMatrixGl);
  }else{
    m_matrix.mv = glm::lookAt(glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
  }

}

void ZSpaceRenderer::setupProjectionMatrix(zspace::stereo::StereoFrustum::StereoEye eye) {
  GLfloat projectionMatrixGl[16];

  // Get the projection matrix from the zSpace StereoFrustum for a specified eye
  // and convert it into OpenGl matrix format.
  zspace::common::Matrix4 projectionMatrix = zspace::common::Matrix4::IDENTITY();
  m_stereoFrustum->getProjectionMatrix(eye, projectionMatrix);

  zspace::common::MathConverterGl::convertMatrix4ToMatrixGl(projectionMatrix, projectionMatrixGl);

  // Set OpenGl MatrixMode to GL_PROJECTION and set the projection matrix.
  m_matrix.pj = glm::make_mat4(projectionMatrixGl); 
}
