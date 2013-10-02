#pragma once

#include <map>
#include <vector>
#include "../defines.h"

#ifdef _WIN32
#include "libs/OpenGL/GLEW/include/GL/glew.h"
#else
#include "GLES/gl.h"
#endif

namespace star
{

	class AudioManager
	{
	public:
		~AudioManager(void){}

		static AudioManager* GetInstance();

		bool LoadSound(const tstring& path, const tstring& name);
		bool DeleteSound(const tstring& name);
		GLuint GetSound(const tstring& name);
		void EraseSounds();

	private:
		//Data Members
		static AudioManager* mAudioManager;
		//std::map<tstring, Texture2D*> mSoundsList;
		std::vector<tstring> mPathList;

		AudioManager(void){}

		AudioManager(const AudioManager& yRef);
		AudioManager(AudioManager&& yRef);
		AudioManager& operator=(const AudioManager& yRef);
	};
}
