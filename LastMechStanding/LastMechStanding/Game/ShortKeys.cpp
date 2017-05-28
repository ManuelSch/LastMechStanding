#include "ShortKeys.h"



ShortKeys::ShortKeys(GLFWwindow* window)
{
	this->window = window;

	// initialize shortkey parameters:
	this->showHelp = false;
	this->frameTimeOn = false;
	this->wireFrameOn = false;
	this->textureSamplingQuality = TextureSamplingQuality::BILINEAR;
	this->mipMappingQuality = MipMappingQuality::OFF;
	this->shadowMappinOn = true;
	this->viewFrustumCullingOn = true;
	this->blendingOn = true;
}


ShortKeys::~ShortKeys()
{
}

void ShortKeys::pressShortKey(int key)
{
	switch(key) {
		// esc key -> close window:
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(this->window, GL_TRUE);
			break;

		// f1 -> show help:
		case GLFW_KEY_F1:
			showHelp = !showHelp;
			// TODO
			cout << "Show help = " << (showHelp ? "ON" : "OFF") << endl;
			break;

		// f2 -> frame time on/off:
		case GLFW_KEY_F2:
			frameTimeOn = !frameTimeOn;
			cout << "Frame time = " << (frameTimeOn ? "ON" : "OFF") << endl;
			break;

		// f3 -> wire frame on/off:
		case GLFW_KEY_F3:
			wireFrameOn = !wireFrameOn;
			glPolygonMode(GL_FRONT_AND_BACK, (wireFrameOn ? GL_LINE : GL_FILL));
			cout << "Wire frame = " << (wireFrameOn ? "ON" : "OFF") << endl;
			break;

		// f4 -> texture sampling quality (nearest neighbor/bilinear):
		case GLFW_KEY_F4:
			textureSamplingQuality = (textureSamplingQuality == TextureSamplingQuality::BILINEAR ? TextureSamplingQuality::NEAREST_NEIGHBOR : TextureSamplingQuality::BILINEAR);
			// TODO
			cout << "Texture sampling quality = " << (textureSamplingQuality == TextureSamplingQuality::BILINEAR ? "BILINEAR" : "NEAREST_NEIGHBOR") << endl;
			break;

		// f5 -> mip mapping quality (off/nearest neighbor/linear):
		case GLFW_KEY_F5:
			mipMappingQuality = (mipMappingQuality == MipMappingQuality::OFF ? MipMappingQuality::NEAREST_NEIGHBOR : (mipMappingQuality == MipMappingQuality::NEAREST_NEIGHBOR ? MipMappingQuality::LINEAR : MipMappingQuality::OFF));
			switch (mipMappingQuality) {
				case MipMappingQuality::OFF:
					//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					cout << "Mip mapping quality = OFF" << endl;
					break;
				case MipMappingQuality::NEAREST_NEIGHBOR:
					//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
					cout << "Mip mapping quality = NEAREST_NEIGHBOR" << endl;
					break;
				case MipMappingQuality::LINEAR:
					//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
					cout << "Mip mapping quality = LINEAR" << endl;
					break;
			}
			break;

		// f6 -> enable/disable shadow mapping:
		case GLFW_KEY_F6:
			shadowMappinOn = !shadowMappinOn;
			cout << "Shadow Mapping = " << (shadowMappinOn ? "ON" : "OFF") << endl;
			break;

		// f7 -> enable/disable effect:
		case GLFW_KEY_F7:
			// TODO
			break;

		// f8 -> view frustum culling on/off
		case GLFW_KEY_F8:
			viewFrustumCullingOn = !viewFrustumCullingOn;
			// TODO
			cout << "View frustum culling = " << (viewFrustumCullingOn ? "ON" : "OFF") << endl;
			break;

		// f9 -> blending on/off:
		case GLFW_KEY_F9:
			blendingOn = !blendingOn;
			if (blendingOn) {
				glEnable(GL_TEXTURE_2D);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}
			else {
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_BLEND);
				glDisable(GL_SRC_ALPHA);
			}
			cout << "Blending = " << (blendingOn ? "ON" : "OFF") << endl;
			break;
	}
}

