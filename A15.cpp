// This has been adapted from the Vulkan tutorial

#include "Starter.hpp"
#include "TextMaker.hpp"

#include "planet.hpp"
#include "particle.hpp"




std::vector<SingleText> demoText = {
    {1, {"Solar System: static scene", "", "", ""}, 0, 0},
     {1, {"Solar System: dynamic scene", "", "", ""}, 0, 0}
};

// The uniform buffer object used in this example
struct UniformBufferObject {
    alignas(16) glm::mat4 mvpMat;
    alignas(16) glm::mat4 mMat;
    alignas(16) glm::mat4 nMat;
};

struct SkyUniformBufferObject {
    alignas(16) glm::mat4 mvpMat;
    alignas(16) glm::mat4 mMat;
    alignas(16) glm::mat4 nMat;
};

struct GlobalUniformBufferObject {
    alignas(16) glm::vec3 selector;
    alignas(16) glm::vec3 lightDir;
    alignas(16) glm::vec4 lightColor;
    alignas(16) glm::vec3 eyePos;
};

struct Vertex {
    glm::vec3 pos;
    glm::vec3 norm;
    glm::vec2 UV;
};


float currSpinAngSun = 0.0f;
float currSpinAngMercury = 0.0f;
float currSpinAngVenus = 0.0f;
float currSpinAngEarth = 0.0f;
float currSpinAngMars = 0.0f;
float currSpinAngJupiter = 0.0f;
float currSpinAngSaturn = 0.0f;
float currSpinAngUranus = 0.0f;
float currSpinAngNeptune = 0.0f;
float currSpinAngSaturnRings = 0.0f;

float orbitAngleMercury = 0.0f;
float orbitAngleVenus = 0.0f;
float orbitAngleEarth = 0.0f;
float orbitAngleMars = 0.0f;
float orbitAngleJupiter = 0.0f;
float orbitAngleSaturn = 0.0f;
float orbitAngleUranus = 0.0f;
float orbitAngleNeptune = 0.0f;
float orbitAngleSaturnRings = 0.0f;

class Assignment15;
void CameraLogic(Assignment15 *A, float Ar, glm::mat4 &ViewPrj, glm::mat4 &World);

class Assignment15 : public BaseProject {
    public:
    Assignment15() :
        MSun2(4.0f, 0.0071892f, 0.0f, "Sun", 0.0f, 0.0f),
        MMercury2(0.1f, 0.00001083f, 0.004787f, "Mercury", 0.0f, 25.0f),
        MVenus2(0.35f, 0.00000652f, 0.003502f, "Venus", 0.0f, 30.0f), //177.0
        MEarth2(0.4f, 0.001574f, 0.002978f, "Earth", 0.0f, 40.0f), //23.0
        MMars2(0.2f, 0.000866f, 0.0024077f, "Mars", 0.0f, 55.0f), //25.0
        MJupiter2(1.1f, 0.045583f, 0.001307f, "Jupiter", 0.0f, 60.0f), //3.0
        MSaturn2(1.2f, 0.036840f, 0.000968f, "Saturn", 0.0f, 70.0f), //27.0
        MUranus2(0.5f, 0.014794f, 0.00068f, "Uranus", 0.0f, 80.0f), //97.0
        MNeptune2(0.5f, 0.009719f, 0.000543f, "Neptune", 0.0f, 90.0f), //28.0
        MSaturnRings2(2.0f, 0.0001f, 0.000968f, "Saturn Rings", 0.0f, 42.0f), //30.0
        MSun1(10.0f, 0.0071892f, 0.001f, "Sun", 0.0f, 0.0f),
        MMercury1(0.1f, 0.00001083f, 0.0f, "Mercury", 0.0f, 25.0f),
        MVenus1(0.35f, 0.0041f, 0.0f, "Venus", 177.0f, 30.0f),
        MEarth1(0.4f, 0.001574f, 0.0f, "Earth", 23.0f, 140.0f),
        MMars1(0.2f, 0.000866f, 0.0f, "Mars", 25.0f, 60.0f),
        MJupiter1(1.1f, 0.045583f, 0.0f, "Jupiter", 3.0f, 60.0f),
        MSaturn1(1.2f, 0.036840f, 0.0f, "Saturn", 27.0f, 70.0f),
        MUranus1(0.5f, 0.014794f, 0.0f, "Uranus", 97.0f, 80.0f),
        MNeptune1(0.5f, 0.009719f, 0.0f, "Neptune", 28.0f, 90.0f),
        MSaturnRings1(2.0f, 0.0001f, 0.0f, "Saturn Rings", 30.0f, 42.0f)
{
    }
    
    protected:
    
    // Descriptor Layouts
    DescriptorSetLayout DSL;
    DescriptorSetLayout DSLSun2;
    // DescriptorSetLayout DSLPlanets, DSLSun, DSLAsteroidBelt;
    // Pipelines [Shader couples]

    VertexDescriptor VD;
    VertexDescriptor VDSun2;
    Pipeline P;
    Pipeline PSun2;

    
    // Models, textures and Descriptors
    
    //Scene 2
    PlanetModel<Vertex> MSun2, MMercury2, MVenus2, MEarth2, MMars2, MJupiter2, MSaturn2, MUranus2, MNeptune2, MSaturnRings2;
    Texture TSun, TMercury, TVenus, TEarth, TMars, TJupiter, TSaturn, TUranus, TNeptune, TSaturnRings;
    DescriptorSet DSSun2, DSMercury2, DSVenus2, DSEarth2, DSMars2, DSJupiter2, DSSaturn2, DSUranus2, DSNeptune2, DSSaturnRings2;
    
    //Scene 1
    PlanetModel<Vertex> MSun1, MMercury1, MVenus1, MEarth1, MMars1, MJupiter1, MSaturn1, MUranus1, MNeptune1, MSaturnRings1;
    DescriptorSet DSSun1, DSMercury1, DSVenus1, DSEarth1, DSMars1, DSJupiter1, DSSaturn1, DSUranus1, DSNeptune1, DSSaturnRings1;
    
    //Background
    VertexDescriptor VDSky;
    DescriptorSetLayout DSLSky;
    Pipeline PSky;
    Model<Vertex> MSky;
    Texture TSky;
    DescriptorSet DSSky;
    
    TextMaker txt;
    
    // Other application parameters
    int currScene = 0;
    float Ar;
    glm::mat4 ViewPrj;
    glm::vec3 Pos = glm::vec3(5.0f,2.0f,12.0f);
    glm::vec3 cameraPos;
    float Yaw = glm::radians(-5.0f);
    float Pitch = glm::radians(12.5f);
    float Roll = glm::radians(0.0f);
    
    glm::vec3 Pos2 = glm::vec3(0.0f,-0.5f,1.0f); //first number was -10
    glm::vec3 cameraPos2;
    float Yaw2 = glm::radians(0.0f);
    float Pitch2 = glm::radians(90.0f);
    float Roll2 = glm::radians(0.0f);
    
   
    void setWindowParameters() {
        // window size, titile and initial background
        windowWidth = 800;
        windowHeight = 600;
        windowTitle = "Project";
        windowResizable = GLFW_TRUE;
        initialBackgroundColor = {0.0f, 0.0f, 0.0f, 0.0f};
        
        // Descriptor pool sizes

        uniformBlocksInPool = 42; // +2 each addition
        texturesInPool = 22; // +1 each addition
        setsInPool = 40; // +2 each addition
        
        Ar = 4.0f / 3.0f;
    }
    
