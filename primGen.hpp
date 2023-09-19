#define M_PI 3.141595f

void Assignment15::createBoxMesh(std::vector<Vertex> &vDef, std::vector<uint32_t> &vIdx) {
	// The primitive built here is a box centered in the origin, with proportions respecting the texture.

	// The procedure fills array vPos with the positions of the vertices and of the normal vectors of the mesh
	//vDef.push_back({{0,0,0}, {0,0,1}, {0.09,-0.18}});	// vertex 0 - Position, Normal and uv

    /// ******************Coordinates in Texture Plane ****************** ///
    float y0 = -0.18f; float y1 = -0.815f;
    float x0 = 0.092f; float x1 = 0.434f; float x2 = 0.525f; float x3 = 0.87f;

    /// ********************** Coordinates in 3D Space **********************///
    float scale = 1.5f;
    float Y = scale*1.5 * (y1-y0) * -1; 
    float Z = scale*3.5 * (x1-x0) * -1;
    float X = scale*3.5 * (x0); 

    /// ******************Define Vertices and Triangles ******************** ///

    // Top
	vDef.push_back({{0,Y,0}, {0,1,0}, {x0,-1}});	
	vDef.push_back({{0,Y,Z}, {0,1,0}, {x1,-1}});	
	vDef.push_back({{X,Y,0}, {0,1,0}, {x0,y1}});	
	vDef.push_back({{X,Y,Z}, {0,1,0}, {x1,y1}});

	vIdx.push_back(0); vIdx.push_back(1); vIdx.push_back(2);	
	vIdx.push_back(1); vIdx.push_back(2); vIdx.push_back(3);	

    // Front
	vDef.push_back({{0,Y,0}, {0,0,1}, {0,y1}});	
	vDef.push_back({{X,Y,0}, {0,0,1}, {x0,y1}});
	vDef.push_back({{0,0,0}, {0,0,1}, {0,y0}});	
	vDef.push_back({{X,0,0}, {0,0,1}, {x0,y0}});

	vIdx.push_back(4); vIdx.push_back(5); vIdx.push_back(6);
	vIdx.push_back(5); vIdx.push_back(6); vIdx.push_back(7);

    // Side face
	vDef.push_back({{X,Y,0}, {1,0,0}, {x0,y1}});
	vDef.push_back({{X,Y,Z}, {1,0,0}, {x1,y1}});
	vDef.push_back({{X,0,0}, {1,0,0}, {x0,y0}});
	vDef.push_back({{X,0,Z}, {1,0,0}, {x1,y0}});

	vIdx.push_back(8); vIdx.push_back(9); vIdx.push_back(10);
	vIdx.push_back(9); vIdx.push_back(10); vIdx.push_back(11);

    // Back Edge
	vDef.push_back({{X,Y,Z}, {0,0,-1}, {x1,y1}});
	vDef.push_back({{0,Y,Z}, {0,0,-1}, {x2,y1}});
	vDef.push_back({{X,0,Z}, {0,0,-1}, {x1,y0}});
	vDef.push_back({{0,0,Z}, {0,0,-1}, {x2,y0}});

	
	vIdx.push_back(12); vIdx.push_back(13); vIdx.push_back(14);
	vIdx.push_back(13); vIdx.push_back(14); vIdx.push_back(15);

    // Back Face
	vDef.push_back({{0,Y,Z}, {-1,0,0}, {x2,y1}});
	vDef.push_back({{0,Y,0}, {-1,0,0}, {x3,y1}});
	vDef.push_back({{0,0,Z}, {-1,0,0}, {x2,y0}});
	vDef.push_back({{0,0,0}, {-1,0,0}, {x3,y0}});

	vIdx.push_back(16); vIdx.push_back(17); vIdx.push_back(18);	
	vIdx.push_back(17); vIdx.push_back(18); vIdx.push_back(19);	

    // Bottom edge
	vDef.push_back({{X,0,0}, {0,-1,0}, {x0,y0}});
	vDef.push_back({{X,0,Z}, {0,-1,0}, {x1,y0}});
	vDef.push_back({{0,0,0}, {0,-1,0}, {x0,0}});
	vDef.push_back({{0,0,Z}, {0,-1,0}, {x1,0}});
	
	vIdx.push_back(20); vIdx.push_back(21); vIdx.push_back(22);
	vIdx.push_back(21); vIdx.push_back(22); vIdx.push_back(23);

}

void Assignment15::createSphereMesh(std::vector<Vertex> &vDef, std::vector<uint32_t> &vIdx) {

    const int verticalSegments = 12;
    const int horizontalSegments = 24;

    for (int i = 0; i <= verticalSegments; ++i) {
        float v = (1.0f * i) / verticalSegments; // Vertical texture coordinate

        for (int j = 0; j <= horizontalSegments; ++j) {
            float u = (1.0f * j) / horizontalSegments; // Horizontal texture coordinate

            float theta = u * 2.0f * glm::pi<float>();
            float phi = v * M_PI;

            float x = cos(theta) * sin(phi);
            float y = cos(phi);
            float z = sin(theta) * sin(phi);
            

            vDef.push_back({{x, y, z}, glm::normalize(glm::vec3(x, y, z)), {u, v}});
        }
    }

    for (int i = 0; i < verticalSegments; ++i) {
        for (int j = 0; j < horizontalSegments; ++j) {
            int index0 = i * (horizontalSegments + 1) + j;
            int index1 = index0 + 1;
            int index2 = (i + 1) * (horizontalSegments + 1) + j;
            int index3 = index2 + 1;

            // Create two triangles for each quad
            vIdx.push_back(index0);
            vIdx.push_back(index1);
            vIdx.push_back(index2);

            vIdx.push_back(index2);
            vIdx.push_back(index1);
            vIdx.push_back(index3);
        }
    }


}

void Assignment15::createParticleMesh(std::vector<Vertex>&vDef, std::vector<uint32_t>&vIdx, float radiusX, float radiusY, float radiusZ, int segments = 32) {

    // Create vertices
    for (int i = 0; i <= segments; ++i) {
        float theta = static_cast<float>(i) * glm::two_pi<float>() / static_cast<float>(segments);
        for (int j = 0; j <= segments; ++j) {
            float phi = static_cast<float>(j) * glm::pi<float>() / static_cast<float>(segments);

            Vertex vertex;
            vertex.pos.x = radiusX * sin(phi) * cos(theta);
            vertex.pos.y = radiusY * sin(phi) * sin(theta);
            vertex.pos.z = radiusZ * cos(phi);
            vertex.norm = glm::normalize(vertex.pos);
            vertex.UV = glm::vec2(static_cast<float>(i) / static_cast<float>(segments), static_cast<float>(j) / static_cast<float>(segments));

            vDef.push_back(vertex);
        }
    }

    // Create indices
    for (int i = 0; i < segments; ++i) {
        for (int j = 0; j < segments; ++j) {
            uint32_t topLeft = i * (segments + 1) + j;
            uint32_t topRight = topLeft + 1;
            uint32_t bottomLeft = (i + 1) * (segments + 1) + j;
            uint32_t bottomRight = bottomLeft + 1;

            // Triangle 1
            vIdx.push_back(topLeft);
            vIdx.push_back(bottomLeft);
            vIdx.push_back(topRight);

            // Triangle 2
            vIdx.push_back(topRight);
            vIdx.push_back(bottomLeft);
            vIdx.push_back(bottomRight);
        }
    }
}

void Assignment15::createRingMesh(std::vector<Vertex> &vDef, std::vector<uint32_t> &vIdx) { 
    
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



