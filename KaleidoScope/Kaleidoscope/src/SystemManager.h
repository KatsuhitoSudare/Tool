#pragma once

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
		};
	}
}


