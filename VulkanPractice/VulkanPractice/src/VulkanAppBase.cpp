#include "VulkanAppBase.h"

VulkanAppBase::VulkanAppBase()
{
}

VulkanAppBase::~VulkanAppBase()
{
}

void VulkanAppBase::initialize(GLFWwindow* window, const char* appName)
{
}

void VulkanAppBase::terminate()
{
}

void VulkanAppBase::prepare()
{
}

void VulkanAppBase::render()
{
}

void VulkanAppBase::checkResult(VkResult)
{
}

void VulkanAppBase::initializeInstance(const char* appName)
{
	using namespace std;
	vector<const char*> extensions;
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = appName;
	appInfo.pEngineName = appName;
	appInfo.apiVersion = VK_API_VERSION_1_1;
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);

	// 拡張情報の取得.
	vector<VkExtensionProperties> props;
	{
		uint32_t count = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr);
		props.resize(count);
		vkEnumerateInstanceExtensionProperties(nullptr, &count, props.data());

		for (const auto& v : props)
		{
			extensions.push_back(v.extensionName);
		}
	}
	VkInstanceCreateInfo ci{};
	ci.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	ci.enabledExtensionCount = uint32_t(extensions.size());
	ci.ppEnabledExtensionNames = extensions.data();
	ci.pApplicationInfo = &appInfo;
#ifdef _DEBUG 
	// デバッグビルド時には検証レイヤーを有効化
	const char* layers[] = { "VK_LAYER_KHRONOS_validation" };
	if (VK_HEADER_VERSION_COMPLETE < VK_MAKE_VERSION(1, 1, 106)) {
		// "VK_LAYER_LUNARG_standard_validation" は廃止になっているが昔の Vulkan SDK では動くので対処しておく.
		layers[0] = "VK_LAYER_LUNARG_standard_validation";
	}
	ci.enabledLayerCount = 1;
	ci.ppEnabledLayerNames = layers;
#endif

	// インスタンス生成
	auto result = vkCreateInstance(&ci, nullptr, &m_instance);
	checkResult(result);
}

void VulkanAppBase::selectPhysicalDevice()
{
}

uint32_t VulkanAppBase::searchGraphicsQueueIndex()
{
	return 0;
}

void VulkanAppBase::createDevice()
{
}

void VulkanAppBase::prepareCommandPool()
{
}

void VulkanAppBase::selectSurfaceFormat(VkFormat format)
{
}

void VulkanAppBase::createSwapchain(GLFWwindow* window)
{
}

void VulkanAppBase::createDepthBuffer()
{
}

void VulkanAppBase::createViews()
{
}

void VulkanAppBase::createRenderPass()
{
}

void VulkanAppBase::createFramebuffer()
{
}

void VulkanAppBase::prepareCommandBuffers()
{
}

void VulkanAppBase::prepareSemaphores()
{
}

uint32_t VulkanAppBase::getMemoryTypeIndex(uint32_t requestBits, VkMemoryPropertyFlags requestProps) const
{
	return 0;
}

void VulkanAppBase::enableDebugReport()
{
}

void VulkanAppBase::disableDebugReport()
{
}
