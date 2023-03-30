#pragma onc
#include<string>

namespace KALEIDOSCOPE
{
	namespace SYSTEM
	{
		class SystemManager
		{
		public:
			SystemManager();
			~SystemManager();

			void SystemInitialize();
			void SystemRunning();
			void SystemShutDown();
		private:
			void ProjectSettingFileInit();

			std::string OpenScene;
		};
	}
}


