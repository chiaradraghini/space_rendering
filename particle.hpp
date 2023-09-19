template <typename VertexType>
class ParticleModel : public Model<VertexType> {
public:
    ParticleModel(float scale)
        : Model<VertexType>(),
          /*rotation(rotation),*/
          scale(scale) {}


    // Setters and Getters for Scale
    void setScale(float newScale) { scale = newScale; }
    float getScale() const { return scale; }

    bool isValid() {
        return (this->vertexBuffer != VK_NULL_HANDLE) && (this->indexBuffer != VK_NULL_HANDLE);
    }
private:
    /*glm::vec3 position; // Position in 3D space*/
    /*glm::vec3 rotation; // Rotation angles (e.g., pitch, yaw, roll)*/
    float scale;        // Scale factor
};
