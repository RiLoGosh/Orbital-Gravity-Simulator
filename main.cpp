#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

 

class GravitySource{
    
    sf::Vector2f position;
    float strength;
    sf::CircleShape shape;
    
public:
    GravitySource(sf::Vector2f pos, float gravityStrength, float radius){
        position = pos;
        this->strength = gravityStrength;
        
        shape.setPosition(position);
        shape.setFillColor(sf::Color::Yellow);
        shape.setRadius(radius);
    }
    
    void render(sf::RenderWindow& window){
        window.draw(shape);
    }
    
    sf::Vector2f getPosition(){
        return position;
    }
    
    float getStrength(){
        return strength;
    }
    
    sf::CircleShape getShape(){
        return shape;
    }
    
};

class OrbitingGravitySource{
    
    sf::Vector2f velocity;
    sf::Vector2f position;
    float gravityStrength;
    sf::CircleShape shape;
    
public:
    OrbitingGravitySource(sf::Vector2f initialPosition, sf::Vector2f initialVelocity, float strength, float radius){
        position = initialPosition;
        velocity = initialVelocity;
        this->gravityStrength = strength;
        
        shape.setPosition(position);
        shape.setFillColor(sf::Color::Blue);
        shape.setRadius(radius);
    }
    
    void update(GravitySource &sun){
        
        //Distance vector
        float distance_x = sun.getPosition().x - position.x;
        float distance_y = sun.getPosition().y - position.y;
 
        float distance = sqrt(distance_x * distance_x + distance_y * distance_y);
 
        //Use inverse for math because more efficient
        float inverseDistance = 1.f / distance;
 
        sf::Vector2f normalised = sf::Vector2f(inverseDistance*distance_x, inverseDistance*distance_y);
 
        // Gravity strength dropoff is inversely proportional to square distance from source
        float dropoff = inverseDistance * inverseDistance;
 
        sf::Vector2f acceleration = sf::Vector2f(normalised.x * sun.getStrength() * dropoff, normalised.y * sun.getStrength() * dropoff);
         
        // Apply acceleration to velocity
        velocity += acceleration;
        
        // Apply velocity to position
        position += velocity;
        
    }
    
    void render(sf::RenderWindow& wind){
        shape.setPosition(position);
        wind.draw(shape);
    }
    
    void setColour(sf::Color colour){
        shape.setFillColor(colour);
    }
    
    float getStrength(){
        return gravityStrength;
    }
    
    sf::Vector2f getPosition(){
        return position;
    }
    
    sf::Vector2f getVelocity(){
        return velocity;
    }
    
    sf::CircleShape getShape(){
        return shape;
    }
    
};

class OrbitingBody{
    
    sf::Vector2f velocity;
    sf::Vector2f position;
    sf::CircleShape shape;
    
public:
    OrbitingBody(sf::Vector2f initialPosition, sf::Vector2f initialVelocity, float radius){
        position = initialPosition;
        velocity = initialVelocity;
        
        shape.setPosition(position);
        shape.setFillColor(sf::Color::Blue);
        shape.setRadius(radius);
    }
    
    void update(GravitySource &planet){
        
        //Distance vector
        float distance_x = planet.getPosition().x - position.x;
        float distance_y = planet.getPosition().y - position.y;
 
        float distance = sqrt(distance_x * distance_x + distance_y * distance_y);
 
        //Use inverse for math because more efficient
        float inverseDistance = 1.f / distance;
 
        sf::Vector2f normalised = sf::Vector2f(inverseDistance*distance_x, inverseDistance*distance_y);
 
        // Gravity strength dropoff is inversely proportional to square distance from source
        float dropoff = inverseDistance * inverseDistance;
 
        sf::Vector2f acceleration = sf::Vector2f(normalised.x * planet.getStrength() * dropoff, normalised.y * planet.getStrength() * dropoff);
         
        // Apply acceleration to velocity
        velocity += acceleration;
        
        // Apply velocity to position
        position += velocity;
        
    }
    
    void update(OrbitingGravitySource &planet){
        
        //Distance vector
        float distance_x = planet.getPosition().x - position.x;
        float distance_y = planet.getPosition().y - position.y;
 
        float distance = sqrt(distance_x * distance_x + distance_y * distance_y);
 
        //Use inverse for math because more efficient
        float inverseDistance = 1.f / distance;
 
        sf::Vector2f normalised = sf::Vector2f(inverseDistance*distance_x, inverseDistance*distance_y);
 
        float normalized_x = inverseDistance * distance_x;
        float normalized_y = inverseDistance * distance_y;
        // Gravity strength dropoff is inversely proportional to square distance from source
        float dropoff = inverseDistance * inverseDistance;
 
        sf::Vector2f acceleration = sf::Vector2f(normalized_x * planet.getStrength() * dropoff, normalized_y * planet.getStrength() * dropoff);
        
        float acceleration_x = normalized_x * planet.getStrength() * dropoff;
        float acceleration_y = normalized_y * planet.getStrength() * dropoff;
         
        // Apply acceleration to velocity
        //velocity += acceleration;
        
        velocity.x += acceleration_x;
        velocity.y += acceleration_y;
        
        // Apply velocity to position
        //position += velocity;
        position.x += velocity.x;
        position.y += velocity.y;
        
    }
    
