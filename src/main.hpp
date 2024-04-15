/* File: main.hpp
*
* Author: Jacob Meadows
*
* This is the header file for main.cpp
*/
#ifndef MAIN_HPP
#define MAIN_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <array>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <limits>
#include <optional>
#include <set>
#include <map>
#include <format>
// #include <vulkan/vulkan.h>

#pragma region Constants
constexpr const char* TITLE = "False Insignia";
constexpr const char* VERTEX_FILE = "E:/Vulkan-Project/shaders/vert.spv";
constexpr const char* FRAGMENT_FILE = "E:/Vulkan-Project/shaders/frag.spv";
constexpr const uint32_t DEFAULT_WIDTH = 1280;
constexpr const uint32_t DEFAULT_HEIGHT = 720;
constexpr const int MAX_FRAMES_IN_FLIGHT = 2;


#ifndef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};
const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

#pragma region Error strings
constexpr const char* VALIDATION_LAYER_ERROR = \
    "Validation layers requested, but not available!";
constexpr const char* INSTANCE_CREATION_ERROR = \
    "Failed to create instance!";
constexpr const char* DEBUG_MESSENGER_ERROR = \
    "Failed to set up debug messenger!";
constexpr const char* SURFACE_CREATION_ERROR = \
    "Failed to create window surface!";
constexpr const char* VULKAN_GPU_ERROR = \
    "Failed to find GPUs with Vulkan support!";
constexpr const char* SUITABLE_GPU_ERROR = \
    "Failed to find a suitable GPU!";
constexpr const char* LOGICAL_DEVICE_CREATION_ERROR = \
    "Failed to create logical device!";
constexpr const char* SWAPCHAIN_CREATION_ERROR = \
    "Failed to create swap chain!";
constexpr const char* IMAGEVIEWS_CREATION_ERROR = \
    "Failed to create image views!";
constexpr const char* FILE_OPEN_ERROR = \
    "Failed to open file!";
constexpr const char* SHADER_CREATION_ERROR = \
    "Failed to create shader module!";
constexpr const char* PIPELINE_LAYOUT_CREATION_ERROR = \
    "Failed to create pipeline layout!";
constexpr const char* RENDER_PASS_CREATION_ERROR = \
    "Failed to create render pass!";
constexpr const char* GRAPHICS_PIPELINE_CREATION_ERROR = \
    "Failed to create graphics pipeline!";
constexpr const char* FRAMEBUFFER_CREATION_ERROR = \
    "Failed to create framebuffer!";
constexpr const char* COMMAND_POOL_CREATION_ERROR = \
    "Failed to create command pool!";
constexpr const char* COMMAND_BUFFER_ALLOCATION_ERROR = \
    "Failed to allocate command buffers!";
constexpr const char* COMMAND_BUFFER_RECORDING_ERROR = \
    "Failed to begin recording command buffer!";
constexpr const char* COMMAND_BUFFER_RECORD_ERROR = \
    "Failed to record command buffer!";
constexpr const char* SEMAPHORE_CREATION_ERROR = \
    "Failed to create semaphores!";
constexpr const char* COMMAND_BUFFER_SUBMISSION_ERROR = \
    "Failed to submit draw command buffer!";
constexpr const char* SWAP_CHAIN_ACQUISITION_ERROR = \
    "Failed to acquire swap chain image!";
constexpr const char* SWAP_CHAIN_PRESENTATION_ERROR = \
    "Failed to present swap chain image!";
constexpr const char* VERTEX_BUFFER_CREATION_ERROR = \
    "Failed to create vertex buffer!";
constexpr const char* MEMORY_TYPE_ASSESSMENT_ERROR = \
    "Failed to find suitable memory type!";
constexpr const char* VERTEX_BUFFER_MEMORY_ALLOCATION_ERROR = \
    "Failed to allocate vertex buffer memory!";
#pragma endregion
#pragma endregion

#pragma region Structs
struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() const;
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

struct Vertex {
    glm::uvec4 data;

    static VkVertexInputBindingDescription getBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions();
};
#pragma endregion

#pragma region Functions
VkResult CreateDebugUtilsMessengerEXT(
    VkInstance, const VkDebugUtilsMessengerCreateInfoEXT*,
    const VkAllocationCallbacks*, VkDebugUtilsMessengerEXT*
);

void DestroyDebugUtilsMessengerEXT(
    VkInstance, VkDebugUtilsMessengerEXT, const VkAllocationCallbacks*
);

static std::vector<char> readFile(const std::string&);
#pragma endregion

#pragma region Classes
class FIApplication {
public:
    void run();

private:
    GLFWwindow* window;

    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkSurfaceKHR surface;

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;

    VkQueue graphicsQueue;
    VkQueue presentQueue;

    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;

    VkRenderPass renderPass;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;

    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;

    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;

    uint32_t currentFrame = 0;
    bool framebufferResized = false;
    const std::vector<Vertex> vertices = {
	{{0b00000000, 0, 0, 0}},
	{{0b00000010, 0, 0, 0}},
	{{0b00000100, 0, 0, 0}},
	{{0b00000100, 0, 0, 0}},
	{{0b00000010, 0, 0, 0}},
	{{0b00000110, 0, 0, 0}}
    };

    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();

    void createInstance();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT&);
    void setupDebugMessenger();
    void createSurface();
    void pickPhysicalDevice();
    void createLogicalDevice();
    void createSwapChain();
    void createImageViews();
    void createRenderPass();
    void createGraphicsPipeline();
    void createFramebuffers();
    void createCommandPool();
    void createVertexBuffer();
    void createCommandBuffers();
    void createSyncObjects();

    void drawFrame();

    void cleanupSwapChain();
    void recreateSwapChain();
    void recordCommandBuffer(VkCommandBuffer, uint32_t);
    VkShaderModule createShaderModule(const std::vector<char>&);
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(
	const std::vector<VkSurfaceFormatKHR>&
    );
    VkPresentModeKHR chooseSwapPresentMode(
	const std::vector<VkPresentModeKHR>&
    );
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR&);
    int rateDeviceSuitability(VkPhysicalDevice);
    bool checkDeviceExtensionSupport(VkPhysicalDevice);
    uint32_t findMemoryType(uint32_t, VkMemoryPropertyFlags);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice);
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice);
    std::vector<const char*> getRequiredExtensions();
    bool checkValidationLayerSupport();
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT,
	VkDebugUtilsMessageTypeFlagsEXT,
	const VkDebugUtilsMessengerCallbackDataEXT*, void*
    );
    static void framebufferResizeCallback(GLFWwindow*, int, int);
};
#pragma endregion

#endif /* MAIN_HPP */