    // What to do when the window changes size
    void onWindowResize(int w, int h) {
        std::cout << "Window resized to: " << w << " x " << h << "\n";
        Ar = (float)w / (float)h;
    }
    
    
    void localInit() {
        
        // Descriptor Layouts
        DSL.init(this, {// Binding # | Type [Buffer/ Texture] | Pipeline Stage Used
                    {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT},
                    {1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS},
                    {2, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT}
                });
           
        DSLSky.init(this, {
                            {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT},
                            {1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT}
                          });
        
        // Vertex descriptors
        VD.init(this, {
                  {0, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX}
                }, {
                  {0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, pos),
                         sizeof(glm::vec3), POSITION},
                  {0, 1, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, norm),
                         sizeof(glm::vec3), NORMAL},
                  {0, 2, VK_FORMAT_R32G32_SFLOAT, offsetof(Vertex, UV),
                         sizeof(glm::vec2), UV}
                });

        DSLSun2.init(this, {// Binding # | Type [Buffer/ Texture] | Pipeline Stage Used
                    {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT},
                    {1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS},
                    {2, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT}
                });
           

        // Vertex descriptors
        VDSun2.init(this, {
                  {0, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX}
                }, {
                  {0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, pos),
                         sizeof(glm::vec3), POSITION},
                  {0, 1, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, norm),
                         sizeof(glm::vec3), NORMAL},
                  {0, 2, VK_FORMAT_R32G32_SFLOAT, offsetof(Vertex, UV),
                         sizeof(glm::vec2), UV}
                });
        
        VDSky.init(this, {
                  {0, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX}
                }, {
                  {0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, pos),
                         sizeof(glm::vec3), POSITION},
                  {0, 1, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, norm),
                         sizeof(glm::vec3), NORMAL},
                  {0, 2, VK_FORMAT_R32G32_SFLOAT, offsetof(Vertex, UV),
                         sizeof(glm::vec2), UV}
                });


        /* Particle Support
        generateParticles(100);
        */
        
		

        // Pipelines [Shader couples]
        // The last array, is a vector of pointer to the layouts of the sets that will
        // be used in this pipeline. The first element will be set 0, and so on..
        P.init(this, &VD, "shaders/CelestialVert.spv", "shaders/CelestialFrag.spv", {&DSL});
        P.setAdvancedFeatures(VK_COMPARE_OP_LESS, VK_POLYGON_MODE_FILL,
                                             VK_CULL_MODE_NONE, false);

        PSun2.init(this, &VDSun2, "shaders/SunVert.spv", "shaders/SunFrag.spv", {&DSLSun2});
        PSun2.setAdvancedFeatures(VK_COMPARE_OP_LESS, VK_POLYGON_MODE_FILL,
                                             VK_CULL_MODE_NONE, false);


        // Models, textures and Descriptors (values assigned to the uniforms)
        MSun2.init(this, &VDSun2, "models/Sphere.obj", OBJ);


        // Models, textures and Descriptors
        
        //Scene 2: models
        MMercury2.init(this, &VD, "models/Sphere.obj", OBJ);
        MVenus2.init(this, &VD, "models/Sphere.obj", OBJ);
        MEarth2.init(this, &VD, "models/Sphere.obj", OBJ);
        MMars2.init(this, &VD, "models/Sphere.obj", OBJ);
        MJupiter2.init(this, &VD, "models/Sphere.obj", OBJ);
        MSaturn2.init(this, &VD, "models/Sphere.obj", OBJ);
        MUranus2.init(this, &VD, "models/Sphere.obj", OBJ);
        MNeptune2.init(this, &VD, "models/Sphere.obj", OBJ);
        createRingMesh(MSaturnRings2.vertices, MSaturnRings2.indices);
        MSaturnRings2.initMesh(this, &VD);
        
        //Scene 1: models
        MSun1.init(this, &VD, "models/Sphere.obj", OBJ);
        MMercury1.init(this, &VD, "models/Sphere.obj", OBJ);
        MVenus1.init(this, &VD, "models/Sphere.obj", OBJ);
        MEarth1.init(this, &VD, "models/Sphere.obj", OBJ);
        MMars1.init(this, &VD, "models/Sphere.obj", OBJ);
        MJupiter1.init(this, &VD, "models/Sphere.obj", OBJ);
        MSaturn1.init(this, &VD, "models/Sphere.obj", OBJ);
        MUranus1.init(this, &VD, "models/Sphere.obj", OBJ);
        MNeptune1.init(this, &VD, "models/Sphere.obj", OBJ);
        createRingMesh(MSaturnRings1.vertices, MSaturnRings1.indices);
        MSaturnRings1.initMesh(this, &VD);
        
        //Background
        PSky.init(this, &VDSky,"shaders/SkyBoxVert.spv", "shaders/SkyBoxFrag.spv", { &DSLSky});
        PSky.setAdvancedFeatures(VK_COMPARE_OP_LESS_OR_EQUAL, VK_POLYGON_MODE_FILL,
                                             VK_CULL_MODE_BACK_BIT, false);
        
        //Scene 1 and 2: textures
        TSun.init(this, "textures/sun.png");
        TMercury.init(this, "textures/mercury.png");
        TVenus.init(this, "textures/venus.png");
        TEarth.init(this, "textures/earth.png");
        TMars.init(this, "textures/mars.png");
        TJupiter.init(this, "textures/jupiter.png");
        TSaturn.init(this, "textures/saturn1.png");
        TUranus.init(this, "textures/uranus.png");
        TNeptune.init(this, "textures/neptune.png");
        TSaturnRings.init(this, "textures/rings.png");
        
        //Background: textures
        MSky.init(this, &VDSky, "models/SkyBoxCube.obj", OBJ);
        const char *T2fn[] = {"textures/sky/starsmilkyway.png", "textures/sky/starsmilkyway.png", "textures/sky/starsmilkyway.png",     "textures/sky/starsmilkyway.png", "textures/sky/starsmilkyway.png", "textures/sky/starsmilkyway.png"};
        TSky.initCubic(this, T2fn);
        
        txt.init(this, &demoText);
    }
    
    // Here you create your pipelines and Descriptor Sets!
    void pipelinesAndDescriptorSetsInit() {
        
        P.create();
        PSun2.create();

        DSSun2.init(this, &DSLSun2, {
                    {0, UNIFORM, sizeof(UniformBufferObject), nullptr},
                    {1, UNIFORM, sizeof(GlobalUniformBufferObject), nullptr},
                    {2, TEXTURE, 0, &TSun}
                });
        
        DSMercury2.init(this, &DSL, {
                    {0, UNIFORM, sizeof(UniformBufferObject), nullptr},
                    {1, UNIFORM, sizeof(GlobalUniformBufferObject), nullptr},
                    {2, TEXTURE, 0, &TMercury}
                });

        DSVenus2.init(this, &DSL, {
                    {0, UNIFORM, sizeof(UniformBufferObject), nullptr},
                    {1, UNIFORM, sizeof(GlobalUniformBufferObject), nullptr},
                    {2, TEXTURE, 0, &TVenus}
                });

        DSEarth2.init(this, &DSL, {
                    {0, UNIFORM, sizeof(UniformBufferObject), nullptr},
                    {1, UNIFORM, sizeof(GlobalUniformBufferObject), nullptr},
                    {2, TEXTURE, 0, &TEarth}
                });

        DSMars2.init(this, &DSL, {
                    {0, UNIFORM, sizeof(UniformBufferObject), nullptr},
                    {1, UNIFORM, sizeof(GlobalUniformBufferObject), nullptr},
                    {2, TEXTURE, 0, &TMars}
                });

        DSJupiter2.init(this, &DSL, {
                    {0, UNIFORM, sizeof(UniformBufferObject), nullptr},
                    {1, UNIFORM, sizeof(GlobalUniformBufferObject), nullptr},
                    {2, TEXTURE, 0, &TJupiter}
                });

        DSSaturn2.init(this, &DSL, {
                    {0, UNIFORM, sizeof(UniformBufferObject), nullptr},
                    {1, UNIFORM, sizeof(GlobalUniformBufferObject), nullptr},
                    {2, TEXTURE, 0, &TSaturn}
                });

        DSUranus2.init(this, &DSL, {
                    {0, UNIFORM, sizeof(UniformBufferObject), nullptr},
                    {1, UNIFORM, sizeof(GlobalUniformBufferObject), nullptr},
                    {2, TEXTURE, 0, &TUranus}
                });

        DSNeptune2.init(this, &DSL, {
                    {0, UNIFORM, sizeof(UniformBufferObject), nullptr},
                    {1, UNIFORM, sizeof(GlobalUniformBufferObject), nullptr},
                    {2, TEXTURE, 0, &TNeptune}
                });
        
        DSSaturnRings2.init(this, &DSL, {
                    {0, UNIFORM, sizeof(UniformBufferObject), nullptr},
                    {1, UNIFORM, sizeof(GlobalUniformBufferObject), nullptr},
                    {2, TEXTURE, 0, &TSaturnRings}
                });
        
        //Scene 1
        DSSun1.init(this, &DSL, {
                    {0, UNIFORM, sizeof(UniformBufferObject), nullptr},
                    {1, UNIFORM, sizeof(GlobalUniformBufferObject), nullptr},
                    {2, TEXTURE, 0, &TSun}
                });
        
        DSMercury1.init(this, &DSL, {
                    {0, UNIFORM, sizeof(UniformBufferObject), nullptr},
                    {1, UNIFORM, sizeof(GlobalUniformBufferObject), nullptr},
                    {2, TEXTURE, 0, &TMercury}
                });
        
        DSVenus1.init(this, &DSL, {
                    {0, UNIFORM, sizeof(UniformBufferObject), nullptr},
                    {1, UNIFORM, sizeof(GlobalUniformBufferObject), nullptr},
                    {2, TEXTURE, 0, &TVenus}
                });
        
        DSEarth1.init(this, &DSL, {
                    {0, UNIFORM, sizeof(UniformBufferObject), nullptr},
                    {1, UNIFORM, sizeof(GlobalUniformBufferObject), nullptr},
                    {2, TEXTURE, 0, &TEarth}
                });
        
        DSMars1.init(this, &DSL, {
                    {0, UNIFORM, sizeof(UniformBufferObject), nullptr},
                    {1, UNIFORM, sizeof(GlobalUniformBufferObject), nullptr},
                    {2, TEXTURE, 0, &TMars}
                });

        DSJupiter1.init(this, &DSL, {
                    {0, UNIFORM, sizeof(UniformBufferObject), nullptr},
                    {1, UNIFORM, sizeof(GlobalUniformBufferObject), nullptr},
                    {2, TEXTURE, 0, &TJupiter}
                });
        
        DSSaturn1.init(this, &DSL, {
                    {0, UNIFORM, sizeof(UniformBufferObject), nullptr},
                    {1, UNIFORM, sizeof(GlobalUniformBufferObject), nullptr},
                    {2, TEXTURE, 0, &TSaturn}
                });

        DSUranus1.init(this, &DSL, {
                    {0, UNIFORM, sizeof(UniformBufferObject), nullptr},
                    {1, UNIFORM, sizeof(GlobalUniformBufferObject), nullptr},
                    {2, TEXTURE, 0, &TUranus}
                });

        DSNeptune1.init(this, &DSL, {
                    {0, UNIFORM, sizeof(UniformBufferObject), nullptr},
                    {1, UNIFORM, sizeof(GlobalUniformBufferObject), nullptr},
                    {2, TEXTURE, 0, &TNeptune}
                });
        
        DSSaturnRings1.init(this, &DSL, {
                    {0, UNIFORM, sizeof(UniformBufferObject), nullptr},
                    {1, UNIFORM, sizeof(GlobalUniformBufferObject), nullptr},
                    {2, TEXTURE, 0, &TSaturnRings}
                });
        
        //Background
        PSky.create();
        DSSky.init(this, &DSLSky, {
                    {0, UNIFORM, sizeof(SkyUniformBufferObject), nullptr},
                    {1, TEXTURE, 0, &TSky}
                });
        
        txt.pipelinesAndDescriptorSetsInit();
    }

    // Here you destroy your pipelines and Descriptor Sets!
    void pipelinesAndDescriptorSetsCleanup() {
        
        //Scenes 1 and 2: pipeline clean up
        P.cleanup();
        PSun2.cleanup();
        
        DSSun2.cleanup(); DSMercury2.cleanup(); DSVenus2.cleanup(); DSEarth2.cleanup(); DSMars2.cleanup();
        DSJupiter2.cleanup(); DSSaturn2.cleanup(); DSUranus2.cleanup(); DSNeptune2.cleanup(); DSSaturnRings2.cleanup();
        
        DSSun1.cleanup(); DSMercury1.cleanup(); DSVenus1.cleanup(); DSEarth1.cleanup(); DSMars1.cleanup();
        DSJupiter1.cleanup(); DSSaturn1.cleanup(); DSUranus1.cleanup(); DSNeptune1.cleanup(); DSSaturnRings1.cleanup();
        
        //Background: pipeline clean up
        PSky.cleanup();
        DSSky.cleanup();
        
        txt.pipelinesAndDescriptorSetsCleanup();
    }

    // Here you destroy all the Models, Texture and Desc. Set Layouts you created!
    // You also have to destroy the pipelines
    void localCleanup() {
        
        //Scene 1 and 2: textures clean up
        TSun.cleanup(); TMercury.cleanup(); TVenus.cleanup(); TEarth.cleanup(); TMars.cleanup();
        TJupiter.cleanup(); TSaturn.cleanup(); TUranus.cleanup(); TNeptune.cleanup(); TSaturnRings.cleanup();
        
        //Background: textures clean up
        TSky.cleanup();
        
        //Scene 2: models clean up
        MSun2.cleanup(); MMercury2.cleanup(); MVenus2.cleanup(); MEarth2.cleanup(); MMars2.cleanup();
        MJupiter2.cleanup(); MSaturn2.cleanup(); MUranus2.cleanup(); MNeptune2.cleanup(); MSaturnRings2.cleanup();
        
        //Scene 1: models clean up
        MSun1.cleanup(); MMercury1.cleanup(); MVenus1.cleanup(); MEarth1.cleanup(); MMars1.cleanup();
        MJupiter1.cleanup(); MSaturn1.cleanup(); MUranus1.cleanup(); MNeptune1.cleanup(); MSaturnRings1.cleanup();
        
        //Background: models clean up
        MSky.cleanup();
        
        //Scenes 1 and 2: destroy
        DSL.cleanup();

        DSLSun2.cleanup();


        P.destroy();
        PSun2.destroy();
        
        //Background: destroy
        DSLSky.cleanup();
        PSky.destroy();
        
        txt.localCleanup();
    }
    
    // Command buffer creation:
    // You send to the GPU all the objects you want to draw with their buffers and textures
    void populateCommandBuffer(VkCommandBuffer commandBuffer, int currentImage) {
        switch(currScene) {
                
          case 0: //Scene 1 + Background
                
                PSky.bind(commandBuffer);
                
                MSky.bind(commandBuffer);
                DSSky.bind(commandBuffer, PSky, currentImage);
                vkCmdDrawIndexed(commandBuffer,
                    static_cast<uint32_t>(MSky.indices.size()), 1, 0, 0, 0);
                
                P.bind(commandBuffer);

                DSSun1.bind(commandBuffer, P, currentImage);
                MSun1.bind(commandBuffer);
                vkCmdDrawIndexed(commandBuffer,
                                    static_cast<uint32_t>(MSun1.indices.size()), 1, 0, 0, 0);
                
                DSMercury1.bind(commandBuffer, P, currentImage);
                MMercury1.bind(commandBuffer);
                vkCmdDrawIndexed(commandBuffer,
                                    static_cast<uint32_t>(MMercury1.indices.size()), 1, 0, 0, 0);
                
                DSVenus1.bind(commandBuffer, P, currentImage);
                MVenus1.bind(commandBuffer);
                vkCmdDrawIndexed(commandBuffer,
                                    static_cast<uint32_t>(MVenus1.indices.size()), 1, 0, 0, 0);
                
                DSEarth1.bind(commandBuffer, P, currentImage);
                MEarth1.bind(commandBuffer);
                vkCmdDrawIndexed(commandBuffer,
                        static_cast<uint32_t>(MEarth1.indices.size()), 1, 0, 0, 0);
                
                DSMars1.bind(commandBuffer, P, currentImage);
                MMars1.bind(commandBuffer);
                vkCmdDrawIndexed(commandBuffer,
                        static_cast<uint32_t>(MMars1.indices.size()), 1, 0, 0, 0);

                DSJupiter1.bind(commandBuffer, P, currentImage);
                MJupiter1.bind(commandBuffer);
                vkCmdDrawIndexed(commandBuffer,
                                    static_cast<uint32_t>(MJupiter1.indices.size()), 1, 0, 0, 0);
                
                DSSaturn1.bind(commandBuffer, P, currentImage);
                MSaturn1.bind(commandBuffer);
                vkCmdDrawIndexed(commandBuffer,
                                    static_cast<uint32_t>(MSaturn1.indices.size()), 1, 0, 0, 0);

                DSUranus1.bind(commandBuffer, P, currentImage);
                MUranus1.bind(commandBuffer);
                vkCmdDrawIndexed(commandBuffer,
                                    static_cast<uint32_t>(MUranus1.indices.size()), 1, 0, 0, 0);

                DSNeptune1.bind(commandBuffer, P, currentImage);
                MNeptune1.bind(commandBuffer);
                vkCmdDrawIndexed(commandBuffer,
                        static_cast<uint32_t>(MNeptune1.indices.size()), 1, 0, 0, 0);
                                
                DSSaturnRings1.bind(commandBuffer, P, currentImage);
                MSaturnRings1.bind(commandBuffer);
                vkCmdDrawIndexed(commandBuffer,
                        static_cast<uint32_t>(MSaturnRings1.indices.size()), 1, 0, 0, 0);
                
            break;
                
          case 1: // Scene 2 + Background
                
                PSky.bind(commandBuffer);
                
                MSky.bind(commandBuffer);
                DSSky.bind(commandBuffer, PSky, currentImage);
                vkCmdDrawIndexed(commandBuffer,
                    static_cast<uint32_t>(MSky.indices.size()), 1, 0, 0, 0);
                
                P.bind(commandBuffer);
                PSun2.bind(commandBuffer);

                DSSun2.bind(commandBuffer, PSun2, currentImage);
                MSun2.bind(commandBuffer);
                vkCmdDrawIndexed(commandBuffer,
                                    static_cast<uint32_t>(MSun2.indices.size()), 1, 0, 0, 0);

                DSMercury2.bind(commandBuffer, P, currentImage);
                MMercury2.bind(commandBuffer);
                vkCmdDrawIndexed(commandBuffer,
                                    static_cast<uint32_t>(MMercury2.indices.size()), 1, 0, 0, 0);

                DSVenus2.bind(commandBuffer, P, currentImage);
                MVenus2.bind(commandBuffer);
                vkCmdDrawIndexed(commandBuffer,
                                    static_cast<uint32_t>(MVenus2.indices.size()), 1, 0, 0, 0);

                DSEarth2.bind(commandBuffer, P, currentImage);
                MEarth2.bind(commandBuffer);
                vkCmdDrawIndexed(commandBuffer,
                        static_cast<uint32_t>(MEarth2.indices.size()), 1, 0, 0, 0);

                DSMars2.bind(commandBuffer, P, currentImage);
                MMars2.bind(commandBuffer);
                vkCmdDrawIndexed(commandBuffer,
                        static_cast<uint32_t>(MMars2.indices.size()), 1, 0, 0, 0);

                DSJupiter2.bind(commandBuffer, P, currentImage);
                MJupiter2.bind(commandBuffer);
                vkCmdDrawIndexed(commandBuffer,
                                    static_cast<uint32_t>(MJupiter2.indices.size()), 1, 0, 0, 0);

                DSSaturn2.bind(commandBuffer, P, currentImage);
                MSaturn2.bind(commandBuffer);
                vkCmdDrawIndexed(commandBuffer,
                                    static_cast<uint32_t>(MSaturn2.indices.size()), 1, 0, 0, 0);

                DSUranus2.bind(commandBuffer, P, currentImage);
                MUranus2.bind(commandBuffer);
                vkCmdDrawIndexed(commandBuffer,
                                    static_cast<uint32_t>(MUranus2.indices.size()), 1, 0, 0, 0);

                DSNeptune2.bind(commandBuffer, P, currentImage);
                MNeptune2.bind(commandBuffer);
                vkCmdDrawIndexed(commandBuffer,
                        static_cast<uint32_t>(MNeptune2.indices.size()), 1, 0, 0, 0);
                                
                DSSaturnRings2.bind(commandBuffer, P, currentImage);
                MSaturnRings2.bind(commandBuffer);
                vkCmdDrawIndexed(commandBuffer,
                        static_cast<uint32_t>(MSaturnRings2.indices.size()), 1, 0, 0, 0);
            break;
        }

        txt.populateCommandBuffer(commandBuffer, currentImage, currScene);
    }

  
    void updateUniformBuffer(uint32_t currentImage) {
        static bool debounce = false;
        static int curDebounce = 0;

        if(glfwGetKey(window, GLFW_KEY_SPACE)) {
            if(!debounce) {
                debounce = true;
                curDebounce = GLFW_KEY_SPACE;
                currScene = (currScene+1) % 2;
                std::cout << "Scene : " << currScene << "\n";
                RebuildPipeline();
            }
        } else {
            if((curDebounce == GLFW_KEY_SPACE) && debounce) {
                debounce = false;
                curDebounce = 0;
            }
        }

        static bool showNormal = false;
        static bool showUV = false;
        
        if(glfwGetKey(window, GLFW_KEY_N)) {
            if(!debounce) {
                debounce = true;
                curDebounce = GLFW_KEY_N;
                showNormal = !showNormal;
                showUV = false;
            }
        } else {
            if((curDebounce == GLFW_KEY_N) && debounce) {
                debounce = false;
                curDebounce = 0;
            }
        }

        if(glfwGetKey(window, GLFW_KEY_U)) {
            if(!debounce) {
                debounce = true;
                curDebounce = GLFW_KEY_U;
                showNormal = false;
                showUV = !showUV;
            }
        } else {
            if((curDebounce == GLFW_KEY_U) && debounce) {
                debounce = false;
                curDebounce = 0;
            }
        }

        if(glfwGetKey(window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }

        
        CameraLogic();
        
        GlobalUniformBufferObject gubo{};
        UniformBufferObject ubo{};
        UniformBufferObject uboSun2{}, uboMercury2{}, uboVenus2{}, uboEarth2{}, uboMars2{}, uboJupiter2{}, uboSaturn2{}, uboUranus2{}, uboNeptune2{}, uboSaturnRings2{}, uboSun1{}, uboMercury1{}, uboVenus1{}, uboEarth1{}, uboMars1{}, uboJupiter1{}, uboSaturn1{}, uboUranus1{}, uboNeptune1{}, uboSaturnRings1{};
        SkyUniformBufferObject subo{};
        SkyUniformBufferObject suboSky{};
                    
        // updates global uniforms
        ubo.mMat = glm::mat4(1);
        ubo.mvpMat = ViewPrj;
        ubo.nMat = glm::inverse(glm::transpose(ubo.mMat));
        
        float dang = Pitch + glm::radians(15.0f);

        ubo.mMat = glm::scale(glm::mat4(1), glm::vec3(3));
        ubo.mvpMat = ViewPrj * ubo.mMat;
        ubo.nMat = glm::inverse(glm::transpose(ubo.mMat));

        gubo.selector = glm::vec3(showNormal || showUV ? 0 : 1, showNormal ? 1 : 0, showUV ? 1 : 0);
        gubo.lightDir = glm::normalize(glm::vec3(-1, 0, 0));
        gubo.lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        gubo.eyePos = cameraPos;

        subo.mMat = glm::scale(glm::mat4(50), glm::vec3(50));
        subo.mvpMat = ViewPrj * subo.mMat;
        subo.nMat = glm::inverse(glm::transpose(subo.mMat));
        
        //Positions
        glm::mat4 moveSky = glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, -10.0f, -10.0f));
        
        glm::mat4 moveSun2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 moveMercury2 = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));
        glm::mat4 moveVenus2 = glm::translate(glm::mat4(1.0f), glm::vec3(4.0f, 0.0f, 0.0f));
        glm::mat4 moveEarth2 = glm::translate(glm::mat4(1.0f), glm::vec3(6.0f, 0.0f, 0.0f));
        glm::mat4 moveMars2 = glm::translate(glm::mat4(1.0f), glm::vec3(8.0f, 0.0f, 0.0f));
        glm::mat4 moveJupiter2 = glm::translate(glm::mat4(1.0f), glm::vec3(12.0f, 0.0f, 0.0f));
        glm::mat4 moveSaturn2 = glm::translate(glm::mat4(1.0f), glm::vec3(12.0f, 0.0f, 0.0f));
        glm::mat4 moveUranus2 = glm::translate(glm::mat4(1.0f), glm::vec3(22.0f, 0.0f, 0.0f));
        glm::mat4 moveNeptune2 = glm::translate(glm::mat4(1.0f), glm::vec3(29.0f, 0.0f, 0.0f));
        glm::mat4 moveSaturnRings2 = glm::translate(glm::mat4(1.0f), glm::vec3(12.0f, 0.0f, 0.0f));
        
        glm::mat4 moveSun1 = glm::translate(glm::mat4(1.0f), glm::vec3(-11.0f, 0.0f, 0.0f));
        glm::mat4 moveMercury1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 moveVenus1 = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 moveEarth1 = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));
        glm::mat4 moveMars1 = glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 0.0f, 0.0f));
        glm::mat4 moveJupiter1 = glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 0.0f, 0.0f));
        glm::mat4 moveSaturn1 = glm::translate(glm::mat4(1.0f), glm::vec3(8.5f, 0.0f, 0.0f));
        glm::mat4 moveUranus1 = glm::translate(glm::mat4(1.0f), glm::vec3(11.5f, 0.0f, 0.0f));
        glm::mat4 moveNeptune1 = glm::translate(glm::mat4(1.0f), glm::vec3(13.0f, 0.0f, 0.0f));
        glm::mat4 moveSaturnRings1 = glm::translate(glm::mat4(1.0f), glm::vec3(8.5f, 0.0f, 0.0f));

        //Scales
        glm::mat4 scaleSky = glm::mat4(100.0f);
        
        glm::mat4 scaleSun2 = glm::scale(glm::mat4(1.0f), glm::vec3(MSun2.getScale()));
        glm::mat4 scaleMercury2 = glm::scale(glm::mat4(1.0f), glm::vec3(MMercury2.getScale()));
        glm::mat4 scaleVenus2 = glm::scale(glm::mat4(1.0f), glm::vec3(MVenus2.getScale()));
        glm::mat4 scaleEarth2 = glm::scale(glm::mat4(1.0f), glm::vec3(MEarth2.getScale()));
        glm::mat4 scaleMars2 = glm::scale(glm::mat4(1.0f), glm::vec3(MMars2.getScale()));
        glm::mat4 scaleJupiter2 = glm::scale(glm::mat4(1.0f), glm::vec3(MJupiter2.getScale()));
        glm::mat4 scaleSaturn2 = glm::scale(glm::mat4(1.0f), glm::vec3(MSaturn2.getScale()));
        glm::mat4 scaleUranus2 = glm::scale(glm::mat4(1.0f), glm::vec3(MUranus2.getScale()));
        glm::mat4 scaleNeptune2 = glm::scale(glm::mat4(1.0f), glm::vec3(MNeptune2.getScale()));
        glm::mat4 scaleSaturnRings2 = glm::scale(glm::mat4(1.0f), glm::vec3(MSaturnRings2.getScale()));

        glm::mat4 scaleSun1 = glm::scale(glm::mat4(1.0f), glm::vec3(MSun1.getScale()));
        glm::mat4 scaleMercury1 = glm::scale(glm::mat4(1.0f), glm::vec3(MMercury1.getScale()));
        glm::mat4 scaleVenus1 = glm::scale(glm::mat4(1.0f), glm::vec3(MVenus1.getScale()));
        glm::mat4 scaleEarth1 = glm::scale(glm::mat4(1.0f), glm::vec3(MEarth1.getScale()));
        glm::mat4 scaleMars1 = glm::scale(glm::mat4(1.0f), glm::vec3(MMars1.getScale()));
        glm::mat4 scaleJupiter1 = glm::scale(glm::mat4(1.0f), glm::vec3(MJupiter1.getScale()));
        glm::mat4 scaleSaturn1 = glm::scale(glm::mat4(1.0f), glm::vec3(MSaturn1.getScale()));
        glm::mat4 scaleUranus1 = glm::scale(glm::mat4(1.0f), glm::vec3(MUranus1.getScale()));
        glm::mat4 scaleNeptune1 = glm::scale(glm::mat4(1.0f), glm::vec3(MNeptune1.getScale()));
        glm::mat4 scaleSaturnRings1 = glm::scale(glm::mat4(1.0f), glm::vec3(MSaturnRings1.getScale()));
        
        //Update spin
        currSpinAngSun += MSun1.getRotationSpeed();
        currSpinAngMercury += MMercury1.getRotationSpeed();
        currSpinAngVenus += MVenus1.getRotationSpeed();
        currSpinAngEarth += MEarth1.getRotationSpeed();
        currSpinAngMars += MMars1.getRotationSpeed();
        currSpinAngJupiter += MJupiter1.getRotationSpeed();
        currSpinAngSaturn += MSaturn1.getRotationSpeed();
        currSpinAngUranus += MUranus1.getRotationSpeed();
        currSpinAngNeptune += MNeptune1.getRotationSpeed();
        currSpinAngSaturnRings += MSaturnRings1.getRotationSpeed();

        //Update orbits
        orbitAngleMercury += MMercury2.getOrbitSpeed();
        orbitAngleVenus += MVenus2.getOrbitSpeed();
        orbitAngleEarth += MEarth2.getOrbitSpeed();
        orbitAngleMars += MMars2.getOrbitSpeed();
        orbitAngleJupiter += MJupiter2.getOrbitSpeed();
        orbitAngleSaturn += MSaturn2.getOrbitSpeed();
        orbitAngleUranus += MUranus2.getOrbitSpeed();
        orbitAngleNeptune += MNeptune2.getOrbitSpeed();
        orbitAngleSaturnRings += MSaturnRings2.getOrbitSpeed();

        //Calculate the model matrixes
        glm::mat4 mMatSky = moveSky * scaleSky;
        suboSky.mMat = mMatSky;
        suboSky.mvpMat = ViewPrj * suboSky.mMat;
        suboSky.nMat = glm::inverse(glm::transpose(suboSky.mMat));
        
        //Scene 1
        glm::mat4 mMatSun1 = moveSun1 * scaleSun1 * glm::rotate(glm::mat4(1.0f), currSpinAngSun, glm::vec3(0.0f, 1.0f, 0.0f));
        uboSun1.mMat = mMatSun1;
        uboSun1.mvpMat = ViewPrj * mMatSun1;
        uboSun1.nMat = glm::inverse(glm::transpose(mMatSun1));
        
        glm::mat4 mMatMercury1 = moveMercury1 * scaleMercury1 * glm::rotate(glm::mat4(1.0f), currSpinAngMercury, glm::vec3(0.0f, 1.0f, 0.0f));
        uboMercury1.mMat = mMatMercury1;
        uboMercury1.mvpMat = ViewPrj * mMatMercury1;
        uboMercury1.nMat = glm::inverse(glm::transpose(mMatMercury1));
        
        glm::mat4 mMatVenus1 = moveVenus1 * scaleVenus1 * glm::rotate(glm::mat4(1.0f), currSpinAngVenus, glm::vec3(0.0f, 1.0f, 0.0f));
        uboVenus1.mMat = mMatVenus1;
        uboVenus1.mvpMat = ViewPrj * mMatVenus1;
        uboVenus1.nMat = glm::inverse(glm::transpose(mMatVenus1));
        
        glm::mat4 mMatEarth1 = moveEarth1 * scaleEarth1 * glm::rotate(glm::mat4(1.0f), currSpinAngEarth, glm::vec3(0.0f, 1.0f, 0.0f));
        uboEarth1.mMat = mMatEarth1;
        uboEarth1.mvpMat = ViewPrj * mMatEarth1;
        uboEarth1.nMat = glm::inverse(glm::transpose(mMatEarth1));
        
        glm::mat4 mMatMars1 =  moveMars1 * scaleMars1 * glm::rotate(glm::mat4(1.0f), currSpinAngMars, glm::vec3(0.0f, 1.0f, 0.0f));
        uboMars1.mMat = mMatMars1;
        uboMars1.mvpMat = ViewPrj * mMatMars1;
        uboMars1.nMat = glm::inverse(glm::transpose(mMatMars1));
        
        glm::mat4 mMatJupiter1 = moveJupiter1 * scaleJupiter1 * glm::rotate(glm::mat4(1.0f), currSpinAngJupiter, glm::vec3(0.0f, 1.0f, 0.0f));
        uboJupiter1.mMat = mMatJupiter1;
        uboJupiter1.mvpMat = ViewPrj * mMatJupiter1;
        uboJupiter1.nMat = glm::inverse(glm::transpose(mMatJupiter1));
        
        glm::mat4 mMatSaturn1 = moveSaturn1 * scaleSaturn1 * glm::rotate(glm::mat4(1.0f), currSpinAngSaturn, glm::vec3(0.0f, 1.0f, 0.0f));
        uboSaturn1.mMat = mMatSaturn1;
        uboSaturn1.mvpMat = ViewPrj * mMatSaturn1;
        uboSaturn1.nMat = glm::inverse(glm::transpose(mMatSaturn1));
        
        glm::mat4 mMatUranus1 = moveUranus1  * scaleUranus1 * glm::rotate(glm::mat4(1.0f), currSpinAngUranus, glm::vec3(0.0f, 1.0f, 0.0f));
        uboUranus1.mMat = mMatUranus1;
        uboUranus1.mvpMat = ViewPrj * mMatUranus1;
        uboUranus1.nMat = glm::inverse(glm::transpose(mMatUranus1));
        
        glm::mat4 mMatNeptune1 = moveNeptune1 * scaleNeptune1 * glm::rotate(glm::mat4(1.0f), currSpinAngNeptune, glm::vec3(0.0f, 1.0f, 0.0f));
        uboNeptune1.mMat = mMatNeptune1;
        uboNeptune1.mvpMat = ViewPrj * mMatNeptune1;
        uboNeptune1.nMat = glm::inverse(glm::transpose(mMatNeptune1));
        
        glm::mat4 mMatSaturnRings1 = moveSaturnRings1 * scaleSaturnRings1 * glm::rotate(glm::mat4(1.0f), currSpinAngSaturnRings, glm::vec3(0.0f, 1.0f, 0.0f));
        uboSaturnRings1.mMat = mMatSaturnRings1;
        uboSaturnRings1.mvpMat = ViewPrj * mMatSaturnRings1;
        uboSaturnRings1.nMat = glm::inverse(glm::transpose(mMatSaturnRings1));
        
        //********************************************************************************************//
        
        //Scene 2
        glm::mat4 mMatSun = moveSun2 * scaleSun2 * glm::rotate(glm::mat4(1.0f), currSpinAngSun, glm::vec3(0.0f, 1.0f, 0.0f));
        uboSun2.mMat = mMatSun;
        uboSun2.mvpMat = ViewPrj * mMatSun;
        uboSun2.nMat = glm::inverse(glm::transpose(mMatSun));
        
        
        glm::mat4 orbitTransformMercury = glm::translate(glm::mat4(1.0f), (glm::vec3(0.0f, 0.0f, 0.0f)));
        orbitTransformMercury = glm::rotate(orbitTransformMercury, orbitAngleMercury, glm::vec3(0.0f, 1.0f, 0.0f));
        orbitTransformMercury = glm::translate(orbitTransformMercury, glm::vec3(MMercury2.getOrbitRadius(), 0.0f, 0.0f));

        glm::mat4 mMatMercury = moveMercury2 * scaleMercury2 * orbitTransformMercury * glm::rotate(glm::mat4(1.0f), currSpinAngMercury, glm::vec3(0.0f, 1.0f, 0.0f));
        uboMercury2.mMat = mMatMercury;
        uboMercury2.mvpMat = ViewPrj * mMatMercury;
        uboMercury2.nMat = glm::inverse(glm::transpose(mMatMercury));

        
        glm::mat4 orbitTransformVenus = glm::translate(glm::mat4(1.0f), (glm::vec3(0.0f, 0.0f, 0.0f)));
        orbitTransformVenus = glm::rotate(orbitTransformVenus, orbitAngleVenus, glm::vec3(0.0f, 1.0f, 0.0f));
        orbitTransformVenus = glm::translate(orbitTransformVenus, glm::vec3(MVenus2.getOrbitRadius(), 0.0f, 0.0f));
        
        glm::mat4 mMatVenus = moveVenus2 * scaleVenus2 * orbitTransformVenus * glm::rotate(glm::mat4(1.0f), currSpinAngVenus, glm::vec3(0.0f, 1.0f, 0.0f));
        uboVenus2.mMat = mMatVenus;
        uboVenus2.mvpMat = ViewPrj * mMatVenus;
        uboVenus2.nMat = glm::inverse(glm::transpose(mMatVenus));

        
        glm::mat4 orbitTransformEarth = glm::translate(glm::mat4(1.0f), (glm::vec3(0.0f, 0.0f, 0.0f)));
        orbitTransformEarth = glm::rotate(orbitTransformEarth, orbitAngleEarth, glm::vec3(0.0f, 1.0f, 0.0f));
        orbitTransformEarth = glm::translate(orbitTransformEarth, glm::vec3(MEarth2.getOrbitRadius(), 0.0f, 0.0f));
        
        glm::mat4 mMatEarth = moveEarth2 * scaleEarth2 * orbitTransformEarth * glm::rotate(glm::mat4(1.0f), currSpinAngEarth, glm::vec3(0.0f, 1.0f, 0.0f));
        uboEarth2.mMat = mMatEarth;
        uboEarth2.mvpMat = ViewPrj * mMatEarth;
        uboEarth2.nMat = glm::inverse(glm::transpose(mMatEarth));

        
        glm::mat4 orbitTransformMars = glm::translate(glm::mat4(1.0f), (glm::vec3(0.0f, 0.0f, 0.0f)));
        orbitTransformMars = glm::rotate(orbitTransformMars, orbitAngleMars, glm::vec3(0.0f, 1.0f, 0.0f));
        orbitTransformMars = glm::translate(orbitTransformMars, glm::vec3(MMars2.getOrbitRadius(), 0.0f, 0.0f));
        
        glm::mat4 mMatMars =  moveMars2 * scaleMars2 * orbitTransformMars * glm::rotate(glm::mat4(1.0f), currSpinAngMars, glm::vec3(0.0f, 1.0f, 0.0f));
        uboMars2.mMat = mMatMars;
        uboMars2.mvpMat = ViewPrj * mMatMars;
        uboMars2.nMat = glm::inverse(glm::transpose(mMatMars));

        
        glm::mat4 orbitTransformJupiter = glm::translate(glm::mat4(1.0f), (glm::vec3(0.0f, 0.0f, 0.0f)));
        orbitTransformJupiter = glm::rotate(orbitTransformJupiter, orbitAngleJupiter, glm::vec3(0.0f, 1.0f, 0.0f));
        orbitTransformJupiter = glm::translate(orbitTransformJupiter, glm::vec3(MJupiter2.getOrbitRadius(), 0.0f, 0.0f));
        
        glm::mat4 mMatJupiter = moveJupiter2 * scaleJupiter2 * orbitTransformJupiter * glm::rotate(glm::mat4(1.0f), currSpinAngJupiter, glm::vec3(0.0f, 1.0f, 0.0f));
        uboJupiter2.mMat = mMatJupiter;
        uboJupiter2.mvpMat = ViewPrj * mMatJupiter;
        uboJupiter2.nMat = glm::inverse(glm::transpose(mMatJupiter));

        
        glm::mat4 orbitTransformSaturn = glm::translate(glm::mat4(1.0f), (glm::vec3(0.0f, 0.0f, 0.0f)));
        orbitTransformSaturn = glm::rotate(orbitTransformSaturn, orbitAngleSaturn, glm::vec3(0.0f, 1.0f, 0.0f));
        orbitTransformSaturn = glm::translate(orbitTransformSaturn, glm::vec3(MSaturn2.getOrbitRadius(), 0.0f, 0.0f));
        
        glm::mat4 mMatSaturn = moveSaturn2 * scaleSaturn2 * orbitTransformSaturn * glm::rotate(glm::mat4(1.0f), currSpinAngSaturn, glm::vec3(0.0f, 1.0f, 0.0f));
        uboSaturn2.mMat = mMatSaturn;
        uboSaturn2.mvpMat = ViewPrj * mMatSaturn;
        uboSaturn2.nMat = glm::inverse(glm::transpose(mMatSaturn));

        
        glm::mat4 orbitTransformUranus = glm::translate(glm::mat4(1.0f), (glm::vec3(0.0f, 0.0f, 0.0f)));
        orbitTransformUranus = glm::rotate(orbitTransformUranus, orbitAngleUranus, glm::vec3(0.0f, 1.0f, 0.0f));
        orbitTransformUranus = glm::translate(orbitTransformUranus, glm::vec3(MUranus2.getOrbitRadius(), 0.0f, 0.0f));
        
        glm::mat4 mMatUranus = moveUranus2  * scaleUranus2 * orbitTransformUranus * glm::rotate(glm::mat4(1.0f), currSpinAngUranus, glm::vec3(0.0f, 1.0f, 0.0f));
        uboUranus2.mMat = mMatUranus;
        uboUranus2.mvpMat = ViewPrj * mMatUranus;
        uboUranus2.nMat = glm::inverse(glm::transpose(mMatUranus));

        
        glm::mat4 orbitTransformNeptune = glm::translate(glm::mat4(1.0f), (glm::vec3(0.0f, 0.0f, 0.0f)));
        orbitTransformNeptune = glm::rotate(orbitTransformNeptune, orbitAngleNeptune, glm::vec3(0.0f, 1.0f, 0.0f));
        orbitTransformNeptune = glm::translate(orbitTransformNeptune, glm::vec3(MNeptune2.getOrbitRadius(), 0.0f, 0.0f));
        
        glm::mat4 mMatNeptune = moveNeptune2 * scaleNeptune2 * orbitTransformNeptune * glm::rotate(glm::mat4(1.0f), currSpinAngNeptune, glm::vec3(0.0f, 1.0f, 0.0f));
        uboNeptune2.mMat = mMatNeptune;
        uboNeptune2.mvpMat = ViewPrj * mMatNeptune;
        uboNeptune2.nMat = glm::inverse(glm::transpose(mMatNeptune));

        
        glm::mat4 orbitTransformSaturnRings = glm::translate(glm::mat4(1.0f), (glm::vec3(0.0f, 0.0f, 0.0f)));
        orbitTransformSaturnRings = glm::rotate(orbitTransformSaturnRings, orbitAngleSaturnRings, glm::vec3(0.0f, 1.0f, 0.0f));
        orbitTransformSaturnRings = glm::translate(orbitTransformSaturnRings, glm::vec3(MSaturnRings2.getOrbitRadius(), 0.0f, 0.0f));
        
        glm::mat4 mMatSaturnRings = moveSaturnRings2 * scaleSaturnRings2 * orbitTransformSaturnRings * glm::rotate(glm::mat4(1.0f), currSpinAngSaturnRings, glm::vec3(0.0f, 1.0f, 0.0f));
        uboSaturnRings2.mMat = mMatSaturnRings;
        uboSaturnRings2.mvpMat = ViewPrj * mMatSaturnRings;
        uboSaturnRings2.nMat = glm::inverse(glm::transpose(mMatSaturnRings));


        // Update the uniform buffer with the modified matrix
        switch(currScene) {
          case 0: //Scene 1 + Background
                
                DSSky.map(currentImage, &subo, sizeof(subo), 0);
                
                DSSun1.map(currentImage, &uboSun1, sizeof(uboSun1), 0);
                DSSun1.map(currentImage, &gubo, sizeof(gubo), 1);
                
                DSMercury1.map(currentImage, &uboMercury1, sizeof(uboMercury1), 0);
                DSMercury1.map(currentImage, &gubo, sizeof(gubo), 1);
                
                DSVenus1.map(currentImage, &uboVenus1, sizeof(uboVenus1), 0);
                DSVenus1.map(currentImage, &gubo, sizeof(gubo), 1);
                
                DSEarth1.map(currentImage, &uboEarth1, sizeof(uboEarth1), 0);
                DSEarth1.map(currentImage, &gubo, sizeof(gubo), 1);
                
                DSMars1.map(currentImage, &uboMars1, sizeof(uboMars1), 0);
                DSMars1.map(currentImage, &gubo, sizeof(gubo), 1);

                DSJupiter1.map(currentImage, &uboJupiter1, sizeof(uboJupiter1), 0);
                DSJupiter1.map(currentImage, &gubo, sizeof(gubo), 1);
                
                DSSaturn1.map(currentImage, &uboSaturn1, sizeof(uboSaturn1), 0);
                DSSaturn1.map(currentImage, &gubo, sizeof(gubo), 1);

                DSUranus1.map(currentImage, &uboUranus1, sizeof(uboUranus1), 0);
                DSUranus1.map(currentImage, &gubo, sizeof(gubo), 1);

                DSNeptune1.map(currentImage, &uboNeptune1, sizeof(uboNeptune1), 0);
                DSNeptune1.map(currentImage, &gubo, sizeof(gubo), 1);
                    
                DSSaturnRings1.map(currentImage, &uboSaturnRings1, sizeof(uboSaturnRings1), 0);
                DSSaturnRings1.map(currentImage, &gubo, sizeof(gubo), 1);
                
            break;
                
          case 1: //Scene 2 + Background

            DSSky.map(currentImage, &subo, sizeof(subo), 0);
                
            DSSun2.map(currentImage, &uboSun2, sizeof(uboSun2), 0);
            DSSun2.map(currentImage, &gubo, sizeof(gubo), 1);

            DSMercury2.map(currentImage, &uboMercury2, sizeof(uboMercury2), 0);
            DSMercury2.map(currentImage, &gubo, sizeof(gubo), 1);
            
            DSVenus2.map(currentImage, &uboVenus2, sizeof(uboVenus2), 0);
            DSVenus2.map(currentImage, &gubo, sizeof(gubo), 1);

            DSEarth2.map(currentImage, &uboEarth2, sizeof(uboEarth2), 0);
            DSEarth2.map(currentImage, &gubo, sizeof(gubo), 1);

            DSMars2.map(currentImage, &uboMars2, sizeof(uboMars2), 0);
            DSMars2.map(currentImage, &gubo, sizeof(gubo), 1);

            DSJupiter2.map(currentImage, &uboJupiter2, sizeof(uboJupiter2), 0);
            DSJupiter2.map(currentImage, &gubo, sizeof(gubo), 1);
            
            DSSaturn2.map(currentImage, &uboSaturn2, sizeof(uboSaturn2), 0);
            DSSaturn2.map(currentImage, &gubo, sizeof(gubo), 1);

            DSUranus2.map(currentImage, &uboUranus2, sizeof(uboUranus2), 0);
            DSUranus2.map(currentImage, &gubo, sizeof(gubo), 1);

            DSNeptune2.map(currentImage, &uboNeptune2, sizeof(uboNeptune2), 0);
            DSNeptune2.map(currentImage, &gubo, sizeof(gubo), 1);
                
            DSSaturnRings2.map(currentImage, &uboSaturnRings2, sizeof(uboSaturnRings2), 0);
            DSSaturnRings2.map(currentImage, &gubo, sizeof(gubo), 1);

            break;
        }
    }
    
    void CameraLogic() {
        
        if (currScene == 0) {
            // Camera FOV-y, Near Plane and Far Plane
            const float FOVy = glm::radians(45.0f);
            const float nearPlane = 1.0f;
            const float farPlane = 100.f;
            
            // Camera target height and distance
            const float camHeight = 1;
            const float camDist = 10;
            
            // Camera Pitch limits
            const float minPitch = glm::radians(-60.0f);
            const float maxPitch = glm::radians(60.0f);
            
            // Rotation and motion speed
            const float ROT_SPEED = glm::radians(120.0f);
            const float MOVE_SPEED = 3.0f;
            
            // Integration with the timers and the controllers
            float deltaT;
            glm::vec3 m = glm::vec3(0.0f), r = glm::vec3(0.0f);
            bool fire = false;
            getSixAxis(deltaT, m, r, fire);
            
            ViewPrj = glm::mat4(1);
            glm::mat4 World = glm::mat4(1);
            
            // World
            // Position
            glm::vec3 ux = glm::rotate(glm::mat4(1.0f), Yaw, glm::vec3(0,1,0)) * glm::vec4(1,0,0,1);
            glm::vec3 uz = glm::rotate(glm::mat4(1.0f), Yaw, glm::vec3(0,1,0)) * glm::vec4(0,0,-1,1);
            Pos = Pos + MOVE_SPEED * m.x * ux * deltaT;
            Pos = Pos + MOVE_SPEED * m.y * glm::vec3(0,1,0) * deltaT;
            Pos.y = Pos.y < 0.0f ? 0.0f : Pos.y;
            Pos = Pos + MOVE_SPEED * m.z * uz * deltaT;
            
            // Rotation
            Yaw = Yaw - ROT_SPEED * deltaT * r.y;
            Pitch = Pitch + ROT_SPEED * deltaT * r.x;
            Pitch  =  Pitch < minPitch ? minPitch :
            (Pitch > maxPitch ? maxPitch : Pitch);
            Roll   = Roll   - ROT_SPEED * deltaT * r.z;
            Roll   = Roll < glm::radians(-175.0f) ? glm::radians(-175.0f) :
            (Roll > glm::radians( 175.0f) ? glm::radians( 175.0f) : Roll);
            
            // Final world matrix computation
            World = glm::translate(glm::mat4(1), Pos) * glm::rotate(glm::mat4(1.0f), Yaw, glm::vec3(0,1,0));
            
            // Projection
            glm::mat4 Prj = glm::perspective(FOVy, Ar, nearPlane, farPlane);
            Prj[1][1] *= -1;
            
            // View
            // Target
            glm::vec3 target = Pos + glm::vec3(0.0f, camHeight, 0.0f);
            
            // Camera position, depending on Yaw parameter, but not character direction
            cameraPos = World * glm::vec4(0.0f, camHeight + camDist * sin(Pitch), camDist * cos(Pitch), 1.0);
            
            // Damping of camera
            glm::mat4 View = glm::rotate(glm::mat4(1.0f), -Roll, glm::vec3(0,0,1)) *
            glm::lookAt(cameraPos, target, glm::vec3(0,1,0));
            
            ViewPrj = Prj * View;
        }
        
        if (currScene == 1) {
            // Camera FOV-y, Near Plane and Far Plane
            const float FOVy = glm::radians(90.0f);
            const float nearPlane = 1.0f;
            const float farPlane = 300.f;
            
            // Camera target height and distance
            const float camHeight = 10;
            const float camDist = 10;
            
            // Camera Pitch limits
            const float minPitch = glm::radians(-50.0f);
            const float maxPitch = glm::radians(50.0f);
            
            // Rotation and motion speed
            const float ROT_SPEED = glm::radians(120.0f);
            const float MOVE_SPEED = 3.0f;
            
            // Integration with the timers and the controllers
            float deltaT;
            glm::vec3 m = glm::vec3(0.0f), r = glm::vec3(0.0f);
            bool fire = false;
            getSixAxis(deltaT, m, r, fire);
            
            ViewPrj = glm::mat4(1);
            glm::mat4 World = glm::mat4(1);
            
            // World
            // Position
            glm::vec3 ux = glm::rotate(glm::mat4(1.0f), Yaw2, glm::vec3(0,1,0)) * glm::vec4(1,0,0,1);
            glm::vec3 uz = glm::rotate(glm::mat4(1.0f), Yaw2, glm::vec3(0,1,0)) * glm::vec4(0,0,-1,1);
            Pos2 = Pos2 + MOVE_SPEED * m.x * ux * deltaT;
            Pos2 = Pos2 + MOVE_SPEED * m.y * glm::vec3(0,1,0) * deltaT;
            Pos2.y = Pos2.y < 0.0f ? 0.0f : Pos2.y;
            Pos2 = Pos2 + MOVE_SPEED * m.z * uz * deltaT;
            
            // Rotation
            Yaw2 = Yaw2 - ROT_SPEED * deltaT * r.y;
            Pitch2 = Pitch2 + ROT_SPEED * deltaT * r.x;
            Pitch2  =  Pitch2 < minPitch ? minPitch :
            (Pitch2 > maxPitch ? maxPitch : Pitch2);
            Roll2   = Roll2   - ROT_SPEED * deltaT * r.z;
            Roll2   = Roll2 < glm::radians(-175.0f) ? glm::radians(-175.0f) :
            (Roll2 > glm::radians( 175.0f) ? glm::radians( 175.0f) : Roll2);
            
            // Final world matrix computation
            World = glm::translate(glm::mat4(1), Pos2) * glm::rotate(glm::mat4(1.0f), Yaw2, glm::vec3(0,1,0));
            
            // Projection
            glm::mat4 Prj = glm::perspective(FOVy, Ar, nearPlane, farPlane);
            Prj[1][1] *= -1;
            
            // View
            // Target
            glm::vec3 target = Pos2 + glm::vec3(0.0f, camHeight, 0.0f);
            
            // Camera position, depending on Yaw parameter, but not character direction
            cameraPos2 = World * glm::vec4(0.0f, camHeight + camDist * sin(Pitch2), camDist * cos(Pitch2), 1.0);
            
            // Damping of camera
            glm::mat4 View = glm::rotate(glm::mat4(1.0f), -Roll2, glm::vec3(0,0,1)) *
            glm::lookAt(cameraPos2, target, glm::vec3(0,1,0));
            
            ViewPrj = Prj * View;
        }
    }
    

    void createRingMesh(std::vector<Vertex> &vDef, std::vector<uint32_t> &vIdx) {
        const int numSegments = 30;
        const int radius = 1;
        
        // Center vertex
        vDef.push_back({{0.0f, 0.0f, 0.0f}, glm::vec3(0.0f, 0.0f, 1.0f), {0.5f, 0.5f}});

        for (int i = 0; i <= numSegments; ++i) {
            float angle = (2.0f * glm::pi<float>() * i) / numSegments;
            float x = radius * cos(angle);
    //        float y = radius * sin(angle);
            float z = radius * sin(angle);


    //        vDef.push_back({{x, y, 0.0f}, glm::vec3(0.0f, 0.0f, 1.0f), {0.5f + 0.5f * cos(angle), 0.5f + 0.5f * sin(angle)}});
            vDef.push_back({{x, 0.0f, z}, glm::vec3(0.0f, 1.0f, 0.0f), {0.5f + 0.5f * cos(angle), 0.5f + 0.5f * sin(angle)}});
        }

        for (int i = 0; i < numSegments; ++i) {
            // Create two triangles for each segment
            vIdx.push_back(0);  // Center vertex
            vIdx.push_back(i + 1);
            vIdx.push_back(i + 2);
        }
    }
    
    //void createBoxMesh(std::vector<Vertex> &vDef, std::vector<uint32_t> &vIdx);
    //void createParticleMesh(std::vector<Vertex> &vDef, std::vector<uint32_t> &vIdx);
    //void createParticleMesh(std::vector<Vertex>&vDef, std::vector<uint32_t>&vIdx, float radiusX, float radiusY, float radiusZ, int segments = 32);

};


int main() {
    Assignment15 app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
