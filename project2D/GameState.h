#pragma once
class GameState 
{
	friend class GameStateManager;
public: 
	
	GameState() {} 
	virtual ~GameState() {} 

	bool isActive() const; //Returns the bool of m_active

protected: 
	
	virtual void onUpdate(float deltaTime) = 0;
	virtual void onDraw() = 0;

	void enter(); //Sets m_active to true, then calls onEnter()
	void exit();  //Sets m_active to false, then calls onExit()

	virtual void onEnter() {} 
	virtual void onExit() {} 
	virtual void onPushed() {}
	virtual void onPopped() {}

private: 
	bool m_active = false; 
};