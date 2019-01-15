#pragma once

class Guesser
{
protected:
	int m_guessAttempts = 0;
public:
	Guesser();
	~Guesser();
	
	int getGuessAttempts() { return m_guessAttempts; }
	void incrementGuessAttempts() { ++m_guessAttempts; }
	void resetGuessAttempts() { m_guessAttempts = 0; }

	virtual int guess();	//Why can't I abstract this? *****
	//virtual int guess(const int & CPUSkillLevel, const Range & range);
};

