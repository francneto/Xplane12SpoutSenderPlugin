#include "SpoutSender.h"
#include <GL/gl.h>

static GLuint gTex = 0;

void SpoutSender::SendFrame()
{
    // Get REAL framebuffer size
    GLint vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);
    // Ensure full framebuffer copy
    glViewport(0, 0, vp[2], vp[3]);

    int fbWidth = vp[2];
    int fbHeight = vp[3];

    if (fbWidth <= 0 || fbHeight <= 0)
        return;

    if (!initialized) {
        spout.CreateSender("XPlane12_Spout", fbWidth, fbHeight);

        glGenTextures(1, &gTex);
        glBindTexture(GL_TEXTURE_2D, gTex);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA8,
            fbWidth,
            fbHeight,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            nullptr
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        initialized = true;
    }

    glBindTexture(GL_TEXTURE_2D, gTex);

    // Copy FULL framebuffer
    glCopyTexSubImage2D(
        GL_TEXTURE_2D,
        0,
        0, 0,
        0, 0,
        fbWidth,
        fbHeight
    );

    spout.SendTexture(
        gTex,
        GL_TEXTURE_2D,
        fbWidth,
        fbHeight
    );
}

void SpoutSender::Shutdown()
{
    if (initialized) {
        spout.ReleaseSender();

        if (gTex != 0) {
            glDeleteTextures(1, &gTex);
            gTex = 0;
        }

        initialized = false;
    }
}
