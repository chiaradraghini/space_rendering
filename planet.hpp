template <typename VertexType>
class PlanetModel : public Model<VertexType> {
public:
    PlanetModel(float iscale, float irotationSpeed, float iorbitSpeed, const std::string& iname, float itilt, float iorbitRadius)
        : Model<VertexType>(),
          scale(iscale),
          rotationSpeed(irotationSpeed),
          orbitSpeed(iorbitSpeed),
          name(iname),
          axialTilt(itilt),
          orbitRadius(iorbitRadius)
    {
    }

    // Getter and setter methods for scale, rotation speed, and orbit speed
    float getScale() const { return scale; }
    void setScale(float newScale) { scale = newScale; }

    float getRotationSpeed() const { return rotationSpeed; }
    void setRotationSpeed(float speed) { rotationSpeed = speed; }

    float getOrbitSpeed() const { return orbitSpeed; }
    void setOrbitSpeed(float speed) { orbitSpeed = speed; }
    
    const std::string& getPlanetName() const { return name; }
    void setPlanetName(const std::string& planetName) { name = planetName; }
    
    float  getTilt() const { return axialTilt; }
    void setTilt(float tilt) { axialTilt = tilt; }
    
    float getOrbitRadius() const { return orbitRadius; }
    void setOrbitRadius(float radius) { orbitRadius = radius; }


private:
    float scale;
    float rotationSpeed;
    float orbitSpeed;
    std::string name;  
    float axialTilt;
    float orbitRadius;

};
