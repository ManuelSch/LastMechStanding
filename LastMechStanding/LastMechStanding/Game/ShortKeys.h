#pragma once

/*
 Manages the short key actions (F1-F9, Esc)
*/

#include "..\commonHeader.h"

class ShortKeys
{
public:
	enum class TextureSamplingQuality {
		NEAREST_NEIGHBOR,
		BILINEAR
	};
	enum class MipMappingQuality {
		OFF,
		NEAREST_NEIGHBOR,
		LINEAR
	};

	ShortKeys(GLFWwindow* window);
	~ShortKeys();

	void pressShortKey(int key);

	// F1-F9 parameters (read only! change via pressShortKey()):
	bool showHelp;
	bool frameTimeOn;
	bool wireFrameOn;
	TextureSamplingQuality textureSamplingQuality;
	MipMappingQuality mipMappingQuality;
	bool shadowMappinOn;
	bool viewFrustumCullingOn;
	bool blendingOn;

private:
	GLFWwindow* window;

};

