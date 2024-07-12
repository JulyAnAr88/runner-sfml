#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class EntityManager;

enum class EntityType{ Base, Enemy, Player };

enum class EntityState{ Idle, Walking, Jumping, Hurt, Dying };

struct TileInfo;

class Entity {
	friend class EntityManager;
protected:
	std::string m_name;
	EntityType m_type;
	unsigned int m_id; // Entity id in the entity manager.
	sf::Vector2f m_position; // Current position.
	sf::Vector2f m_positionOld; // Position before entity moved.
	sf::Vector2f m_velocity; // Current velocity.
	sf::Vector2f m_maxVelocity; // Maximum velocity.
	sf::Vector2f m_speed; // Value of acceleration.
	sf::Vector2f m_acceleration; // Current acceleration.
	sf::Vector2f m_friction; // Default friction value.
	TileInfo* m_referenceTile; // Tile underneath entity.
	sf::Vector2f m_size; // Size of the collision box.
	sf::FloatRect m_hitbox; // The bounding box for collisions.
	EntityState m_state; // Current entity state.

	EntityManager* m_entityManager;
	
public:	
	Entity(EntityManager* l_entityMgr);        			
	virtual ~Entity();
	
	const sf::Vector2f& getPosition() const;
	const sf::Vector2f& getSize()const;
	std::string getName()const;
	unsigned int getId()const;
	EntityState getState()const;
	EntityType getType()const;

	void setPosition(float l_x, float l_y);
	void setPosition(const sf::Vector2f& l_pos);
	void setSize(float l_x, float l_y);
	void setState(const EntityState& l_state);

	void move(float l_x, float l_y);
	void addVelocity(float l_x, float l_y);
	void accelerate(float l_x, float l_y);
	void setAcceleration(float l_x, float l_y);
	void applyFriction(float l_x, float l_y);
	
	sf::FloatRect getGlobalBounds();
	bool collideWith(const Entity & ent2);
	
	void separate(sf::FloatRect overlap, const Entity & ent2);
	
	sf::FloatRect checkCollision(Entity &b);
	void updateHitbox();

	virtual void onEntityCollision(Entity* l_collider, bool l_attack) = 0;
	virtual void draw(sf::RenderWindow* l_wind) = 0;   
	virtual void update(float l_dT);
	
};

#endif

