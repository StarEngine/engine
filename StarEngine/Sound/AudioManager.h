#pragma once
// [COMMENT] you're not using an std::map so why include this header?
#include <map>
#include <vector>
#include "../defines.h"

#ifdef _WIN32
#include <glew.h>
#else
#include "GLES/gl.h"
#endif

namespace star
{

	class AudioManager
	{
	public:
		// [COMMENT] somethimes you use void and somethines you leave it
		// empty. choose of the 2 please.
		~AudioManager(void) {}

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
#ifdef _WIN32
		AudioManager(AudioManager&& yRef);
#endif
		AudioManager& operator=(const AudioManager& yRef);
	};
}
