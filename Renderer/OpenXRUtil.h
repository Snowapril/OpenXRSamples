//
// Created by swinston on 8/19/20.
//

#ifndef OPENXR_OPENXRUTIL_H
#define OPENXR_OPENXRUTIL_H

#include <vulkan/vulkan.h>
#ifndef XR_USE_GRAPHICS_API_VULKAN
#define XR_USE_GRAPHICS_API_VULKAN 1
#endif
#include <openxr/openxr_platform.h>
#include <vector>

class SwapChains;

namespace Util {
    namespace Renderer {
        enum OPENXR_HANDS
        {
            HAND_LEFT = 0,
            HAND_RIGHT = 1,
            HAND_COUNT
        };

        class VulkanUtil;
        class OpenXRUtil {
            friend class VulkanUtil;
            VulkanUtil * app;
            XrInstance instance;
            XrSession session;
            XrSpace local_space;
            XrSystemId system_id;
            XrFormFactor formFactor;
            XrViewConfigurationType viewConfigurationType;
            XrEnvironmentBlendMode environmentBlendMode;

            XrGraphicsBindingVulkanKHR graphics_binding;
            XrViewConfigurationType view_config_type;
            XrViewConfigurationView* configuration_views;
            uint32_t view_count;
            XrInstanceCreateInfo instanceCreateInfo;
            XrFrameState frameState;
            XrView * views;
            XrPath hand_paths[HAND_COUNT];
            XrCompositionLayerProjectionView* projectionView;
            bool is_visible;
            bool is_running;
            std::vector<XrSwapchain> xrSwapChains;
            std::vector<uint32_t> xrSwapChainLengths;
            XrActionSet actionSet;
            XrAction exitAction;
            float fov;
            bool initSpaces();
            bool initActions();
            bool checkExtensions();
            void createProjectionViews();
        public:
            OpenXRUtil(VulkanUtil * _app, const XrInstanceCreateInfo& ici);
            ~OpenXRUtil();

            std::vector<XrSwapchainImageVulkanKHR> images;
            std::vector<VkImage> getImages();
            bool createOpenXRInstance();
            bool initOpenXR(bool useLegacy = false);
            bool setupSwapChain(SwapChains & swapChains);
            bool createOpenXRSystem();

            bool setupViews();
            void beginFrame();
            bool endFrame();
            XrPosef getCurrentHeadPose();
        };

    }
}

#endif //OPENXR_OPENXRUTIL_H
