#pragma once
#include "stdafx.h"
#include "apzRenderer.h"
#include "apzShader.h"
#include "apzData.h"
#include "apzSwitchRenderGroup.h"
#include "apzParticleSystem.h"
#include "apzVelocityParticleSystem.h"
#include "apzTemplateParticleSystem.h"
#include "apzSwitchRGOpacity.h"
#include "apzZSPenObject.h"

namespace apz {

  static bool initGlew = false;

  class ZSpaceRenderer : public Renderer {
  public:
    ZSpaceRenderer(WINDOW_DATA *tWinData);
    virtual void Setup(GLuint x, GLuint y, GLuint width, GLuint height);
    virtual void Render();
    virtual void Resize(GLuint width, GLuint height, GLuint x, GLuint y);

    void AddObject(RenderObject *tObj);

  private:
    RenderGroup *m_renderObjects;
    SwitchRGOpacity *m_animGrp;
    SwitchRGOpacity *m_animGrpArms;

	TemplateParticleSystem *m_renderSystem;

    unsigned long m_lastAnimTime;


    Shader *m_shader;

    //void ReorientCamera();
    void TrueRender();

    /* ZSpace Information */
    unsigned long m_zsx;
    unsigned long m_zsy;
    unsigned long m_wx;
    unsigned long m_wy;
    unsigned long m_width;
    unsigned long m_height;

    time_t timer;
    time_t prevTime;

    glm::vec3 penSavePos;
    glm::vec3 penSaveRot;

    glm::vec3 penScaleSavePos;
    glm::vec3 penScaleSaveRot;
    int lastPenPush;
    float penScale;
    float saveScale;

    glm::vec3 eyePos;
    glm::vec4  pointLightColor;
    glm::vec3  pointLightPos;
    glm::vec3  pointLightRot;
    float pointLightRadius;
    int   v_lastPenPush;
    int   v_isPenActive;
    bool pause;
    bool m_headTrackingActive;

    float stylus[16];


    ZSPenObject *m_pen;

    zspace::stereo::StereoWindow* m_stereoWindow;
    zspace::stereo::StereoViewport* m_stereoViewport;
    zspace::stereo::StereoFrustum* m_stereoFrustum;
    zspace::tracker::TrackerSystem* m_trackerSystem;

    bool                    m_isStylusEnabled;
    zspace::common::Matrix4 m_stylusTransform;

    bool                    m_isSecondaryEnabled;
    zspace::common::Matrix4 m_secondaryTransform;


    zspace::common::Timer* m_timer;

    void zSpaceInitialize();
    void zSpaceUpdate();
    void zSpaceShutdown();
    void renderFrame();
    void renderScene(zspace::stereo::StereoFrustum::StereoEye eye);
    void setupViewMatrix(zspace::stereo::StereoFrustum::StereoEye eye);
    void setupProjectionMatrix(zspace::stereo::StereoFrustum::StereoEye eye);

    void convertPoseToWorldSpace(const zspace::common::Matrix4& pose, zspace::common::Matrix4& worldPose);
    int isStylusButtonPressed();
    void renderStylus();
    void setStylusVisualizationEnabled(bool isStylusEnabled);
    void setStylusTransform(const zspace::common::Matrix4& stylusTransform);

    void setSecondaryVisualizationEnabled(bool isSecondaryEnabled);
    void setSecondaryTransform(const zspace::common::Matrix4& secondaryTransform);

  };

};