    void render(sf::RenderWindow& wind){
        shape.setPosition(position);
        wind.draw(shape);
    }
    
    void setColour(sf::Color colour){
        shape.setFillColor(colour);
    }
    
    sf::Vector2f getPosition(){
        return position;
    }
    
    sf::Vector2f getVelocity(){
        return velocity;
    }
    
    sf::CircleShape getShape(){
        return shape;
    }
    
};


int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 1000), "Orbital Gravity Simulation");
    window.setFramerateLimit(60);
 
    std::vector<GravitySource> Suns;
    std::vector<OrbitingGravitySource> SolarSystemPlanets;
    std::vector<OrbitingBody> OrbitingBodies;
    
    Suns.push_back(GravitySource(sf::Vector2f(700, 350), 100, 50));
    
    SolarSystemPlanets.push_back(OrbitingGravitySource(sf::Vector2f(350, 350), sf::Vector2f(0, 0.5), 4.1, 3));
    SolarSystemPlanets.push_back(OrbitingGravitySource(sf::Vector2f(1000, 350), sf::Vector2f(0, -0.5), 4.1, 3));

    //OrbitingBodies.push_back(OrbitingBody(sf::Vector2f(370, 350), sf::Vector2f(0.00, 0.32), 2));
    
    //OrbitingBodies.push_back(OrbitingBody(sf::Vector2f(330, 350), sf::Vector2f(0.00, 0.35), 2));
    int n = 255*6;
    int totalColours = 255*6;
    sf::Color colour = sf::Color(255, 0, 0);
    for (int i = 0; i < n; i++) {
        OrbitingBodies.push_back(OrbitingBody(sf::Vector2f(330, (360 + (0.1 / n) * i)),
                                              sf::Vector2f(0.000, (0.1 / n) * i), 2));
        if (i%totalColours <= 255) {
            colour.b++;
        }
        else if (255 < i%totalColours && i%totalColours <= 510){
            colour.r--;
        }
        else if (255*2 < i%totalColours && i%totalColours <= 255*3){
            colour.g++;
        }
        else if (255*3 < i%totalColours && i%totalColours <= 255*4){
            colour.b--;
        }
        else if (255*4 < i%totalColours && i%totalColours <= 255*5){
            colour.r++;
        }
        else if (255*5 < i%totalColours && i%totalColours <= 255*6){
            colour.g--;
        }
        OrbitingBodies[i].setColour(colour);

    }
    
    for (int i = 0; i < n; i++) {
        OrbitingBodies.push_back(OrbitingBody(sf::Vector2f(1010, (340 - (0.1 / n) * i)),
                                              sf::Vector2f(0.000, -(0.1 / n) * i), 2));
        if (i%totalColours <= 255) {
            colour.b++;
        }
        else if (255 < i%totalColours && i%totalColours <= 510){
            colour.r--;
        }
        else if (255*2 < i%totalColours && i%totalColours <= 255*3){
            colour.g++;
        }
        else if (255*3 < i%totalColours && i%totalColours <= 255*4){
            colour.b--;
        }
        else if (255*4 < i%totalColours && i%totalColours <= 255*5){
            colour.r++;
        }
        else if (255*5 < i%totalColours && i%totalColours <= 255*6){
            colour.g--;
        }
        OrbitingBodies[i+n].setColour(colour);

    }
 
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }
 
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }
 
 
        window.clear();
        for (int k = 0; k < Suns.size(); k++) {
            Suns[k].render(window);
            for (int i = 0; i < SolarSystemPlanets.size()/2; i++) {
                SolarSystemPlanets[i].update(Suns[k]);
                for (int j = 0; j < OrbitingBodies.size()/2; j++){
                    OrbitingBodies[j].update(SolarSystemPlanets[i]);
                    
                }
            }
        }
        for (int k = 0; k < Suns.size(); k++) {
            for (int i = SolarSystemPlanets.size()/2; i < SolarSystemPlanets.size(); i++) {
                SolarSystemPlanets[i].update(Suns[k]);
                for (int j = OrbitingBodies.size()/2; j < OrbitingBodies.size(); j++){
                    OrbitingBodies[j].update(SolarSystemPlanets[i]);
                    
                }
            }
        }
        
        for (int i = 0; i < SolarSystemPlanets.size(); i++){
            SolarSystemPlanets[i].render(window);
        }
        
        for (int j = 0; j < OrbitingBodies.size(); j++){
            OrbitingBodies[j].render(window);
            //OrbitingBodies[j].update(Suns[0]);
            
        }
        
        
        
        window.display();
    }
 
 
 
    return 0;
}
